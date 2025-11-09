// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "LiteData.generated.h"

UENUM(BlueprintType)
enum class ELiteColor : uint8
{
	NONE UMETA(DisplayName = "NONE"),
	WHITE UMETA(DisplayName = "White"),
	RED UMETA(DisplayName = "Red"),
	GREEN UMETA(DisplayName = "Green"),
	BLUE UMETA(DisplayName = "Blue"),
	CYAN UMETA(DisplayName = "Cyan"),
	MAGENTA UMETA(DisplayName = "Magenta"),
	YELLOW UMETA(DisplayName = "Yellow")
};

FName LiteColorEnumToName(ELiteColor LiteColor);

FLinearColor GetColorValue(ELiteColor LiteColor);

USTRUCT(BlueprintType)
struct FLiteColor : public FTableRowBase
{
	GENERATED_BODY()

public:
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	FLinearColor Color;

	FLiteColor()
	{
		Color = FColor::White;
	}
};

class LUMINESCE_API LiteData
{
public:
	LiteData();
	~LiteData();
};
