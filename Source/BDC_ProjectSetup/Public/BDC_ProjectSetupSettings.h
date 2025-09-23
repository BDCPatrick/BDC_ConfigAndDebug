/* Copyright © beginning at 2025 - BlackDevilCreations
  * Author: Patrick Wenzel
  * All rights reserved.
  * 
  * This file and the corresponding Definition is part of a BlackDevilCreations project and may not be distributed, copied,
  * or modified without prior written permission from BlackDevilCreations.
  * 
  * Unreal Engine and its associated trademarks are property of Epic Games, Inc.
  * and are used with permission.
*/
#pragma once

#include "CoreMinimal.h"
#include "GameplayTagContainer.h"
#include "InputCoreTypes.h"
#include "Engine/DeveloperSettings.h"
#include "BDC_ProjectSetupTypes.h"
#include "BDC_ProjectSetupSettings.generated.h"

UCLASS(Config=Editor, DefaultConfig)
class BDC_PROJECTSETUP_API UBDC_ProjectSetupSettings : public UDeveloperSettings
{
	GENERATED_BODY()

public:
	UBDC_ProjectSetupSettings();

	UPROPERTY(Config, EditAnywhere, Category = "Project Setup")
	ENum_ProjectSetupType CurrentPlayState;
	
	UPROPERTY(Config, EditAnywhere, Category = "Project Setup")
	FKey OverlayHotkey;

	void SaveToProjectDefaultConfig()
}