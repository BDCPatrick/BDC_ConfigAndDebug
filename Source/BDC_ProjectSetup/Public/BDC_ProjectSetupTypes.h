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
 
 UENUM(BlueprintType)
 enum class ENum_ProjectSetupType : uint8
 {
	 Setup_Release UMETA(DisplayName="Release Play"),
	 Setup_Debug UMETA(DisplayName="Debug Play"),
	 Setup_DebugNo UMETA(DisplayName="Debug No Overlay")
 }
 
 UENUM(BlueprintType)
 enum class ENum_ProjectSetupOutExec : uint8
 {
	 Exec_Release UMETA(DisplayName="Release"),
	 Exec_Debug UMETA(DisplayName="Debug")
 }