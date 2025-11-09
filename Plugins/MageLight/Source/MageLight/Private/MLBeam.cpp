#include "MLBeam.h"

#include "Kismet/KismetMathLibrary.h"
#include "Kismet/GameplayStatics.h"
#include "GameFramework/Character.h"

// Fill out your copyright notice in the Description page of Project Settings.


// Sets default values
AMLBeam::AMLBeam()
{
	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	BeamNC = CreateDefaultSubobject<UNiagaraComponent>(TEXT("BeamNC"));
	SetRootComponent(BeamNC);
}

// Called when the game starts or when spawned
void AMLBeam::BeginPlay()
{
	Super::BeginPlay();
}

void AMLBeam::Setup()
{
	BeamNC->SetVariableLinearColor("Color", BeamColor);
	CanBeam = true;
}

// Called every frame
void AMLBeam::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

	if (CanBeam)
	{
		FHitResult Hit = DoubleTraceCenter();
		SetHitting(Hit);
		FRotator TargetRotation = FRotator(0.0f);
		if (Hit.bBlockingHit)
		{
			TargetRotation = UKismetMathLibrary::FindLookAtRotation(SourceComponent->GetComponentLocation(),Hit.ImpactPoint);
			float BeamLength = (SourceComponent->GetComponentLocation() - Hit.ImpactPoint).Length() / 1100.f;
			BeamNC->SetFloatParameter(FName("_Length"), BeamLength);
			if (UNiagaraComponent* HitNSCompPtr = HitNSComp.Get())
			{
				HitNSCompPtr->SetWorldLocation(Hit.ImpactPoint + (AimComponent->GetForwardVector()*-50.f));
			}
			//UGameplayStatics::ApplyDamage(Hit.GetActor(),1.f,UGameplayStatics::GetPlayerController(GetWorld(),0),
			//	UGameplayStatics::GetPlayerCharacter(GetWorld(),0),BeamDamageType);

			//if (Hit.GetActor()->Implements<UMageLightInterface>())
			//	IMageLightInterface::Execute_LightHit(Hit.GetActor(),Hit.GetComponent(),BeamDamageType);
		}
		else
		{
			TargetRotation = AimComponent->GetComponentRotation();
			BeamNC->SetFloatParameter(FName("_Length"), 1.f);
		}
		SetActorRotation(TargetRotation);
		SetActorLocation(SourceComponent->GetComponentLocation());
	}
}

FHitResult AMLBeam::DoubleTraceCenter()
{
	FHitResult Hit;
	if (USceneComponent* AimComponentPtr = AimComponent.Get())
	{
		FVector StartLoc = AimComponentPtr->GetComponentLocation();
		FVector EndLoc = StartLoc + (AimComponentPtr->GetForwardVector() * 5000.f);
		
		GetWorld()->LineTraceSingleByChannel(Hit, StartLoc, EndLoc, ECollisionChannel::ECC_Visibility);
		if (Hit.bBlockingHit)
		{
			float ForwardMult = ((StartLoc - Hit.ImpactPoint).Length() + 100.f);
			FRotator LookRot = UKismetMathLibrary::FindLookAtRotation(StartLoc, Hit.ImpactPoint);
			EndLoc = StartLoc + (UKismetMathLibrary::GetForwardVector(LookRot) * ForwardMult);
		
			FHitResult Hit2;
			GetWorld()->LineTraceSingleByChannel(Hit2, StartLoc, EndLoc, ECollisionChannel::ECC_Visibility);
			if (Hit2.bBlockingHit)
			{
				return Hit2;
			}
		}
	}
	
	return Hit;
}

void AMLBeam::SetHitting(FHitResult& Hit)
{
	if (IsHitting && !Hit.bBlockingHit)
		EndHitting();
	else if (!IsHitting && Hit.bBlockingHit)
		StartHitting(Hit);
}

void AMLBeam::StartHitting(FHitResult& Hit)
{
	IsHitting = true;
	if (HitNSComp != nullptr)
	{
		HitNSComp->DestroyComponent();
	}
	HitNSComp = UNiagaraFunctionLibrary::SpawnSystemAtLocation(GetWorld(), HitNS, FVector(0.f), FRotator(0.f));
	HitNSComp->SetColorParameter("Color", BeamColor);

	FTimerDelegate HitTimerDelegate;
	HitTimerDelegate.BindUFunction(this,"HitTimerEvent",Hit);
	GetWorld()->GetTimerManager().SetTimer(HitTimerHandle,HitTimerDelegate,HitTickTime,true);
}

void AMLBeam::EndHitting()
{
	IsHitting = false;
	HitNSComp->Deactivate();
	HitNSComp->DestroyComponent();
	HitNSComp = nullptr;

	GetWorld()->GetTimerManager().ClearTimer(HitTimerHandle);
}

void AMLBeam::HitTimerEvent(FHitResult& Hit)
{
	if (Hit.GetActor() && Hit.GetActor()->Implements<UMageLightInterface>())
		IMageLightInterface::Execute_LightHit(Hit.GetActor(),Hit.GetComponent(),BeamDamageType);
}


void AMLBeam::Destroyed()
{
	if (HitNSComp != nullptr)
	{
		HitNSComp->Deactivate();
		HitNSComp = nullptr;
	}
}
