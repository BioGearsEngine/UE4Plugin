#pragma once

#include "Modules/ModuleInterface.h"

// Engine
#include "Modules/ModuleManager.h"

class IVH_BioGearsModule : public IModuleInterface
{

public:
	/**
	 * Singleton-like access to this module's interface.  This is just for convenience!
	 * Beware of calling this during the shutdown phase, though.  Your module might have been unloaded already.
	 *
	 * @return Returns singleton instance, loading the module on demand if needed
	 */
	static inline IVH_BioGearsModule& Get()
	{
		return FModuleManager::LoadModuleChecked< IVH_BioGearsModule >("VH_BioGearsPlugin");
	}

	/**
	 * Checks to see if this module is loaded and ready.  It is only valid to call Get() if IsAvailable() returns true.
	 *
	 * @return True if the module is loaded and ready to use
	 */
	static inline bool IsAvailable()
	{
		return FModuleManager::Get().IsModuleLoaded("VH_BioGearsPlugin");
	}
};
