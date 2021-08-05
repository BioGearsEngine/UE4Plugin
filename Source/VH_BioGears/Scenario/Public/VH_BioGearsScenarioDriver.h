#pragma once

// Engine
#include "UObject/Object.h"
#include "Tickable.h"
#include "Templates/SubclassOf.h"

#if  defined(WITH_BIOGEARS_BINDING) // TODO: Remove when biogears works on android
// BioGears
#include "VH_BioGearsPreHeaderBlock.inl"
#include "biogears/cdm/patient/assessments/SEPatientAssessment.h"
#include "biogears/cdm/scenario/SEAdvanceTime.h"
#include "biogears/cdm/scenario/SESerializeState.h"
#include "biogears/cdm/system/equipment/Anesthesia/actions/SEAnesthesiaMachineAction.h"
#include "biogears/schema/cdm/EnvironmentActions.hxx"
#include "biogears/schema/cdm/PatientActions.hxx"
#include "biogears/schema/cdm/PatientAssessments.hxx"
#include "VH_BioGearsPostHeaderBlock.inl"
#endif

// VH BioGears Plugin
#include "VH_BioGearsLogger.h"
#include "VH_BioGearsStructs.h"
#include "VH_BiogearsEngine.h"

// Generated
#include "VH_BioGearsScenarioDriver.generated.h"

/*
 * Driver for running automated scenario.
 * Loads scenario XML and executes the instructions in sequential order
 *
 */
UCLASS(Blueprintable)
class VH_BIOGEARS_API UVH_BioGearsScenarioDriver : public UObject, public FTickableGameObject
{
	GENERATED_BODY()


	// ---------------------------------
	// --- Constructors
	// ---------------------------------

public:
	UVH_BioGearsScenarioDriver(const FObjectInitializer& objectInitializer);

	virtual ~UVH_BioGearsScenarioDriver();


	// ---------------------------------
	// --- Variables
	// ---------------------------------

protected:
	UVH_BioGearsEngine* Engine;

#if  defined(WITH_BIOGEARS_BINDING) // TODO: Remove when biogears works on android
	/** BioGears Actions to Execute*/
	TArray<CDM::ActionData*> Actions;
#endif

	/** BioGears Scenario Containing Actions */
	UPROPERTY(BlueprintReadOnly)
	FString ScenarioFile;

	/** Current Index of Executed Actions */
	UPROPERTY(BlueprintReadOnly)
	int ActionIndex;

	/** Returns True if Actions Are Being Executed */
	UPROPERTY(BlueprintReadOnly)
	bool bRunningScenario;

	/** Time Delay on Next Action */
	UPROPERTY(BlueprintReadOnly)
	float ActionDelay;


	// ---------------------------------
	// --- Inherited (FTickableGameObject)
	// ---------------------------------

private:
	void Tick(float deltaTime) override;
	TStatId GetStatId(void) const override;


	// ---------------------------------
	// --- API
	// ---------------------------------

public:
	/** Generates Action List From File & Prepares Driver for Action Execution */
	virtual void InitializeDriver(UVH_BioGearsEngine* inEngine, const FString& file);

	/** Executes Actions */
	UFUNCTION(BlueprintCallable)
	virtual void StartScenario();

	/** Currently Loaded Scenario File*/
	UFUNCTION(BlueprintCallable)
	FString GetScenarioFile();

	/** Returns True if Valid Actions Are Loaded */
	UFUNCTION(BlueprintCallable)
	bool IsScenarioValid();


	// ---------------------------------
	// --- Implementation
	// ---------------------------------

protected:
#if  defined(WITH_BIOGEARS_BINDING) // TODO: Remove when biogears works on android
	TArray<CDM::ActionData*> PopulateActionList();

	void DelayNextActionBy(float seconds);

	virtual void ProcessNextAction();
	virtual bool ProcessAction(CDM::ActionData* action);
	virtual bool ProcessTimeAdvancement(const CDM::AdvanceTimeData* advancement);
	virtual bool ProcessPatientSerialization(const CDM::SerializeStateData* serialize);
	virtual bool ProcessPatientAssessment(const CDM::PatientAssessmentRequestData* assessment);
	virtual bool ProcessPatientAction(const CDM::PatientActionData* action);
	virtual bool ProcessAnesthesiaMachineAction(const CDM::AnesthesiaMachineActionData* action);
	virtual bool ProcessEnvironmentAction(const CDM::EnvironmentActionData* action);

	virtual bool ProcessConsumeNutrients(const CDM::ConsumeNutrientsData* nutrientsData);
	virtual bool ProcessSubstanceInfusion(const CDM::SubstanceInfusionData* infusionData);
	virtual bool ProcessSubstanceCompoundInfusion(const CDM::SubstanceCompoundInfusionData* infusionData);
	virtual bool ProcessSubstanceBolus(const CDM::SubstanceBolusData* bolusData);
	virtual bool ProcessThermalApplication(const CDM::ThermalApplicationData* thermalData);
	virtual bool ProcessTourniquet(const CDM::TourniquetData* tourniquetData);
	virtual bool ProcessNeedleDecompression(const CDM::NeedleDecompressionData* needleData);
	virtual bool ProcessInfection(const CDM::InfectionData* infectionData);
	virtual bool ProcessTensionPneumothorax(const CDM::TensionPneumothoraxData* pneumothoraxData);
	virtual bool ProcessHemorrhage(const CDM::HemorrhageData* hemorrhageData);
	virtual bool ProcessPainStimulus(const CDM::PainStimulusData* painData);
	virtual bool ProcessUrinate(const CDM::UrinateData* urinateData);
	virtual bool ProcessAnesthesiaMachineConfiguration(const CDM::AnesthesiaMachineConfigurationData* anesthesiaData);
#endif
};
