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
#include "VH_PatientHepaticSystem.generated.h"

/*
 * Rates associated with the patient's hepatic portal vein and its tributaries
 *
 * System of veins responsible for directing blood from gastrointestinal system to liver
 */
UCLASS(Blueprintable)
class VH_BIOGEARS_API UVH_PatientHepaticSystem : public UVH_PatientSubsystem
{
	GENERATED_BODY()


	// ---------------------------------
	// --- Constructors
	// ---------------------------------

public:
	UVH_PatientHepaticSystem(const FObjectInitializer& objectInitializer);

	virtual ~UVH_PatientHepaticSystem();


	// ---------------------------------
	// --- Variables
	// ---------------------------------

protected:
	/***/
	UPROPERTY()
	float KetoneProductionRate;

	/***/
	UPROPERTY()
	float GluconeogenesisRate;

private:
	FCriticalSection CriticalSection;


	// ---------------------------------
	// --- API
	// ---------------------------------

public:
	virtual void InitializeHepatic();

#if  defined(WITH_BIOGEARS_BINDING) // TODO: Remove when biogears works on android
	virtual void UpdateValues(const biogears::SEHepaticSystem* hepatic);
#endif

	UFUNCTION(BlueprintCallable)
	virtual float GetGluconeogenesisRate();
	
	UFUNCTION(BlueprintCallable)
	virtual float GetKetoneProductionRate();
};
