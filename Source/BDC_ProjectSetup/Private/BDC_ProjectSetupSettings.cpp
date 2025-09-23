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
#include "BDC_ProjectSetupSettings.h"
#include "Engine/World.h"
#include "GameplayTagContainer.h"

void UBDC_ProjectSetupSettings::SaveToProjectDefaultConfig()
{
	TryUpdateDefaultConfigFile();
}

UBDC_ProjectSetupSettings::UBDC_ProjectSetupSettings()
{
	CategoryName = TEXT("Plugins");
	SectionName = TEXT("BDC Project Setup");
	
	ENum_ProjectSetupType = ENum_ProjectSetupType::Setup_Debug;
	OverlayHotkey = EKeys::Hash;
}