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
#include "BDC_ProjectSetupConfig.h"
#include "GeneralProjectSettings.h"
#include "MoviePlayerSettings.h"
#include "Engine/UserInterfaceSettings.h"

//~ Getters
// =================================================================================================

void UBDC_ProjectSetupConfig::GetProjectName(FText& AsText, FString& AsString)
{
	if (const UGeneralProjectSettings* Settings = GetDefault<UGeneralProjectSettings>())
	{
		AsString = Settings->ProjectName;
		AsText = FText::FromString(AsString);
	}
}

void UBDC_ProjectSetupConfig::GetProjectDescription(FText& AsText, FString& AsString)
{
	if (const UGeneralProjectSettings* Settings = GetDefault<UGeneralProjectSettings>())
	{
		AsString = Settings->Description;
		AsText = FText::FromString(AsString);
	}
}

void UBDC_ProjectSetupConfig::GetProjectID(FText& AsText, FString& AsString)
{
	if (const UGeneralProjectSettings* Settings = GetDefault<UGeneralProjectSettings>())
	{
		AsString = Settings->ProjectID.ToString();
		AsText = FText::FromString(AsString);
	}
}

void UBDC_ProjectSetupConfig::GetProjectVersion(FText& AsText, FString& AsString)
{
	if (const UGeneralProjectSettings* Settings = GetDefault<UGeneralProjectSettings>())
	{
		AsString = Settings->ProjectVersion;
		AsText = FText::FromString(AsString);
	}
}

void UBDC_ProjectSetupConfig::GetProjectCompany(FText& AsText, FString& AsString)
{
	if (const UGeneralProjectSettings* Settings = GetDefault<UGeneralProjectSettings>())
	{
		AsString = Settings->CompanyName;
		AsText = FText::FromString(AsString);
	}
}

void UBDC_ProjectSetupConfig::GetProjectCompanyDistinguished(FText& AsText, FString& AsString)
{
	if (const UGeneralProjectSettings* Settings = GetDefault<UGeneralProjectSettings>())
	{
		AsString = Settings->CompanyDistinguishedName;
		AsText = FText::FromString(AsString);
	}
}

void UBDC_ProjectSetupConfig::GetProjectHomepage(FText& AsText, FString& AsString)
{
	if (const UGeneralProjectSettings* Settings = GetDefault<UGeneralProjectSettings>())
	{
		AsString = Settings->Homepage;
		AsText = FText::FromString(AsString);
	}
}

void UBDC_ProjectSetupConfig::GetProjectSupportContact(FText& AsText, FString& AsString)
{
	if (const UGeneralProjectSettings* Settings = GetDefault<UGeneralProjectSettings>())
	{
		AsString = Settings->SupportContact;
		AsText = FText::FromString(AsString);
	}
}

void UBDC_ProjectSetupConfig::GetProjectCopyright(FText& AsText, FString& AsString)
{
	if (const UGeneralProjectSettings* Settings = GetDefault<UGeneralProjectSettings>())
	{
		AsString = Settings->CopyrightNotice;
		AsText = FText::FromString(AsString);
	}
}

void UBDC_ProjectSetupConfig::GetProjectLicense(FText& AsText, FString& AsString)
{
	if (const UGeneralProjectSettings* Settings = GetDefault<UGeneralProjectSettings>())
	{
		AsString = Settings->LicensingTerms;
		AsText = FText::FromString(AsString);
	}
}

void UBDC_ProjectSetupConfig::GetProjectPrivacyPolicy(FText& AsText, FString& AsString)
{
	if (const UGeneralProjectSettings* Settings = GetDefault<UGeneralProjectSettings>())
	{
		AsString = Settings->PrivacyPolicy;
		AsText = FText::FromString(AsString);
	}
}

void UBDC_ProjectSetupConfig::GetProjectWindowPreserveAspect(bool& Value)
{
	if (const UUserInterfaceSettings* Settings = GetDefault<UUserInterfaceSettings>())
	{
		Value = Settings->RenderFocusRule == ERenderFocusRule::Always;
	}
	else
	{
		Value = false;
	}
}

void UBDC_ProjectSetupConfig::GetProjectWindowBorderless(bool& Value)
{
	if (const UGeneralProjectSettings* Settings = GetDefault<UGeneralProjectSettings>())
	{
		Value = Settings->bUseBorderlessWindow;
	}
	else
	{
		Value = false;
	}
}

