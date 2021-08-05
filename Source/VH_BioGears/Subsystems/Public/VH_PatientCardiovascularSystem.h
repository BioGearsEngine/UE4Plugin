#pragma once

#include "VH_PatientSubsystem.h"

#if  defined(WITH_BIOGEARS_BINDING) // TODO: Remove when biogears works on android
// BioGears
#include "VH_BioGearsPreHeaderBlock.inl"
#include "biogears/cdm/system/physiology/SECardiovascularSystem.h"
#include "VH_BioGearsPostHeaderBlock.inl"
#endif

// Generated
#include "VH_PatientCardiovascularSystem.generated.h"

/*
 * Information about the patient's Cardiovascular system
 *
 * Organ system that carries blood to and from all parts of the body through vessels
 * Provides nutrients and oxygen to tissues, removing carbon dioxide and other wastes
 */
UCLASS(Blueprintable)
class VH_BIOGEARS_API UVH_PatientCardiovascularSystem : public UVH_PatientSubsystem
{
	GENERATED_BODY()


	// ---------------------------------
	// --- Constructors
	// ---------------------------------

public:
	UVH_PatientCardiovascularSystem(const FObjectInitializer& objectInitializer);

	virtual ~UVH_PatientCardiovascularSystem();


	// ---------------------------------
	// --- Variables
	// ---------------------------------

protected:
	// --------------- Arterial --------------- //

	/***/
	UPROPERTY()
	float ArterialPressure;

	/***/
	UPROPERTY()
	float DiastolicArterialPressure;

	/***/
	UPROPERTY()
	float SystolicArterialPressure;

	/***/
	UPROPERTY()
	float MeanArterialPressure;

	/***/
	UPROPERTY()
	float MeanArterialCarbonDioxidePartialPressure;

	/***/
	UPROPERTY()
	float MeanArterialCarbonDioxidePartialPressureDelta;

	// --------------- Cardiac --------------- //

	/***/
	UPROPERTY()
	float CardiacIndex;

	/***/
	UPROPERTY()
	float CardiacOutput;

	/***/
	UPROPERTY()
	float HeartEjectionFraction;

	/***/
	UPROPERTY()
	float HeartRate;

	/***/
	UPROPERTY()
	float HeartStrokeVolume;

	// --------------- Cerebral --------------- //

	/***/
	UPROPERTY()
	float CentralVenousPressure;

	/***/
	UPROPERTY()
	float CerebralBloodFlow;

	/***/
	UPROPERTY()
	float CerebralPerfusionPressure;

	// --------------- Pulmonary --------------- //
	
	/***/
	UPROPERTY()
	float PulmonaryArterialPressure;

	/***/
	UPROPERTY()
	float PulmonaryCapillariesWedgePressure;

	/***/
	UPROPERTY()
	float PulmonaryDiastolicArterialPressure;

	/***/
	UPROPERTY()
	float PulmonaryMeanArterialPressure;

	/***/
	UPROPERTY()
	float PulmonaryMeanCapillaryFlow;

	/***/
	UPROPERTY()
	float PulmonaryMeanShuntFlow;

	/***/
	UPROPERTY()
	float PulmonarySystolicArterialPressure;

	/***/
	UPROPERTY()
	float PulmonaryVascularResistance;

	/***/
	UPROPERTY()
	float PulmonaryVascularResistanceIndex;

	// --------------- Vascular --------------- //

	/***/
	UPROPERTY()
	float BloodVolume;

	/***/
	UPROPERTY()
	float IntracranialPressure;

	/***/
	UPROPERTY()
	float MeanCentralVenousPressure;

	/***/
	UPROPERTY()
	float MeanSkinFlow;

	/***/
	UPROPERTY()
	float PulsePressure;

	/***/
	UPROPERTY()
	float SystemicVascularResistance;

private:
	FCriticalSection CriticalSection;


	// ---------------------------------
	// --- API
	// ---------------------------------

public:
	virtual void InitializeCardiovascular();

#if  defined(WITH_BIOGEARS_BINDING) // TODO: Remove when biogears works on android
	virtual void UpdateValues(const biogears::SECardiovascularSystem* cardiovascular);
#endif

	// --------------- Arterial --------------- //

	UFUNCTION(BlueprintCallable)
	virtual float GetArterialPressure();
	
	UFUNCTION(BlueprintCallable)
	virtual float GetDiastolicArterialPressure();
	
	UFUNCTION(BlueprintCallable)
	virtual float GetSystolicArterialPressure();
	
	UFUNCTION(BlueprintCallable)
	virtual float GetMeanArterialPressure();
	
	UFUNCTION(BlueprintCallable)
	virtual float GetMeanArterialCarbonDioxidePartialPressure();
	
	UFUNCTION(BlueprintCallable)
	virtual float GetMeanArterialCarbonDioxidePartialPressureDelta();
	
	// --------------- Cardiac --------------- //

	UFUNCTION(BlueprintCallable)
	virtual float GetCardiacIndex();
	
	UFUNCTION(BlueprintCallable)
	virtual float GetCardiacOutput();
	
	UFUNCTION(BlueprintCallable)
	virtual float GetHeartEjectionFraction();
	
	UFUNCTION(BlueprintCallable)
	virtual float GetHeartRate();
	
	UFUNCTION(BlueprintCallable)
	virtual float GetHeartStrokeVolume();
	
	// --------------- Cerebral --------------- //

	UFUNCTION(BlueprintCallable)
	virtual float GetCerebralBloodFlow();
	
	UFUNCTION(BlueprintCallable)
	virtual float GetCerebralPerfusionPressure();
	
	UFUNCTION(BlueprintCallable)
	virtual float GetIntracranialPressure();
	
	// --------------- Pulmonary --------------- //

	UFUNCTION(BlueprintCallable)
	virtual float GetPulmonaryArterialPressure();
	
	UFUNCTION(BlueprintCallable)
	virtual float GetPulmonaryCapillariesWedgePressure();
	
	UFUNCTION(BlueprintCallable)
	virtual float GetPulmonaryDiastolicArterialPressure();
	
	UFUNCTION(BlueprintCallable)
	virtual float GetPulmonaryMeanArterialPressure();
	
	UFUNCTION(BlueprintCallable)
	virtual float GetPulmonaryMeanCapillaryFlow();
	
	UFUNCTION(BlueprintCallable)
	virtual float GetPulmonaryMeanShuntFlow();
	
	UFUNCTION(BlueprintCallable)
	virtual float GetPulmonarySystolicArterialPressure();
	
	UFUNCTION(BlueprintCallable)
	virtual float GetPulmonaryVascularResistance();
	
	UFUNCTION(BlueprintCallable)
	virtual float GetPulmonaryVascularResistanceIndex();
	
	// --------------- Vascular --------------- //

	UFUNCTION(BlueprintCallable)
	virtual float GetBloodVolume();

	UFUNCTION(BlueprintCallable)
	virtual float GetCentralVenousPressure();

	UFUNCTION(BlueprintCallable)
	virtual float GetMeanCentralVenousPressure();

	UFUNCTION(BlueprintCallable)
	virtual float GetMeanSkinFlow();

	UFUNCTION(BlueprintCallable)
	virtual float GetPulsePressure();

	UFUNCTION(BlueprintCallable)
	virtual float GetSystemicVascularResistance();
};
