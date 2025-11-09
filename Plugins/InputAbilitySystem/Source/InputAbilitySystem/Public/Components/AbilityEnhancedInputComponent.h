// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "EnhancedInputComponent.h"
#include "InputAbilitySystem/Public/InputAbilityDataAsset.h"
#include "AbilityEnhancedInputComponent.generated.h"


UCLASS(ClassGroup=(Custom), meta=(BlueprintSpawnableComponent))
class INPUTABILITYSYSTEM_API UAbilityEnhancedInputComponent : public UEnhancedInputComponent
{
	GENERATED_BODY()

public:
	// Sets default values for this component's properties
	UAbilityEnhancedInputComponent();

	template<class UserClass, typename PressFunction, typename ReleaseFunction>
	void BindAbilityInputs(UInputAbilityDataAsset* InputDataAsset, UserClass* Object, PressFunction PressFunctionCallback,
		ReleaseFunction ReleaseFunctionCallback);

protected:
	// Called when the game starts
	virtual void BeginPlay() override;

public:
	// Called every frame
	virtual void TickComponent(float DeltaTime, ELevelTick TickType,
	                           FActorComponentTickFunction* ThisTickFunction) override;
};

template <class UserClass, typename PressFunction, typename ReleaseFunction>
void UAbilityEnhancedInputComponent::BindAbilityInputs(UInputAbilityDataAsset* InputDataAsset, UserClass* Object,
	PressFunction PressFunctionCallback, ReleaseFunction ReleaseFunctionCallback)
{
	checkf(InputDataAsset, TEXT("InputDataAsset INVALID"));
	for (const FAbilitySystemInputAction& AbilityInputAction : InputDataAsset->AbilityInputs)
	{
		BindAction(AbilityInputAction.InputAction, ETriggerEvent::Started, Object, PressFunctionCallback, AbilityInputAction.InputTag);
		BindAction(AbilityInputAction.InputAction, ETriggerEvent::Completed, Object, ReleaseFunctionCallback, AbilityInputAction.InputTag);
	}
}
