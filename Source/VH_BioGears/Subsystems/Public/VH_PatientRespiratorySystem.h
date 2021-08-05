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
#include "VH_PatientRespiratorySystem.generated.h"

/*
 * Information about the patient's respiratory system
 *
 * Network of organs and tissues that assist with breathing.
 * Helps your body absorb oxygen from the air so your organs can work and cleans waste gases from your blood.
 */
UCLASS(Blueprintable)
class VH_BIOGEARS_API UVH_PatientRespiratorySystem : public UVH_PatientSubsystem
{
	GENERATED_BODY()


	// ---------------------------------
	// --- Constructors
	// ---------------------------------

public:
	UVH_PatientRespiratorySystem(const FObjectInitializer& objectInitializer);

	virtual ~UVH_PatientRespiratorySystem();


	// ---------------------------------
	// --- Variables
	// ---------------------------------

protected:
	// --------------- Expiratory --------------- //

	/***/
	UPROPERTY()
	float ExpiratoryFlow;

	// --------------- Inspiratory --------------- //

	/***/
	UPROPERTY()
	float InspiratoryExpiratoryRatio;

	/***/
	UPROPERTY()
	float InspiratoryFlow;

	// --------------- Pressure --------------- //

	/***/
	UPROPERTY()
	float EndTidalCarbonDioxidePressure;

	/***/
	UPROPERTY()
	float RespirationDriverPressure;

	/***/
	UPROPERTY()
	float RespirationMusclePressure;

	/***/
	UPROPERTY()
	float TranspulmonaryPressure;

	// --------------- Pulmonary --------------- //

	/***/
	UPROPERTY()
	float PulmonaryCompliance;

	/***/
	UPROPERTY()
	float PulmonaryResistance;

	/***/
	UPROPERTY()
	float TotalPulmonaryVentilation;

	// --------------- Ventilation --------------- //

	/***/
	UPROPERTY()
	float SpecificVentilation;

	/***/
	UPROPERTY()
	float TargetPulmonaryVentilation;

	/***/
	UPROPERTY()
	float TotalAlveolarVentilation;

	/***/
	UPROPERTY()
	float TotalDeadSpaceVentilation;

	// --------------- Volume --------------- //

	/***/
	UPROPERTY()
	float TidalVolume;

	/***/
	UPROPERTY()
	float TotalLungVolume;

	// --------------- Other --------------- //

	UPROPERTY()
	float AlveolarArterialGradient;

	/***/
	UPROPERTY()
	float CarricoIndex;

	/***/
	UPROPERTY()
	float EndTidalCarbonDioxideFraction;

	/***/
	UPROPERTY()
	float RespirationRate;

private:
	FCriticalSection CriticalSection;


	// ---------------------------------
	// --- API
	// ---------------------------------

public:
	virtual void InitializeRespiratory();

#if  defined(WITH_BIOGEARS_BINDING) // TODO: Remove when biogears works on android
	virtual void UpdateValues(const biogears::SERespiratorySystem* respiratory);
#endif

	// --------------- Expiratory --------------- //

	UFUNCTION(BlueprintCallable)
	virtual float GetExpiratoryFlow();

	// --------------- Inspiratory --------------- //

	UFUNCTION(BlueprintCallable)
	virtual float GetInspiratoryExpiratoryRatio();
	
	UFUNCTION(BlueprintCallable)
	virtual float GetInspiratoryFlow();
	
	// --------------- Pressure --------------- //

	UFUNCTION(BlueprintCallable)
	virtual float GetEndTidalCarbonDioxidePressure();
	
	UFUNCTION(BlueprintCallable)
	virtual float GetRespirationDriverPressure();
	
	UFUNCTION(BlueprintCallable)
	virtual float GetRespirationMusclePressure();

	// --------------- Pulmonary --------------- //

	UFUNCTION(BlueprintCallable)
	virtual float GetPulmonaryCompliance();

	UFUNCTION(BlueprintCallable)
	virtual float GetPulmonaryResistance();

	UFUNCTION(BlueprintCallable)
	virtual float GetTargetPulmonaryVentilation();

	UFUNCTION(BlueprintCallable)
	virtual float GetTotalPulmonaryVentilation();

	UFUNCTION(BlueprintCallable)
	virtual float GetTranspulmonaryPressure();

	// --------------- Ventilation --------------- //

	UFUNCTION(BlueprintCallable)
	virtual float GetSpecificVentilation();
	
	UFUNCTION(BlueprintCallable)
	virtual float GetTotalAlveolarVentilation();

	UFUNCTION(BlueprintCallable)
	virtual float GetTotalDeadSpaceVentilation();

	// --------------- Volume --------------- //

	UFUNCTION(BlueprintCallable)
	virtual float GetTidalVolume();

	UFUNCTION(BlueprintCallable)
	virtual float GetTotalLungVolume();

	// --------------- Other --------------- //

	UFUNCTION(BlueprintCallable)
	virtual float GetAlveolarArterialGradient();
	
	UFUNCTION(BlueprintCallable)
	virtual float GetCarricoIndex();
	
	UFUNCTION(BlueprintCallable)
	virtual float GetEndTidalCarbonDioxideFraction();
		
	UFUNCTION(BlueprintCallable)
	virtual float GetRespirationRate();
};
