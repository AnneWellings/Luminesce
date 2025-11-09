// Fill out your copyright notice in the Description page of Project Settings.


#include "Components/InputAbilityComponent.h"
#include "InputAbilitySystem/Public/Abilities/InputGameplayAbility.h"


// Sets default values for this component's properties
UInputAbilityComponent::UInputAbilityComponent()
{
	// Set this component to be initialized when the game starts, and to be ticked every frame.  You can turn these features
	// off to improve performance if you don't need them.
	PrimaryComponentTick.bCanEverTick = true;

	// ...
}


// Called when the game starts
void UInputAbilityComponent::BeginPlay()
{
	Super::BeginPlay();

	// ...
	
}

void UInputAbilityComponent::OnPlayerControllerSet()
{
	Super::OnPlayerControllerSet();

	if (bAutoGiveStartingAbilities)
		GiveStartingAbilities();

	if (bAutoGiveStartingEffects)
		GiveStartingEffects();
}

void UInputAbilityComponent::GiveStartingAbilities()
{
	if (IsOwnerActorAuthoritative())
	{
		AddAbilities(StartingAbilities);
		AddAbilities(StartingPassiveAbilities, true);
	}
}

void UInputAbilityComponent::GiveStartingEffects()
{
	if (IsOwnerActorAuthoritative())
	{
		AddEffects(StartingEffects);
	}
}


// Called every frame
void UInputAbilityComponent::TickComponent(float DeltaTime, ELevelTick TickType,
                                           FActorComponentTickFunction* ThisTickFunction)
{
	Super::TickComponent(DeltaTime, TickType, ThisTickFunction);

	// ...
}

void UInputAbilityComponent::AddAbility(const TSubclassOf<UGameplayAbility>& Ability, bool bAutoActivateAbility)
{
	FGameplayAbilitySpec Spec = FGameplayAbilitySpec(Ability);
	if (bAutoActivateAbility)
	{
		GiveAbilityAndActivateOnce(Spec);
	}
	else
	{
		GiveAbility(Spec);
	}
}

void UInputAbilityComponent::AddAbilities(const TArray<TSubclassOf<UGameplayAbility>>& Abilities, bool bAutoActivateAbility)
{
	for (const TSubclassOf<UGameplayAbility> Ability : Abilities)
	{
		AddAbility(Ability, bAutoActivateAbility);
	}
}

void UInputAbilityComponent::AddEffect(const TSubclassOf<UGameplayEffect>& Effect)
{
	const FGameplayEffectSpecHandle SpecHandle = MakeOutgoingSpec(Effect, 1.f, FGameplayEffectContextHandle());
	
	ApplyGameplayEffectSpecToSelf(*SpecHandle.Data);
}

void UInputAbilityComponent::AddEffects(const TArray<TSubclassOf<UGameplayEffect>>& Effects)
{
	for (const TSubclassOf<UGameplayEffect> Effect : Effects)
	{
		AddEffect(Effect);
	}
}

void UInputAbilityComponent::OnGiveAbility(FGameplayAbilitySpec& AbilitySpec)
{
	Super::OnGiveAbility(AbilitySpec);

	if (const UInputGameplayAbility* Ability = Cast<UInputGameplayAbility>(AbilitySpec.Ability))
	{
		AbilitySpec.DynamicAbilityTags.AddTag(Ability->InputTag);
	}
}

void UInputAbilityComponent::AbilityInputPressed(const FGameplayTag& Tag)
{
	ABILITYLIST_SCOPE_LOCK();
	for (FGameplayAbilitySpec& AbilitySpec : GetActivatableAbilities())
	{
		if (AbilitySpec.DynamicAbilityTags.HasTagExact(Tag))
		{
			if (!AbilitySpec.IsActive())
				TryActivateAbility(AbilitySpec.Handle);
			
			//Call pressed event even if ability is already active
			AbilitySpecInputPressed(AbilitySpec);
			if (AbilitySpec.Ability->bReplicateInputDirectly && !IsOwnerActorAuthoritative())
				ServerSetInputPressed(AbilitySpec.Handle);
		}
	}
}

void UInputAbilityComponent::AbilityInputReleased(const FGameplayTag& Tag)
{
	ABILITYLIST_SCOPE_LOCK();
	for (FGameplayAbilitySpec& AbilitySpec : GetActivatableAbilities())
	{
		if (AbilitySpec.IsActive() && AbilitySpec.DynamicAbilityTags.HasTagExact(Tag))
		{
			AbilitySpecInputReleased(AbilitySpec);
			
			if (AbilitySpec.Ability->bReplicateInputDirectly && !IsOwnerActorAuthoritative())
				ServerSetInputReleased(AbilitySpec.Handle);
		}
	}
}

