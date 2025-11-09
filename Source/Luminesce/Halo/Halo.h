// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "Camera/CameraComponent.h"
#include "MageLight/Public/MageLightAC.h"
#include "Halo.generated.h"

UCLASS()
class LUMINESCE_API AHalo : public AActor
{
	GENERATED_BODY()

public:
	// Sets default values for this actor's properties
	AHalo();

	//UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = Meshes, meta = (AllowPrivateAccess = "true"))
	//TObjectPtr<UStaticMeshComponent> HaloMesh = nullptr;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category="Meshes", meta = (AllowPrivateAccess = "true"))
	TObjectPtr<UStaticMesh> HaloMesh;
	
	TWeakObjectPtr<UCameraComponent> PlayerCam = nullptr;

	//UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = MageLight, meta = (AllowPrivateAccess = "true"))
	//TObjectPtr<UMageLightAC> MageLightAC = nullptr;

	//Settings
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = Location, meta = (AllowPrivateAccess = "true"))
	FVector CamOffsetMult = FVector(0, 0, 0);

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = Movement, meta = (AllowPrivateAccess = "true"))
	float VInterpSpeed = 50.f;

	FVector HaloLocation = FVector(0, 0, 0);

	float RandomZOffset = 0.f;
	float RandomZOffsetInterp = 0.f;

	void StartBeam(USceneComponent* AimComponent, FLinearColor BeamColor);
	void EndBeam();

	// Called every frame
	virtual void Tick(float DeltaTime) override;

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

private:
	
	void SetRandomOffset();
};
