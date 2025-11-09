// Fill out your copyright notice in the Description page of Project Settings.


#include "Halo.h"


// Sets default values
AHalo::AHalo()
{
	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	//HaloMesh = CreateDefaultSubobject<UStaticMeshComponent>("HaloCenterMesh");
	//HaloMesh->SetupAttachment(RootComponent);

	//MageLightAC = CreateDefaultSubobject<UMageLightAC>("MageLightAC");
}

// Called when the game starts or when spawned
void AHalo::BeginPlay()
{
	Super::BeginPlay();

	//SetRandomOffset();
	//USkeletalMeshComponent* parentComponent = GetParentComponent();
	
}

// Called every frame
void AHalo::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

	/*if (UCameraComponent* PlayerCamPtr = PlayerCam.Get())
	{
		RandomZOffsetInterp = FMath::FInterpTo(RandomZOffsetInterp,RandomZOffset,DeltaTime,10.f);
		FVector GoalLoc = PlayerCamPtr->GetComponentLocation() + (PlayerCamPtr->GetForwardVector() * CamOffsetMult.Z) + (PlayerCamPtr->GetRightVector() * CamOffsetMult.X) + (PlayerCamPtr->GetUpVector() * CamOffsetMult.Y);
		HaloLocation = FMath::VInterpTo(GetActorLocation(),GoalLoc + FVector(0.f, 0.f, RandomZOffsetInterp), DeltaTime, VInterpSpeed);
		SetActorLocation(HaloLocation);
		SetActorRotation(PlayerCamPtr->GetComponentRotation());
	}*/
}

void AHalo::SetRandomOffset()
{
	RandomZOffset = FMath::RandRange(0.f,20.f);
	FTimerHandle RandTimerHandle;
	GetWorldTimerManager().SetTimer(
		RandTimerHandle,this,&AHalo::SetRandomOffset,FMath::RandRange(0.f,5.f),false);
}

/*void AHalo::StartBeam(USceneComponent* AimComponent, FLinearColor BeamColor)
{
	if (UMageLightAC* MageLightACPtr = MageLightAC.Get())
		MageLightACPtr->StartBeam(AimComponent, BeamColor);
}

void AHalo::EndBeam()
{
	if (UMageLightAC* MageLightACPtr = MageLightAC.Get())
		MageLightACPtr->EndBeam();
}*/


