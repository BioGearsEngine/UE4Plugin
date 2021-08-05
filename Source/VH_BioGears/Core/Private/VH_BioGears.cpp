#include "VH_BioGears.h"


DEFINE_LOG_CATEGORY(VH_BioGears);
DEFINE_LOG_CATEGORY(VH_BioGearsScenario);
DEFINE_LOG_CATEGORY(VH_BioGearsThread);

IMPLEMENT_MODULE(FVH_BioGearsModule, VH_BioGears);

void FVH_BioGearsModule::StartupModule()
{}

void FVH_BioGearsModule::ShutdownModule()
{
	/* Free DLL handles */
	for (auto dllHandle : DllHandles)
	{
		FPlatformProcess::FreeDllHandle(dllHandle);
	}

	DllHandles.Empty();
}
