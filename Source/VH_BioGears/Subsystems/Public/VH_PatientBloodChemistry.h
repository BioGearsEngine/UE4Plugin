#pragma once

#include "VH_PatientSubsystem.h"
#include "VH_PatientInflammatoryResponse.h"

// Engine
#include "Templates/SubclassOf.h"

#if  defined(WITH_BIOGEARS_BINDING) // TODO: Remove when biogears works on android
// BioGears
#include "VH_BioGearsPreHeaderBlock.inl"
#include "biogears/cdm/system/physiology/SEBloodChemistrySystem.h"
#include "VH_BioGearsPostHeaderBlock.inl"
#endif

// Generated
#include "VH_PatientBloodChemistry.generated.h"

/*
 * Information about the chemistry of the patient's blood
 *
 */
UCLASS(Blueprintable)
class VH_BIOGEARS_API UVH_PatientBloodChemistry : public UVH_PatientSubsystem
{
	GENERATED_BODY()


	// ---------------------------------
	// --- Constructors
	// ---------------------------------

public:
	UVH_PatientBloodChemistry(const FObjectInitializer& objectInitializer);

	virtual ~UVH_PatientBloodChemistry();


	// ---------------------------------
	// --- Variables
	// ---------------------------------

protected:
	UPROPERTY(EditDefaultsOnly)
	TSubclassOf<UVH_PatientInflammatoryResponse> InflammatoryResponseClass;

	UPROPERTY()
	UVH_PatientInflammatoryResponse* InflammatoryResponse;

	// --------------- Arterial --------------- //

	/** */
	UPROPERTY()
	float ArterialBloodPH;

	/** */
	UPROPERTY()
	float ArterialBloodPHBaseline;

	/** Measured in mmHg */
	UPROPERTY()
	float ArterialCarbonDioxidePressure;

	/** Measured in mmHg */
	UPROPERTY()
	float ArterialOxygenPressure;

	/** Measured in mmHg */
	UPROPERTY()
	float PulmonaryArterialCarbonDioxidePressure;

	/** Measured in mmHg */
	UPROPERTY()
	float PulmonaryArterialOxygenPressure;

	// --------------- Blood --------------- //

	/** Measured in g/cm^3*/
	UPROPERTY()
	float BloodDensity;

	/** Measured in kcal/Ckg */
	UPROPERTY()
	float BloodSpecificHeat;

	/**Measured in g/cm^3 */
	UPROPERTY()
	float BloodUreaNitrogenConcentration;

	/** */
	UPROPERTY()
	float Hematocrit;

	/**Measured in g */
	UPROPERTY()
	float HemoglobinContent;

	/** Measured in ct/L */
	UPROPERTY()
	float Phosphate;

	/** Measured in mL */
	UPROPERTY()
	float PlasmaVolume;

	/** */
	UPROPERTY()
	float PulseOximetry;

	/** Measured in ct/L */
	UPROPERTY()
	float RedBloodCellAcetylcholinesterase;

	/** Measured in ct/L */
	UPROPERTY()
	float RedBloodCellCount;

	/** */
	UPROPERTY()
	float ShuntFraction;

	/** Measured in ct/L */
	UPROPERTY()
	float StrongIonDifference;

	/** Measured in g/mL */
	UPROPERTY()
	float TotalBilirubin;

	/** Measured in g/mL */
	UPROPERTY()
	float TotalProteinConcentration;

	/** */
	UPROPERTY()
	float VenousBloodPH;

	/** */
	UPROPERTY()
	float VolumeFractionNeutralPhospholipidInPlasma;

	/** */
	UPROPERTY()
	float VolumeFractionNeutralLipidInPlasma;

	// --------------- Gases --------------- //

	/** */
	UPROPERTY()
	float CarbonDioxideSaturation;

	/** */
	UPROPERTY()
	float CarbonMonoxideSaturation;

	/** */
	UPROPERTY()
	float OxygenSaturation;

	/** Measured in mmHg */
	UPROPERTY()
	float PulmonaryVenousCarbonDioxidePressure;

