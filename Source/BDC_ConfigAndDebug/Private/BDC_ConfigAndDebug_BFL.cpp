/* Copyright © beginning at 2025 - BlackDevilCreations
  * Author: Patrick Wenzel
  * All rights reserved.
  * * This file and the corresponding Definition is part of a BlackDevilCreations project and may not be distributed, copied,
  * or modified without prior written permission from BlackDevilCreations.
  * * Unreal Engine and its associated trademarks are property of Epic Games, Inc.
  * and are used with permission.
*/
#include "BDC_ConfigAndDebug_BFL.h"
#include "Rendering/SlateRenderer.h"
#include "Engine/TextureRenderTarget2D.h"
#include "IImageWrapper.h"
#include "IImageWrapperModule.h"
#include "Misc/FileHelper.h"
#include "Misc/Paths.h"
#include "HAL/FileManager.h"
#include "Blueprint/UserWidget.h"
#include "Blueprint/WidgetBlueprintLibrary.h"
#include "Blueprint/WidgetLayoutLibrary.h"
#include "Kismet/KismetRenderingLibrary.h"
#include "Slate/WidgetRenderer.h"
#include "Engine/GameViewportClient.h"
#include "Modules/ModuleManager.h"
#include "Engine/Engine.h"
#include "Engine/Texture2D.h"
#include "AssetRegistry/AssetRegistryModule.h"
#include "AssetRegistry/AssetData.h"
#include "RenderingThread.h"
#include "Framework/Application/SlateApplication.h"

