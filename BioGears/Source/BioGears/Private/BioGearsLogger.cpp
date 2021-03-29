#include "BioGearsLogger.h"

// VH BioGears Plugin
#include "BioGears_UE4Module.h"


// ---------------------------------
// --- Constructors
// ---------------------------------

UBioGearsLogger::UBioGearsLogger(const FObjectInitializer& objectInitializer) :
    Super(objectInitializer)
{}


// ---------------------------------
// --- Inherited Methods (LoggerForward)
// ---------------------------------

void UBioGearsLogger::ForwardDebug(const std::string& msg, const std::string& origin)
{
    UE_LOG(BioGears, Verbose, TEXT("[%s]: %s"), *FString(ANSI_TO_TCHAR(origin.c_str())), *FString(ANSI_TO_TCHAR(msg.c_str())));
}

void UBioGearsLogger::ForwardInfo(const std::string& msg, const std::string& origin)
{
	UE_LOG(BioGears, Verbose, TEXT("[%s]: %s"), *FString(ANSI_TO_TCHAR(origin.c_str())), *FString(ANSI_TO_TCHAR(msg.c_str())));
}

void UBioGearsLogger::ForwardWarning(const std::string& msg, const std::string& origin)
{
	UE_LOG(BioGears, Warning, TEXT("[%s]: %s"), *FString(ANSI_TO_TCHAR(origin.c_str())), *FString(ANSI_TO_TCHAR(msg.c_str())));
}

void UBioGearsLogger::ForwardError(const std::string& msg, const std::string& origin)
{
    UE_LOG(BioGears, Error, TEXT("[%s]: %s"), *FString(ANSI_TO_TCHAR(origin.c_str())), *FString(ANSI_TO_TCHAR(msg.c_str())));
}

void UBioGearsLogger::ForwardFatal(const std::string& msg, const std::string& origin)
{
    UE_LOG(BioGears, Fatal, TEXT("[%s]: %s"), *FString(ANSI_TO_TCHAR(origin.c_str())), *FString(ANSI_TO_TCHAR(msg.c_str())));
}


// ---------------------------------
// --- Public Methods
// ---------------------------------

void UBioGearsLogger::Initialize()
{}
