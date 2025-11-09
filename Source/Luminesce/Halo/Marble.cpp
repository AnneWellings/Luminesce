// Fill out your copyright notice in the Description page of Project Settings.


#include "Marble.h"
#include "Luminesce/Halo/HaloInterface.h"

// Sets default values
AMarble::AMarble()
{
	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	MageLightAC = CreateDefaultSubobject<UMageLightAC>("MageLightAC");
}

// Called when the game starts or when spawned
void AMarble::BeginPlay()
{
	Super::BeginPlay();
	
}

// Called every frame
void AMarble::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
}

void AMarble::StartBeam(USceneComponent* AimComponent, FLinearColor BeamColor)
{
	if (UMageLightAC* MageLightACPtr = MageLightAC.Get())
	{
		bBeamDidFire = true;
		bBeamFiring = true;
		MageLightACPtr->StartBeam(AimComponent, BeamColor);
	}
}

void AMarble::EndBeam()
{
	if (UMageLightAC* MageLightACPtr = MageLightAC.Get())
	{
		MageLightACPtr->EndBeam();
		bBeamFiring = false;
		bBeamDidFire = false;
	}
}