bool UBDC_ConfigAndDebug_BFL::ExportWidgetToPNG(UUserWidget* TargetWidget, const FString& TargetFilePath, UTexture2D*& RenderedWidget)
{
	RenderedWidget = nullptr;

	if (!IsValid(TargetWidget))
	{
		UE_LOG(LogTemp, Error, TEXT("ExportWidgetToPNG failed: TargetWidget is null or invalid."));
		return false;
	}

	if (!TargetWidget->GetWorld())
	{
		UE_LOG(LogTemp, Error, TEXT("ExportWidgetToPNG failed: Widget has no valid World."));
		return false;
	}

	const TSharedRef<SWidget> SlateWidget = TargetWidget->TakeWidget();
	SlateWidget->SlatePrepass();
	FVector2D DesiredSize = SlateWidget->GetDesiredSize();

	if (DesiredSize.IsNearlyZero())
	{
		TargetWidget->ForceLayoutPrepass();
		SlateWidget->SlatePrepass();
		DesiredSize = SlateWidget->GetDesiredSize();
	}

	FIntPoint RTSize(FMath::Max(0, FMath::RoundToInt(DesiredSize.X)), FMath::Max(0, FMath::RoundToInt(DesiredSize.Y)));
	if (RTSize.X <= 0 || RTSize.Y <= 0)
	{
		FIntPoint ViewSize = FIntPoint::ZeroValue;
		{
			const FVector2D ViewSizeF = UWidgetLayoutLibrary::GetViewportSize(TargetWidget);
			ViewSize = FIntPoint(FMath::RoundToInt(ViewSizeF.X), FMath::RoundToInt(ViewSizeF.Y));
		}
		if (ViewSize.X > 0 && ViewSize.Y > 0)
		{
			RTSize = ViewSize;
			UE_LOG(LogTemp, Verbose, TEXT("ExportWidgetToPNG: Desired size unavailable for %s; using viewport size %dx%d."), *TargetWidget->GetName(), RTSize.X, RTSize.Y);
		}
		else
		{
			RTSize = FIntPoint(512, 512);
			UE_LOG(LogTemp, Warning, TEXT("ExportWidgetToPNG: Could not determine widget size for %s; using fallback 512x512."), *TargetWidget->GetName());
		}
	}

	UTextureRenderTarget2D* RenderTarget = NewObject<UTextureRenderTarget2D>(TargetWidget);
	RenderTarget->RenderTargetFormat = RTF_RGBA8;
	RenderTarget->InitCustomFormat(RTSize.X, RTSize.Y, PF_B8G8R8A8, false);
	RenderTarget->ClearColor = FLinearColor::Transparent;
	RenderTarget->UpdateResourceImmediate(true);

	{
		FWidgetRenderer WidgetRenderer(true);
		// Warm up a couple of ticks to let async bindings/constructs settle (useful for Editor Utility context)
		for (int32 TickIdx = 0; TickIdx < 2; ++TickIdx)
		{
			TargetWidget->ForceLayoutPrepass();
			SlateWidget->SlatePrepass();
			if (FSlateApplication::IsInitialized())
			{
				FSlateApplication::Get().Tick();
			}
			WidgetRenderer.DrawWidget(RenderTarget, SlateWidget, FVector2D(RTSize), 1.f / 60.f);
		}
	}

	// Ensure all render commands have been processed before reading back pixels
	FlushRenderingCommands();

	const FIntPoint DestSize(RenderTarget->SizeX, RenderTarget->SizeY);
	TArray<FColor> Pixels;

	if (const bool bReadOK = UKismetRenderingLibrary::ReadRenderTarget(TargetWidget, RenderTarget, Pixels); !bReadOK)
	{
		UE_LOG(LogTemp, Error, TEXT("ExportWidgetToPNG failed: Failed to read pixels from RenderTarget."));
		return false;
	}

	UTexture2D* NewTexture = UTexture2D::CreateTransient(DestSize.X, DestSize.Y, PF_B8G8R8A8);
	if (NewTexture)
	{
		NewTexture->SRGB = true;
		NewTexture->MipGenSettings = TMGS_NoMipmaps;
		NewTexture->CompressionSettings = TC_Default;

		FUpdateTextureRegion2D Region(0, 0, 0, 0, DestSize.X, DestSize.Y);
		const int32 DataSize = Pixels.Num() * sizeof(FColor);
		uint8* RawData = static_cast<uint8*>(FMemory::Malloc(DataSize));
		FMemory::Memcpy(RawData, Pixels.GetData(), DataSize);

		NewTexture->UpdateTextureRegions(0, 1, &Region, DestSize.X * sizeof(FColor), sizeof(FColor), RawData,
			[](uint8* SrcData, const FUpdateTextureRegion2D* /*Regions*/)
			{
				FMemory::Free(SrcData);
			});
		NewTexture->UpdateResource();
		RenderedWidget = NewTexture;
	}
	else
	{
		UE_LOG(LogTemp, Error, TEXT("ExportWidgetToPNG: Failed to create transient texture."));
	}

	const bool bRenderSuccessful = true;

	if (!TargetFilePath.IsEmpty())
	{
		FString FinalFilePath = TargetFilePath;
		if (FinalFilePath.EndsWith(TEXT("/")) || FinalFilePath.EndsWith(TEXT("\\")))
		{
			const FString DefaultName = TargetWidget && TargetWidget->GetClass() ? TargetWidget->GetClass()->GetName() : TEXT("WidgetRender");
			FinalFilePath += DefaultName;
		}
		if (!FinalFilePath.EndsWith(TEXT(".png"), ESearchCase::IgnoreCase))
		{
			FinalFilePath += TEXT(".png");
		}
		const FString TargetDir = FPaths::GetPath(FinalFilePath);
		if (!TargetDir.IsEmpty())
		{
			IFileManager::Get().MakeDirectory(*TargetDir, true);
		}

		IImageWrapperModule& ImageWrapperModule = FModuleManager::LoadModuleChecked<IImageWrapperModule>(TEXT("ImageWrapper"));
		TSharedPtr<IImageWrapper> ImageWrapper = ImageWrapperModule.CreateImageWrapper(EImageFormat::PNG);

		if (!ImageWrapper.IsValid())
		{
			UE_LOG(LogTemp, Error, TEXT("ExportWidgetToPNG failed: Failed to create PNG Image Wrapper."));
			return bRenderSuccessful;
		}

		ImageWrapper->SetRaw(Pixels.GetData(), Pixels.Num() * sizeof(FColor), DestSize.X, DestSize.Y, ERGBFormat::BGRA, 8);
		const TArray64<uint8>& CompressedData = ImageWrapper->GetCompressed();

		if (CompressedData.Num() == 0)
		{
			UE_LOG(LogTemp, Error, TEXT("ExportWidgetToPNG failed: Failed to compress image data to PNG."));
			return bRenderSuccessful;
		}

		if (!FFileHelper::SaveArrayToFile(CompressedData, *FinalFilePath))
		{
			UE_LOG(LogTemp, Error, TEXT("ExportWidgetToPNG failed: Failed to save PNG file to %s."), *FinalFilePath);
			return false;
		}
	}
	
	return bRenderSuccessful;
}

