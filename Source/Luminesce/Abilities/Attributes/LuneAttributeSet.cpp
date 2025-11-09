// Fill out your copyright notice in the Description page of Project Settings.


#include "LuneAttributeSet.h"

ULuneAttributeSet::ULuneAttributeSet()
{
	
}

void ULuneAttributeSet::GetLifetimeReplicatedProps(TArray<class FLifetimeProperty>& OutLifetimeProps) const
{
	Super::GetLifetimeReplicatedProps(OutLifetimeProps);

	//DOREPLIFETIME(ULuneAttributeSet, MarbleCount);
}

//void ULuneAttributeSet::OnRep_MarbleCount(const FGameplayAttribute& OldValue)
//{
//	GAMEPLAYATTRIBUTE_REPNOTIFY(ULuneAttributeSet, MarbleCount, OldValue);
//}


