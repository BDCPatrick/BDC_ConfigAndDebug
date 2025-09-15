#include "BDC_ProjectSetup.h"

#include "GeneralEngineSettings.h"
#include "GeneralProjectSettings.h"
#include "MoviePlayerSettings.h"
#include "Engine/UserInterfaceSettings.h"

//~ Getters
// =================================================================================================

void UBDC_ProjectSetup::GetProjectName(FText& AsText, FString& AsString)
{
	if (const UGeneralProjectSettings* Settings = GetDefault<UGeneralProjectSettings>())
	{
		AsString = Settings->ProjectName;
		AsText = FText::FromString(AsString);
	}
}

void UBDC_ProjectSetup::GetProjectDescription(FText& AsText, FString& AsString)
{
	if (const UGeneralProjectSettings* Settings = GetDefault<UGeneralProjectSettings>())
	{
		AsString = Settings->Description;
		AsText = FText::FromString(AsString);
	}
}

void UBDC_ProjectSetup::GetProjectID(FText& AsText, FString& AsString)
{
	if (const UGeneralProjectSettings* Settings = GetDefault<UGeneralProjectSettings>())
	{
		AsString = Settings->ProjectID.ToString();
		AsText = FText::FromString(AsString);
	}
}

void UBDC_ProjectSetup::GetProjectVersion(FText& AsText, FString& AsString)
{
	if (const UGeneralProjectSettings* Settings = GetDefault<UGeneralProjectSettings>())
	{
		AsString = Settings->ProjectVersion;
		AsText = FText::FromString(AsString);
	}
}

void UBDC_ProjectSetup::GetProjectCompany(FText& AsText, FString& AsString)
{
	if (const UGeneralProjectSettings* Settings = GetDefault<UGeneralProjectSettings>())
	{
		AsString = Settings->CompanyName;
		AsText = FText::FromString(AsString);
	}
}

void UBDC_ProjectSetup::GetProjectCompanyDistinguished(FText& AsText, FString& AsString)
{
	if (const UGeneralProjectSettings* Settings = GetDefault<UGeneralProjectSettings>())
	{
		AsString = Settings->CompanyDistinguishedName;
		AsText = FText::FromString(AsString);
	}
}

void UBDC_ProjectSetup::GetProjectHomepage(FText& AsText, FString& AsString)
{
	if (const UGeneralProjectSettings* Settings = GetDefault<UGeneralProjectSettings>())
	{
		AsString = Settings->Homepage;
		AsText = FText::FromString(AsString);
	}
}

void UBDC_ProjectSetup::GetProjectSupportContact(FText& AsText, FString& AsString)
{
	if (const UGeneralProjectSettings* Settings = GetDefault<UGeneralProjectSettings>())
	{
		AsString = Settings->SupportContact;
		AsText = FText::FromString(AsString);
	}
}

void UBDC_ProjectSetup::GetProjectCopyright(FText& AsText, FString& AsString)
{
	if (const UGeneralProjectSettings* Settings = GetDefault<UGeneralProjectSettings>())
	{
		AsString = Settings->CopyrightNotice;
		AsText = FText::FromString(AsString);
	}
}

void UBDC_ProjectSetup::GetProjectLicense(FText& AsText, FString& AsString)
{
	if (const UGeneralProjectSettings* Settings = GetDefault<UGeneralProjectSettings>())
	{
		AsString = Settings->LicensingTerms;
		AsText = FText::FromString(AsString);
	}
}

void UBDC_ProjectSetup::GetProjectPrivacyPolicy(FText& AsText, FString& AsString)
{
	if (const UGeneralProjectSettings* Settings = GetDefault<UGeneralProjectSettings>())
	{
		AsString = Settings->PrivacyPolicy;
		AsText = FText::FromString(AsString);
	}
}

void UBDC_ProjectSetup::GetProjectWindowPreserveAspect(bool& Value)
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

void UBDC_ProjectSetup::GetProjectWindowBorderless(bool& Value)
{
	if (GetDefault<UGeneralEngineSettings>())
	{
		GetProjectWindowBorderless(Value);
	}
	else
	{
		Value = false;
	}
}

void UBDC_ProjectSetup::GetProjectWindowStartAsVR(bool& Value)
{
	if (GetDefault<UGeneralEngineSettings>())
	{
		GetProjectWindowStartAsVR(Value);
	}
	else
	{
		Value = false;
	}
}

void UBDC_ProjectSetup::GetProjectWindowAllowResize(bool& Value)
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

void UBDC_ProjectSetup::GetProjectWindowAllowClose(bool& Value)
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

void UBDC_ProjectSetup::GetProjectWindowAllowMaximize(bool& Value)
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

void UBDC_ProjectSetup::GetProjectMoviesAreSkippable(bool& Value)
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

void UBDC_ProjectSetup::GetProjectMoviesWaitForCompletion(bool& Value)
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

void UBDC_ProjectSetup::SetProjectName(const FString& FromString)
{
	if (UGeneralProjectSettings* Settings = GetMutableDefault<UGeneralProjectSettings>())
	{
		Settings->ProjectName = FromString;
		Settings->SaveConfig();
	}
}

void UBDC_ProjectSetup::SetProjectDescription(const FString& FromString)
{
	if (UGeneralProjectSettings* Settings = GetMutableDefault<UGeneralProjectSettings>())
	{
		Settings->Description = FromString;
		Settings->SaveConfig();
	}
}

