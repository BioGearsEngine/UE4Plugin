#pragma once

// BioGears
#include "BioGearsPreHeaderBlock.inl"
#include "cdm/patient/assessments/SEPatientAssessment.h"
#include "cdm/scenario/SESerializeState.h"
#include "schema/cdm/PatientActions.hxx"
#include "schema/cdm/PatientAssessments.hxx"
#include "BioGearsPostHeaderBlock.inl"

// VH BioGears Plugin
#include "BioGearsDriver.h"
#include "BioGearsLogger.h"
#include "BioGearsStructs.h"

#include "BioGearsScenarioDriver.generated.h"


UCLASS(Blueprintable, Config="BioGears")
class BIOGEARS_UE4_API UBioGearsScenarioDriver : public UObject, public FTickableGameObject
{
	GENERATED_BODY()


	// ---------------------------------
	// --- Member Variables
	// ---------------------------------

protected:
	/** BioGears Driver for Executing Actions*/
	UPROPERTY(BlueprintReadOnly)
	UBioGearsDriver* BGDriver;

	/** BioGears Actions to Execute*/
	TArray<CDM::ActionData*> Actions;

	/** BioGears Scenario Containing Actions */
	UPROPERTY(BlueprintReadOnly)
	FString ScenarioFile;

	/** Current Index of Executed Actions */
	UPROPERTY(BlueprintReadOnly)
	int ActionIndex;

	/** Returns True if Actions Are Being Executed */
	UPROPERTY(BlueprintReadOnly)
	bool bRunningScenario;

	/** Returns True If Actions Aren't Being Delayed */
	UPROPERTY(BlueprintReadOnly)
	bool bProcessAction;

	/** Time to Delay Next Action */
	UPROPERTY(BlueprintReadOnly)
	float DelayedActionSimTime;


	// ---------------------------------
	// --- Constructors
	// ---------------------------------

public:
	UBioGearsScenarioDriver(const FObjectInitializer& objectInitializer);

	virtual ~UBioGearsScenarioDriver();


	// ---------------------------------
	// --- Inherited Methods (FTickableGameObject)
	// ---------------------------------

private:
	void Tick(float deltaTime) override;
	TStatId GetStatId(void) const override;


	// ---------------------------------
	// --- Public Methods
	// ---------------------------------

public:
	/** Generates Action List From File & Prepares Driver for Action Execution */
	UFUNCTION(BlueprintCallable)
	virtual void InitializeDriver(UBioGearsDriver* driver, const FString& file);

	/** Executes Actions */
	UFUNCTION(BlueprintCallable)
	virtual void StartScenario();

	/** Currently Loaded Scenario File*/
	UFUNCTION(BlueprintCallable)
	FString GetScenarioFile();

	/** Returns True if Valid Actions Are Loaded */
	UFUNCTION(BlueprintCallable)
	bool IsValid();


	// ---------------------------------
	// --- Implementation Methods
	// ---------------------------------

protected:
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
};
