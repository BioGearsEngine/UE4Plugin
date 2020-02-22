#include "UBioGearsLogger.h"

#include "Containers/StringConv.h"
#include "CoreMinimal.h"
DEFINE_LOG_CATEGORY(BioGearsLog);

void BioGearsLogForward::ForwardDebug(const std::string& msg, const std::string& origin)
{
	UE_LOG(BioGearsLog, Verbose, TEXT("[%s]: %s"), ANSI_TO_TCHAR(origin.c_str()), ANSI_TO_TCHAR(msg.c_str()));
}
//-------------------------------------------------------------------------------
void BioGearsLogForward::ForwardInfo(const std::string& msg, const std::string& origin)
{
	UE_LOG(BioGearsLog, Display, TEXT("[%s]: %s"), ANSI_TO_TCHAR(origin.c_str()), ANSI_TO_TCHAR(msg.c_str()));
}
//-------------------------------------------------------------------------------
void BioGearsLogForward::ForwardWarning(const std::string& msg, const std::string& origin)
{
	UE_LOG(BioGearsLog, Warning, TEXT("[%s]: %s"), ANSI_TO_TCHAR(origin.c_str()), ANSI_TO_TCHAR(msg.c_str()));
}
//-------------------------------------------------------------------------------
void BioGearsLogForward::ForwardError(const std::string& msg, const std::string& origin)
{
	UE_LOG(BioGearsLog, Error, TEXT("[%s]: %s"), ANSI_TO_TCHAR(origin.c_str()), ANSI_TO_TCHAR(msg.c_str()))
}
//-------------------------------------------------------------------------------
void BioGearsLogForward::ForwardFatal(const std::string& msg, const std::string& origin)
{
	UE_LOG(BioGearsLog, Fatal, TEXT("[%s]: %s"), ANSI_TO_TCHAR(origin.c_str()), ANSI_TO_TCHAR(msg.c_str()));
}

//-------------------------------------------------------------------------------

UBioGearsLogger::UBioGearsLogger()	
{
}
//-------------------------------------------------------------------------------
void UBioGearsLogger::initialize(const FString& working_dir, const FString& logFilename) {
	_logger = MakeUnique<biogears::Logger>(TCHAR_TO_ANSI(*logFilename), TCHAR_TO_ANSI(*working_dir));
	_logger->SetForward(&UE4LogStream);
}
//-------------------------------------------------------------------------------
UBioGearsLogger::~UBioGearsLogger()
{
	
}
//-------------------------------------------------------------------------------
biogears::Logger* UBioGearsLogger::get() {
	return _logger.Get();
}
//-------------------------------------------------------------------------------
void UBioGearsLogger::setup_ue4_fowarding()
{
	_logger->SetForward(&UE4LogStream);
}
//-------------------------------------------------------------------------------
void UBioGearsLogger::Debug(const FString& msg, const FString& origin)
{
	_logger->Debug(TCHAR_TO_ANSI(*msg), TCHAR_TO_ANSI(*origin));
}
//-------------------------------------------------------------------------------
void UBioGearsLogger::Info(const FString& msg, const FString& origin)
{
	_logger->Info(TCHAR_TO_ANSI(*msg), TCHAR_TO_ANSI(*origin));
}
//-------------------------------------------------------------------------------
void UBioGearsLogger::Warning(const FString& msg, const FString& origin)
{
	_logger->Warning(TCHAR_TO_ANSI(*msg), TCHAR_TO_ANSI(*origin));
}
//-------------------------------------------------------------------------------
void UBioGearsLogger::Error(const FString& msg, const FString& origin)
{
	_logger->Error(TCHAR_TO_ANSI(*msg), TCHAR_TO_ANSI(*origin));
}
//-------------------------------------------------------------------------------
void UBioGearsLogger::Fatal(const FString& msg, const FString& origin)
{
	_logger->Fatal(TCHAR_TO_ANSI(*msg), TCHAR_TO_ANSI(*origin));
}
//-------------------------------------------------------------------------------