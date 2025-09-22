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
#include "BDC_ProjectSetupEditor.h"
#include "Modules/ModuleManager.h"

#define LOCTEXT_NAMESPACE "FBDC_ProjectSetupEditorModule"

void FBDC_ProjectSetupEditorModule::StartupModule()
{
}

void FBDC_ProjectSetupEditorModule::ShutdownModule()
{
}

#undef LOCTEXT_NAMESPACE

IMPLEMENT_MODULE(FBDC_ProjectSetupEditorModule, BDC_ProjectSetupEditor);
