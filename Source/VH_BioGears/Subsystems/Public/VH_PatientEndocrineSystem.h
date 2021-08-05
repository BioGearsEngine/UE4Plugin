#pragma once

#include "VH_PatientSubsystem.h"

#if  defined(WITH_BIOGEARS_BINDING) // TODO: Remove when biogears works on android
// BioGears
#include "VH_BioGearsPreHeaderBlock.inl"
#include "biogears/engine/Controller/BioGearsEngine.h"
#include "biogears/schema/biogears/BioGears.hxx"
#include "VH_BioGearsPostHeaderBlock.inl"
#endif

// Generated
#include "VH_PatientEndocrineSystem.generated.h"

/*
 * Information about the patient's Endocrine system
 *
 * Known as the Hormone System
 * Glands located throughout the body that release hormones into the bloodstream
 * and the fluid surrounding cells
 */
UCLASS(Blueprintable)
class VH_BIOGEARS_API UVH_PatientEndocrineSystem : public UVH_PatientSubsystem
{
	GENERATED_BODY()


	// ---------------------------------
	// --- Constructors
	// ---------------------------------

public:
	UVH_PatientEndocrineSystem(const FObjectInitializer& objectInitializer);

	virtual ~UVH_PatientEndocrineSystem();


	// ---------------------------------
	// --- Variables
	// ---------------------------------

protected:
	/** */
	UPROPERTY()
	float InsulinSynthesisRate;

	/** */
	UPROPERTY()
	float GlucagonSynthesisRate;

private:
	FCriticalSection CriticalSection;


	// ---------------------------------
	// --- API
	// ---------------------------------

public:
	virtual void InitializeEndocrine();

#if  defined(WITH_BIOGEARS_BINDING) // TODO: Remove when biogears works on android
	virtual void UpdateValues(const biogears::SEEndocrineSystem* endocrine);
#endif

	UFUNCTION(BlueprintCallable)
	virtual float GetInsulinSynthesisRate();

	UFUNCTION(BlueprintCallable)
	virtual float GetGlucagonSynthesisRate();
};
