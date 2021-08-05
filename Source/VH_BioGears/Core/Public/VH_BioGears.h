#pragma once

// Engine
#include "Engine.h"
#include "Interfaces/IPluginManager.h"

// VH BioGears Plugin
#include "VH_BioGearsModule.h"


DECLARE_LOG_CATEGORY_EXTERN(VH_BioGears, Log, All);
DECLARE_LOG_CATEGORY_EXTERN(VH_BioGearsScenario, Log, All);
DECLARE_LOG_CATEGORY_EXTERN(VH_BioGearsThread, Log, All);


class FVH_BioGearsModule : public IVH_BioGearsModule
{
	// ---------------------------------
	// --- Variables
	// ---------------------------------

private:
	TArray<void*> DllHandles;


	// ---------------------------------
	// --- Inherited (FRunnable)
	// ---------------------------------

public:
	// This code will execute after your module is loaded into memory (but after global variables are initialized, of course)
	// The exact timing is specified in the.uplugin file per-module
	virtual void StartupModule() override;

	// This function may be called during shutdown to clean up your module.  For modules that support dynamic reloading,
	// we call this function before unloading the module.
	virtual void ShutdownModule() override;
};
