#pragma once

#include "VH_PatientSubsystem.h"

// Engine
#include "Templates/SubclassOf.h"

#if  defined(WITH_BIOGEARS_BINDING) // TODO: Remove when biogears works on android
// BioGears
#include "VH_BioGearsPreHeaderBlock.inl"
#include "biogears/engine/Controller/BioGearsEngine.h"
#include "biogears/schema/biogears/BioGears.hxx"
#include "VH_BioGearsPostHeaderBlock.inl"
#endif

// VH BioGears Plugin
#include "VH_BioGearsEnums.h"
#include "VH_PatientPupillaryResponse.h"

// Generated
#include "VH_PatientNervousSystem.generated.h"

/*
 * Information about the patient's nervous system
 *
 * The nervous system carries data via electrical signals to and from the brain.
 * The data helps you move your limbs and feel sensations, such as pain.
 * These electrical signals travel between your brain, skin, organs, glands and muscles.
 */
UCLASS(Blueprintable)
class VH_BIOGEARS_API UVH_PatientNervousSystem : public UVH_PatientSubsystem
{
	GENERATED_BODY()


	// ---------------------------------
	// --- Constructors
	// ---------------------------------

public:
	UVH_PatientNervousSystem(const FObjectInitializer& objectInitializer);

	virtual ~UVH_PatientNervousSystem();


	// ---------------------------------
	// --- Variables
	// ---------------------------------

protected:
	UPROPERTY(EditDefaultsOnly)
	TSubclassOf<UVH_PatientPupillaryResponse> PupillaryResponseClass;

	/***/
	UPROPERTY()
	float AttentionLapses;

	/***/
	UPROPERTY()
	float BiologicalDebt;

	/***/
	UPROPERTY()
	float ComplianceScale;

	/***/
	UPROPERTY()
	float HeartRateScale;

	/***/
	UPROPERTY()
	float HeartElastanceScale;

	/***/
	UPROPERTY()
	UVH_PatientPupillaryResponse* LeftEyePupillaryResponse;

	/***/
	UPROPERTY()
	float PainVisualAnalogueScale;

	/***/
	UPROPERTY()
	float ReactionTime;

	/***/
	UPROPERTY()
	float ResistanceScaleExtrasplanchnic;

	/***/
	UPROPERTY()
	float ResistanceScaleMuscle;

	/***/
	UPROPERTY()
	float ResistanceScaleMyocardium;

	/***/
	UPROPERTY()
	float ResistanceScaleSplanchnic;
	
	/***/
	UPROPERTY()
	float RichmondAgitationSedationScale;
	
	/***/
	UPROPERTY()
	UVH_PatientPupillaryResponse* RightEyePupillaryResponse;

	/***/
	UPROPERTY()
	EPatientSleep SleepState;

	/***/
	UPROPERTY()
	float SleepTime;
	
	/***/
	UPROPERTY()
	float WakeTime;

private:
	FCriticalSection CriticalSection;


	// ---------------------------------
	// --- API
	// ---------------------------------

public:
	virtual void InitializeNervous();

#if  defined(WITH_BIOGEARS_BINDING) // TODO: Remove when biogears works on android
	virtual void UpdateValues(const biogears::SENervousSystem* nervous);
#endif

	UFUNCTION(BlueprintCallable)
	virtual float GetAttentionLapses();

	UFUNCTION(BlueprintCallable)
	virtual float GetBiologicalDebt();

	UFUNCTION(BlueprintCallable)
	virtual float GetComplianceScale();
	
	UFUNCTION(BlueprintCallable)
	virtual float GetHeartRateScale();
	
	UFUNCTION(BlueprintCallable)
	virtual float GetHeartElastanceScale();
	
	UFUNCTION(BlueprintCallable)
	UVH_PatientPupillaryResponse* GetLeftEyePupillaryResponse() const { return LeftEyePupillaryResponse; }

	UFUNCTION(BlueprintCallable)
	virtual float GetPainVisualAnalogueScale();

	UFUNCTION(BlueprintCallable)
	virtual float GetReactionTime();

	UFUNCTION(BlueprintCallable)
	virtual float GetResistanceScaleExtrasplanchnic();
	
	UFUNCTION(BlueprintCallable)
	virtual float GetResistanceScaleMuscle();
	
	UFUNCTION(BlueprintCallable)
	virtual float GetResistanceScaleMyocardium();
	
	UFUNCTION(BlueprintCallable)
	virtual float GetResistanceScaleSplanchnic();
	
	UFUNCTION(BlueprintCallable)
	virtual float GetRichmondAgitationSedationScale();

	UFUNCTION(BlueprintCallable)
	UVH_PatientPupillaryResponse* GetRightEyePupillaryResponse() const { return RightEyePupillaryResponse; }


	UFUNCTION(BlueprintCallable)
	EPatientSleep GetSleepState();

	UFUNCTION(BlueprintCallable)
	virtual float GetSleepTime();

	UFUNCTION(BlueprintCallable)
	virtual float GetWakeTime();
};