void UBDC_ProjectSetupConfig::GetProjectWindowStartAsVR(bool& Value)
{
	if (const UGeneralProjectSettings* Settings = GetDefault<UGeneralProjectSettings>())
	{
		Value = Settings->bStartInVR;
	}
	else
	{
		Value = false;
	}
}

void UBDC_ProjectSetupConfig::GetProjectWindowAllowResize(bool& Value)
{
	if (const UGeneralProjectSettings* Settings = GetDefault<UGeneralProjectSettings>())
	{
		Value = Settings->bAllowWindowResize;
	}
	else
	{
		Value = false;
	}
}

void UBDC_ProjectSetupConfig::GetProjectWindowAllowClose(bool& Value)
{
	if (const UGeneralProjectSettings* Settings = GetDefault<UGeneralProjectSettings>())
	{
		Value = Settings->bAllowClose;
	}
	else
	{
		Value = false;
	}
}

void UBDC_ProjectSetupConfig::GetProjectWindowAllowMaximize(bool& Value)
{
	if (const UGeneralProjectSettings* Settings = GetDefault<UGeneralProjectSettings>())
	{
		Value = Settings->bAllowMaximize;
	}
	else
	{
		Value = false;
	}
}

void UBDC_ProjectSetupConfig::GetProjectMoviesAreSkippable(bool& Value)
{
	if (const UMoviePlayerSettings* Settings = GetDefault<UMoviePlayerSettings>())
	{
		Value = Settings->bMoviesAreSkippable;
	}
	else
	{
		Value = true;
	}
}

void UBDC_ProjectSetupConfig::GetProjectMoviesWaitForCompletion(bool& Value)
{
	if (const UMoviePlayerSettings* Settings = GetDefault<UMoviePlayerSettings>())
	{
		Value = Settings->bWaitForMoviesToComplete;
	}
	else
	{
		Value = true;
	}
}

//~ Setters
// =================================================================================================

#if WITH_EDITOR

void UBDC_ProjectSetupConfig::SetProjectName(const FString& FromString)
{
	if (UGeneralProjectSettings* Settings = GetMutableDefault<UGeneralProjectSettings>())
	{
		Settings->ProjectName = FromString;
		Settings->TryUpdateDefaultConfigFile();
	}
}

void UBDC_ProjectSetupConfig::SetProjectDescription(const FString& FromString)
{
	if (UGeneralProjectSettings* Settings = GetMutableDefault<UGeneralProjectSettings>())
	{
		Settings->Description = FromString;
		Settings->TryUpdateDefaultConfigFile();
	}
}

void UBDC_ProjectSetupConfig::SetProjectID(const FString& FromString)
{
	if (UGeneralProjectSettings* Settings = GetMutableDefault<UGeneralProjectSettings>())
	{
		if (FGuid NewGuid; FGuid::ParseExact(FromString, EGuidFormats::DigitsWithHyphens, NewGuid))
		{
			Settings->ProjectID = NewGuid;
		}
		Settings->TryUpdateDefaultConfigFile();
	}
}

void UBDC_ProjectSetupConfig::SetProjectVersion(const FString& FromString)
{
	if (UGeneralProjectSettings* Settings = GetMutableDefault<UGeneralProjectSettings>())
	{
		Settings->ProjectVersion = FromString;
		Settings->TryUpdateDefaultConfigFile();
	}
}

void UBDC_ProjectSetupConfig::SetProjectCompany(const FString& FromString)
{
	if (UGeneralProjectSettings* Settings = GetMutableDefault<UGeneralProjectSettings>())
	{
		Settings->CompanyName = FromString;
		Settings->TryUpdateDefaultConfigFile();
	}
}

void UBDC_ProjectSetupConfig::SetProjectCompanyDistinguished(const FString& FromString)
{
	if (UGeneralProjectSettings* Settings = GetMutableDefault<UGeneralProjectSettings>())
	{
		Settings->CompanyDistinguishedName = FromString;
		Settings->TryUpdateDefaultConfigFile();
	}
}

void UBDC_ProjectSetupConfig::SetProjectHomepage(const FString& FromString)
{
	if (UGeneralProjectSettings* Settings = GetMutableDefault<UGeneralProjectSettings>())
	{
		Settings->Homepage = FromString;
		Settings->TryUpdateDefaultConfigFile();
	}
}

