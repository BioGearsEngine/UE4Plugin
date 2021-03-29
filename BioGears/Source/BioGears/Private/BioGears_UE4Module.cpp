#include "BioGears_UE4Module.h"


DEFINE_LOG_CATEGORY(BioGears);
DEFINE_LOG_CATEGORY(BioGearsThread);

IMPLEMENT_MODULE(FBioGears_UE4Module, BioGears_UE4);

void FBioGears_UE4Module::StartupModule()
{

}

void FBioGears_UE4Module::ShutdownModule()
{
	/* Free DLL handles */
	for (auto dllHandle : DllHandles)
	{
		FPlatformProcess::FreeDllHandle(dllHandle);
	}

	DllHandles.Empty();
}
