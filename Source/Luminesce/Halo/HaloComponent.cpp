// Fill out your copyright notice in the Description page of Project Settings.


#include "HaloComponent.h"

#include <ThirdParty/skia/skia-simplify.h>

#include "Kismet/KismetSystemLibrary.h"


// Sets default values for this component's properties
UHaloComponent::UHaloComponent()
{
	// Set this component to be initialized when the game starts, and to be ticked every frame.  You can turn these features
	// off to improve performance if you don't need them.
	PrimaryComponentTick.bCanEverTick = true;
}

// Called when the game starts
void UHaloComponent::BeginPlay()
{
	Super::BeginPlay();

	SetupHalo();
	
}


// Called every frame
void UHaloComponent::TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction)
{
	Super::TickComponent(DeltaTime, TickType, ThisTickFunction);
	TickMarbleLocations(DeltaTime);
	TickMarbleBeams(DeltaTime);
}

void UHaloComponent::TickMarbleBeams(float DeltaTime)
{
	if (Marbles.Num() > 0)
	{
		if (Marbles[LiteIndex]->bBeamFiring && !HasRainbowLight)
		{
			Marbles[LiteIndex]->BeamTimeRemaining -= DeltaTime;
			if (Marbles[LiteIndex]->BeamTimeRemaining <= 0)
			{
				EndBeam();
				ReturnLightToSource(LiteIndex);
			}
		}
	}
}

void UHaloComponent::TickMarbleLocations(float DeltaTime)
{
	FindTargetCircleRotation();
	
	CurrentCircleRotation = FMath::RInterpTo(FRotator(0.f,CurrentCircleRotation,0.f), FRotator(0.f,TargetCircleRotation,0.f),
		DeltaTime,MarbleCircleRotationSpeed).Yaw;
	
	FindMarbleTargetLocations();
	if (!TakingMarble)
	{
		for (int i = 0; i < Marbles.Num(); i++)
		{
			FVector setMarbleLoc = FMath::VInterpTo(Marbles[i]->GetActorLocation(), MarbleTargetLocations[i],DeltaTime,MarbleInterpSpeed);
			Marbles[i]->SetActorLocation(setMarbleLoc);
			//Marbles[i]->SetActorRelativeLocation(setMarbleLoc);
		}
	}
}


void UHaloComponent::SetupHalo()
{
	if (HaloClass)
	{
		Halo = GetWorld()->SpawnActor<AHalo>(HaloClass,FVector::ZeroVector,FRotator::ZeroRotator);
		Halo->AttachToComponent(HaloSpringArm.Get(), FAttachmentTransformRules::SnapToTargetNotIncludingScale);
		Halo->PlayerCam = PlayerCam;
	}
}

void UHaloComponent::ReturnLightToSource_Implementation(int Index)
{
	//ALite* SourceLite = Marbles[LiteIndex]->SourceLite;
	//TakeLight_Implementation(SourceLite->GetActorLocation() + SourceLite->LightSourceLocation);
	//SourceLite->ReturnLightToSource(this);
	EndBeam();
}


ELiteColor UHaloComponent::TakeLight_Implementation(FVector LiteSourceLocation)
{
	ELiteColor TempColor = ELiteColor::NONE;
		
		if (Marbles.Num() > 0)
		{
			if (LiteColors[LiteIndex] != ELiteColor::NONE)
			{
				TempColor = LiteColors[LiteIndex];
				LiteColors[LiteIndex] = ELiteColor::NONE;
				Marbles[LiteIndex]->LiteOff(GetColorValue(TempColor), LiteSourceLocation);
				LiteCount--;
				return TempColor;
			}
			else
			{
				for (int i = 0; i < Marbles.Num(); i++)
				{
					if (LiteColors[i] != ELiteColor::NONE)
					{
						SetActiveIndex(i);
						TempColor = LiteColors[LiteIndex];
						LiteColors[LiteIndex] = ELiteColor::NONE;
						LiteCount--;
						return TempColor;
					}
				}
		
			}
		}
	return TempColor;
}

void UHaloComponent::GiveLight_Implementation(ELiteColor LiteColor, ALite* SourceLite)
{
		if (Marbles.Num() > 0)
		{
			LiteColors[LiteIndex] = LiteColor;
			Marbles[LiteIndex]->LiteOn(GetColorValue(LiteColor), SourceLite->GetActorLocation() + SourceLite->LightSourceLocation);
			Marbles[LiteIndex]->SourceLite = SourceLite;
			Marbles[LiteIndex]->BeamTimeRemaining = Marbles[LiteIndex]->MaxBeamTime;
			LiteCount++;
		}
}

bool UHaloComponent::HasSpace_Implementation()
{
	bool hasSpace = false;
	if (Marbles.Num() > 0)
	{
		if (LiteColors[LiteIndex] == ELiteColor::NONE)
		{
			hasSpace = true;
		}
		else
		{
			for (int i = 0; i < Marbles.Num(); i++)
			{
				if (LiteColors[i] == ELiteColor::NONE)
				{
					hasSpace = true;
					SetActiveIndex(i);
					break;
				}
			}
		
		}
	}
	return hasSpace;
}

