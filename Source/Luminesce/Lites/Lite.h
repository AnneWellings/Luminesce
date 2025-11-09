// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "InteractInterface.h"
#include "Components/StaticMeshComponent.h"
#include "Components/TimelineComponent.h"
#include "LiteData.h"
#include "Lite.generated.h"



UCLASS()
class LUMINESCE_API ALite : public AActor, public IInteractInterface
{
	GENERATED_BODY()

	DECLARE_DYNAMIC_MULTICAST_DELEGATE(FLiteOn);
	DECLARE_DYNAMIC_MULTICAST_DELEGATE(FLiteOff);
	DECLARE_DYNAMIC_MULTICAST_DELEGATE_OneParam(FLiteColorSet, FLinearColor, NewColor);

public:
	// Sets default values for this actor's properties
	ALite();

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = Meshes, meta = (AllowPrivateAccess = "true"))
	TObjectPtr<UStaticMeshComponent> LiteMesh = nullptr;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = Meshes, meta = (AllowPrivateAccess = "true"))
	TObjectPtr<UMaterialInterface> LiteMaterial = nullptr;
	
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = Meshes, meta = (AllowPrivateAccess = "true"))
	FVector LightSourceLocation = FVector::ZeroVector;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = Meshes, meta = (AllowPrivateAccess = "true"))
	int GlowMatIndex = 0;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = Lite, meta = (AllowPrivateAccess = "true"))
	bool bIsLiteOn = false;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = Lite, meta = (AllowPrivateAccess = "true"))
	bool bCanTakeLite = true;

	bool bHasLiteBeenOn = false;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = Lite , meta = (AllowPrivateAccess = "true"))
	float LiteScale = 1.0f;
	
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = Lite , meta = (AllowPrivateAccess = "true"))
	float GlowScale = 10.f;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = Lite , meta = (AllowPrivateAccess = "true"))
	bool bSwitchLite = false;
	
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = Lite , meta = (AllowPrivateAccess = "true"))
	bool bHiddenLite = false;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = Color , meta = (AllowPrivateAccess = "true"))
	ELiteColor CurrentLiteColor = ELiteColor::WHITE;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = Color , meta = (AllowPrivateAccess = "true"))
	ELiteColor WantedLiteColor = ELiteColor::WHITE;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = Color , meta = (AllowPrivateAccess = "true"))
	ELiteColor PrevLiteColor = ELiteColor::NONE;

	FLinearColor ColorValue = FLinearColor::White;
	FLinearColor StartColor = FLinearColor::White;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = Color , meta = (AllowPrivateAccess = "true"))
	FLinearColor EndColor = FLinearColor::White;

	UPROPERTY(editAnywhere, BlueprintReadOnly, Category = Lite , meta = (AllowPrivateAccess = "true"))
	UCurveFloat* LiteFadeCurve;

	FTimeline FadeLiteTimeline;
	FTimeline FadeColorTimeline;

	UPROPERTY(BlueprintAssignable)
	FLiteColorSet LiteColorSet;

	UPROPERTY(BlueprintAssignable)
	FLiteOn LiteOn;

	UPROPERTY(BlueprintAssignable)
	FLiteOff LiteOff;

	UFUNCTION(BlueprintCallable)
	void ToggleLite();

	UFUNCTION(BlueprintCallable)
	void TurnLiteOn();
	
	UFUNCTION(BlueprintCallable)
	void TurnLiteOff();

	UFUNCTION(BlueprintImplementableEvent)
	void ToggleLiteBP(bool isPreferredColor);

	UFUNCTION()
	void FadeLite(float Value);

	UFUNCTION()
	void FadeColor(float Value);

	UFUNCTION(BlueprintCallable)
	void FadeColorStart();

	/*UFUNCTION()
	void FadeLiteFinished();*/

	UFUNCTION(BlueprintImplementableEvent)
	void FadeLiteBP(float Value);

	UFUNCTION(BlueprintImplementableEvent)
	void FadeColorBP(FLinearColor Color);

	virtual float GetLiteScale(){return LiteScale;};
	virtual void SetLiteScale(float NewScale){LiteScale = NewScale;};

	UFUNCTION(BlueprintCallable)
	virtual void SetLiteColor(FLinearColor NewColor);

	virtual void InteractWith_Implementation(UObject* Instigator) override;

	UFUNCTION(BlueprintCallable)
	virtual void Setup();

	//void ReturnLightToSource(UObject* Instig);
	
protected:
	virtual void OnConstruction(const FTransform& Transform) override;

	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

	UPROPERTY()
	TObjectPtr<UMaterialInstanceDynamic> GlowMat = nullptr;

	float StartLiteScale = 1.0f;
	float CurrentLiteScale = 1.0f;
	float EndLiteScale = 1.0f;

public:
	// Called every frame
	virtual void Tick(float DeltaTime) override;
};
