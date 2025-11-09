// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"

#include "InteractInterface.generated.h"

// This class does not need to be modified.
UINTERFACE(Blueprintable)
class UInteractInterface : public UInterface
{
	GENERATED_BODY()
};

/**
 * 
 */
class INTERACTION_API IInteractInterface
{
	GENERATED_BODY()

public:
	UFUNCTION(BlueprintCallable, BlueprintNativeEvent, Category = Interact)
	AActor* LookAt();

	UFUNCTION(BlueprintCallable, BlueprintNativeEvent, Category = Interact)
	FText GetMessage();

	UFUNCTION(BlueprintCallable, BlueprintNativeEvent, Category = Interact)
	float GetInteractDistance();

	UFUNCTION(BlueprintCallable, BlueprintNativeEvent, Category = Interact)
	void LookAway();

	UFUNCTION(BlueprintCallable, BlueprintNativeEvent, Category = Interact)
	void InteractWith(UObject* Instigator);

};
