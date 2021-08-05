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
#include "VH_PatientTissue.generated.h"

/*
 * Information about the substances contained within the patient's various types of tissue
 *
 * Tissue an ensemble of cells that carry out a specific function
 * Separated into 4 groups: connective, muscle, nervous, and epithelial (skin)
 */
UCLASS(Blueprintable)
class VH_BIOGEARS_API UVH_PatientTissue : public UVH_PatientSubsystem
{
	GENERATED_BODY()


	// ---------------------------------
	// --- Constructors
	// ---------------------------------

public:
	UVH_PatientTissue(const FObjectInitializer& objectInitializer);

	virtual ~UVH_PatientTissue();


	// ---------------------------------
	// --- Variables
	// ---------------------------------

protected:
	// --------------- Cellular --------------- //

	/** Measured in mL*/
	UPROPERTY()
	float ExtracellularFluidVolume;

	/***/
	UPROPERTY()
	float IntracellularFluidPH;

	/** Measued in mL*/
	UPROPERTY()
	float IntracellularFluidVolume;

	// --------------- Fat --------------- //

	/** Measured in g/mL */
	UPROPERTY()
	float FatGlucagonSetPoint;

	/** Measured in mol/mL */
	UPROPERTY()
	float FatInsulinSetPoint;

	/** Measured in g */
	UPROPERTY()
	float StoredFat;

	// --------------- Liver --------------- //

	/** Measured in g/mL */
	UPROPERTY()
	float LiverGlucagonSetPoint;

	/** Measured in g */
	UPROPERTY()
	float LiverGlycogen;

	/** Measured in mol/mL */
	UPROPERTY()
	float LiverInsulinSetPoint;

	// --------------- Muscle --------------- //

	/** Measured in g/ml */
	UPROPERTY()
	float MuscleGlucagonSetPoint;

	/** Measured in g */
	UPROPERTY()
	float MuscleGlycogen;

	/** Measured in mol/mL*/
	UPROPERTY()
	float MuscleInsulinSetPoint;

	// --------------- Other --------------- //

	/** Measured in mL/min */
	UPROPERTY()
	float CarbonDioxideProductionRate;

	/** */
	UPROPERTY()
	float DehydrationFraction;

	/** Measured in mL*/
	UPROPERTY()
	float ExtravascularFluidVolume;

	/** Measured in mL/min */
	UPROPERTY()
	float OxygenConsumptionRate;

	/***/
	UPROPERTY()
	float RespiratoryExchangeRatio;

	/** Measured in g */
	UPROPERTY()
	float StoredProtein;

	/** Measured in mL */
	UPROPERTY()
	float TotalBodyFluidVolume;

private:
	FCriticalSection CriticalSection;


	// ---------------------------------
	// --- API
	// ---------------------------------

public:
	virtual void InitializeTissue();

#if  defined(WITH_BIOGEARS_BINDING) // TODO: Remove when biogears works on android
	virtual void UpdateValues(const biogears::SETissueSystem* tissue);
#endif

	// --------------- Cellular --------------- //
	
	/** Measued in mL*/
	UFUNCTION(BlueprintCallable)
	virtual float GetExtracellularFluidVolume();

	UFUNCTION(BlueprintCallable)
	virtual float GetIntracellularFluidPH();
	
	/** Measued in mL*/
	UFUNCTION(BlueprintCallable)
	virtual float GetIntracellularFluidVolume();

	// --------------- Fat --------------- //
	
	/** Measured in g/mL */
	UFUNCTION(BlueprintCallable)
	virtual float GetFatInsulinSetPoint();

	/** Measured in mol/mL */
	UFUNCTION(BlueprintCallable)
	virtual float GetFatGlucagonSetPoint();

	/** Measured in g */
	UFUNCTION(BlueprintCallable)
	virtual float GetStoredFat();

	// --------------- Liver --------------- //
	
	/** Measured in g/mL */
	UFUNCTION(BlueprintCallable)
	virtual float GetLiverInsulinSetPoint();

	/** Measured in g */
	UFUNCTION(BlueprintCallable)
	virtual float GetLiverGlucagonSetPoint();

	/** Measured in mol/mL */
	UFUNCTION(BlueprintCallable)
	virtual float GetLiverGlycogen();

	// --------------- Muscle --------------- //

	/** Measured in g/ml */
	UFUNCTION(BlueprintCallable)
	virtual float GetMuscleInsulinSetPoint();
	
	/** Measured in g */
	UFUNCTION(BlueprintCallable)
	virtual float GetMuscleGlucagonSetPoint();
	
	/** Measured in mol/mL*/
	UFUNCTION(BlueprintCallable)
	virtual float GetMuscleGlycogen();
	
	// --------------- Other --------------- //

	/** Measured in mL/min */
	UFUNCTION(BlueprintCallable)
	virtual float GetCarbonDioxideProductionRate();
	
	UFUNCTION(BlueprintCallable)
	virtual float GetDehydrationFraction();
	
	/** Measured in mL*/
	UFUNCTION(BlueprintCallable)
	virtual float GetExtravascularFluidVolume();
	
	/** Measured in mL/min */
	UFUNCTION(BlueprintCallable)
	virtual float GetOxygenConsumptionRate();
	
	UFUNCTION(BlueprintCallable)
	virtual float GetRespiratoryExchangeRatio();
	
	/** Measured in g */
	UFUNCTION(BlueprintCallable)
	virtual float GetStoredProtein();

	/** Measured in mL */
	UFUNCTION(BlueprintCallable)
	virtual float GetTotalBodyFluidVolume();
};
