#pragma once

#if  defined(WITH_BIOGEARS_BINDING) // TODO: Remove when biogears works on android
// BioGears
#include "VH_BioGearsPreHeaderBlock.inl"
#include <biogears/engine/Controller/BioGearsEngine.h>
#include <biogears/schema/biogears/BioGears.hxx>
#include "VH_BioGearsPostHeaderBlock.inl"
#endif

// Engine
#include "Containers/Queue.h"
#include "HAL/Runnable.h"
#include "HAL/RunnableThread.h"
#include "HAL/ThreadSafeBool.h"

// VH BioGears Plugin
#include "VH_BioGearsEnums.h"
#include "VH_BioGearsLogger.h"
#include "VH_BioGearsPhysiology.h"

// Generated
#include "VH_BioGearsEngine.generated.h"


/**
 * The driving class in charge of creating and managing BioGears physiology simulation.
 * Handles the processing of BioGears actions and the updating of simulation data.
 *
 */
UCLASS(Blueprintable, Config = "VH_BioGears")
class VH_BIOGEARS_API UVH_BioGearsEngine : public UObject, public FRunnable
{
	GENERATED_BODY()


	// ---------------------------------
	// --- Constructors
	// ---------------------------------

public:
	UVH_BioGearsEngine(const FObjectInitializer& objectInitializer);

	virtual ~UVH_BioGearsEngine();


	// ---------------------------------
	// --- Variables
	// ---------------------------------

protected:
	UPROPERTY()
	UVH_BioGearsPhysiology* Physiology;

	/** Simulation Play Type */
	UPROPERTY()
	EScenarioPlayMode ScenarioPlayMode;

	/** Has Engine Been Initialized */
	FThreadSafeBool bInitialized;

	/** Is Data Being Tracked */
	FThreadSafeBool bTrackingData;

	UPROPERTY()
	float SimulationTime;

	// ---------- Config Variables ---------- //

	/**
	 * Root directory for BioGears files/folders.
	 * Relative to the project's Content directory (e.g. Game/Content/).
	 */
	UPROPERTY(Config)
	FString WorkingDirectory;

	/**
	 * Temp directory for BioGears files/folders.
	 * Relative to the project's Content directory (e.g. Game/Content/).
	 */
	UPROPERTY(Config)
	FString TempDirectory;

	/**
	 * Root directory for patient files/folders.
	 * Relative to WorkingDirectory.
	 */
	UPROPERTY(Config)
	FString PatientsDirectory;

	/**
	 * Root directory for scenario files/folders.
	 * Relative to WorkingDirectory.
	 */
	UPROPERTY(Config)
	FString ScenariosDirectory;

	/**
	 * Root directory for patient state files/folders.
	 * Relative to WorkingDirectory.
	 */
	UPROPERTY(Config)
	FString PatientStatesDirectory;

	/**
	 * BioGears logging output file.
	 * Relative to the project's Logs directory (e.g. Game/Saved/Logs).
	 */
	UPROPERTY(Config)
	FString LogFile;

private:
#if  defined(WITH_BIOGEARS_BINDING) // TODO: Remove when biogears works on android
	/** BioGears Physiology Engine */
	biogears::BioGearsEngine* BGEngine = nullptr;
#endif

	/** */
	FRunnableThread* Thread;

#if  defined(WITH_BIOGEARS_BINDING) // TODO: Remove when biogears works on android
	/** Actions to be executed between BioGears Updates */
	TQueue<TSharedPtr<biogears::SEAction>> ActionQueue;
#endif

	/** Is Engine Stopping */
	FThreadSafeBool bStopping;

	/** Critical Sections */
	FCriticalSection ActionsCriticalSection;
	FCriticalSection ModeCriticalSection;
	FCriticalSection EngineCriticalSection;


	// ---------------------------------
	// --- Inherited (FRunnable)
	// ---------------------------------

protected:
	virtual bool Init() override;
	virtual uint32 Run() override;
	virtual void Stop() override;
	virtual void Exit() override;


	// ---------------------------------
	// --- API
	// ---------------------------------

public:
	/** Initializes BioGears Engine and Spawns Thread for Managing Engine */
	/** Returns True if Initialized & Thread Created Successfully */
	UFUNCTION(BlueprintCallable)
	virtual bool InitializeEngine(UVH_BioGearsLogger* logger, UVH_BioGearsPhysiology* bgPhysiology);

	/** Sets State of Engine by Patient File */
	/** Returns True if File Exists & Set Successfully */
	UFUNCTION(BlueprintCallable)
	virtual bool LoadPatient(const FString& patientFile);

	/** Sets State of Engine by Patient State File */
	/** Returns True if File Exists & Set Successfully */
	UFUNCTION(BlueprintCallable)
	virtual bool LoadPatientState(const FString& patientStateFile);

#if  defined(WITH_BIOGEARS_BINDING) // TODO: Remove when biogears works on android
	/** Tracks Physiology State & Outputs Results to File */
	virtual void TrackData(const FString& outputFile, TMap<FString, biogears::CCompoundUnit>& trackedData);
#endif

	// ------------ Engine State ------------ //

	/** Returns True if Engine & Thread are Valid */
	UFUNCTION(BlueprintCallable)
	bool IsEngineActive();

