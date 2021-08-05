#pragma once

#if  defined(WITH_BIOGEARS_BINDING) // TODO: Remove when biogears works on android
// BioGears
#include "VH_BioGearsPreHeaderBlock.inl"
#include "biogears/engine/Controller/BioGearsEngine.h"
#include "biogears/schema/biogears/BioGears.hxx"
#include "VH_BioGearsPostHeaderBlock.inl"
#endif

// Generated
#include "VH_PatientUrinarySystem.generated.h"

/*
 * Information about the patient's urine production
 * 
 */
UCLASS(Blueprintable)
class VH_BIOGEARS_API UVH_PatientUrinarySystem : public UObject
{
	GENERATED_BODY()


	// ---------------------------------
	// --- Constructors
	// ---------------------------------

public:
	UVH_PatientUrinarySystem(const FObjectInitializer& objectInitializer);

	virtual ~UVH_PatientUrinarySystem();


	// ---------------------------------
	// --- Variables
	// ---------------------------------

protected:
	/** Measured in mL/min */
	UPROPERTY()
	float MeanUrineOutput;

	/***/
	UPROPERTY()
	float MaxUrineVolume;

	/** Measured in mL/min */
	UPROPERTY()
	float UrinationRate;

	/** Measured in Osm/kg */
	UPROPERTY()
	float UrineOsmolality;

	/** Measured in Osm/kg */
	UPROPERTY()
	float UrineOsmolarity;

	/** Measured in mL/min */
	UPROPERTY()
	float UrineProductionRate;

	/***/
	UPROPERTY()
	float UrineSpecificGravity;

	/** Measured in g/mL*/
	UPROPERTY()
	float UrineUreaNitrogenConcentration;

	/** Measured in mL */
	UPROPERTY()
	float UrineVolume;

private:
	FCriticalSection CriticalSection;


	// ---------------------------------
	// --- API
	// ---------------------------------

public:
	virtual void InitializeUrinary();

#if  defined(WITH_BIOGEARS_BINDING) // TODO: Remove when biogears works on android
	virtual void UpdateValues(const biogears::SERenalSystem* renal);
#endif

	UFUNCTION(BlueprintCallable)
	virtual float GetMaxUrineVolume();
	
	UFUNCTION(BlueprintCallable)
	virtual float GetUrinationRate();
	
	UFUNCTION(BlueprintCallable)
	virtual float GetUrineOsmolality();
	
	UFUNCTION(BlueprintCallable)
	virtual float GetUrineOsmolarity();
	
	UFUNCTION(BlueprintCallable)
	virtual float GetUrineProductionRate();
	
	UFUNCTION(BlueprintCallable)
	virtual float GetMeanUrineOutput();
	
	UFUNCTION(BlueprintCallable)
	virtual float GetUrineSpecificGravity();
	
	UFUNCTION(BlueprintCallable)
	virtual float GetUrineVolume();
	
	UFUNCTION(BlueprintCallable)
	virtual float GetUrineUreaNitrogenConcentration();
};