bool UBDC_ConfigAndDebug_BFL::ExportWidgetClassToPNG(TSubclassOf<UUserWidget> TargetWidgetClass, const FString& TargetFilePath, UTexture2D*& RenderedWidget)
{
	RenderedWidget = nullptr;

	if (!TargetWidgetClass)
	{
		UE_LOG(LogTemp, Error, TEXT("ExportWidgetClassToPNG failed: TargetWidgetClass is null."));
		return false;
	}

	UClass* WidgetClass = TargetWidgetClass.Get();

	if (!IsValid(WidgetClass))
	{
		UE_LOG(LogTemp, Error, TEXT("ExportWidgetClassToPNG failed: TargetWidgetClass is invalid."));
		return false;
	}
	
	UWorld* World = nullptr;
	if (GEngine)
	{
		for (const FWorldContext& Ctx : GEngine->GetWorldContexts())
		{
			if (Ctx.World() && (Ctx.WorldType == EWorldType::PIE || Ctx.WorldType == EWorldType::Game || Ctx.WorldType == EWorldType::Editor))
			{
				World = Ctx.World();
				break;
			}
		}
		if (!World && GEngine->GameViewport)
		{
			World = GEngine->GameViewport->GetWorld();
		}
	}
	if (!World && GWorld)
	{
		World = GWorld;
	}

	if (!World)
	{
		UE_LOG(LogTemp, Error, TEXT("ExportWidgetClassToPNG failed: Could not get a valid World context."));
		return false;
	}

	UUserWidget* TempWidget = CreateWidget<UUserWidget>(World, WidgetClass);

	if (!IsValid(TempWidget))
	{
		UE_LOG(LogTemp, Error, TEXT("ExportWidgetClassToPNG failed: Failed to instantiate widget of class %s."), *WidgetClass->GetName());
		return false;
	}
	
	TempWidget->ForceLayoutPrepass();

	const bool bSuccess = ExportWidgetToPNG(TempWidget, TargetFilePath, RenderedWidget);

	if (TempWidget)
	{
		TempWidget->MarkAsGarbage();
		TempWidget = nullptr;
	}
	
	return bSuccess;
}

