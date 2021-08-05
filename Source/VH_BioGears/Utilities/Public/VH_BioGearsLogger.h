#pragma once

#if  defined(WITH_BIOGEARS_BINDING) // TODO: Remove when biogears works on android
// BioGears
#include "VH_BioGearsPreHeaderBlock.inl"
#include "biogears/cdm/utils/Logger.h"

// Windows
#include <string>
#include "VH_BioGearsPostHeaderBlock.inl"
#endif

// Generated
#include "VH_BioGearsLogger.generated.h"

#if  defined(WITH_BIOGEARS_BINDING) // TODO: Remove when biogears works on android
// Class extension won't accept a namespace, so typedef it here
typedef biogears::LoggerForward BGLoggerForward;
#else
class FDummyBGLoggerClass { };
typedef FDummyBGLoggerClass BGLoggerForward;
#endif

/*
 * Bridge class between BioGears logging system with Unreal's logging system
 *
 */
UCLASS(Blueprintable)
class VH_BIOGEARS_API UVH_BioGearsLogger : public UObject, public BGLoggerForward
{
    GENERATED_BODY()


	// ---------------------------------
	// --- Constructors
	// ---------------------------------

public:
    UVH_BioGearsLogger(const FObjectInitializer& objectInitializer);


	// ---------------------------------
	// --- Inherited (LoggerForward)
	// ---------------------------------

public:
#if  defined(WITH_BIOGEARS_BINDING) // TODO: Remove when biogears works on android
	virtual void Debug(char const*) const override;
    virtual void Info(char const*) const override;
    virtual void Warning(char const*) const override;
    virtual void Error(char const*) const override;
    virtual void Fatal(char const*) const override;
#endif

    // ---------------------------------
    // --- API
    // ---------------------------------

public:
    virtual void Initialize();
};
