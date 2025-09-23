/* Copyright © beginning at 2025 - BlackDevilCreations
* Author: Patrick Wenzel
 * All rights reserved.
 *
 * This file is part of a BlackDevilCreations project and may not be distributed, copied,
 * or modified without prior written permission from BlackDevilCreations.
 *
 * Unreal Engine and its associated trademarks are property of Epic Games, Inc.
 * and are used with permission.
 */
#include "BDC_ProjectSetup.h"
#include "Modules/ModuleManager.h"

#define LOCTEXT_NAMESPACE "FBDC_ProjectSetupModule"

void FBDC_ProjectSetupModule::StartupModule()
{
}

void FBDC_ProjectSetupModule::ShutdownModule()
{
}

#undef LOCTEXT_NAMESPACE

IMPLEMENT_MODULE(FBDC_ProjectSetupModule, BDC_ProjectSetup);
