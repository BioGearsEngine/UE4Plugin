#pragma once
#include <string>
#include <biogears/cdm/utils/Logger.h>

#include <UObject/Object.h>
#include <CoreMinimal.h>
#include <Containers/UnrealString.h>
#include <Templates/UniquePtr.h>

#include "UBioGearsLogger.generated.h"

DECLARE_LOG_CATEGORY_EXTERN(BioGearsLog, Log, All);

class BIOGEARSENGINE_API BioGearsLogForward : public biogears::LoggerForward {
public:
	BioGearsLogForward() = default;
	~BioGearsLogForward() = default;
	void ForwardDebug(const std::string& msg, const std::string& origin) final;
	void ForwardInfo(const std::string& msg, const std::string& origin) final;
	void ForwardWarning(const std::string& msg, const std::string& origin) final;
	void ForwardError(const std::string& msg, const std::string& origin) final;
	void ForwardFatal(const std::string& msg, const std::string& origin) final;
};

UCLASS(BlueprintType, Config = "BioGears", meta = (DisplayName = "BioGearsLogger"))
class UBioGearsLogger : public UObject {
	
	GENERATED_BODY()

public:
	UBioGearsLogger();
	~UBioGearsLogger() override;


	biogears::Logger* get();
	void initialize(const FString& working_dir, const FString& logFilename);
	void setup_ue4_fowarding();

	UFUNCTION(BlueprintCallable, Category = "Physiology", meta = (DisplayName = "Physiology::Log::Debug"))
	void Debug(const FString& msg, const FString& origin = TEXT(""));
	UFUNCTION(BlueprintCallable, Category = "Physiology", meta = (DisplayName = "Physiology::Log::Info"))
	void Info(const FString& msg, const FString& origin = TEXT(""));
	UFUNCTION(BlueprintCallable, Category = "Physiology", meta = (DisplayName = "Physiology::Log::Warning"))
	void Warning(const FString& msg, const FString& origin = TEXT(""));
	UFUNCTION(BlueprintCallable, Category = "Physiology", meta = (DisplayName = "Physiology::Log::Error"))
	void Error(const FString& msg, const FString& origin = TEXT(""));
	UFUNCTION(BlueprintCallable, Category = "Physiology", meta = (DisplayName = "Physiology::Log::Fatal"))
	void Fatal(const FString& msg, const FString& origin = TEXT(""));

protected:

private:
	BioGearsLogForward UE4LogStream;
	TUniquePtr<biogears::Logger> _logger;
};
