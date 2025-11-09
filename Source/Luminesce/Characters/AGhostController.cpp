// Fill out your copyright notice in the Description page of Project Settings.
#include "AGhostController.h"
#include "BehaviorTree/BlackboardComponent.h"
#include "BehaviorTree/Blackboard/BlackboardKeyType_Vector.h"
#include <BehaviorTree/Tasks/BTTask_RotateToFaceBBEntry.h>

namespace
{
	bool SetBlackboardKeySelectorProperty(
		UObject* Target,
		const FName& VarName,
		const FBlackboardKeySelector& NewValue)
	{
		if (Target)
		{
			if (const FStructProperty* Prop = FindFieldChecked<FStructProperty>(Target->GetClass(), VarName))
			{
				Prop->SetValue_InContainer(Target, &NewValue);
				return true;
			}
		}
		return false;
	}
}


// Sets default values
AAGhostController::AAGhostController()
{
	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	Perception = CreateDefaultSubobject<UAIPerceptionComponent>(TEXT("Perception"));

	//Initialize blackboard and behavior tree components
	BlackboardComponent = CreateDefaultSubobject<UBlackboardComponent>(TEXT("BlackboardComponent"));
	BehaviorTreeComponent = CreateDefaultSubobject<UBehaviorTreeComponent>(TEXT("BehaviorTreeComponent"));
}

// Called when the game starts or when spawned
void AAGhostController::BeginPlay()
{
	Super::BeginPlay();
	
}

void AAGhostController::OnPossess(APawn* NewPawn)
{
	Super::OnPossess(NewPawn);

	if (BehaviorTree)
		RunBehaviorTree(BehaviorTree);
}

// Called every frame
void AAGhostController::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
}

