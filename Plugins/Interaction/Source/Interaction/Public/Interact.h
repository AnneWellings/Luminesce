// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Camera/CameraComponent.h"
#include "Engine/World.h"
#include "Engine/EngineTypes.h"
#include "Kismet/KismetSystemLibrary.h"
#include "InteractInterface.h"

#include "Interact.generated.h"

UCLASS(ClassGroup=(Custom), meta=(BlueprintSpawnableComponent))
class INTERACTION_API UInteract : public UActorComponent
{
	GENERATED_BODY()

	DECLARE_DYNAMIC_MULTICAST_DELEGATE_OneParam(FItemLookedAt, AActor*, LookedAtActor);
	DECLARE_DYNAMIC_MULTICAST_DELEGATE(FLookedAway);
	DECLARE_DYNAMIC_MULTICAST_DELEGATE_OneParam(FItemInteractedWith, AActor*, InteractedWithActor);

public:
	// Sets default values for this component's properties
	UInteract();

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = Interact, meta = (AllowPrivateAccess = "true"))
	float InteractDistance = 300.f;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = Interact, meta = (AllowPrivateAccess = "true"))
	TObjectPtr<AActor> InteractActor = nullptr;

	UPROPERTY(BlueprintAssignable)
	FItemLookedAt ItemLookedAt;

	UPROPERTY(BlueprintAssignable)
	FLookedAway LookedAway;

	UPROPERTY(BlueprintAssignable)
	FItemInteractedWith ItemInteractedWith;

	// Called every frame
	virtual void TickComponent(float DeltaTime, ELevelTick TickType,
							   FActorComponentTickFunction* ThisTickFunction) override;

	UFUNCTION(BlueprintCallable)
	void InteractWith(UObject* Instigator);

protected:
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = Settings, meta = (AllowPrivateAccess = "true"))
	TEnumAsByte<ECollisionChannel> InteractTraceChannel;
	
	// Called when the game starts
	virtual void BeginPlay() override;

	UFUNCTION()
	void Setup();

private:
	TWeakObjectPtr<UCameraComponent> OwnerCam = nullptr;

	void InteractTrace();
};
