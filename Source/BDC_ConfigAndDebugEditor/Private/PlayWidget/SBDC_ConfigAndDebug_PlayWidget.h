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
#include "BDC_ConfigAndDebug_Types.h"
#include "Widgets/Input/SComboBox.h"

class SBDC_ConfigAndDebug_PlayWidget : public SCompoundWidget
{
public:
    SLATE_BEGIN_ARGS(SBDC_ConfigAndDebug_PlayWidget) {}
    SLATE_END_ARGS()

    /** Constructs this widget with InArgs */
    void Construct(const FArguments& InArgs);

private:
    /** Handles the selection change in the combo box. */
    void OnSelectionChanged(TSharedPtr<ENum_ProjectSetupType> NewSelection, ESelectInfo::Type SelectInfo);

    /** Generates a widget for an item in the combo box. */
    TSharedRef<SWidget> OnGenerateWidget(TSharedPtr<ENum_ProjectSetupType> InItem);

    /** Gets the text for the currently selected item. */
    FText GetCurrentItemLabel() const;
    
    /** Gets the display text for a given enum value. */
    FText GetEnumAsText(ENum_ProjectSetupType EnumValue) const;

    /** The options for the combo box. */
    TArray<TSharedPtr<ENum_ProjectSetupType>> ComboBoxOptions;

    /** The combo box widget. */
    TSharedPtr<SComboBox<TSharedPtr<ENum_ProjectSetupType>>> ComboBox;
};