#pragma once

// BioGears
#include "BioGearsPreHeaderBlock.inl"
#include <biogears/cdm/patient/actions/SEPatientAssessmentRequest.h>
#include <biogears/cdm/patient/assessments/SEPatientAssessment.h>
#include <biogears/cdm/scenario/SEAction.h>
#include "BioGearsPostHeaderBlock.inl"

// VH BioGears Plugin
#include "BioGearsEngine.h"
#include "BioGearsLogger.h"
#include "BioGearsStructs.h"

#include "BioGearsDriver.generated.h"


UCLASS(Blueprintable, Config="BioGears")
class BIOGEARS_UE4_API UBioGearsDriver : public UObject
{
	GENERATED_BODY()

		
	// ---------------------------------
	// --- Delegate
	// ---------------------------------
	
private:
	DECLARE_DYNAMIC_MULTICAST_DELEGATE(FBioGearsEngineInitializedDynamic);
	DECLARE_DYNAMIC_MULTICAST_DELEGATE(FBioGearsScenarioBeginDynamic);
	DECLARE_DYNAMIC_MULTICAST_DELEGATE(FBioGearsPatientDeathDynamic);


	// ---------------------------------
	// --- Member Variables
	// ---------------------------------

public:
	/** Logging Class */
	UPROPERTY(EditDefaultsOnly)
	TSubclassOf<UBioGearsLogger> BGLoggerClass;

	/** Broadcast On Engine Initialization */
	UPROPERTY(BlueprintAssignable)
	FBioGearsEngineInitializedDynamic OnBioGearsEngineInitialized;

	/** Broadcast On Patient/Scenario Loaded */
	UPROPERTY(BlueprintAssignable)
	FBioGearsScenarioBeginDynamic OnBioGearsScenarioBegin;

	/** Broadcast On Patient Irreversible State (Death) */
	UPROPERTY(BlueprintAssignable)
	FBioGearsPatientDeathDynamic OnBioGearsPatientDeath;

protected:
	/** BioGears Engine handling physiology */
	TSharedPtr<FBioGearsEngine> BGEngine;

	/** Forward Logger */
	UPROPERTY(BlueprintReadOnly)
	UBioGearsLogger* BGLogger;

	/** Relative to the project content directory */
	UPROPERTY(Config)
	FString WorkingDirectory;

	/** Relative to the project content directory */
	UPROPERTY(Config)
	FString DataFilesDirectory;

	/** Relative to the project content directory */
	UPROPERTY(Config)
	FString TempDirectory;

	/** Relative to DataFilesDir */
	UPROPERTY(Config)
	TArray<FString> DataFilesSearchDirectories;

	/** Name of the module. This is used when referencing files in "DataFiles/BioGears/<ModuleName>/". */
	UPROPERTY(Config)
	FString ModuleName;

	/** Name Of File For Log Output */
	UPROPERTY(Config)
	FString LogFile;


	// ---------------------------------
	// --- Constructors
	// ---------------------------------

public:
	UBioGearsDriver(const FObjectInitializer& objectInitializer);

	virtual ~UBioGearsDriver();


	// ---------------------------------
	// --- Public Methods
	// ---------------------------------

public:
	/** Initialize Driver With Default Values */
	virtual void InitializeDriver();

	/** Initialize Driver With Log File */
	virtual void InitializeDriver(const FString& logFile);

	/** Load Patient File */
	virtual bool LoadPatient(const FString& patientFile);

	/** Load Patient State File */
	virtual bool LoadPatientState(const FString& stateFile);

	/** Stop BioGears Execution */
	virtual void StopBioGearsEngine();

	// ----------------- Logging ----------------- //

	/**  */
	UBioGearsLogger* GetVHLogger();

	/**  */
	biogears::Logger* GetLogger();
	
	/**  */
	void SetLogLevel(log4cpp::Priority::Value logLevel);

	/**  */
	virtual bool TrackData(const FString& outputFile, TMap<FString, biogears::CCompoundUnit>& data);

	// ---------------- Play Mode ---------------- //

	/** Returns Current State of Play */
	UFUNCTION(BlueprintPure, Category = "VhBioGears")
	EScenarioPlayMode GetPlayMode();

	/** Set Current State of Play */
	UFUNCTION(BlueprintCallable)
	bool SetPlayMode(EScenarioPlayMode mode);

	/** Returns True if Engine is Active & Executing */
	UFUNCTION(BlueprintCallable)
	bool IsEngineActive();

	// ----------------- Actions ----------------- //

	/** Adds Action To Engine Action Queue */
	virtual bool AddAction(TSharedPtr<biogears::SEAction> action);

	/**  */
	bool GetPatientAssessment(biogears::SEPatientAssessment& assessment);

	/**  */
	bool GetPatientAssessmentRequest(biogears::SEPatientAssessmentRequest& request);

	/** Returns List of Actions Generated From Scenario File */
	TArray<CDM::ActionData*> GetActionsFromScenarioFile(const FString& scenarioFile);

	/** Returns State of Tourniquet in Given Compartment */
	UFUNCTION(BlueprintCallable)
	EBioGearsTourniquetLevel IsTourniquetApplied(const FString& compartment);

