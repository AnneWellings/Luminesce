// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Components/ActorComponent.h"
#include "MLBeam.h"
#include "MageLightAC.generated.h"


UCLASS(ClassGroup=(Custom), meta=(BlueprintSpawnableComponent))
class MAGELIGHT_API UMageLightAC : public UActorComponent
{
	GENERATED_BODY()

public:
	// Sets default values for this component's properties
	UMageLightAC();

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = Beam, meta = (AllowPrivateAccess = "true"))
	TSubclassOf<AMLBeam> BeamClass;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = Beam, meta = (AllowPrivateAccess = "true"))
	TSubclassOf<AMLBeam> RainbowBeamClass;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = Beam, meta = (AllowPrivateAccess = "true"))
	bool bHasRainbow;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = Beam, meta = (AllowPrivateAccess = "true"))
	AActor* HaloActor = nullptr;

	//UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = Beam, meta = (AllowPrivateAccess = "true"))
	//class UNiagaraSystem* RainbowBeamClass;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = FX, meta = (AllowPrivateAccess = "true"))
	class UNiagaraSystem* HitNS = nullptr;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = FX, meta = (AllowPrivateAccess = "true"))
	class UNiagaraSystem* HandLoopNS = nullptr;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = FX, meta = (AllowPrivateAccess = "true"))
	FVector HandLoopLocOffset;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = FX, meta = (AllowPrivateAccess = "true"))
	class UNiagaraSystem* HandBurstNS = nullptr;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = FX, meta = (AllowPrivateAccess = "true"))
	class UNiagaraSystem* HandSparkNS = nullptr;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = FX, meta = (AllowPrivateAccess = "true"))
	class UNiagaraSystem* RainbowHitNS = nullptr;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = FX, meta = (AllowPrivateAccess = "true"))
	class UNiagaraSystem* RainbowHandLoopNS = nullptr;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = FX, meta = (AllowPrivateAccess = "true"))
	class UNiagaraSystem* RainbowHandBurstNS = nullptr;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = FX, meta = (AllowPrivateAccess = "true"))
	class UNiagaraSystem* RainbowHandSparkNS = nullptr;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = FX, meta = (AllowPrivateAccess = "true"))
	TSubclassOf<UDamageType> BeamDamageType;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = FX, meta = (AllowPrivateAccess = "true"))
	TSubclassOf<UDamageType> RainbowBeamDamageType;
	
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category=Beam, meta = (AllowPrivateAccess = "true"))
	float BeamRotSpeed = 20.f;

	UFUNCTION(BlueprintCallable)
	void StartBeam(USceneComponent* AimComponent, FLinearColor BeamColor);

	UFUNCTION(BlueprintCallable)
	void EndBeam();
	
	// Called every frame
	virtual void TickComponent(float DeltaTime, ELevelTick TickType,
							   FActorComponentTickFunction* ThisTickFunction) override;
	

protected:
	// Called when the game starts
	virtual void BeginPlay() override;
	
private:
	TWeakObjectPtr<UNiagaraComponent> HandLoopNSComp = nullptr;
	TWeakObjectPtr<UNiagaraComponent> HandBurstNSComp = nullptr;
	TObjectPtr<AMLBeam> BeamActor = nullptr;

	FLinearColor SavedBeamColor;
	
};

