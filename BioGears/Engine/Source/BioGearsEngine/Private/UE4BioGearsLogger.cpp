#include "UE4BioGearsLogger.h"

#include "Containers/StringConv.h"
#include "CoreMinimal.h"
DEFINE_LOG_CATEGORY(BioGearsLog);

void UE4BioGearsLogForward::ForwardDebug(const std::string& msg, const std::string& origin)
{
	UE_LOG(BioGearsLog, Log, TEXT("[%s]: %s"), ANSI_TO_TCHAR(origin.c_str()), ANSI_TO_TCHAR(msg.c_str()));
}
//-------------------------------------------------------------------------------
void UE4BioGearsLogForward::ForwardInfo(const std::string& msg, const std::string& origin)
{
	UE_LOG(BioGearsLog, Display, TEXT("[%s]: %s"), ANSI_TO_TCHAR(origin.c_str()), ANSI_TO_TCHAR(msg.c_str()));
}
//-------------------------------------------------------------------------------
void UE4BioGearsLogForward::ForwardWarning(const std::string& msg, const std::string& origin)
{
	UE_LOG(BioGearsLog, Warning, TEXT("[%s]: %s"), ANSI_TO_TCHAR(origin.c_str()), ANSI_TO_TCHAR(msg.c_str()));
}
//-------------------------------------------------------------------------------
void UE4BioGearsLogForward::ForwardError(const std::string& msg, const std::string& origin)
{
	UE_LOG(BioGearsLog, Error, TEXT("[%s]: %s"), ANSI_TO_TCHAR(origin.c_str()), ANSI_TO_TCHAR(msg.c_str()))
}
//-------------------------------------------------------------------------------
void UE4BioGearsLogForward::ForwardFatal(const std::string& msg, const std::string& origin)
{
	UE_LOG(BioGearsLog, Fatal, TEXT("[%s]: %s"), ANSI_TO_TCHAR(origin.c_str()), ANSI_TO_TCHAR(msg.c_str()));
}
//-------------------------------------------------------------------------------
struct UE4BioGearsLogger::Implementation
{
	UE4BioGearsLogForward UE4LogStream;
};
//-------------------------------------------------------------------------------

UE4BioGearsLogger::UE4BioGearsLogger(const FString& logFilename, const FString& working_dir)
	:biogears::Logger(TCHAR_TO_ANSI(*logFilename), TCHAR_TO_ANSI(*working_dir))
	, _pimpl(MakeUnique<Implementation>())
{
	biogears::Logger::SetForward(&_pimpl->UE4LogStream);
}
//-------------------------------------------------------------------------------
UE4BioGearsLogger::~UE4BioGearsLogger()
{
	_pimpl = nullptr;
}

//-------------------------------------------------------------------------------
void UE4BioGearsLogger::Debug(const FString& msg, const FString& origin)
{
	biogears::Logger::Debug(TCHAR_TO_ANSI(*msg), TCHAR_TO_ANSI(*origin));
}
//-------------------------------------------------------------------------------
void UE4BioGearsLogger::Info(const FString& msg, const FString& origin)
{
	biogears::Logger::Info(TCHAR_TO_ANSI(*msg), TCHAR_TO_ANSI(*origin));
}
//-------------------------------------------------------------------------------
void UE4BioGearsLogger::Warning(const FString& msg, const FString& origin)
{
	biogears::Logger::Warning(TCHAR_TO_ANSI(*msg), TCHAR_TO_ANSI(*origin));
}
//-------------------------------------------------------------------------------
void UE4BioGearsLogger::Error(const FString& msg, const FString& origin)
{
	biogears::Logger::Error(TCHAR_TO_ANSI(*msg), TCHAR_TO_ANSI(*origin));
}
//-------------------------------------------------------------------------------
void UE4BioGearsLogger::Fatal(const FString& msg, const FString& origin)
{
	biogears::Logger::Fatal(TCHAR_TO_ANSI(*msg), TCHAR_TO_ANSI(*origin));
}
//-------------------------------------------------------------------------------