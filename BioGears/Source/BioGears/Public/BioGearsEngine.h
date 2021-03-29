#pragma once

// BioGears
#include "BioGearsPreHeaderBlock.inl"
#include "engine/Controller/BioGearsEngine.h"
#include "schema/biogears/BioGears.hxx"
#include "BioGearsPostHeaderBlock.inl"

// Engine
#include "HAL/RunnableThread.h"
#include "HAL/ThreadSafeBool.h"

// VH BioGears Plugin
#include "BioGearsLogger.h"
#include "BioGearsStructs.h"
#include "BioGearsTypes_Enums.h"

class UBioGearsDriver;

/** */
class BIOGEARS_UE4_API FBioGearsEngine : public FRunnable
{

	// ---------------------------------
	// --- Delegates
	// ---------------------------------

private:
	DECLARE_DELEGATE(FBioGearsPatientDeathDynamic);


	// ---------------------------------
	// --- Member Variables
	// ---------------------------------

public:
	/** */
	FBioGearsPatientDeathDynamic OnBioGearsPatientDeath;

private:
	/** BioGears Physiology Engine */
	UPROPERTY()
	TUniquePtr<biogears::BioGearsEngine> BGEngine;

	/** */
	UPROPERTY()
	FRunnableThread* Thread;

	/** Actions to be executed between BioGears Updates */
	TQueue<TSharedPtr<biogears::SEAction>> ActionQueue;

	/** Simulation Play Type */
	EScenarioPlayMode ScenarioPlayMode;

	/** Has Engine Been Initialized */
	FThreadSafeBool bInitialized;

	/** Is Data Being Tracked */
	FThreadSafeBool bTrackingData;

	/** Is Engine Stopping */
	FThreadSafeBool bStopping;

	/** Thread Critical Sections */
	FCriticalSection ActionsCriticalSection;
	FCriticalSection DataCriticalSection;
	FCriticalSection ModeCriticalSection;

	/** Patient Data */
	FBioGearsAnesthesiaMachine BioGearsAnesthesiaMachine;
	FBioGearsBloodChemistry BloodChemistry;
	FBioGearsBloodCount BloodSystem;
	FBioGearsCardiovascular CardiovascularSystem;
	FBioGearsDrugs DrugSystem;
	FBioGearsEndocrine EndocrineSystem;
	FBioGearsEnergy EnergySystem;
	FBioGearsEnvironmentalConditions EnvironmentConditions;
	FBioGearsGastrointestinal GastrointestinalSystem;
	FBioGearsHepatic HepaticSystem;
	FBioGearsInflamatoryRespose InflammatoryResponse;
	FBioGearsNervous NervousSystem;
	FBioGearsPatient PatientData;
	FBioGearsRenal RenalSystem;
	FBioGearsRespiratory RespiratorySystem;
	FBioGearsTissue TissueSystem;

	/** Infusion Data */
	FBioGearsCompoundInfusions CompoundInfusions;
	FBioGearsSubstanceInfusions SubstanceInfusions;

	/** BioGears Data */
	FBioGearsConditions BioGearsConditions;
	FBioGearsMetrics BioGearsMetrics;
	FBioGearsState BioGearsState;


	// ---------------------------------
	// --- Constructors
	// ---------------------------------

public:
	FBioGearsEngine();

	~FBioGearsEngine();


	// ---------------------------------
	// --- Inherited Methods (FRunnable)
	// ---------------------------------
	
public:
	bool Init() override;
	uint32 Run() override;
	void Stop() override;
	void Exit() override;


	// ---------------------------------
	// --- Public Methods
	// ---------------------------------

public:
	bool InitializeEngine(UBioGearsDriver* driver, const FString& workingDir, const FString& logFile);

	bool LoadPatient(UBioGearsDriver* driver, const FString& patientFile);

	bool LoadPatientState(UBioGearsDriver* driver, const FString& patientStateFile);

	void TrackData(const FString& outputFile, TMap<FString, biogears::CCompoundUnit>& trackedData);

	biogears::Logger* GetLogger();

	// ------------ Engine State ------------ //

	bool IsEngineReady();