bool UHaloComponent::HasLight_Implementation()
{
	bool hasLight = false;
	if (Marbles.Num() > 0)
	{
		for (int i = 0; i < Marbles.Num(); i++)
		{
			if (LiteColors[i] != ELiteColor::NONE)
			{
				hasLight = true;
				if (LiteColors[LiteIndex] == ELiteColor::NONE)
					LiteIndex = i;
			}
		}
	}
	return hasLight;
}

bool UHaloComponent::HasRainbow_Implementation()
{
	return HasRainbowLight;
}

void UHaloComponent::AddMarble_Implementation(AMarble* NewMarble)
{
	Marbles.Add(NewMarble);
	LiteColors.Add(ELiteColor::NONE);
	MarbleTargetLocations.Add(NewMarble->GetActorLocation());
	FindMarbleStartLocations();
	FindMarbleTargetLocations();
	TakingMarble = true;

}

void UHaloComponent::SetActiveIndex(int NewIndex)
{
	IndexChangedEvent.Broadcast();
	LiteIndex = NewIndex;
}

void UHaloComponent::LiteIndexUp_Implementation()
{
	if (Marbles.Num() > 1)
	{
		if (LiteIndex < Marbles.Num() - 1)
			SetActiveIndex(LiteIndex + 1);
		else
			SetActiveIndex(0);
	}
}

void UHaloComponent::LiteIndexDown_Implementation()
{
	if (Marbles.Num() > 1)
	{
		if (LiteIndex > 0)
			SetActiveIndex(LiteIndex - 1);
		else
			SetActiveIndex(Marbles.Num() - 1);
	}
}

void UHaloComponent::StartBeam(USceneComponent* AimComponent)
{
	//if (!HasRainbowLight)
	//{
		if ((Marbles.Num() > LiteIndex && HasLight_Implementation() && Marbles[LiteIndex]->BeamTimeRemaining > 0.f) || HasRainbowLight)
		{
			Marbles[LiteIndex]->StartBeam(AimComponent, GetColorValue((LiteColors[LiteIndex])));
			StartBeamEvent.Broadcast();
		}
	//}
	/*if (AHalo* HaloPtr = Halo.Get())
	{
		if (HasLight_Implementation())
		{
			FLinearColor GotColor = GetColorValue(LiteColors[LiteIndex]);
			HaloPtr->StartBeam(AimComponent, GetColorValue((LiteColors[LiteIndex])));
		}
	}*/
}

void UHaloComponent::EndBeam()
{
	//if (!HasRainbowLight)
	//{
		if (Marbles.Num() > LiteIndex)
		{
			if (Marbles[LiteIndex]->bBeamDidFire)
				EndBeamEvent.Broadcast();
		
			Marbles[LiteIndex]->EndBeam();
		
		}
	//}
	//if (AHalo* HaloPtr = Halo.Get())
	//	HaloPtr->EndBeam();
}

void UHaloComponent::GetRainbowLight()
{
	HasRainbowLight = true;
}


void UHaloComponent::FindTargetCircleRotation()
{
	TargetCircleRotation = LiteIndex * -(360.f / Marbles.Num());
}

void UHaloComponent::FindMarbleStartLocations()
{
	MarbleStartingLocations.Empty();
	for (int i = 0; i < Marbles.Num(); i++)
	{
		MarbleStartingLocations.Add(Marbles[i]->GetActorLocation());
	}
}

void UHaloComponent::FindMarbleTargetLocations()
{
	/*FVector camForwardOffset = PlayerCam->GetForwardVector() * HaloLocationOffset.Z;
	FVector camRightOffset = PlayerCam->GetRightVector() * HaloLocationOffset.X;
	FVector camUpOffset = PlayerCam->GetUpVector() * HaloLocationOffset.Y;
	FVector camOffset = camForwardOffset + camRightOffset + camUpOffset;
	FVector playerCamLocation = PlayerCam->GetComponentLocation();
	FVector centerLocation = playerCamLocation + camOffset;*/
	FVector centerLocation = Halo->GetActorLocation();
	for (int i = 0; i < Marbles.Num(); i++)
	{
		float test = Marbles.Num();
		float radiusMult = HaloRadiusMultiplier * (test - 1);
		float indexRadians = ((PI * 2.f) / Marbles.Num()) * i;
		float circleRotationRadians = FMath::DegreesToRadians(CurrentCircleRotation);
		float rotationRadians = circleRotationRadians + indexRadians;
		
		float cosRadians = FMath::Cos(rotationRadians);
		float sinRadians = FMath::Sin(rotationRadians);
		FVector rightOffset = PlayerCam->GetRightVector() * FVector(radiusMult * sinRadians);
		FVector upOffset = PlayerCam->GetUpVector() * FVector(radiusMult * cosRadians);
		//FVector marbleLocation = playerCamLocation + camOffset + rightOffset + upOffset;
		FVector marbleLocation = centerLocation + rightOffset + upOffset;
		if (MarbleTargetLocations.Num() - 1 >= i)
			MarbleTargetLocations[i] = marbleLocation;
		else
			MarbleTargetLocations.Add(marbleLocation);
	}
}



