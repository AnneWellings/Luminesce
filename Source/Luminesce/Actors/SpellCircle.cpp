// Fill out your copyright notice in the Description page of Project Settings.


#include "SpellCircle.h"


// Sets default values
ASpellCircle::ASpellCircle()
{
	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	Arrow = CreateDefaultSubobject<UArrowComponent>(TEXT("Arrow"));
	SetRootComponent(Arrow);

	SpellCircleDecal = CreateDefaultSubobject<UDecalComponent>(TEXT("SpellCircleDecal"));
	SpellCircleDecal->SetupAttachment(RootComponent);
	SpellCircleDecal->SetDecalMaterial(SpellCircleDecalMat);

	//Setup();
}

/*
void ASpellCircle::Setup()
{
	SpawnCandles();
}
*/

/*void ASpellCircle::SpawnCandles()
{
	if (CandleClass != nullptr)
	{
		for (int i = 0; i < CandleCount; i++)
		{
			float x = CircleRadius*cos(((2*PI)/CandleCount)*i);
			float y = CircleRadius*sin(((2*PI)/CandleCount)*i);
			FVector CandleLocation = FVector(x,y,0);
			CandleLocation += GetActorLocation();
			FActorSpawnParameters SpawnParams;

			Candles.Add(GetWorld()->SpawnActor<ALite>(CandleClass, CandleLocation, FRotator(0.f),SpawnParams));
		}
	}
}*/


// Called when the game starts or when spawned
void ASpellCircle::BeginPlay()
{
	Super::BeginPlay();
	
}

// Called every frame
void ASpellCircle::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
}