void UBDC_ProjectSetupConfig::SetProjectSupportContact(const FString& FromString)
{
	if (UGeneralProjectSettings* Settings = GetMutableDefault<UGeneralProjectSettings>())
	{
		Settings->SupportContact = FromString;
		Settings->TryUpdateDefaultConfigFile();
	}
}

void UBDC_ProjectSetupConfig::SetProjectCopyright(const FString& FromString)
{
	if (UGeneralProjectSettings* Settings = GetMutableDefault<UGeneralProjectSettings>())
	{
		Settings->CopyrightNotice = FromString;
		Settings->TryUpdateDefaultConfigFile();
	}
}

void UBDC_ProjectSetupConfig::SetProjectLicense(const FString& FromString)
{
	if (UGeneralProjectSettings* Settings = GetMutableDefault<UGeneralProjectSettings>())
	{
		Settings->LicensingTerms = FromString;
		Settings->TryUpdateDefaultConfigFile();
	}
}

void UBDC_ProjectSetupConfig::SetProjectPrivacyPolicy(const FString& FromString)
{
	if (UGeneralProjectSettings* Settings = GetMutableDefault<UGeneralProjectSettings>())
	{
		Settings->PrivacyPolicy = FromString;
		Settings->TryUpdateDefaultConfigFile();
	}
}

void UBDC_ProjectSetupConfig::SetProjectWindowPreserveAspect(bool bNewValue)
{
	if (UUserInterfaceSettings* Settings = GetMutableDefault<UUserInterfaceSettings>())
	{
		Settings->RenderFocusRule = bNewValue 
			? ERenderFocusRule::Always 
			: ERenderFocusRule::Never;
		Settings->TryUpdateDefaultConfigFile();
	}
}

void UBDC_ProjectSetupConfig::SetProjectWindowBorderless(const bool bNewValue)
{
	if (UGeneralProjectSettings* Settings = GetMutableDefault<UGeneralProjectSettings>())
	{
		Settings->bUseBorderlessWindow = bNewValue;
		Settings->TryUpdateDefaultConfigFile();
	}
}

void UBDC_ProjectSetupConfig::SetProjectWindowStartAsVR(const bool bNewValue)
{
	if (UGeneralProjectSettings* Settings = GetMutableDefault<UGeneralProjectSettings>())
	{
		Settings->bStartInVR = bNewValue;
		Settings->TryUpdateDefaultConfigFile();
	}
}

void UBDC_ProjectSetupConfig::SetProjectWindowAllowResize(const bool bNewValue)
{
	if (UGeneralProjectSettings* Settings = GetMutableDefault<UGeneralProjectSettings>())
	{
		Settings->bAllowWindowResize = bNewValue;
		Settings->TryUpdateDefaultConfigFile();
	}
}

void UBDC_ProjectSetupConfig::SetProjectWindowAllowClose(const bool bNewValue)
{
	if (UGeneralProjectSettings* Settings = GetMutableDefault<UGeneralProjectSettings>())
	{
		Settings->bAllowClose = bNewValue;
		Settings->TryUpdateDefaultConfigFile();
	}
}

void UBDC_ProjectSetupConfig::SetProjectWindowAllowMaximize(const bool bNewValue)
{
	if (UGeneralProjectSettings* Settings = GetMutableDefault<UGeneralProjectSettings>())
	{
		Settings->bAllowMaximize = bNewValue;
		Settings->TryUpdateDefaultConfigFile();
	}
}

void UBDC_ProjectSetupConfig::SetProjectMoviesAreSkippable(const bool bNewValue)
{
	if (UMoviePlayerSettings* Settings = GetMutableDefault<UMoviePlayerSettings>())
	{
		Settings->bMoviesAreSkippable = bNewValue;
		Settings->TryUpdateDefaultConfigFile();
	}
}

void UBDC_ProjectSetupConfig::SetProjectMoviesWaitForCompletion(const bool bNewValue)
{
	if (UMoviePlayerSettings* Settings = GetMutableDefault<UMoviePlayerSettings>())
	{
		Settings->bWaitForMoviesToComplete = bNewValue;
		Settings->TryUpdateDefaultConfigFile();
	}
}

#endif