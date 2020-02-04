// Copyright 1998-2019 Epic Games, Inc. All Rights Reserved.

#include "FBioGearsEngineModule.h"
#include "Core.h"
#include "Modules/ModuleManager.h"
#include "Interfaces/IPluginManager.h"
#include <biogears/version.h>

#define LOCTEXT_NAMESPACE "FBioGearsEngineModule"

void FBioGearsEngineModule::StartupModule()
{
  // This code will execute after your module is loaded into memory; the exact timing is specified in the .uplugin file per-module

  // Get the base directory of this plugin
  FString BaseDir = IPluginManager::Get().FindPlugin("BioGearsEngine")->GetBaseDir();

  // Add on the relative location of the third party dll and load it
  FString LibraryPath;
#if PLATFORM_WINDOWS
  #ifdef _WIN64
#define DLL_PATH(x) "Binaries/Win64/" ##x
  #else
  #  define DLL_PREFIX = "Binaries/Win32/"
  #endif
  char* BioGearsDLLs[] = {
	  DLL_PATH("Log4cpp.dll")
	, DLL_PATH("xerces-c_3_2.dll")
	, DLL_PATH("libbiogears_cdm.dll")
	, DLL_PATH("libbiogears.dll")
  };
  for ( auto dll : BioGearsDLLs)
  {
	  LibraryPath = FPaths::Combine(*BaseDir, ANSI_TO_TCHAR(dll));
	  UE_LOG(LogTemp, Log, TEXT("Loading %s -> %s"), ANSI_TO_TCHAR(dll), *LibraryPath);
	  ExampleLibraryHandle = !LibraryPath.IsEmpty() ? FPlatformProcess::GetDllHandle(*LibraryPath) : nullptr;
  }
#elif PLATFORM_MAC
  static_assert(false, "MacOS Unsupported at this time");
#elif PLATFORM_ANDROID
  static_assert(false, "Android Unsupported at this time");
#elif PLATFORM_LINUX
  static_assert(false, "Linux Unsupported at this time");
#endif // PLATFORM_WINDOWS

  ExampleLibraryHandle = !LibraryPath.IsEmpty() ? FPlatformProcess::GetDllHandle(*LibraryPath) : nullptr;

  if (ExampleLibraryHandle)
  {
    // Call the test function in the third party library that opens a message box
    UE_LOG(LogTemp, Warning, TEXT("Sucessfully Loaded libBioGears %s"), ANSI_TO_TCHAR(::biogears::full_version_string_str()));
  }
  else
  {
    FMessageDialog::Open(EAppMsgType::Ok, LOCTEXT("ThirdPartyLibraryError", "Failed to load BioGears library"));
  }
}

void FBioGearsEngineModule::ShutdownModule()
{
  // This function may be called during shutdown to clean up your module.  For modules that support dynamic reloading,
  // we call this function before unloading the module.

  // Free the dll handle
  FPlatformProcess::FreeDllHandle(ExampleLibraryHandle);
  ExampleLibraryHandle = nullptr;
}

#undef LOCTEXT_NAMESPACE
  
IMPLEMENT_MODULE(FBioGearsEngineModule, BioGearsEngine)
