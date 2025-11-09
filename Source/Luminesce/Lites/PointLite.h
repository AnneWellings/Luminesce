// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Lite.h"
#include "Components/PointLightComponent.h"
#include "PointLite.generated.h"

UCLASS()
class LUMINESCE_API APointLite : public ALite
{
	GENERATED_BODY()

public:
	// Sets default values for this actor's properties
	APointLite();

	float GetLiteScale() override;
	void SetLiteScale(float NewScale) override;
	void SetLiteColor(FLinearColor NewColor) override;

	void Setup() override;

protected:
	virtual void OnConstruction(const FTransform& Transform) override;
	
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

	UPROPERTY(EditAnywhere,BlueprintReadWrite,Category="Lite",meta=(AllowPrivateAccess="true"))
	TObjectPtr<UPointLightComponent> PointLite = nullptr;

public:
	// Called every frame
	virtual void Tick(float DeltaTime) override;
};
