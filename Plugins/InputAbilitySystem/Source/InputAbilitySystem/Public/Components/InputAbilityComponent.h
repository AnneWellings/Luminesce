// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "AbilitySystemComponent.h"
#include "InputAbilityComponent.generated.h"


UCLASS(ClassGroup=(Custom), meta=(BlueprintSpawnableComponent))
class INPUTABILITYSYSTEM_API UInputAbilityComponent : public UAbilitySystemComponent
{
	GENERATED_BODY()

public:
	// Sets default values for this component's properties
	UInputAbilityComponent();

protected:
	UPROPERTY(EditDefaultsOnly, Category = "Abilities")
	bool bAutoGiveStartingAbilities {true};

	UPROPERTY(EditDefaultsOnly, Category = "Abilities")
	bool bAutoGiveStartingEffects {true};
	
	UPROPERTY(EditDefaultsOnly, Category = "Abilities")
	TArray<TSubclassOf<UGameplayAbility>> StartingAbilities;

	UPROPERTY(EditDefaultsOnly, Category = "Abilities")
	TArray<TSubclassOf<UGameplayAbility>> StartingPassiveAbilities;

	UPROPERTY(EditDefaultsOnly, Category = "Abilities")
	TArray<TSubclassOf<UGameplayEffect>> StartingEffects;
	
	// Called when the game starts
	virtual void BeginPlay() override;
	virtual void OnPlayerControllerSet() override;

public:
	// Called every frame
	virtual void TickComponent(float DeltaTime, ELevelTick TickType,
	                           FActorComponentTickFunction* ThisTickFunction) override;

	void GiveStartingAbilities();
	void GiveStartingEffects();

	void AddAbility(const TSubclassOf<UGameplayAbility>& Ability, bool bAutoActivateAbility = false);
	void AddAbilities(const TArray<TSubclassOf<UGameplayAbility>>& Abilities, bool bAutoActivateAbility = false);
	
	void AddEffect(const TSubclassOf<UGameplayEffect>& Effect);
	void AddEffects(const TArray<TSubclassOf<UGameplayEffect>>& Effects);

	virtual void OnGiveAbility(FGameplayAbilitySpec& AbilitySpec) override;

	void AbilityInputPressed(const FGameplayTag& Tag);
	void AbilityInputReleased(const FGameplayTag& Tag);
};
