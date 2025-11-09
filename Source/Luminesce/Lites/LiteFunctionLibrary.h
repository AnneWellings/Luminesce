// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Kismet/BlueprintFunctionLibrary.h"
#include "LiteData.h"
#include "LiteFunctionLibrary.generated.h"

/**
 * 
 */
UCLASS()
class LUMINESCE_API ULiteFunctionLibrary : public UBlueprintFunctionLibrary
{
	GENERATED_BODY()

	UFUNCTION(BlueprintCallable, BlueprintPure)
	static FName ColorEnumToName(ELiteColor LiteColor);

	UFUNCTION(BlueprintCallable, BlueprintPure)
	static FLinearColor GetLiteColorValue(ELiteColor LiteColor);
};