void UBDC_ConfigAndDebug_BFL::GetAllWidgets(TArray<TSubclassOf<UUserWidget>>& WidgetClasses, TArray<FName>& AssetNames)
{
	WidgetClasses.Reset();
	AssetNames.Reset();

	FAssetRegistryModule& AssetRegistryModule = FModuleManager::LoadModuleChecked<FAssetRegistryModule>(TEXT("AssetRegistry"));
	IAssetRegistry& AssetRegistry = AssetRegistryModule.Get();

	AssetRegistry.WaitForCompletion();

	// Ensure the AssetRegistry has scanned the project content and then query all assets under /Game (recursive)
	TArray<FString> ScanPaths;
	ScanPaths.Add(TEXT("/Game"));
	AssetRegistry.ScanPathsSynchronous(ScanPaths, /*bForceRescan=*/true);
	AssetRegistry.WaitForCompletion();
	
	TArray<FAssetData> Assets;
	AssetRegistry.GetAssetsByPath(FName(TEXT("/Game")), Assets, /*bRecursive=*/true, /*bIncludeOnlyOnDiskAssets=*/false);

	for (const FAssetData& Asset : Assets)
	{
		FString ClassPathStr;
		if (!Asset.GetTagValue(FName(TEXT("GeneratedClassPath")), ClassPathStr)
			&& !Asset.GetTagValue(FName(TEXT("GeneratedClass")), ClassPathStr))
		{
			continue;
		}

		FString ObjectPath = ClassPathStr;
		int32 FirstQuoteIdx = INDEX_NONE;
		int32 LastQuoteIdx = INDEX_NONE;
		if (ObjectPath.FindChar('\'', FirstQuoteIdx) && ObjectPath.FindLastChar('\'', LastQuoteIdx) && LastQuoteIdx > FirstQuoteIdx)
		{
			ObjectPath = ObjectPath.Mid(FirstQuoteIdx + 1, LastQuoteIdx - FirstQuoteIdx - 1);
		}
		else
		{
			const FString Prefix1(TEXT("WidgetBlueprintGeneratedClass"));
			const FString Prefix2(TEXT("Class"));
			if (ObjectPath.StartsWith(Prefix1))
			{
				ObjectPath = ObjectPath.RightChop(Prefix1.Len());
				ObjectPath.TrimStartAndEndInline();
				if (ObjectPath.StartsWith(TEXT("'")) && ObjectPath.EndsWith(TEXT("'")) && ObjectPath.Len() > 2)
				{
					ObjectPath = ObjectPath.Mid(1, ObjectPath.Len() - 2);
				}
			}
			else if (ObjectPath.StartsWith(Prefix2))
			{
				ObjectPath = ObjectPath.RightChop(Prefix2.Len());
				ObjectPath.TrimStartAndEndInline();
				if (ObjectPath.StartsWith(TEXT("'")) && ObjectPath.EndsWith(TEXT("'")) && ObjectPath.Len() > 2)
				{
					ObjectPath = ObjectPath.Mid(1, ObjectPath.Len() - 2);
				}
			}
		}

		const FString AssetNameStr = Asset.AssetName.ToString();
		const FString ExpectedSuffix = FString::Printf(TEXT(".%s_C"), *AssetNameStr);
		int32 DotIdx = INDEX_NONE;
		if (!ObjectPath.FindLastChar('.', DotIdx))
		{
			ObjectPath = ObjectPath + ExpectedSuffix;
		}

		FSoftObjectPath SoftPath(ObjectPath);
		UClass* ResolvedClass = Cast<UClass>(SoftPath.TryLoad());
		if (ResolvedClass && ResolvedClass->IsChildOf(UUserWidget::StaticClass()))
		{
			WidgetClasses.Add(ResolvedClass);
			AssetNames.Add(Asset.AssetName);
		}
		else
		{
			UE_LOG(LogTemp, Warning, TEXT("GetAllWidgets: Failed to load widget class from path: %s (Asset: %s)"), *ObjectPath, *Asset.ObjectPath.ToString());
		}
	}

	if (WidgetClasses.Num() > 1 && AssetNames.Num() == WidgetClasses.Num())
	{
		TArray<int32> Indices;
		Indices.Reserve(AssetNames.Num());
		for (int32 i = 0; i < AssetNames.Num(); ++i)
		{
			Indices.Add(i);
		}

		Indices.Sort([&](int32 A, int32 B)
		{
			const FString NameA = AssetNames[A].ToString();
			const FString NameB = AssetNames[B].ToString();
			return NameA.Compare(NameB, ESearchCase::IgnoreCase) < 0;
		});

		TArray<TSubclassOf<UUserWidget>> SortedClasses;
		TArray<FName> SortedNames;
		SortedClasses.Reserve(WidgetClasses.Num());
		SortedNames.Reserve(AssetNames.Num());
		for (int32 Idx : Indices)
		{
			SortedClasses.Add(WidgetClasses[Idx]);
			SortedNames.Add(AssetNames[Idx]);
		}

		WidgetClasses = MoveTemp(SortedClasses);
		AssetNames = MoveTemp(SortedNames);
	}
}
