#pragma once

// Engine
#include "Engine.h"
#include "Interfaces/IPluginManager.h"

// VH BioGears Plugin
#include "IBioGears_UE4Module.h"


DECLARE_LOG_CATEGORY_EXTERN(BioGears, Log, All);
DECLARE_LOG_CATEGORY_EXTERN(BioGearsThread, Log, All);


class FBioGears_UE4Module : public IBioGears_UE4Module
{
	// ---------------------------------
	// --- Member Variables
	// ---------------------------------

private:
	TArray<void*> DllHandles;


	// ---------------------------------
	// --- Inherited Methods (FRunnable)
	// ---------------------------------

public:
	// This code will execute after your module is loaded into memory (but after global variables are initialized, of course)
	// The exact timing is specified in the.uplugin file per-module
	virtual void StartupModule() override;

	// This function may be called during shutdown to clean up your module.  For modules that support dynamic reloading,
	// we call this function before unloading the module.
	virtual void ShutdownModule() override;
};
