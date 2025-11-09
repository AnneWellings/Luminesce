// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Engine/DataAsset.h"
#include "GameplayTagContainer.h"
#include "InputAbilityDataAsset.generated.h"

class UInputAction;

USTRUCT(BlueprintType)
struct FAbilitySystemInputAction
{
	GENERATED_BODY()
	
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Input")
	TObjectPtr<UInputAction> InputAction;

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Input")
	FGameplayTag InputTag;
};

UCLASS()
class INPUTABILITYSYSTEM_API UInputAbilityDataAsset : public UDataAsset
{
	GENERATED_BODY()

	public:
		UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Input")
		TArray<FAbilitySystemInputAction> AbilityInputs;
};