	/** Measured in mmHg */
	UPROPERTY()
	float PulmonaryVenousOxygenPressure;

	/** Measured in mmHg */
	UPROPERTY()
	float VenousCarbonDioxidePressure;

	/** Measured in mmHg */
	UPROPERTY()
	float VenousOxygenPressure;

private:
	FCriticalSection CriticalSection;


	// ---------------------------------
	// --- API
	// ---------------------------------

public:
	virtual void InitializeBlood();

#if  defined(WITH_BIOGEARS_BINDING) // TODO: Remove when biogears works on android
	virtual void UpdateValues(const biogears::SEBloodChemistrySystem* blood);
#endif

	UFUNCTION(BlueprintCallable)
	virtual UVH_PatientInflammatoryResponse* GetInflammatoryResponse() const { return InflammatoryResponse; }

	// --------------- Arterial --------------- //

	UFUNCTION(BlueprintCallable)
	virtual float GetArterialBloodPH();
	
	UFUNCTION(BlueprintCallable)
	virtual float GetArterialBloodPHBaseline();
	
	UFUNCTION(BlueprintCallable)
	virtual float GetArterialCarbonDioxidePressure();
	
	UFUNCTION(BlueprintCallable)
	virtual float GetArterialOxygenPressure();
	
	UFUNCTION(BlueprintCallable)
	virtual float GetPulmonaryArterialCarbonDioxidePressure();
	
	UFUNCTION(BlueprintCallable)
	virtual float GetPulmonaryArterialOxygenPressure();
	
	// --------------- Blood --------------- //

	UFUNCTION(BlueprintCallable)
	virtual float GetBloodDensity();
	
	UFUNCTION(BlueprintCallable)
	virtual float GetBloodSpecificHeat();
	
	UFUNCTION(BlueprintCallable)
	virtual float GetBloodUreaNitrogenConcentration();
	
	UFUNCTION(BlueprintCallable)
	virtual float GetHematocrit();
	
	UFUNCTION(BlueprintCallable)
	virtual float GetHemoglobinContent();

	UFUNCTION(BlueprintCallable)
	virtual float GetPhosphate();
	
	UFUNCTION(BlueprintCallable)
	virtual float GetPlasmaVolume();
	
	UFUNCTION(BlueprintCallable)
	virtual float GetPulseOximetry();

	UFUNCTION(BlueprintCallable)
	virtual float GetRedBloodCellAcetylcholinesterase();

	UFUNCTION(BlueprintCallable)
	virtual float GetRedBloodCellCount();

	UFUNCTION(BlueprintCallable)
	virtual float GetShuntFraction();

	UFUNCTION(BlueprintCallable)
	virtual float GetStrongIonDifference();

	UFUNCTION(BlueprintCallable)
	virtual float GetTotalBilirubin();

	UFUNCTION(BlueprintCallable)
	virtual float GetTotalProteinConcentration();

	UFUNCTION(BlueprintCallable)
	virtual float GetVenousBloodPH();

	UFUNCTION(BlueprintCallable)
	virtual float GetVolumeFractionNeutralPhospholipidInPlasma();

	UFUNCTION(BlueprintCallable)
	virtual float GetVolumeFractionNeutralLipidInPlasma();

	// --------------- Gases --------------- //

	UFUNCTION(BlueprintCallable)
	virtual float GetCarbonDioxideSaturation();
	
	UFUNCTION(BlueprintCallable)
	virtual float GetCarbonMonoxideSaturation();
	
	UFUNCTION(BlueprintCallable)
	virtual float GetOxygenSaturation();
	
	UFUNCTION(BlueprintCallable)
	virtual float GetPulmonaryVenousCarbonDioxidePressure();

	UFUNCTION(BlueprintCallable)
	virtual float GetPulmonaryVenousOxygenPressure();

	UFUNCTION(BlueprintCallable)
	virtual float GetVenousCarbonDioxidePressure();

	UFUNCTION(BlueprintCallable)
	virtual float GetVenousOxygenPressure();
};