	/** Returns True if Engine is Valid & Initialized */
	UFUNCTION(BlueprintCallable)
	bool IsEngineReady();

	// -------------- Play Mode -------------- //

	/** Returns the Current Play Mode/Rate (Paused, Play, Fast Forward) */
	UFUNCTION(BlueprintCallable)
	EScenarioPlayMode GetPlayMode();

	/** Sets the Current Play Mode/Rate (Paused, Play, Fast Forward) */
	UFUNCTION(BlueprintCallable)
	void SetPlayMode(EScenarioPlayMode playMode);

	// --------------- Timing  --------------- //

	/** Returns the Length of Time Simulated by Engine */
	UFUNCTION(BlueprintCallable)
	virtual float GetSimulationTime();

	// --------------- Actions --------------- //

#if  defined(WITH_BIOGEARS_BINDING) // TODO: Remove when biogears works on android
	/** Adds BioGears Action to be Processed */
	/** Returns True if Queued Successfully */
	FThreadSafeBool AddAction(TSharedPtr<biogears::SEAction> action);

	/** Processes Patient Assessment */
	/** Returns True of Processed Successfully */
	bool ProcessPatientAssessment(biogears::SEPatientAssessment& assessment);

	/** Processes Patient Assessment Request */
	/** Returns True of Processed Successfully */
	bool ProcessPatientAssessmentRequest(biogears::SEPatientAssessmentRequest& request);
#endif

	// --------------- Scenario -------------- //

#if  defined(WITH_BIOGEARS_BINDING) // TODO: Remove when biogears works on android
	/** Reads a File of Patient Actions & Converts it to a List of Actions */
	/** Returns List of Actions */
	TArray<CDM::ActionData*> GetActionsFromScenarioFile(const FString& fileName);
#endif

	// -------------- Substance Access ------------- //

#if  defined(WITH_BIOGEARS_BINDING) // TODO: Remove when biogears works on android
	/** Returns Engine's Substance Manager */
	biogears::SESubstanceManager* GetSubstanceManager();
#endif

	// -------------- Files ------------- //

	/** Returns True if Working Directory exists */
	bool GetWorkingDirectory(bool bAbsolutePath, FString& outDirectory);

	/** Returns True if Temporary Directory exists */
	bool GetTempDirectory(bool bAbsolutePath, FString& outDirectory);

	/** Returns True if Root Directory of Patient Files exists */
	bool GetPatientsDirectory(bool bAbsolutePath, FString& outDirectory);

	/** Returns True if Root Directory of Patient State Files exists */
	bool GetPatientStatesDirectory(bool bAbsolutePath, FString& outDirectory);

	/** Return True if Root Directory of Scenario Files exists */
	bool GetScenariosDirectory(bool bAbsolutePath, FString& outDirectory);

	/** Sets the Working Directory Relative to Project Content Directory */
	/** Returns True if Directory Exists */
	bool SetWorkingDirectory(const FString& directory);

	/** Sets Patient Files Root Directory Relative to Working Directory */
	/** Returns True if Directory Exists */
	bool SetPatientsDirectory(const FString& directory);

	/** Sets Patient State Files Root Directory Relative to Working Directory */
	/** Returns True if Directory Exists */
	bool SetPatientStatesDirectory(const FString& directory);

	/** Sets Scenario Files Root Directory Relative to Working Directory */
	/** Returns True if Directory Exists */
	bool SetScenariosDirectory(const FString& directory);


	// ---------------------------------
	// --- Implementation
	// ---------------------------------
	void BeginDestroy()	override;
private:
	UWorld* GetVHWorld();

#if  defined(WITH_BIOGEARS_BINDING) // TODO: Remove when biogears works on android
	biogears::Logger* GetLogger();
#endif

	/** Progresses Engine Time by Given Seconds*/
	void AdvanceTime(float seconds);

	// --------------- Actions --------------- //

	/** Returns True if No Actions are Waiting to be Processed */
	FThreadSafeBool IsActionQueueEmpty();

#if  defined(WITH_BIOGEARS_BINDING) // TODO: Remove when biogears works on android
	/** Returns Next Action to be Processed */
	TSharedPtr<biogears::SEAction> GetTopAction();

	/** Passes Action To Engine to be Processed */
	bool ProcessAction(const biogears::SEAction& action);
#endif

	// ---------------- Data ---------------- //

	void UpdateData();

	void UpdateBioGearsMetrics();

	// ------------- File Structure ------------- //

	/** Gets Path of Given Patient File */
	/** Returns True if File is Found */
	bool FindPatientFile(const FString& file, FString& outPath, bool bGetFullPath);

	/** Gets Path of Given Patient State File */
	/** Returns True if File is Found */
	bool FindPatientStateFile(const FString& file, FString& outPath, bool bGetFullPath);

	/** Gets Path of Given Scenario File */
	/** Returns True if File is Found */
	bool FindScenarioFile(const FString& file, FString& outPath, bool bGetFullPath);


	/** Gets Path of Given File */
	/** Returns True if File is Found */
	bool FindFile(FString& root, const FString& file, FString& outPath);

	/** Converts Relative Given Path to Full Path */
	FString ConvertProjectPathToFull(const FString& directory);

	/** Converts Collapsed Path to Actual Path */
	FString FixedCollapseRelativeDirectories(const FString& path);
};