void UBDC_ProjectSetup::SetProjectID(const FString& FromString)
{
	if (UGeneralProjectSettings* Settings = GetMutableDefault<UGeneralProjectSettings>())
	{
		if (FGuid NewGuid; FGuid::ParseExact(FromString, EGuidFormats::DigitsWithHyphens, NewGuid))
		{
			Settings->ProjectID = NewGuid;
		}
		Settings->SaveConfig();
	}
}

void UBDC_ProjectSetup::SetProjectVersion(const FString& FromString)
{
	if (UGeneralProjectSettings* Settings = GetMutableDefault<UGeneralProjectSettings>())
	{
		Settings->ProjectVersion = FromString;
		Settings->SaveConfig();
	}
}

void UBDC_ProjectSetup::SetProjectCompany(const FString& FromString)
{
	if (UGeneralProjectSettings* Settings = GetMutableDefault<UGeneralProjectSettings>())
	{
		Settings->CompanyName = FromString;
		Settings->SaveConfig();
	}
}

void UBDC_ProjectSetup::SetProjectCompanyDistinguished(const FString& FromString)
{
	if (UGeneralProjectSettings* Settings = GetMutableDefault<UGeneralProjectSettings>())
	{
		Settings->CompanyDistinguishedName = FromString;
		Settings->SaveConfig();
	}
}

void UBDC_ProjectSetup::SetProjectHomepage(const FString& FromString)
{
	if (UGeneralProjectSettings* Settings = GetMutableDefault<UGeneralProjectSettings>())
	{
		Settings->Homepage = FromString;
		Settings->SaveConfig();
	}
}

void UBDC_ProjectSetup::SetProjectSupportContact(const FString& FromString)
{
	if (UGeneralProjectSettings* Settings = GetMutableDefault<UGeneralProjectSettings>())
	{
		Settings->SupportContact = FromString;
		Settings->SaveConfig();
	}
}

void UBDC_ProjectSetup::SetProjectCopyright(const FString& FromString)
{
	if (UGeneralProjectSettings* Settings = GetMutableDefault<UGeneralProjectSettings>())
	{
		Settings->CopyrightNotice = FromString;
		Settings->SaveConfig();
	}
}

void UBDC_ProjectSetup::SetProjectLicense(const FString& FromString)
{
	if (UGeneralProjectSettings* Settings = GetMutableDefault<UGeneralProjectSettings>())
	{
		Settings->LicensingTerms = FromString;
		Settings->SaveConfig();
	}
}

void UBDC_ProjectSetup::SetProjectPrivacyPolicy(const FString& FromString)
{
	if (UGeneralProjectSettings* Settings = GetMutableDefault<UGeneralProjectSettings>())
	{
		Settings->PrivacyPolicy = FromString;
		Settings->SaveConfig();
	}
}

void UBDC_ProjectSetup::SetProjectWindowPreserveAspect(bool bNewValue)
{
	if (UUserInterfaceSettings* Settings = GetMutableDefault<UUserInterfaceSettings>())
	{
		Settings->RenderFocusRule = bNewValue 
			? ERenderFocusRule::Always 
			: ERenderFocusRule::Never;
		Settings->SaveConfig();
	}
}

void UBDC_ProjectSetup::SetProjectWindowBorderless(const bool bNewValue)
{
	if (UGeneralEngineSettings* Settings = GetMutableDefault<UGeneralEngineSettings>())
	{
		SetProjectWindowBorderless(bNewValue);
		Settings->SaveConfig();
	}
}

void UBDC_ProjectSetup::SetProjectWindowStartAsVR(const bool bNewValue)
{
	if (UGeneralEngineSettings* Settings = GetMutableDefault<UGeneralEngineSettings>())
	{
		SetProjectWindowStartAsVR(bNewValue);
		Settings->SaveConfig();
	}
}

void UBDC_ProjectSetup::SetProjectWindowAllowResize(const bool bNewValue)
{
	if (UGeneralProjectSettings* Settings = GetMutableDefault<UGeneralProjectSettings>())
	{
		Settings->bAllowWindowResize = bNewValue;
		Settings->SaveConfig();
	}
}

void UBDC_ProjectSetup::SetProjectWindowAllowClose(const bool bNewValue)
{
	if (UGeneralProjectSettings* Settings = GetMutableDefault<UGeneralProjectSettings>())
	{
		Settings->bAllowClose = bNewValue;
		Settings->SaveConfig();
	}
}

void UBDC_ProjectSetup::SetProjectWindowAllowMaximize(const bool bNewValue)
{
	if (UGeneralProjectSettings* Settings = GetMutableDefault<UGeneralProjectSettings>())
	{
		Settings->bAllowMaximize = bNewValue;
		Settings->SaveConfig();
	}
}

void UBDC_ProjectSetup::SetProjectMoviesAreSkippable(const bool bNewValue)
{
	if (UMoviePlayerSettings* Settings = GetMutableDefault<UMoviePlayerSettings>())
	{
		Settings->bMoviesAreSkippable = bNewValue;
		Settings->SaveConfig();
	}
}

void UBDC_ProjectSetup::SetProjectMoviesWaitForCompletion(const bool bNewValue)
{
	if (UMoviePlayerSettings* Settings = GetMutableDefault<UMoviePlayerSettings>())
	{
		Settings->bWaitForMoviesToComplete = bNewValue;
		Settings->SaveConfig();
	}
}

#endif