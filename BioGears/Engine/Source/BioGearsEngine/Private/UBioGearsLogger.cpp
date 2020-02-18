#include "UBioGearsLogger.h"

#include "Containers/StringConv.h"
#include "CoreMinimal.h"
DEFINE_LOG_CATEGORY(BioGearsLog);

void UBioGearsLogForward::ForwardDebug(const std::string& msg, const std::string& origin)
{
	UE_LOG(BioGearsLog, Log, TEXT("[%s]: %s"), ANSI_TO_TCHAR(origin.c_str()), ANSI_TO_TCHAR(msg.c_str()));
}
//-------------------------------------------------------------------------------
void UBioGearsLogForward::ForwardInfo(const std::string& msg, const std::string& origin)
{
	UE_LOG(BioGearsLog, Display, TEXT("[%s]: %s"), ANSI_TO_TCHAR(origin.c_str()), ANSI_TO_TCHAR(msg.c_str()));
}
//-------------------------------------------------------------------------------
void UBioGearsLogForward::ForwardWarning(const std::string& msg, const std::string& origin)
{
	UE_LOG(BioGearsLog, Warning, TEXT("[%s]: %s"), ANSI_TO_TCHAR(origin.c_str()), ANSI_TO_TCHAR(msg.c_str()));
}
//-------------------------------------------------------------------------------
void UBioGearsLogForward::ForwardError(const std::string& msg, const std::string& origin)
{
	UE_LOG(BioGearsLog, Error, TEXT("[%s]: %s"), ANSI_TO_TCHAR(origin.c_str()), ANSI_TO_TCHAR(msg.c_str()))
}
//-------------------------------------------------------------------------------
void UBioGearsLogForward::ForwardFatal(const std::string& msg, const std::string& origin)
{
	UE_LOG(BioGearsLog, Fatal, TEXT("[%s]: %s"), ANSI_TO_TCHAR(origin.c_str()), ANSI_TO_TCHAR(msg.c_str()));
}
//-------------------------------------------------------------------------------
struct UBioGearsLogger::Implementation
{
	UBioGearsLogForward UE4LogStream;
};
//-------------------------------------------------------------------------------

UBioGearsLogger::UBioGearsLogger(const FString& logFilename, const FString& working_dir)
	:biogears::Logger(TCHAR_TO_ANSI(*logFilename), TCHAR_TO_ANSI(*working_dir))
	, _pimpl(MakeUnique<Implementation>())
{
	biogears::Logger::SetForward(&_pimpl->UE4LogStream);
}
//-------------------------------------------------------------------------------
UBioGearsLogger::~UBioGearsLogger()
{
	_pimpl = nullptr;
}

//-------------------------------------------------------------------------------
void UBioGearsLogger::Debug(const FString& msg, const FString& origin)
{
	biogears::Logger::Debug(TCHAR_TO_ANSI(*msg), TCHAR_TO_ANSI(*origin));
}
//-------------------------------------------------------------------------------
void UBioGearsLogger::Info(const FString& msg, const FString& origin)
{
	biogears::Logger::Info(TCHAR_TO_ANSI(*msg), TCHAR_TO_ANSI(*origin));
}
//-------------------------------------------------------------------------------
void UBioGearsLogger::Warning(const FString& msg, const FString& origin)
{
	biogears::Logger::Warning(TCHAR_TO_ANSI(*msg), TCHAR_TO_ANSI(*origin));
}
//-------------------------------------------------------------------------------
void UBioGearsLogger::Error(const FString& msg, const FString& origin)
{
	biogears::Logger::Error(TCHAR_TO_ANSI(*msg), TCHAR_TO_ANSI(*origin));
}
//-------------------------------------------------------------------------------
void UBioGearsLogger::Fatal(const FString& msg, const FString& origin)
{
	biogears::Logger::Fatal(TCHAR_TO_ANSI(*msg), TCHAR_TO_ANSI(*origin));
}
//-------------------------------------------------------------------------------