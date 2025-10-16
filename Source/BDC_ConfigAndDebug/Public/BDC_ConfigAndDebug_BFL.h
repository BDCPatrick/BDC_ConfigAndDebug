/* Copyright © beginning at 2025 - BlackDevilCreations
* Author: Patrick Wenzel
  * All rights reserved.
  * * This file and the corresponding Definition is part of a BlackDevilCreations project and may not be distributed, copied,
  * or modified without prior written permission from BlackDevilCreations.
  * * Unreal Engine and its associated trademarks are property of Epic Games, Inc.
  * and are used with permission.
*/
#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "Kismet/BlueprintFunctionLibrary.h"
#include "BDC_ConfigAndDebug_BFL.generated.h"

UCLASS()
class BDC_CONFIGANDDEBUG_API UBDC_ConfigAndDebug_BFL : public UBlueprintFunctionLibrary
{
	GENERATED_BODY()

public:
	/**
	 * Renders a UUserWidget instance to a UTexture2D and optionally exports it as a PNG file.
	 * @param TargetWidget The widget instance to be rendered.
	 * @param TargetFilePath The absolute path including the filename (e.g., "C:/MyFolder/MyImage.png"). If empty, the widget is only rendered to the UTexture2D and not saved to disk. ".png" will be added if missing.
	 * @param RenderedWidget The resulting UTexture2D object of the rendered widget.
	 * @return True if the widget was successfully rendered to Texture2D and optionally saved to PNG, false otherwise.
	 */
	UFUNCTION(BlueprintCallable, Category = "BDC | ConfigAndDebug | Widget", meta=(HidePin="RenderedWidget", DefaultToSelf="TargetWidget"))
	static bool ExportWidgetToPNG(UUserWidget* TargetWidget, const FString& TargetFilePath, UTexture2D*& RenderedWidget);

	/**
	 * Renders a UUserWidget subclass (hard reference) by instantiating it temporarily, then renders it to a UTexture2D and optionally exports it as a PNG file.
	 * @param TargetWidgetClass The subclass of UUserWidget to be rendered (hard reference, e.g., a Blueprint class reference).
	 * @param TargetFilePath The absolute path including the filename (e.g., "C:/MyFolder/MyImage.png"). If empty, the widget is only rendered to the UTexture2D and not saved to disk. ".png" will be added if missing.
	 * @param RenderedWidget The resulting UTexture2D object of the rendered widget.
	 * @return True if the widget class was successfully instantiated, rendered to Texture2D and optionally saved to PNG, false otherwise.
	 */
	UFUNCTION(BlueprintCallable, Category = "BDC | ConfigAndDebug | Widget")
	static bool ExportWidgetClassToPNG(TSubclassOf<UUserWidget> TargetWidgetClass, const FString& TargetFilePath, UTexture2D*& RenderedWidget);

	/**
	 * Recursively scans the project Content folder (/Game) and returns all UUserWidget classes and their asset names.
	 * @param WidgetClasses Array of found widget classes (hard references loaded at call time).
	 * @param AssetNames Array of corresponding asset names for each class.
	 */
	UFUNCTION(BlueprintCallable, Category = "BDC | ConfigAndDebug | Widget")
	static void GetAllWidgets(TArray<TSubclassOf<UUserWidget>>& WidgetClasses, TArray<FName>& AssetNames);
};