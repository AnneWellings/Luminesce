// Fill out your copyright notice in the Description page of Project Settings.
#include "Interact.h"

// Sets default values for this component's properties
UInteract::UInteract()
{
	// Set this component to be initialized when the game starts, and to be ticked every frame.  You can turn these features
	// off to improve performance if you don't need them.
	PrimaryComponentTick.bCanEverTick = true;

	// ...
}


// Called when the game starts
void UInteract::BeginPlay()
{
	Super::BeginPlay();

	Setup();
	
}

void UInteract::Setup()
{
	TArray<UCameraComponent*> Cameras;
	GetOwner()->GetComponents<UCameraComponent>(Cameras);
	
	for (int i = 0; i < Cameras.Num(); i++)
	{
		if (Cameras[i]->IsActive())
		{
			if (OwnerCam.IsExplicitlyNull())
			{
				OwnerCam = TWeakObjectPtr<UCameraComponent>(Cameras[i]);
				break;
			}
		}
	}
}

void UInteract::InteractTrace()
{
	if (UCameraComponent* OwnerCamPtr = OwnerCam.Get())
	{
		FHitResult Hit;
		FVector StartLoc = OwnerCamPtr->GetComponentLocation();
		FVector EndLoc = StartLoc + (OwnerCamPtr->GetForwardVector() * 1000.f);
		FCollisionQueryParams QParams;
		TArray<TWeakObjectPtr<const AActor>> IgnoredActors;
		IgnoredActors.Add(GetOwner());
		QParams.AddIgnoredActors(IgnoredActors);
		GetWorld()->LineTraceSingleByChannel(Hit, StartLoc, EndLoc, InteractTraceChannel, QParams);

		if (Hit.bBlockingHit)
		{
			if (Hit.GetActor() != nullptr && Hit.GetActor()->Implements<UInteractInterface>())
			{
				float currentInteractDistance = (Hit.GetActor()->GetActorLocation() - GetOwner()->GetActorLocation()).Length();
				float wantedInteractDistance = 1000.f;
				wantedInteractDistance = IInteractInterface::Execute_GetInteractDistance(Hit.GetActor());
				
				if (Hit.GetActor() != InteractActor.Get())
				{
					if (currentInteractDistance <= wantedInteractDistance)
					{
						if (AActor* InteractActorPtr = InteractActor.Get())
						{
							IInteractInterface::Execute_LookAway(InteractActorPtr);
						}
						InteractActor = Hit.GetActor();
						AActor* LookedAtActor = IInteractInterface::Execute_LookAt(InteractActor.Get());
						ItemLookedAt.Broadcast(Hit.GetActor());
					}
				}
				else
				{
					if (currentInteractDistance > wantedInteractDistance)
					{
						IInteractInterface::Execute_LookAway(InteractActor.Get());
						LookedAway.Broadcast();
						InteractActor = nullptr;
					}
				}
			}
			else
			{
				if (AActor* InteractActorPtr = InteractActor.Get())
				{
					IInteractInterface::Execute_LookAt(InteractActorPtr);
					//InteractActorPtr = nullptr;
				}
				InteractActor = nullptr;
			}
		}
		else
		{
			if (AActor* InteractActorPtr = InteractActor.Get())
			{
				IInteractInterface::Execute_LookAway(InteractActorPtr);
			}
			InteractActor = nullptr;
		}
	}
}

void UInteract::InteractWith(UObject* Instigator)
{
	if (AActor* InteractActorPtr = InteractActor.Get())
	{
		IInteractInterface::Execute_InteractWith(InteractActorPtr, Instigator);
		ItemInteractedWith.Broadcast(InteractActorPtr);
	}
}


// Called every frame
void UInteract::TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction)
{
	Super::TickComponent(DeltaTime, TickType, ThisTickFunction);

	InteractTrace();
}