	bool IsEngineActive();

	// -------------- Play Mode -------------- //

	EScenarioPlayMode GetPlayMode();
	
	void SetPlayMode(EScenarioPlayMode playMode);

	// --------------- Actions --------------- //

public:
	FThreadSafeBool AddAction(TSharedPtr<biogears::SEAction> action);

	bool ProcessPatientAssessment(biogears::SEPatientAssessment& assessment);

	void GetPatientAssessment(biogears::SEPatientAssessment& assessment);

	void GetPatientAssessmentRequest(biogears::SEPatientAssessmentRequest& request);

	TArray<CDM::ActionData*> GetActionsFromScenarioFile(const FString& fileName);

	// --------- BioGears Patient Condition --------- //

	EBioGearsTourniquetLevel IsTourniquetApplied(const FString& compartment);

	EBioGearsChestSide HasTensionPneumothorax();

	EBioGearsChestSide HasNeedleDecompression();

	// -------------- Substance Access ------------- //

	biogears::SESubstanceManager* GetSubstanceManager();

	const biogears::SESubstance* const GetSubstance(const FString& substanceName);
	const biogears::SESubstanceCompound* const GetCompound(const FString& compoundName);

	// --------------- Patient Data --------------- //
	
	FBioGearsAnesthesiaMachine GetAnesthesiaMachine();
	FBioGearsBloodChemistry GetBloodChemistryData();
	FBioGearsBloodCount GetBloodCountData();
	FBioGearsInflamatoryRespose GetInflammatoryResponseData();
	FBioGearsCardiovascular GetCardiovascularSystemData();
	FBioGearsDrugs GetDrugSystemData();
	FBioGearsEndocrine GetEndocrineSystemData();
	FBioGearsEnergy GetEnergySystemData();
	FBioGearsEnvironmentalConditions GetEnvironmentConditions();
	FBioGearsGastrointestinal GetGastrointestinalSystemData();
	FBioGearsHepatic GetHepaticSystemData();
	FBioGearsNervous GetNervousSystemData();
	FBioGearsPatient GetPatientData();
	FBioGearsRenal GetRenalSystemData();
	FBioGearsRespiratory GetRespiratorySystemData();
	FBioGearsTissue GetTissueSystemData();

	// -------------- Infusion Data -------------- //

	FBioGearsCompoundInfusions GetCompoundInfusions();
	FBioGearsSubstanceInfusions GetSubstanceInfusions();

	// -------------- BioGears Data -------------- //

	FBioGearsConditions GetBioGearsConditionsData();
	FBioGearsMetrics GetBioGearsMetrics();
	FBioGearsState GetBioGearsStateData();
	

	// ---------------------------------
	// --- Implementation Methods
	// ---------------------------------

private:
	UWorld* GetVHWorld();

	void AdvanceTime(float seconds);

	// --------------- Actions --------------- //

	FThreadSafeBool IsActionQueueEmpty();

	TSharedPtr<biogears::SEAction> GetTopAction();

	bool ProcessAction(const biogears::SEAction& action);

	void ClearActions();

	// ---------------- Data ---------------- //

	void UpdateEngineData();

	// --------------- Patient Data --------------- //

	void UpdateAnesthesiaMachine();
	void UpdateBloodChemistry();
	void UpdateBloodCountData();
	void UpdateCardiovascularSystem();
	void UpdateDrugSystem();
	void UpdateEndocrineSystem();
	void UpdateEnergySystem();
	void UpdateEnvironmentConditions();
	void UpdateGastrointestinalSystem();
	void UpdateHepaticSystem();
	void UpdateInflammatoryResponse();
	void UpdateNervousSystem();
	void UpdatePatientData();
	void UpdateRenalSystem();
	void UpdateRespiratorySystem();
	void UpdateTissueSystem();

	// -------------- Infusion Data -------------- //

	void UpdateSubstanceInfusions();
	void UpdateCompoundInfusions();

	// -------------- BioGears Data -------------- //

	void UpdateBioGearsConditions();
	void UpdateBioGearsState();
	void UpdateBioGearsMetrics();
};
