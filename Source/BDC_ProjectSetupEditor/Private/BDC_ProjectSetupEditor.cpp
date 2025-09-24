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
#include "BDC_ProjectSetupSettings.h"
#include "LevelEditor.h"
#include "ToolMenus.h"
#include "PlayWidget/SBDC_ProjectSetup_PlayWidget.h"
#include "OverlayWidget/SBDC_ProjectSetup_OverlayWidget.h"
#include "Framework/Commands/Commands.h"
#include "Framework/Commands/UICommandInfo.h"
#include "Widgets/Docking/SDockTab.h"
#include "Editor/EditorEngine.h"
#include "Engine/Engine.h"
#include "Engine/GameViewportClient.h"
#include "Widgets/SWeakWidget.h"
#include "InputCoreTypes.h"
#include "Framework/Commands/InputBindingManager.h"
#include "Framework/Application/IInputProcessor.h"
#include "Framework/Application/SlateApplication.h"
#include "Widgets/SOverlay.h"

#define LOCTEXT_NAMESPACE "FBDC_ProjectSetupEditorModule"

class FOverlayCommands : public TCommands<FOverlayCommands>
{
public:
	FOverlayCommands(): TCommands<FOverlayCommands>(TEXT("BDC_ProjectSetup"), NSLOCTEXT("Contexts", "BDC_ProjectSetup",  "BDC Project Setup"), NAME_None, "EditorStyle")
	{
	}

	virtual void RegisterCommands() override
	{
		// Default chord is empty; we handle hotkey via input preprocessor using settings
		UI_COMMAND(ToggleOverlay, "Toggle Overlay", "Toggles the actor/function overlay.", EUserInterfaceActionType::Button, FInputChord());
	}

	TSharedPtr<FUICommandInfo> ToggleOverlay;
};

// Slate input processor to capture the overlay hotkey even when game viewport has focus
class FOverlayInputProcessor : public IInputProcessor
{
public:
	explicit FOverlayInputProcessor(FBDC_ProjectSetupEditorModule* InModule, FKey InKey)
		: ModulePtr(InModule), OverlayKey(InKey)
	{
	}

	virtual ~FOverlayInputProcessor() override = default;

	// Required by IInputProcessor in UE 5.6 (pure virtual)
	virtual void Tick(const float DeltaTime, FSlateApplication& SlateApp, TSharedRef<ICursor> Cursor) override {}

	virtual bool HandleKeyDownEvent(FSlateApplication& SlateApp, const FKeyEvent& InKeyEvent) override
	{
		if (InKeyEvent.GetKey() == OverlayKey)
		{
			if (ModulePtr)
			{
				ModulePtr->ToggleOverlay();
				return true;
			}
		}
		return false;
	}

private:
	FBDC_ProjectSetupEditorModule* ModulePtr = nullptr;
	FKey OverlayKey;
};

void FBDC_ProjectSetupEditorModule::StartupModule()
{
	// Register commands and bind hotkey
	FOverlayCommands::Register();
	PluginCommands = MakeShareable(new FUICommandList);

	const UBDC_ProjectSetupSettings* Settings = GetDefault<UBDC_ProjectSetupSettings>();

	// Read overlay key from settings
	OverlayKey = Settings ? Settings->OverlayHotkey : EKeys::Three;

	PluginCommands->MapAction(
		FOverlayCommands::Get().ToggleOverlay,
		FExecuteAction::CreateRaw(this, &FBDC_ProjectSetupEditorModule::ToggleOverlay)
	);

	// Register the command with the Level Editor's global actions so it works in editor and during PIE
	FLevelEditorModule& LevelEditorModule = FModuleManager::LoadModuleChecked<FLevelEditorModule>("LevelEditor");
	LevelEditorModule.GetGlobalLevelEditorActions()->Append(PluginCommands.ToSharedRef());

	// Register input preprocessor to catch the overlay key even when PIE has focus
	OverlayInputProcessor = MakeShared<FOverlayInputProcessor>(this, OverlayKey);
	FSlateApplication::Get().RegisterInputPreProcessor(OverlayInputProcessor.ToSharedRef());

    // Register the toolbar widget
    FToolMenuOwnerScoped OwnerScoped(this);
    UToolMenu* ToolbarMenu = UToolMenus::Get()->ExtendMenu("LevelEditor.LevelEditorToolBar.PlayToolBar");
    FToolMenuSection& Section = ToolbarMenu->FindOrAddSection("Play");
    Section.AddEntry(FToolMenuEntry::InitWidget("ProjectSetupPlayWidget", SNew(SBDC_ProjectSetup_PlayWidget), FText::GetEmpty(), true));

	// Create the overlay widget, but don't show it yet
	OverlayWidget = SNew(SBDC_ProjectSetup_OverlayWidget);
}

void FBDC_ProjectSetupEditorModule::ToggleOverlay()
{
	if (const UBDC_ProjectSetupSettings* Settings = GetDefault<UBDC_ProjectSetupSettings>())
	{
		if (Settings->CurrentPlayState != ENum_ProjectSetupType::Setup_Debug)
		{
			return;
		}
	}

	if (!OverlayWidget.IsValid() || !GEngine || !GEngine->GameViewport)
	{
		return;
	}

	if (bOverlayVisible)
	{
		if (OverlayContainer.IsValid())
		{
			GEngine->GameViewport->RemoveViewportWidgetContent(OverlayContainer.ToSharedRef());
			OverlayContainer.Reset();
		}
		bOverlayVisible = false;
	}
	else
	{
		SAssignNew(OverlayContainer, SOverlay)
		+ SOverlay::Slot()
		.HAlign(HAlign_Right)
		.VAlign(VAlign_Top)
		.Padding(FMargin(10.0f))
		[
			SNew(SWeakWidget)
			.PossiblyNullContent(OverlayWidget)
		];

		GEngine->GameViewport->AddViewportWidgetContent(OverlayContainer.ToSharedRef());
		bOverlayVisible = true;
		OverlayWidget->RefreshActorList();
	}
}

void FBDC_ProjectSetupEditorModule::ShutdownModule()
{
	// Unregister input preprocessor (only if Slate is still initialized)
	if (OverlayInputProcessor.IsValid())
	{
		if (FSlateApplication::IsInitialized())
		{
			FSlateApplication::Get().UnregisterInputPreProcessor(OverlayInputProcessor.ToSharedRef());
		}
		OverlayInputProcessor.Reset();
	}

	// Ensure we remove any overlay content from the viewport safely
	const bool bCanRemoveOverlay = bOverlayVisible && (GEngine != nullptr) && (GEngine->GameViewport != nullptr) && OverlayContainer.IsValid();
	if (bCanRemoveOverlay)
	{
		GEngine->GameViewport->RemoveViewportWidgetContent(OverlayContainer.ToSharedRef());
		OverlayContainer.Reset();
		bOverlayVisible = false;
	}

	UToolMenus::UnregisterOwner(this);
	FOverlayCommands::Unregister();
}

#undef LOCTEXT_NAMESPACE

IMPLEMENT_MODULE(FBDC_ProjectSetupEditorModule, BDC_ProjectSetupEditor);