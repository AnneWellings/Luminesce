// Fill out your copyright notice in the Description page of Project Settings.


#include "Lite.h"

#include "GameFramework/Character.h"
#include "Kismet/GameplayStatics.h"
#include "Luminesce/Halo/HaloInterface.h"
#include "Luminesce/Halo/HaloComponent.h"


// Sets default values
ALite::ALite()
{
	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	USceneComponent* RootSceneComponent = CreateDefaultSubobject<USceneComponent>("Root");
	SetRootComponent(RootSceneComponent);

	LiteMesh = CreateDefaultSubobject<UStaticMeshComponent>("LiteMesh");
	LiteMesh->SetupAttachment(RootComponent);
}

void ALite::OnConstruction(const FTransform& Transform)
{
	Super::OnConstruction(Transform);

	ColorValue = GetColorValue(CurrentLiteColor);
	
	if (UStaticMeshComponent* LiteMeshPtr = LiteMesh.Get())
	{
		if (GlowMatIndex != -1)
		{
			//UMaterialInterface* mat = LoadObject<UMaterialInterface>(nullptr, TEXT("/Game/Materials/Shared/GlowMat_Inst.GlowMat_Inst"));

			if (LiteMaterial != nullptr)
			{
				GlowMat = UMaterialInstanceDynamic::Create(LiteMaterial, LiteMeshPtr);
				UMaterialInstanceDynamic* GlowMatPtr = GlowMat.Get();
				if (GlowMatPtr != nullptr)
				{
					LiteMeshPtr->SetMaterial(GlowMatIndex, GlowMatPtr);

					GlowMatPtr->SetVectorParameterValue("Color", ColorValue);
					//LiteNC->SetAutoActivate(true);
					//LiteNC->SetColorParameter(FName("Color"), ColorValue);
				}
			}
		}
	}

	if (bIsLiteOn)
	{
		bHasLiteBeenOn = true;
		if (UMaterialInstanceDynamic* GlowMatPtr = GlowMat.Get())
		{
			GlowMatPtr->SetScalarParameterValue("Glow", GlowScale);
			GlowMatPtr->SetScalarParameterValue("Mode", 1.f);
			//LiteNC->SetAutoActivate(true);
		}
	}
	else
	{
		if (UMaterialInstanceDynamic* GlowMatPtr = GlowMat.Get())
		{
			GlowMatPtr->SetScalarParameterValue("Glow", 0.f);
			GlowMatPtr->SetScalarParameterValue("Mode", 0.f);
			//LiteNC->SetActive(false);
		}
		bHasLiteBeenOn = false;
	}
}

// Called when the game starts or when spawned
void ALite::BeginPlay()
{
	Super::BeginPlay();
}

// Called every frame
void ALite::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

	FadeLiteTimeline.TickTimeline(DeltaTime);
	FadeColorTimeline.TickTimeline(DeltaTime);
}

void ALite::Setup()
{
}

void ALite::ToggleLite()
{
	StartLiteScale = 0.f;
	EndLiteScale = LiteScale;
	FOnTimelineFloat TimelineProgress;
	TimelineProgress.BindUFunction(this, FName("FadeLite"));
	FadeLiteTimeline.AddInterpFloat(LiteFadeCurve,TimelineProgress);
	FadeLiteTimeline.SetLooping(false);

	//FOnTimelineFloat ColorTimelineProgress;
	//ColorTimelineProgress.BindUFunction(this, FName("FadeColor"));
	//FadeColorTimeline.AddInterpFloat(LiteFadeCurve, ColorTimelineProgress);
	//FadeColorTimeline.SetLooping(false);

	if (bIsLiteOn)
	{
		StartColor = GetColorValue(WantedLiteColor);
		EndColor = GetColorValue(CurrentLiteColor);
		FadeLiteTimeline.Play();
		//FadeColorTimeline.Play();
		bIsLiteOn = false;
		PrevLiteColor = CurrentLiteColor;
		CurrentLiteColor = WantedLiteColor;
		LiteOff.Broadcast();
	}
	else
	{
		StartColor = GetColorValue(WantedLiteColor);
		EndColor = GetColorValue(CurrentLiteColor);
		if (bHasLiteBeenOn)
		{
			FadeLiteTimeline.Reverse();
			//FadeColorTimeline.Reverse();
		}
		else
		{
			FadeLiteTimeline.ReverseFromEnd();
			//FadeColorTimeline.ReverseFromEnd();
			bHasLiteBeenOn = true;
		}

		bIsLiteOn = true;
		LiteOn.Broadcast();
	}

	ToggleLiteBP(CurrentLiteColor == WantedLiteColor);
}

