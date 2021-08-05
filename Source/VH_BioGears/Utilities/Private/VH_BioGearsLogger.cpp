#include "VH_BioGearsLogger.h"

// VH BioGears Plugin
#include "VH_BioGears.h"


// ---------------------------------
// --- Constructors
// ---------------------------------

UVH_BioGearsLogger::UVH_BioGearsLogger(const FObjectInitializer& objectInitializer) :
    Super(objectInitializer)
{}


// ---------------------------------
// --- Inherited (LoggerForward)
// ---------------------------------

#if  defined(WITH_BIOGEARS_BINDING) // TODO: Remove when biogears works on android
void UVH_BioGearsLogger::Debug(char const* msg) const
{
    UE_LOG(VH_BioGears, Verbose, TEXT("%s"), *FString(ANSI_TO_TCHAR(msg)));
}

void UVH_BioGearsLogger::Info(char const*  msg) const
{
	UE_LOG(VH_BioGears, Verbose, TEXT("%s"), *FString(ANSI_TO_TCHAR(msg)));
}

void UVH_BioGearsLogger::Warning(char const*  msg) const
{
	UE_LOG(VH_BioGears, Warning, TEXT("%s"),  *FString(ANSI_TO_TCHAR(msg)));
}

void UVH_BioGearsLogger::Error(char const* msg) const
{
    UE_LOG(VH_BioGears, Error, TEXT("%s"),  *FString(ANSI_TO_TCHAR(msg)));
}

void UVH_BioGearsLogger::Fatal(char const* msg) const
{
    UE_LOG(VH_BioGears, Fatal, TEXT("%s"), *FString(ANSI_TO_TCHAR(msg)));
}
#endif


// ---------------------------------
// --- API
// ---------------------------------

void UVH_BioGearsLogger::Initialize()
{}
