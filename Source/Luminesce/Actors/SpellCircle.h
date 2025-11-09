// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "Luminesce/Lites/Lite.h"
#include "Components/DecalComponent.h"
#include "Components/ArrowComponent.h"
#include "SpellCircle.generated.h"

UCLASS()
class LUMINESCE_API ASpellCircle : public AActor
{
	GENERATED_BODY()

public:
	// Sets default values for this actor's properties
	ASpellCircle();

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category="SpellCircle")
	TSubclassOf<ALite> CandleClass = nullptr;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category="SpellCircle")
	int CandleCount = 5;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category="SpellCircle")
	float CircleRadius = 200.f;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category="SpellCircle")
	TArray<TObjectPtr<ALite>> Candles;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category="SpellCircle")
	TObjectPtr<UDecalComponent> SpellCircleDecal = nullptr;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category="SpellCircle")
	UMaterialInterface* SpellCircleDecalMat = nullptr;

	UPROPERTY()
	TObjectPtr<UArrowComponent> Arrow = nullptr;

	UPROPERTY(EditAnywhere, Blueprintreadwrite, Category="SpellCircle")
	FVector CircleScale = FVector(0.08f,1.f,1.f);

	//UFUNCTION(BlueprintCallable)
	//virtual void Setup();

	// Called every frame
	virtual void Tick(float DeltaTime) override;

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

private:
	//TWeakObjectPtr<ADecalActor> SpellDecal = nullptr;

	//void SpawnCandles();
};