void ALite::TurnLiteOn()
{
	if (bHasLiteBeenOn)
	{
		FadeLiteTimeline.Reverse();
		//FadeColorTimeline.Reverse();
	}
	else
	{
		FadeLiteTimeline.ReverseFromEnd();
		//FadeColorTimeline.ReverseFromEnd();
		bHasLiteBeenOn = true;
	}

	bIsLiteOn = true;
	LiteOn.Broadcast();
}

void ALite::TurnLiteOff()
{
	
}

/*void ALite::ReturnLightToSource(UObject* Instig)
{
	//CurrentLiteColor = IHaloInterface::Execute_TakeLight(Instig, LightSourceLocation + GetActorLocation());
	ColorValue = GetColorValue(CurrentLiteColor);
	ToggleLite();
}*/


void ALite::InteractWith_Implementation(UObject* Instig)
{
	if (Instig != nullptr && Instig->Implements<UHaloInterface>())
	{
		if (!IHaloInterface::Execute_HasRainbow(Instig))
		{
			if (bIsLiteOn)
			{
				if (IHaloInterface::Execute_HasSpace(Instig))
				{
					IHaloInterface::Execute_GiveLight(Instig, CurrentLiteColor, this);
					ToggleLite();
				}
			}
			else
			{
				if (IHaloInterface::Execute_HasLight(Instig) && bCanTakeLite)
				{
					CurrentLiteColor = IHaloInterface::Execute_TakeLight(Instig, LightSourceLocation + GetActorLocation());
					ColorValue = GetColorValue(CurrentLiteColor);
					//SetLiteColor(ColorValue);
					ToggleLite();
				}
			}
		}
		

	}
}

void ALite::FadeLite(float Value)
{
	float TempFloat = FMath::Lerp(StartLiteScale, EndLiteScale, Value);
	SetLiteScale(TempFloat);
	if (UMaterialInstanceDynamic* GlowMatPtr = GlowMat.Get())
	{
		GlowMatPtr->SetScalarParameterValue("Glow", Value * GlowScale);
		GlowMatPtr->SetScalarParameterValue("Mode",Value);
	}
	FadeLiteBP(Value);

	if (!FadeColorTimeline.IsPlaying())
	{
		float r = FMath::Lerp(StartColor.R,EndColor.R,Value);
		float g = FMath::Lerp(StartColor.G,EndColor.G,Value);
		float b = FMath::Lerp(StartColor.B,EndColor.B,Value);
		FLinearColor tempColor = FLinearColor(r,g,b);
		SetLiteColor(tempColor);
	}
}

void ALite::FadeColor(float Value)
{
	//StartColor = GetColorValue(PrevLiteColor);
	//EndColor = GetColorValue(CurrentLiteColor);
	float r = FMath::Lerp(StartColor.R,EndColor.R,Value);
	float g = FMath::Lerp(StartColor.G,EndColor.G,Value);
	float b = FMath::Lerp(StartColor.B,EndColor.B,Value);
	FLinearColor tempColor = FLinearColor(r,g,b);
	SetLiteColor(tempColor);
	FadeColorBP(tempColor);
}

void ALite::FadeColorStart()
{
	if (!FadeColorTimeline.IsPlaying() && !FadeLiteTimeline.IsPlaying())
	{
		StartColor = GetColorValue(PrevLiteColor);
		EndColor = GetColorValue(CurrentLiteColor);
		FOnTimelineFloat ColorTimelineProgress;
		ColorTimelineProgress.BindUFunction(this, FName("FadeColor"));
		FadeColorTimeline.AddInterpFloat(LiteFadeCurve, ColorTimelineProgress);
		FadeColorTimeline.SetLooping(false);
		//StartColor = GetColorValue(WantedLiteColor);
		//EndColor = GetColorValue(CurrentLiteColor);
		FadeColorTimeline.ReverseFromEnd();
	}
}


/*void ALite::FadeLiteFinished()
{
	if (!bIsLiteOn)
	{
		LiteOff.Broadcast();
	}
}*/


void ALite::SetLiteColor(FLinearColor NewColor)
{
	if (UMaterialInstanceDynamic* GlowMatPtr = GlowMat.Get())
		GlowMatPtr->SetVectorParameterValue("Color",NewColor);

	LiteColorSet.Broadcast(NewColor);
	//LiteNC->SetColorParameter(FName("Color"), ColorValue);
}



