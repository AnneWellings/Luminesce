// Fill out your copyright notice in the Description page of Project Settings.


#include "LiteFunctionLibrary.h"

FName ULiteFunctionLibrary::ColorEnumToName(ELiteColor LiteColor)
{
	return LiteColorEnumToName(LiteColor);
}

FLinearColor ULiteFunctionLibrary::GetLiteColorValue(ELiteColor LiteColor)
{
	return GetColorValue(LiteColor);
}


