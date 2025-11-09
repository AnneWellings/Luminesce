// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "AbilitySystemComponent.h"
#include "AttributeSet.h"
#include "LuneAttributeSet.generated.h"

#define ATTRIBUTE_ACCESSORS(ClassName, PropertyName) \
	GAMEPLAYATTRIBUTE_PROPERTY_GETTER(ClassName, PropertyName) \
	GAMEPLAYATTRIBUTE_VALUE_GETTER(PropertyName) \
	GAMEPLAYATTRIBUTE_VALUE_SETTER(PropertyName) \
	GAMEPLAYATTRIBUTE_VALUE_INITTER(PropertyName)

/**
 * 
 */
UCLASS()
class LUMINESCE_API ULuneAttributeSet : public UAttributeSet
{
	GENERATED_BODY()

public:
	ULuneAttributeSet();

	virtual void GetLifetimeReplicatedProps(TArray<class FLifetimeProperty>& OutLifetimeProps) const override;

	//UPROPERTY(BlueprintReadOnly, ReplicatedUsing = OnRep_MarbleCount, Category = Halo)
	//FGameplayAttributeData MarbleCount;
	//ATTRIBUTE_ACCESSORS(ULuneAttributeSet, MarbleCount);

	//UFUNCTION()
	//virtual void OnRep_MarbleCount(const FGameplayAttribute& OldValue);
};
