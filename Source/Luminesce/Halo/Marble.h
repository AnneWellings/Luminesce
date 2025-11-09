// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "InteractInterface.h"
#include "MageLight/Public/MageLightAC.h"
#include "Luminesce/Lites/Lite.h"
#include "Marble.generated.h"

UCLASS()
class LUMINESCE_API AMarble : public AActor
{
	GENERATED_BODY()

public:
	// Sets default values for this actor's properties
	AMarble();

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = MageLight, meta = (AllowPrivateAccess = "true"))
	TObjectPtr<UMageLightAC> MageLightAC = nullptr;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = MageLight, meta = (AllowPrivateAccess = "true"))
	float MaxBeamTime = 1.f;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = MageLight, meta = (AllowPrivateAccess = "true"))
	float BeamTimeRemaining = 0.f;
	
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = MageLight, meta = (AllowPrivateAccess = "true"))
	bool bBeamFiring = false;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = MageLight, meta = (AllowPrivateAccess = "true"))
	bool bBeamDidFire = false;

	UFUNCTION(BlueprintImplementableEvent)
	void LiteOn(FLinearColor LiteColor, FVector LiteSourceLocation);

	UFUNCTION(BlueprintImplementableEvent)
	void LiteOff(FLinearColor LiteColor, FVector LiteSourceLocation);

	UPROPERTY(BlueprintReadOnly, meta = (AllowPrivateAccess = "true"))
	TObjectPtr<ALite> SourceLite = nullptr;

	void StartBeam(USceneComponent* AimComponent, FLinearColor BeamColor);
	void EndBeam();

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:
	// Called every frame
	virtual void Tick(float DeltaTime) override;
};
