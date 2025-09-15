#include "BDC_ProjectSetupModule.h"
#define LOCTEXT_NAMESPACE "FBDC_ProjectSetupModule"

void FBDC_ProjectSetupModule::StartupModule()
{
}
void FBDC_ProjectSetupModule::ShutdownModule()
{
}

#undef LOCTEXT_NAMESPACE

IMPLEMENT_MODULE(FBDC_ProjectSetupModule, BDC_ProjectSetup)