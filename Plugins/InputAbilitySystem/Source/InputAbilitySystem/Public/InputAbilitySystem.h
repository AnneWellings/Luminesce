// Copyright Epic Games, Inc. All Rights Reserved.

//https://www.youtube.com/playlist?list=PLnHeglBaPYu-XVKTntS2hoEUs7M4INBPx
//Sneaky Kitty
//Based off of this tutorial series

#pragma once

#include "Modules/ModuleManager.h"

class FInputAbilitySystemModule : public IModuleInterface
{
public:

	/** IModuleInterface implementation */
	virtual void StartupModule() override;
	virtual void ShutdownModule() override;
};
