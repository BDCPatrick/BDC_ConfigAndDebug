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
#pragma once
#include "CoreMinimal.h"
#include "Modules/ModuleInterface.h"
#include "Framework/Commands/UICommandList.h"

class SBDC_ProjectSetup_OverlayWidget;
class IInputProcessor;
class SOverlay;

class FBDC_ProjectSetupEditorModule : public IModuleInterface
{
public:
	virtual void StartupModule() override;
	virtual void ShutdownModule() override;

	/** Toggles the visibility of the overlay widget. */
	void ToggleOverlay();

private:

	/** The overlay widget instance. */
	TSharedPtr<SBDC_ProjectSetup_OverlayWidget> OverlayWidget;

	/** Command list for handling keybindings. */
	TSharedPtr<FUICommandList> PluginCommands;

	/** Tracks whether overlay is currently added to the viewport. */
	bool bOverlayVisible = false;

	/** The hotkey from settings. */
	FKey OverlayKey;

	/** Input preprocessor to catch the overlay key during PIE. */
	TSharedPtr<IInputProcessor> OverlayInputProcessor;

	/** Container added to the GameViewport to position the overlay top-right. */
	TSharedPtr<SOverlay> OverlayContainer;
};