#pragma once
#include <string>
#include <biogears/cdm/utils/Logger.h>

#include "CoreMinimal.h"
#include "Containers/UnrealString.h"
#include "Templates/UniquePtr.h"

DECLARE_LOG_CATEGORY_EXTERN(BioGearsLog, Log, All);

class UE4BioGearsLogForward : public biogears::LoggerForward {
public:
	UE4BioGearsLogForward() = default;
	~UE4BioGearsLogForward() = default;
	void ForwardDebug(const std::string& msg, const std::string& origin) final;
	void ForwardInfo(const std::string& msg, const std::string& origin) final;
	void ForwardWarning(const std::string& msg, const std::string& origin) final;
	void ForwardError(const std::string& msg, const std::string& origin) final;
	void ForwardFatal(const std::string& msg, const std::string& origin) final;
};

class UE4BioGearsLogger : public biogears::Logger {
	friend biogears::Loggable;

public:
	UE4BioGearsLogger(const FString& logFilename, const FString& working_dir);
	virtual ~UE4BioGearsLogger();

	void Debug(const FString& msg, const FString& origin = TEXT(""));
	void Info(const FString& msg, const FString& origin = TEXT(""));
	void Warning(const FString& msg, const FString& origin = TEXT(""));
	void Error(const FString& msg, const FString& origin = TEXT(""));
	void Fatal(const FString& msg, const FString& origin = TEXT(""));

protected:
	using biogears::Logger::SetForward;
	using biogears::Logger::HasForward;

	using biogears::Logger::Debug;
	using biogears::Logger::Info;
	using biogears::Logger::Warning;
	using biogears::Logger::Error;
	using biogears::Logger::Fatal;
private:
	struct Implementation;
	TUniquePtr<Implementation> _pimpl;
};
