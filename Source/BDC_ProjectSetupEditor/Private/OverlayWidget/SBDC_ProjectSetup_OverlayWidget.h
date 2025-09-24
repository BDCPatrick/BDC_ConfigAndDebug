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
#include "Widgets/SCompoundWidget.h"
#include "Async/Future.h"

// Forward declarations
class SScrollBox;
class SVerticalBox;

/**
 * A simple struct to hold information about an actor and its callable functions.
 */
struct FCallableActor
{
	TWeakObjectPtr<AActor> Actor;
	TArray<UFunction*> Functions;
};

class SBDC_ProjectSetup_OverlayWidget : public SCompoundWidget
{
public:
    SLATE_BEGIN_ARGS(SBDC_ProjectSetup_OverlayWidget) {}
    SLATE_END_ARGS()

    /** Constructs this widget with InArgs */
    void Construct(const FArguments& InArgs);
	
	/** Refreshes the list of actors and their functions asynchronously. */
	void RefreshActorList();

private:
	/** Called when the "Refresh" button is clicked. */
	FReply OnRefreshClicked();
	
	/** Called when a function button is clicked. */
	FReply OnFunctionButtonClicked(TWeakObjectPtr<AActor> Actor, UFunction* Function);

	/** Populates the actor list scrollbox based on the provided data. */
	void PopulateList(const TArray<FCallableActor>& CallableActors);

	/** The main scrollbox containing the list of actors. */
	TSharedPtr<SScrollBox> ActorListScrollBox;
	
	/** A future that represents the async refresh task. */
	TFuture<void> RefreshTaskFuture;
};