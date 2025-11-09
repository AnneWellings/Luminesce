// Fill out your copyright notice in the Description page of Project Settings.


#include "MageLightAC.h"


// Sets default values for this component's properties
UMageLightAC::UMageLightAC()
{
	// Set this component to be initialized when the game starts, and to be ticked every frame.  You can turn these features
	// off to improve performance if you don't need them.
	PrimaryComponentTick.bCanEverTick = true;

	// ...
}


// Called when the game starts
void UMageLightAC::BeginPlay()
{
	Super::BeginPlay();

	// ...
	
}


// Called every frame
void UMageLightAC::TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction)
{
	Super::TickComponent(DeltaTime, TickType, ThisTickFunction);

}

void UMageLightAC::StartBeam(USceneComponent* AimComponent, FLinearColor BeamColor)
{
	if (!BeamActor.Get())
	{
		SavedBeamColor = BeamColor;

		if (bHasRainbow)
		{
			HandBurstNSComp = UNiagaraFunctionLibrary::SpawnSystemAttached(RainbowHandBurstNS, GetOwner()->GetRootComponent(), FName("none"),
				HaloActor->GetActorLocation(), GetOwner()->GetActorRotation(),EAttachLocation::KeepWorldPosition,false);
		
			HandLoopNSComp = UNiagaraFunctionLibrary::SpawnSystemAttached(RainbowHandLoopNS, GetOwner()->GetRootComponent(), FName("none"),
				HaloActor->GetActorLocation(), GetOwner()->GetActorRotation(), EAttachLocation::KeepWorldPosition,false);

			FActorSpawnParameters SpawnParams;
			BeamActor = GetWorld()->SpawnActor<AMLBeam>(RainbowBeamClass,HaloActor->GetActorLocation(),HaloActor->GetActorRotation(), SpawnParams);

			BeamActor->HitNS = RainbowHitNS;
			BeamActor->BeamDamageType = RainbowBeamDamageType;
			BeamActor->SourceComponent = HaloActor->GetRootComponent();
		}
		else
		{
			HandBurstNSComp = UNiagaraFunctionLibrary::SpawnSystemAttached(HandBurstNS, GetOwner()->GetRootComponent(), FName("none"),
				GetOwner()->GetActorLocation() + HandLoopLocOffset, GetOwner()->GetActorRotation(),EAttachLocation::KeepWorldPosition,false);
		
			HandLoopNSComp = UNiagaraFunctionLibrary::SpawnSystemAttached(HandLoopNS, GetOwner()->GetRootComponent(), FName("none"),
				GetOwner()->GetActorLocation() + HandLoopLocOffset, GetOwner()->GetActorRotation(), EAttachLocation::KeepWorldPosition,false);

			HandBurstNSComp->SetColorParameter("Color", BeamColor);
			HandLoopNSComp->SetColorParameter("Color", BeamColor);

			FActorSpawnParameters SpawnParams;
			BeamActor = GetWorld()->SpawnActor<AMLBeam>(BeamClass,AimComponent->GetComponentLocation(),AimComponent->GetComponentRotation(), SpawnParams);

			BeamActor->BeamColor = BeamColor;
			BeamActor->HitNS = HitNS;
			BeamActor->BeamDamageType = BeamDamageType;
			BeamActor->SourceComponent = GetOwner()->GetRootComponent();
		}
		
		BeamActor->AimComponent = AimComponent;
		//BeamActor->SourceComponent = GetOwner()->GetRootComponent();
		BeamActor->BeamRotSpeed = BeamRotSpeed;
		BeamActor->Setup();
		
	}
}

void UMageLightAC::EndBeam()
{
	
	if (IsValid(BeamActor))
	{
		BeamActor->Destroy();
		BeamActor = nullptr;

		if (HandBurstNSComp != nullptr)
			HandBurstNSComp->Deactivate();

		UNiagaraComponent* HandSparkComp = UNiagaraFunctionLibrary::SpawnSystemAttached(HandSparkNS, GetOwner()->GetRootComponent(), FName("none"),
			GetOwner()->GetActorLocation() + HandLoopLocOffset, GetOwner()->GetActorRotation(), EAttachLocation::KeepWorldPosition,false);
		HandSparkComp->SetColorParameter("Color", SavedBeamColor);
		
		if (HandLoopNSComp != nullptr)
		{
			HandLoopNSComp->Deactivate();
			HandLoopNSComp = nullptr;
		}
	}
}



