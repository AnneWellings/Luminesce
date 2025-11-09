// Fill out your copyright notice in the Description page of Project Settings.


#include "PointLite.h"


// Sets default values
APointLite::APointLite()
{
	Super::
	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;
	
	PointLite = CreateDefaultSubobject<UPointLightComponent>("PointLite");
	PointLite->SetupAttachment(LiteMesh);
	
}

void APointLite::OnConstruction(const FTransform& Transform)
{
	Super::OnConstruction(Transform);

	if (UPointLightComponent* PointLitePtr = PointLite.Get())
	{
		//PointLitePtr->SetLightColor(ColorValue);
		SetLiteColor(ColorValue);

		if (bIsLiteOn)
		{
			PointLitePtr->SetIntensity(LiteScale);
		}
		else
		{
			PointLitePtr->SetIntensity(0.f);
		}
	}
}

// Called when the game starts or when spawned
void APointLite::BeginPlay()
{
	Super::BeginPlay();
	
}

void APointLite::Setup()
{
	Super::Setup();
}


// Called every frame
void APointLite::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
}

float APointLite::GetLiteScale()
{
	if (UPointLightComponent* PointLitePtr = PointLite.Get())
		CurrentLiteScale = PointLitePtr->Intensity;
	return CurrentLiteScale;
};

void APointLite::SetLiteScale(float NewScale)
{
	CurrentLiteScale = NewScale;
	if (UPointLightComponent* PointLitePtr = PointLite.Get())
		PointLitePtr->SetIntensity(CurrentLiteScale);
}

void APointLite::SetLiteColor(FLinearColor NewColor)
{
	Super::SetLiteColor(NewColor);
	if (UPointLightComponent* PointLitePtr = PointLite.Get())
		PointLitePtr->SetLightColor(NewColor);
}
