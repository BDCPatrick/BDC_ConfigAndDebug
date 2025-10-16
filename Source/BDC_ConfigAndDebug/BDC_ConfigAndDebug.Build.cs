/* Copyright © beginning at 2025 - BlackDevilCreations
 * Author: Patrick Wenzel
 * All rights reserved.
 * * This file is part of a BlackDevilCreations project and may not be distributed, copied,
 * or modified without prior written permission from BlackDevilCreations.
 * * Unreal Engine and its associated trademarks are property of Epic Games, Inc.
 * and are used with permission.
 */
using UnrealBuildTool;

public class BDC_ConfigAndDebug : ModuleRules
{
	public BDC_ConfigAndDebug(ReadOnlyTargetRules Target) : base(Target)
	{
		PCHUsage = PCHUsageMode.UseExplicitOrSharedPCHs;
		PrivatePCHHeaderFile = "Public/BDC_ConfigAndDebug.h";
		
		PublicDependencyModuleNames.AddRange(
			new string[]
			{
				"Core",
				"Engine",
				"InputCore"
			}
		);
			
		
		PrivateDependencyModuleNames.AddRange(
			new string[]
			{
				"CoreUObject",
				"Engine",
				"Slate",
				"SlateCore",
				"ApplicationCore",
				"UMG",
				"DeveloperSettings", 
				"MoviePlayer",
				"EngineSettings",
				"AssetRegistry",
				"RenderCore"
			}
		);
	}
}