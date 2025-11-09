// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "UObject/Interface.h"
#include "Luminesce/Lites/LiteData.h"
#include "Luminesce/Lites/Lite.h"
#include "Luminesce/Halo/Marble.h"
#include "HaloInterface.generated.h"

// This class does not need to be modified.
UINTERFACE()
class UHaloInterface : public UInterface
{
	GENERATED_BODY()
};

/**
 * 
 */
class LUMINESCE_API IHaloInterface
{
	GENERATED_BODY()

	// Add interface functions to this class. This is the class that will be inherited to implement this interface.
public:

	UFUNCTION(BlueprintCallable, BlueprintNativeEvent, Category = Halo)
	ELiteColor TakeLight(FVector LightSourceLocation);

	UFUNCTION(BlueprintCallable, BlueprintNativeEvent, Category = Halo)
	void GiveLight(ELiteColor LiteColor, ALite* SourceLite);

	UFUNCTION(BlueprintCallable, BlueprintNativeEvent, Category = Halo)
	bool HasSpace();

	UFUNCTION(BlueprintCallable, BlueprintNativeEvent, Category = Halo)
	bool HasLight();

	UFUNCTION(BlueprintCallable, BlueprintNativeEvent, Category = Halo)
	bool HasRainbow();

	UFUNCTION(BlueprintCallable, BlueprintNativeEvent, Category = Halo)
	void AddMarble(AMarble* NewMarble);
	
};
