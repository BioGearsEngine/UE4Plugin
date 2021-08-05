#pragma once

#include "VH_PatientSubsystem.h"

#if  defined(WITH_BIOGEARS_BINDING) // TODO: Remove when biogears works on android
// BioGears
#include "VH_BioGearsPreHeaderBlock.inl"
#include <biogears/engine/Controller/BioGearsEngine.h>
#include <biogears/schema/biogears/BioGears.hxx>
#include <biogears/cdm/system/physiology/SEDrugSystem.h>
#include "VH_BioGearsPostHeaderBlock.inl"
#endif

// Generated
#include "VH_PatientDrugSystem.generated.h"

/*
 * Information about the effects on the patient due to drugs
 *
 */
UCLASS(Blueprintable)
class VH_BIOGEARS_API UVH_PatientDrugSystem : public UVH_PatientSubsystem
{
	GENERATED_BODY()


	// ---------------------------------
	// --- Constructors
	// ---------------------------------

public:
	UVH_PatientDrugSystem(const FObjectInitializer& objectInitializer);

	virtual ~UVH_PatientDrugSystem();


	// ---------------------------------
	// --- Variables
	// ---------------------------------

protected:
	/***/
	UPROPERTY()
	float BronchodilationLevel;

	/***/
	UPROPERTY()
	float HeartRateChange;

	/***/
	UPROPERTY()
	float HemorrhageChange;

	/***/
	UPROPERTY()
	float MeanBloodPressureChange;

	/***/
	UPROPERTY()
	float NeuromuscularBlockLevel;

	/***/
	UPROPERTY()
	float PulsePressureChange;

	/***/
	UPROPERTY()
	float RespirationRateChange;

	/***/
	UPROPERTY()
	float SedationLevel;

	/***/
	UPROPERTY()
	float TidalVolumeChange;

	/***/
	UPROPERTY()
	float TubularPermeabilityChange;

	/***/
	UPROPERTY()
	float CentralNervousResponse;

private:
	FCriticalSection CriticalSection;


	// ---------------------------------
	// --- API
	// ---------------------------------

public:
	virtual void InitializeDrugs();

#if  defined(WITH_BIOGEARS_BINDING) // TODO: Remove when biogears works on android
	virtual void UpdateValues(const biogears::SEDrugSystem* drugs);
#endif

	UFUNCTION(BlueprintCallable)
	float GetBronchodilationLevel();
	
	UFUNCTION(BlueprintCallable)
	float GetCentralNervousResponse();
	
	UFUNCTION(BlueprintCallable)
	float GetHeartRateChange();
	
	UFUNCTION(BlueprintCallable)
	float GetHemorrhageChange();
	
	UFUNCTION(BlueprintCallable)
	float GetMeanBloodPressureChange();
	
	UFUNCTION(BlueprintCallable)
	float GetNeuromuscularBlockLevel();
	
	UFUNCTION(BlueprintCallable)
	float GetPulsePressureChange();
	
	UFUNCTION(BlueprintCallable)
	float GetRespirationRateChange();
	
	UFUNCTION(BlueprintCallable)
	float GetSedationLevel();
	
	UFUNCTION(BlueprintCallable)
	float GetTidalVolumeChange();
	
	UFUNCTION(BlueprintCallable)
	float GetTubularPermeabilityChange();
};
