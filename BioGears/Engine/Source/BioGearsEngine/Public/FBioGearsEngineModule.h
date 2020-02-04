// Copyright 1998-2019 Epic Games, Inc. All Rights Reserved.

#pragma once


class FBioGearsEngineModule : public IModuleInterface
{
public:

	/** IModuleInterface implementation */
	virtual void StartupModule() override;
	virtual void ShutdownModule() override;

    /**
	* Checks to see if this module is loaded and ready.  It is only valid to call Get() if IsAvailable() returns true.
	*
	* @return True if the module is loaded and ready to use
	*/
	static inline bool IsAvailable()
	{
		return FModuleManager::Get().IsModuleLoaded("Module");
	}
private:
	/** Handle to the test dll we will load */
	void*	ExampleLibraryHandle;
};
