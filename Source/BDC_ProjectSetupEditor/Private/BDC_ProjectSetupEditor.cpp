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

#define LOCTEXT_NAMESPACE "FBDC_ProjectSetupEditorModule"

class FOverlayCommands : public TCommands<FOverlayCommands>
{
public:
	FOverlayCommands(): TCommands<FOverlayCommands>(TEXT("BDC_ProjectSetup"), NSLOCTEXT("Contexts", "BDC_ProjectSetup",  "BDC Project Setup"), NAME_None, "EditorStyle")
	{
	}

	virtual void RegisterCommands() override
	{
		UI_COMMAND(ToggleOverlay, "Toggle Overlay", "Toggles the actor/function overlay.", EUserInterfaceActionType::Button, FInputChord());
	}

	TSharedPtr<FUICommandInfo> ToggleOverlay;
};

void FBDC_ProjectSetupEditorModule::StartupModule()
{
	// Register commands and bind hotkey
	FOverlayCommands::Register();
	PluginCommands = MakeShareable(new FUICommandList);

	const UBDC_ProjectSetupSettings* Settings = GetDefault<UBDC_ProjectSetupSettings>();
	const FInputChord Hotkey(Settings->OverlayHotkey);

	PluginCommands->MapAction(
		FOverlayCommands::Get().ToggleOverlay,
		FExecuteAction::CreateRaw(this, &FBDC_ProjectSetupEditorModule::ToggleOverlay),
		FCanExecuteAction(),
		FInputChord(Settings->OverlayHotkey)
	);

	// Register the command delegate with the level editor
	FLevelEditorModule& LevelEditorModule = FModuleManager::LoadModuleChecked<FLevelEditorModule>("LevelEditor");
	LevelEditorModule.GetGlobalLevelEditorActions()->ProcessCommandBindings(PluginCommands.ToSharedRef());
	
    // Register the toolbar widget
    FToolMenuOwnerScoped OwnerScoped(this);
    UToolMenu* ToolbarMenu = UToolMenus::Get()->ExtendMenu("LevelEditor.LevelEditorToolBar.PlayToolBar");
    FToolMenuSection& Section = ToolbarMenu->FindOrAddSection("Play");
    Section.AddEntry(FToolMenuEntry::InitWidget("ProjectSetupPlayWidget", SNew(SBDC_ProjectSetup_PlayWidget), FText::GetEmpty(), true, FToolMenuInsert("Play", EToolMenuInsertType::Before)));

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

	if (OverlayWidget->IsVisible())
	{
		GEngine->GameViewport->RemoveViewportWidgetContent(OverlayWidget.ToSharedRef());
	}
	else
	{
		GEngine->GameViewport->AddViewportWidgetContent(
			SNew(SWeakWidget)
			.PossiblyNullContent(OverlayWidget)
		);
		OverlayWidget->RefreshActorList();
	}
}

void FBDC_ProjectSetupEditorModule::ShutdownModule()
{
    UToolMenus::UnregisterOwner(this);
	FOverlayCommands::Unregister();
}

#undef LOCTEXT_NAMESPACE

IMPLEMENT_MODULE(FBDC_ProjectSetupEditorModule, BDC_ProjectSetupEditor);