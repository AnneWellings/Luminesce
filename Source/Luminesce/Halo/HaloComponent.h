// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Components/ActorComponent.h"
#include "Halo.h"
#include "HaloInterface.h"
#include "Luminesce/Lites/Lite.h"
#include "Luminesce/Lites/LiteData.h"
#include "Marble.h"
#include "GameFramework/SpringArmComponent.h"
#include "HaloComponent.generated.h"


UCLASS(ClassGroup=(Custom), meta=(BlueprintSpawnableComponent), Blueprintable)
class LUMINESCE_API UHaloComponent : public UActorComponent, public IHaloInterface
{
	GENERATED_BODY()

	DECLARE_DYNAMIC_MULTICAST_DELEGATE(FStartBeam);
	DECLARE_DYNAMIC_MULTICAST_DELEGATE(FEndBeam);
	DECLARE_DYNAMIC_MULTICAST_DELEGATE(FIndexChanged);

public:
	// Sets default values for this component's properties
	UHaloComponent();
	
	//UPROPERTY(VisibleAnywhere, BlueprintReadWrite, Category = Items, meta = (AllowPrivateAccess = "true"))
	//TObjectPtr<AHalo> Halo;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = Items, meta = (AllowPrivateAccess = "true"))
	TSubclassOf<AHalo> HaloClass;

	//UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = References, meta = (AllowPrivateAccess = "true"))
	TWeakObjectPtr<UCameraComponent> PlayerCam = nullptr;

	TWeakObjectPtr<USpringArmComponent> HaloSpringArm = nullptr;

	UPROPERTY(VisibleAnywhere, BlueprintReadWrite, Category = Light, meta = (AllowPrivateAccess = "true"))
	TArray<ELiteColor> LiteColors;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = Light, meta = (AllowPrivateAccess = "true"))
	int LiteCountMax = 1;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = Light, meta = (AllowPrivateAccess = "true"))
	int LiteCount = 0;
	
	UPROPERTY(VisibleAnywhere, BlueprintReadWrite, Category = Light, meta = (AllowPrivateAccess = "true"))
	int LiteIndex = 0;

	UPROPERTY(VisibleAnywhere, BlueprintReadWrite, Category = Light, meta = (AllowPrivateAccess = "true"))
	bool HasRainbowLight = false;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = Color, meta = (AllowPrivateAccess = "true"))
	UDataTable* ColorDataTable;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = Halo, meta = (AllowPrivateAccess = "true"))
	TArray<TObjectPtr<AMarble>> Marbles;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = Halo, meta = (AllowPrivateAccess = "true"))
	bool TakingMarble = false;

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = Halo , meta = (AllowPrivateAccess = "true"))
	UCurveFloat* TakeMarbleCurve;

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = Halo , meta = (AllowPrivateAccess = "true"))
	TArray<FVector> MarbleStartingLocations;

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = Halo , meta = (AllowPrivateAccess = "true"))
	TArray<FVector> MarbleTargetLocations;

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = Halo , meta = (AllowPrivateAccess = "true"))
	FVector HaloLocationOffset;

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = Halo , meta = (AllowPrivateAccess = "true"))
	float HaloRadiusMultiplier = 10.f;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = Halo , meta = (AllowPrivateAccess = "true"))
	float TargetCircleRotation = 0.f;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = Halo , meta = (AllowPrivateAccess = "true"))
	float CurrentCircleRotation = 0.f;
	
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = Halo , meta = (AllowPrivateAccess = "true"))
	float MarbleCircleRotationSpeed = 5.f;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = Halo , meta = (AllowPrivateAccess = "true"))
	float MarbleInterpSpeed = 50.f;

	FTimeline TakeMarbleTimeline;

	virtual ELiteColor TakeLight_Implementation(FVector LiteSourceLocation) override;
	virtual void GiveLight_Implementation(ELiteColor LiteColor, ALite* SourceLite) override;
	virtual bool HasSpace_Implementation() override;
	virtual bool HasLight_Implementation() override;
	virtual bool HasRainbow_Implementation() override;
	virtual void AddMarble_Implementation(AMarble* NewMarble) override;

	UFUNCTION(BlueprintNativeEvent)
	void LiteIndexUp();

	UFUNCTION(BlueprintNativeEvent)
	void LiteIndexDown();

	UFUNCTION(BlueprintCallable)
	void GetRainbowLight();

	UPROPERTY(BlueprintAssignable)
	FStartBeam StartBeamEvent;

	UPROPERTY(BlueprintAssignable)
	FEndBeam EndBeamEvent;

	UPROPERTY(BlueprintAssignable)
	FIndexChanged IndexChangedEvent;

	void StartBeam(USceneComponent* AimComponent);
	void EndBeam();

	UFUNCTION(BlueprintNativeEvent, BlueprintCallable)
	void ReturnLightToSource(int Index);
	
	// Called every frame
	virtual void TickComponent(float DeltaTime, ELevelTick TickType,
							   FActorComponentTickFunction* ThisTickFunction) override;

protected:
	UPROPERTY(BlueprintReadWrite, Category = Halo, meta = (AllowPrivateAccess = "true"))
	TObjectPtr<AHalo> Halo = nullptr;
	
	// Called when the game starts
	virtual void BeginPlay() override;

	void SetupHalo();


private:
	void SetActiveIndex(int NewIndex);

	void FindTargetCircleRotation();
	void FindMarbleStartLocations();
	void FindMarbleTargetLocations();

	void TickMarbleLocations(float DeltaTime);
	void TickMarbleBeams(float DeltaTime);
	
};
