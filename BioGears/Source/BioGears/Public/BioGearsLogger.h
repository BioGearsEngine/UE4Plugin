#pragma once

// BioGears
#include <biogears/cdm/utils/Logger.h>

// Windows
#include "BioGearsPreHeaderBlock.inl"
#include <string>
#include "BioGearsPostHeaderBlock.inl"

#include "BioGearsLogger.generated.h"

// Class extension won't accept namespace, so typedeffed it
typedef biogears::LoggerForward BGLoggerForward;

UCLASS(Blueprintable)
class BIOGEARS_UE4_API UBioGearsLogger : public UObject, public BGLoggerForward
{
    GENERATED_BODY()


	// ---------------------------------
	// --- Constructors
	// ---------------------------------

public:
    UBioGearsLogger(const FObjectInitializer& objectInitializer);


	// ---------------------------------
	// --- Inherited Methods (LoggerForward)
	// ---------------------------------

public:
    virtual void ForwardDebug(const std::string& msg, const std::string& origin) override;
    virtual void ForwardInfo(const std::string& msg, const std::string& origin) override;
    virtual void ForwardWarning(const std::string& msg, const std::string& origin) override;
    virtual void ForwardError(const std::string& msg, const std::string& origin) override;
    virtual void ForwardFatal(const std::string& msg, const std::string& origin) override;


    // ---------------------------------
    // --- Public Methods
    // ---------------------------------

public:
    virtual void Initialize();
};
