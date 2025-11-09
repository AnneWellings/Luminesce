// Fill out your copyright notice in the Description page of Project Settings.


#include "LiteData.h"


LiteData::LiteData()
{
}

LiteData::~LiteData()
{
}

FName LiteColorEnumToName(ELiteColor LiteColor)
{
	FName LiteColorName = FName("WHITE");
	switch (LiteColor)
	{
	case ELiteColor::RED:
		LiteColorName = FName("RED");
		break;
	case ELiteColor::YELLOW:
		LiteColorName = FName("YELLOW");
		break;
	case ELiteColor::GREEN:
		LiteColorName = FName("GREEN");
		break;
	case ELiteColor::BLUE:
		LiteColorName = FName("BLUE");
		break;
	case ELiteColor::CYAN:
		LiteColorName = FName("CYAN");
		break;
	case ELiteColor::MAGENTA:
		LiteColorName = FName("MAGENTA");
		break;
	case ELiteColor::NONE:
		LiteColorName = FName("NOCOLOR");
		break;
	//case default:
		//break;
		
	}
	return LiteColorName;
}


FLinearColor GetColorValue(ELiteColor LiteColor)
{
	UDataTable* ColorDataTable = LoadObject<UDataTable>(nullptr, TEXT("/Game/Blueprints/Data/LiteColorDT.LiteColorDT"));
	if (ColorDataTable != nullptr)
	{
		TArray<FName> Rows = ColorDataTable->GetRowNames();
		FName ColorName = LiteColorEnumToName(LiteColor);
		FLiteColor* RowColor = ColorDataTable->FindRow<FLiteColor>(ColorName, FString("stringy"),true);
		if (RowColor != nullptr)
		{
			return RowColor->Color;
		}
	}
	
	return FColor::White;
}

