// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "NiagaraFunctionLibrary.h"
#include "NiagaraComponent.h"
#include "Engine/World.h"
#include "MageLightInterface.h"
#include "MLBeam.generated.h"

UCLASS()
class MAGELIGHT_API AMLBeam : public AActor
{
	GENERATED_BODY()

public:
	// Sets default values for this actor's properties
	AMLBeam();

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = FX, meta = (AllowPrivateAccess = "true"))
	UNiagaraComponent* BeamNC = nullptr;
	//TObjectPtr<UNiagaraComponent> BeamNC = nullptr;

	UPROPERTY()
	TWeakObjectPtr<USceneComponent> AimComponent = nullptr;

	UPROPERTY()
	TWeakObjectPtr<USceneComponent> SourceComponent = nullptr;

	UPROPERTY()
	FLinearColor BeamColor = FLinearColor::White;

	UPROPERTY(VisibleAnywhere, BlueprintReadWrite, Category = FX, meta = (AllowPrivateAccess = "true"))
	TWeakObjectPtr<UNiagaraComponent> HitNSComp = nullptr;

	UPROPERTY()
	class UNiagaraSystem* HitNS = nullptr;

	UPROPERTY()
	float BeamRotSpeed = 20.f;

	UPROPERTY()
	float HitTickTime = 0.1f;

	TSubclassOf<UDamageType> BeamDamageType;

	void Setup();

	// Called every frame
	virtual void Tick(float DeltaTime) override;

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

	virtual void Destroyed() override;

	UFUNCTION()
	void HitTimerEvent(FHitResult& Hit);

private:
	FHitResult DoubleTraceCenter();
	
	bool CanBeam = false;

	bool IsHitting = false;

	FTimerHandle HitTimerHandle;

	void SetHitting(FHitResult& Hit);
	void StartHitting(FHitResult& Hit);
	void EndHitting();
};