	// -------------- BioGears Access ------------- //

	/** Returns BioGears Substance Manager */
	biogears::SESubstanceManager* GetSubstanceManager();

	/** Returns BioGears Compound With Given Name */
	const biogears::SESubstanceCompound* GetCompound(const FString& compoundName);

	// --------------- Patient Data --------------- //

	/** Patient Blood Chemistry Data */
	UFUNCTION(BlueprintPure, Category = "VhBioGears")
	FBioGearsAnesthesiaMachine GetAnesthesiaData();

	/** Patient Blood Chemistry Data */
	UFUNCTION(BlueprintPure, Category = "VhBioGears")
	FBioGearsBloodChemistry GetBloodChemistryData();

	/** Patient Blood Data */
	UFUNCTION(BlueprintPure, Category = "VhBioGears")
	FBioGearsBloodCount GetBloodCountData();
	
	/** Patient Cardiovascular System Data */
	UFUNCTION(BlueprintPure, Category = "VhBioGears")
	FBioGearsCardiovascular GetCardiovascularSystemData();
	
	/** Patient Drug Data*/
	UFUNCTION(BlueprintPure, Category = "VhBioGears")
	FBioGearsDrugs GetDrugSystemData();
	
	/** Patient Endocrine System Data */
	UFUNCTION(BlueprintPure, Category = "VhBioGears")
	FBioGearsEndocrine GetEndocrineSystemData();
	
	/** Patient Energy System Data */
	UFUNCTION(BlueprintPure, Category = "VhBioGears")
	FBioGearsEnergy GetEnergySystemData();

	/** BioGears Environment Conditions */
	UFUNCTION(BlueprintPure, Category = "VhBioGears")
	FBioGearsEnvironmentalConditions GetEnvironmentConditions();
	
	/** Patient Gastrointestinal System Data */
	UFUNCTION(BlueprintPure, Category = "VhBioGears")
	FBioGearsGastrointestinal GetGastrointestinalSystemData();
	
	/** Patient Hepatic System Data */
	UFUNCTION(BlueprintPure, Category = "VhBioGears")
	FBioGearsHepatic GetHepaticSystemData();

	/** Patient Inflammatory Resposne Data */
	UFUNCTION(BlueprintPure, Category = "VhBioGears")
	FBioGearsInflamatoryRespose GetInflammatoryResponseData();
	
	/** Patient Nervous System Data */
	UFUNCTION(BlueprintPure, Category = "VhBioGears")
	FBioGearsNervous GetNervousSystemData();

	/** Patient Data */
	UFUNCTION(BlueprintPure, Category = "VhBioGears")
	FBioGearsPatient GetPatientData();
	
	/** Patient Renal System Data */
	UFUNCTION(BlueprintPure, Category = "VhBioGears")
	FBioGearsRenal GetRenalSystemData();
	
	/** Patient Respiratory System Data */
	UFUNCTION(BlueprintPure, Category = "VhBioGears")
	FBioGearsRespiratory GetRespiratorySystemData();
	
	/** Patient Tissue System Data */
	UFUNCTION(BlueprintPure, Category = "VhBioGears")
	FBioGearsTissue GetTissueSystemData();

	// -------------- Infusion Data -------------- //

	/** BioGears Active Substance Infusions */
	UFUNCTION(BlueprintPure, Category = "VhBioGears")
	FBioGearsSubstanceInfusions GetSubstanceInfusions();

	/** BioGears Active Compound Infusions */
	UFUNCTION(BlueprintPure, Category = "VhBioGears")
	FBioGearsCompoundInfusions GetCompoundInfusions();

	// -------------- BioGears Data -------------- //

	/** BioGears Conditions Data */
	UFUNCTION(BlueprintPure, Category = "VhBioGears")
	FBioGearsConditions GetBioGearsConditionsData();
	
	/** BioGears Metrics */
	UFUNCTION(BlueprintPure, Category = "VhBioGears")
	FBioGearsMetrics GetBioGearsMetrics();

	/** BioGears State Data */
	UFUNCTION(BlueprintPure, Category = "VhBioGears")
	FBioGearsState GetBioGearsStateData();


	// ---------------------------------
	// --- Implementation Methods
	// ---------------------------------
	
private:
	/** Broadcast BioGears Patient Death */
	void BroadcastPatientDeath();

	// ------------- File Structure ------------- //

	/** Gets Path of Given File */
	/** Returns True if File is Found */
	bool FindDataFile(const FString& file, FString& result, bool bGetFullPath);

	/** Returns Path to Working Directory */
	FString GetWorkingDirectory(bool bAbsolutePath);

	/** Returns Path to Temporary Directory */
	FString GetTempDirectory(bool bGetFullPath);

	/** Return Path to Module's Temporary Directory */
	FString GetModuleTempDirectory(bool bGetFullPath);

	/** Returns Path To Data Files Directory */
	FString GetDataFilesDirectory(bool bGetFullPath);

	/** Converts Relative Given Path to Full Path */
	FString ConvertProjectPathToFull(const FString& directory);

	/** Converts Collapsed Path to Actual Path */
	FString FixedCollapseRelativeDirectories(const FString& path);
};
