#include "VH_BioGearsEngine.h"

#if  defined(WITH_BIOGEARS_BINDING) // TODO: Remove when biogears works on android
// BioGears
#include "VH_BioGearsPreHeaderBlock.inl"
#include <biogears/cdm/scenario/SEScenario.h>
#include <biogears/io/io-manager.h>
#include <biogears/io/directories/states.h>
#include <biogears/io/directories/patients.h>
#include <biogears/filesystem/path.h>
#include "VH_BioGearsPostHeaderBlock.inl"
#endif

// Engine
#include <map>

// VH BioGears Plugin
#include "VH_BioGears.h"


// ---------------------------------
// --- Constructors
// ---------------------------------

UVH_BioGearsEngine::UVH_BioGearsEngine(const FObjectInitializer& objectInitializer) :
	ScenarioPlayMode(EScenarioPlayMode::Paused),
	bInitialized(false),
	bTrackingData(false),
	SimulationTime(0.0f),
	BGEngine(nullptr),
	bStopping(true)
{}

UVH_BioGearsEngine::~UVH_BioGearsEngine()
{
	if (Thread != nullptr)
	{
		Thread->Kill();
	}
}


// ---------------------------------
// --- Inherited (FRunnable)
// ---------------------------------

bool UVH_BioGearsEngine::Init()
{
	UE_LOG(VH_BioGears, VeryVerbose, TEXT("-- UVH_BioGearsEngine::Init()"));

	bStopping = false;

	return true;
}

uint32 UVH_BioGearsEngine::Run()
{
	UWorld* world = GetVHWorld();
	float timeOfLastAdvancment = (world != nullptr) ? world->GetTimeSeconds() : 0.0f;
	float timeBetweenAdvancements = (1.0f / 60.0f);

	float timeOfLastDataRequest = (world != nullptr) ? world->GetTimeSeconds() : 0.0f;
	bool bAppendDataRequests = false;

	while (!bStopping)
	{
		FScopeLock lock(&EngineCriticalSection);
		float currentTime = (world != nullptr) ? world->GetTimeSeconds() : 0.0f;

#if  defined(WITH_BIOGEARS_BINDING) // TODO: Remove when biogears works on android
		if (bInitialized && BGEngine && GetPlayMode() != EScenarioPlayMode::Paused)
		{
			// Data Request
			float timeBetweenDataRequests = 1.0f / BGEngine->GetEngineTrack()->GetDataRequestManager().GetSamplesPerSecond();
			float dDataRequestTime = currentTime - timeOfLastDataRequest;

			if (bTrackingData && dDataRequestTime > timeBetweenDataRequests)
			{
				// Write out data requests
				BGEngine->GetEngineTrack()->TrackData(BGEngine->GetSimulationTime(biogears::TimeUnit::s), bAppendDataRequests);
				bAppendDataRequests = true;

				// Update time of data request
				timeOfLastDataRequest = currentTime;
			}

			// Engine Update
			float dTime = currentTime - timeOfLastAdvancment;
			if (dTime > timeBetweenAdvancements)
			{
				// Perform Actions
				while (!IsActionQueueEmpty())
				{
					TSharedPtr<biogears::SEAction> action = GetTopAction();
					ProcessAction(*action.Get());
				}

				// Update Data
				UpdateData();

				// Advance Time
				float step = (ScenarioPlayMode == EScenarioPlayMode::Play) ? dTime : dTime * 6.0f;
				AdvanceTime(step);

				// Check if patient is alive
				if (Physiology != nullptr && Physiology->GetPatientBody()->GetEvents()->HasIrreversibleState())
				{
					// Exit execution loop
					break;
				}

				// Update time of engine update
				timeOfLastAdvancment = currentTime;
			}
		}
#endif
	}

	return 0;
}

void UVH_BioGearsEngine::Stop()
{
	UE_LOG(VH_BioGears, VeryVerbose, TEXT("-- UVH_BioGearsEngine::Stop()"));

	bStopping = true;
}

void UVH_BioGearsEngine::Exit()
{
	UE_LOG(VH_BioGears, VeryVerbose, TEXT("-- UVH_BioGearsEngine::Exit()"));
}


// ---------------------------------
// --- API
// ---------------------------------

bool UVH_BioGearsEngine::InitializeEngine(UVH_BioGearsLogger* logger, UVH_BioGearsPhysiology* physiology)
{
#if  defined(WITH_BIOGEARS_BINDING) // TODO: Remove when biogears works on android
	Physiology = physiology;

	FString workingDirectoryFull;
	if (GetWorkingDirectory(true, workingDirectoryFull))
	{
		UE_LOG(VH_BioGears, VeryVerbose, TEXT("WorkingDirectory: '%s'"), *workingDirectoryFull);

		// Initialize Physiology Engine
		FString fullLogFile = FPaths::Combine(FPaths::ProjectLogDir(), LogFile);
		//biogears::Logger* bgLogger = biogears::create_logger(TCHAR_TO_ANSI(*fullLogFile));

		BGEngine = nullptr;
		BGEngine = biogears::create_biogears_engine(TCHAR_TO_ANSI(*fullLogFile), TCHAR_TO_ANSI(*workingDirectoryFull));

		if (logger != nullptr)
		{
			BGEngine->GetLogger()->SetForward(logger);
		}

		// Create Worker Thread to advance engine
		Thread = FRunnableThread::Create(this, TEXT("BioGears Worker"));

		return true;
	}
	else
	{
		UE_LOG(VH_BioGears, Error, TEXT("Unable to start BioGears Engine. Invalid Working Directory: '%s'"), *workingDirectoryFull);
	}
#endif

	return false;
}

bool UVH_BioGearsEngine::LoadPatient(const FString& patientFile)
{
	// Patient File Doesn't Exist
	FString absPatientFile;
	if (!FindPatientFile(patientFile, absPatientFile, true))
	{
		UE_LOG(VH_BioGears, Warning, TEXT("Failed to Load Patient: Unable to Find Patient File '%s'"), *patientFile);
		return false;
	}

	// Pause Engine Updates
	SetPlayMode(EScenarioPlayMode::Paused);

	// Create a New Engine
#if  defined(WITH_BIOGEARS_BINDING) // TODO: Remove when biogears works on android
	bInitialized = BGEngine->InitializeEngine(TCHAR_TO_ANSI(*absPatientFile));
#endif

	// Set Play Mode
	if (bInitialized)
	{
		SetPlayMode(EScenarioPlayMode::Play);
	}

	return bInitialized;
}

bool UVH_BioGearsEngine::LoadPatientState(const FString& stateFile)
{
	//
	//	We need to know if the file exist in Game/Content. If it doesn't then we need to ask 
	//  libBiogears if it can fall back to a baked in state
	//  For testing I am ingoring the return of FindPatientState until this is patched

	FString absStateFile;
	if (!FindPatientStateFile(stateFile, absStateFile, true))
	{
		UE_LOG(VH_BioGears, Warning, TEXT("Failed to Load Patient State: Unable to Find Patient File '%s'"), *stateFile);
		//return false;
	}

	// Pause Engine Updates
	SetPlayMode(EScenarioPlayMode::Paused);

	// Load State
#if  defined(WITH_BIOGEARS_BINDING) // TODO: Remove when biogears works on android
	bInitialized = BGEngine->LoadState(TCHAR_TO_ANSI(*stateFile));
#endif

	// Set Play Mode
	if (bInitialized)
	{ SetPlayMode(EScenarioPlayMode::Play);
	} else {
	  UE_LOG(VH_BioGears, Warning, TEXT("Failed to Load Patient State: libBioGears return false on LoadState for  '%s'"), *stateFile);
	}

	return bInitialized;
}

#if  defined(WITH_BIOGEARS_BINDING) // TODO: Remove when biogears works on android
void UVH_BioGearsEngine::TrackData(const FString& outputFile, TMap<FString, biogears::CCompoundUnit>& trackedData)
{
	// Data to be requested
	if (trackedData.Num() > 0)
	{
		bTrackingData = true;

		// Data request sample rate (1/30s)
		BGEngine->GetEngineTrack()->GetDataRequestManager().SetSamplesPerSecond(1.0f / 30.0f);

		TArray<FString> data;
		trackedData.GetKeys(data);

		for (FString dataType : data)
		{
			BGEngine->GetEngineTrack()->GetDataRequestManager().CreatePhysiologyDataRequest().Set(TCHAR_TO_ANSI(*dataType), trackedData[dataType]);
		}

		// Ouput file
		BGEngine->GetEngineTrack()->GetDataRequestManager().SetResultsFilename(TCHAR_TO_ANSI(*outputFile));
	}
}
#endif

// ------------ Engine State ------------ //

bool UVH_BioGearsEngine::IsEngineActive()
{
#if  defined(WITH_BIOGEARS_BINDING) // TODO: Remove when biogears works on android
	return BGEngine && Thread != nullptr;
#else
	return false;
#endif
}

bool UVH_BioGearsEngine::IsEngineReady()
{
#if  defined(WITH_BIOGEARS_BINDING) // TODO: Remove when biogears works on android
	return bInitialized && BGEngine;
#else
	return false;
#endif
}

// -------------- Play Mode -------------- //

EScenarioPlayMode UVH_BioGearsEngine::GetPlayMode()
{
	FScopeLock lock(&ModeCriticalSection);
	return ScenarioPlayMode;
}

void UVH_BioGearsEngine::SetPlayMode(EScenarioPlayMode playMode)
{
	UE_LOG(VH_BioGears, Verbose, TEXT("SetPlayMode: %s"), *UEnum::GetValueAsString(TEXT("VH_BioGears.EScenarioPlayMode"), playMode));

	FScopeLock lock(&ModeCriticalSection);
	ScenarioPlayMode = playMode;
}

// --------------- Timing --------------- //

float UVH_BioGearsEngine::GetSimulationTime()
{
	//FScopeLock lock(&EngineCriticalSection);
	return SimulationTime;
}

// ----------------- Actions ----------------- //

#if  defined(WITH_BIOGEARS_BINDING) // TODO: Remove when biogears works on android
FThreadSafeBool UVH_BioGearsEngine::AddAction(TSharedPtr<biogears::SEAction> action)
{
	FScopeLock lock(&ActionsCriticalSection);
	return FThreadSafeBool(ActionQueue.Enqueue(action));
}

bool UVH_BioGearsEngine::ProcessPatientAssessment(biogears::SEPatientAssessment& assessment)
{
	FScopeLock modeLock(&EngineCriticalSection);
	if (BGEngine)
	{
		return BGEngine->GetPatientAssessment(assessment);
	}

	return false;
}

bool UVH_BioGearsEngine::ProcessPatientAssessmentRequest(biogears::SEPatientAssessmentRequest& request)
{
	FScopeLock actionLock(&EngineCriticalSection);
	if (BGEngine)
	{
		return BGEngine->ProcessAction(request);
	}

	return false;
}
#endif

// ----------------- Scenario ---------------- //

#if  defined(WITH_BIOGEARS_BINDING) // TODO: Remove when biogears works on android
TArray<CDM::ActionData*> UVH_BioGearsEngine::GetActionsFromScenarioFile(const FString& scenarioFile)
{
	TArray<CDM::ActionData*> actions = TArray<CDM::ActionData*>();

	if (BGEngine)
	{
		// Load Actions
		biogears::SEScenario scenario = biogears::SEScenario(BGEngine->GetSubstanceManager());
		scenario.Load(TCHAR_TO_ANSI(*scenarioFile));
		CDM::ScenarioData* scenarioData = scenario.Unload();
		CDM::ScenarioData::Action_sequence scenarioActions = scenarioData->Action();

		for (CDM::ActionData& action : scenarioActions)
		{
			actions.Add(action._clone());
		}

		// Load Data Requests
		BGEngine->GetEngineTrack()->GetDataRequestManager().Load(scenarioData->DataRequests().get(), BGEngine->GetSubstanceManager());
		BGEngine->GetEngineTrack()->GetDataRequestManager().SetResultsFilename("BioGearsDataRequests.csv");
		BGEngine->GetEngineTrack()->TrackData(BGEngine->GetSimulationTime(biogears::TimeUnit::s));
	}

	return actions;
}
#endif

// -------------- Substance Access ------------- //

#if  defined(WITH_BIOGEARS_BINDING) // TODO: Remove when biogears works on android
biogears::SESubstanceManager* UVH_BioGearsEngine::GetSubstanceManager()
{
	if (BGEngine)
	{
		return &BGEngine->GetSubstanceManager();
	}

	return nullptr;
}
#endif

// ----------- File Structure ----------- //

bool UVH_BioGearsEngine::GetWorkingDirectory(bool bAbsolutePath, FString& outDirectory)
{
	outDirectory = WorkingDirectory;

	if (bAbsolutePath && FPaths::IsRelative(outDirectory))
	{
		outDirectory = FPaths::ConvertRelativePathToFull(FPaths::Combine(FPaths::ProjectContentDir(), outDirectory));
	}

	// Ensure trailing '/' (NOTE: There is a bug in MakePathRelativeTo() that strips off the last dir if there is no '/' on the end!)

	outDirectory = FPaths::Combine(outDirectory, TEXT(""));
	if (!FPaths::DirectoryExists(outDirectory)) {
		IPlatformFile& platformFile = FPlatformFileManager::Get().GetPlatformFile();
		platformFile.CreateDirectoryTree(*outDirectory);
	}
	return FPaths::DirectoryExists(outDirectory);
}

bool UVH_BioGearsEngine::GetPatientsDirectory(bool bAbsolutePath, FString& outDirectory)
{
	if (bAbsolutePath && GetWorkingDirectory(true, outDirectory))
	{
		outDirectory = FPaths::Combine(outDirectory, PatientsDirectory);
	}
	else
	{
		outDirectory = PatientsDirectory;
	}
	if (!FPaths::DirectoryExists(outDirectory)) {
		IPlatformFile& platformFile = FPlatformFileManager::Get().GetPlatformFile();
		platformFile.CreateDirectoryTree(*outDirectory);
	}
	return FPaths::DirectoryExists(outDirectory);
}

bool UVH_BioGearsEngine::GetPatientStatesDirectory(bool bAbsolutePath, FString& outDirectory)
{
	if (bAbsolutePath && GetWorkingDirectory(true, outDirectory))
	{
		outDirectory = FPaths::Combine(outDirectory, PatientStatesDirectory);
	}
	else
	{
		outDirectory = PatientStatesDirectory;
	}
	if (!FPaths::DirectoryExists(outDirectory)) {
		IPlatformFile& platformFile = FPlatformFileManager::Get().GetPlatformFile();
		platformFile.CreateDirectoryTree(*outDirectory);
	}
	return FPaths::DirectoryExists(outDirectory);
}

bool UVH_BioGearsEngine::GetScenariosDirectory(bool bAbsolutePath, FString& outDirectory)
{
	if (bAbsolutePath && GetWorkingDirectory(true, outDirectory))
	{
		outDirectory = FPaths::Combine(outDirectory, ScenariosDirectory);
	}
	else
	{
		outDirectory = ScenariosDirectory;
	}
	if (!FPaths::DirectoryExists(outDirectory)) {
		IPlatformFile& platformFile = FPlatformFileManager::Get().GetPlatformFile();
		platformFile.CreateDirectoryTree(*outDirectory);
	}
	return FPaths::DirectoryExists(outDirectory);
}

bool UVH_BioGearsEngine::GetTempDirectory(bool bAbsolutePath, FString& outDirectory)
{
	outDirectory = (bAbsolutePath && FPaths::IsRelative(TempDirectory)) ? ConvertProjectPathToFull(TempDirectory) : TempDirectory;
	if (!FPaths::DirectoryExists(outDirectory)) {
		IPlatformFile& platformFile = FPlatformFileManager::Get().GetPlatformFile();
		platformFile.CreateDirectoryTree(*outDirectory);
	}
	return FPaths::DirectoryExists(outDirectory);
}


bool UVH_BioGearsEngine::SetWorkingDirectory(const FString& directory)
{
	FString fullPath = FPaths::Combine(FPaths::ProjectContentDir(), directory);
	if (!FPaths::DirectoryExists(fullPath)) {
		IPlatformFile& platformFile = FPlatformFileManager::Get().GetPlatformFile();
		platformFile.CreateDirectoryTree(*fullPath);
	}
	if (FPaths::DirectoryExists(fullPath))
	{
		WorkingDirectory = directory;
		return true;
	}

	return false;
}

bool UVH_BioGearsEngine::SetPatientsDirectory(const FString& directory)
{
	FString fullPath = FPaths::Combine(WorkingDirectory, directory);

	if (!FPaths::DirectoryExists(fullPath)) {
		IPlatformFile& platformFile = FPlatformFileManager::Get().GetPlatformFile();
		platformFile.CreateDirectoryTree(*fullPath);
	}
	if (FPaths::DirectoryExists(fullPath))
	{
		PatientsDirectory = directory;
		return true;
	}
	return false;
}

bool UVH_BioGearsEngine::SetPatientStatesDirectory(const FString& directory)
{
	FString fullPath = FPaths::Combine(WorkingDirectory, directory);
	if (!FPaths::DirectoryExists(fullPath)) {
		IPlatformFile& platformFile = FPlatformFileManager::Get().GetPlatformFile();
		platformFile.CreateDirectoryTree(*fullPath);
	}
	if (FPaths::DirectoryExists(fullPath))
	{
		PatientStatesDirectory = directory;
		return true;
	}

	return false;
}

bool UVH_BioGearsEngine::SetScenariosDirectory(const FString& directory)
{
	FString fullPath = FPaths::Combine(WorkingDirectory, directory);
	if (!FPaths::DirectoryExists(fullPath)) {
		IPlatformFile& platformFile = FPlatformFileManager::Get().GetPlatformFile();
		platformFile.CreateDirectoryTree(*fullPath);
	}
	if (FPaths::DirectoryExists(fullPath))
	{
		ScenariosDirectory = directory;
		return true;
	}

	return false;
}


// ---------------------------------
// --- Implementation
// ---------------------------------

UWorld* UVH_BioGearsEngine::GetVHWorld()
{
	if (GEngine && GEngine->GameViewport)
	{
		return GEngine->GameViewport->GetWorld();
	}

	return nullptr;
}

#if  defined(WITH_BIOGEARS_BINDING) // TODO: Remove when biogears works on android
biogears::Logger* UVH_BioGearsEngine::GetLogger()
{
	return BGEngine->GetLogger();
}
#endif

void UVH_BioGearsEngine::AdvanceTime(float seconds)
{
#if  defined(WITH_BIOGEARS_BINDING) // TODO: Remove when biogears works on android
	//FScopeLock lock(&EngineCriticalSection);
	if (BGEngine)
	{
		BGEngine->AdvanceModelTime(seconds, biogears::TimeUnit::s);
	}
#endif
}

// --------------- Actions --------------- //

FThreadSafeBool UVH_BioGearsEngine::IsActionQueueEmpty()
{
#if  defined(WITH_BIOGEARS_BINDING) // TODO: Remove when biogears works on android
	FScopeLock lock(&ActionsCriticalSection);
	return FThreadSafeBool(ActionQueue.IsEmpty());
#else
	return true;
#endif
}

#if  defined(WITH_BIOGEARS_BINDING) // TODO: Remove when biogears works on android
TSharedPtr<biogears::SEAction> UVH_BioGearsEngine::GetTopAction()
{
	FScopeLock lock(&ActionsCriticalSection);

	TSharedPtr<biogears::SEAction> action;
	if (ActionQueue.Dequeue(action))
	{
		return action;
	}

	return nullptr;
}

bool UVH_BioGearsEngine::ProcessAction(const biogears::SEAction& action)
{
	//FScopeLock lock(&EngineCriticalSection);
	if (BGEngine)
	{
		return BGEngine->ProcessAction(action);
	}

	return false;
}
#endif

// ---------------- Data ---------------- //

void UVH_BioGearsEngine::UpdateData()
{
#if  defined(WITH_BIOGEARS_BINDING) // TODO: Remove when biogears works on android
	if (BGEngine != nullptr)
	{
		if (Physiology != nullptr)
		{
			Physiology->UpdateValues(BGEngine);
		}

		UpdateBioGearsMetrics();
	}
#endif
}

void UVH_BioGearsEngine::UpdateBioGearsMetrics()
{
	//FScopeLock lock(&EngineCriticalSection);
#if  defined(WITH_BIOGEARS_BINDING) // TODO: Remove when biogears works on android
	SimulationTime = BGEngine->GetSimulationTime(biogears::TimeUnit::s);
#endif
}

// ----------- File Structure ----------- //

bool UVH_BioGearsEngine::FindPatientFile(const FString& file, FString& outPath, bool bGetFullPath)
{

	FString fallback = TEXT("");
#if  defined(WITH_BIOGEARS_BINDING) // TODO: Remove when biogears works on android
	if (BGEngine) {
		if (biogears::io::does_embedded_patients_file_exist(TCHAR_TO_ANSI(*file))) {
			fallback = file;
		}
	}
#endif

	FString directory;
	if (GetPatientsDirectory(true, directory))
	{
		if (FindFile(directory, file, outPath)) {
			return true;
		}
	}
	if (!fallback.IsEmpty()) {
		outPath = fallback;
		return true;
	}
	return false;
}

bool UVH_BioGearsEngine::FindPatientStateFile(const FString& file, FString& outPath, bool bGetFullPath)
{
	FString fallback = "";
#if  defined(WITH_BIOGEARS_BINDING)
	if (biogears::io::does_embedded_states_file_exist(TCHAR_TO_ANSI(*file))) {
		UE_LOG(VH_BioGears, Verbose, TEXT("Biogears found embedded state file %s"), *file);
		fallback = file;
	}
#endif

	FString directory;
	if (GetPatientStatesDirectory(true, directory)) {}
	{
#if !defined(ANDROID)
		//When running on Android I do not believe this function properly test for 
		//The existance of files where libBioGears can read them. We will need to write
		//Our own hand rolled FindFile or get io-manager to find one
		if (FindFile(directory, file, outPath)) {
			return true;
		}
#endif
	}
	if (!fallback.IsEmpty()) {
		UE_LOG(VH_BioGears, Verbose, TEXT("UE4 is using the fall back file %s"), *fallback);
		outPath = fallback;
		return true;
	}
	return false;
}

bool UVH_BioGearsEngine::FindScenarioFile(const FString& file, FString& outPath, bool bGetFullPath)
{
	FString fallback = TEXT("");
#if  defined(WITH_BIOGEARS_BINDING) // TODO: Remove when biogears works on android
	if (BGEngine) {
#if defined(WITH_BIOGEARS_EMBEDDED_SCENARIOS)
		if (biogears::io::does_embedded_scenario_file(TCHAR_TO_ANSI(*file)))
		{
			fallback = file;
		}
#endif
	}
#endif

	FString directory;
	if (GetScenariosDirectory(true, directory))
	{
		if (FindFile(directory, file, outPath)) {
			return true;
		}
	}
	if (!fallback.IsEmpty()) {
		outPath = fallback;
		return true;
	}
	return false;
}

bool UVH_BioGearsEngine::FindFile(FString& root, const FString& file, FString& outPath)
{
	outPath = FString(TEXT(""));

	TArray<FString> directories;
	directories.Add("");

	FString format = FPaths::Combine(root, FString("*"));
	IFileManager& fileManager = IFileManager::Get();
	fileManager.FindFiles(directories, *format, false, true);

	for (FString directory : directories)
	{
		FString fullpath = FPaths::Combine(root, directory, file);
		UE_LOG(VH_BioGears, VeryVerbose, TEXT("Looking for patient: '%s'"), *fullpath);

		if (FPaths::FileExists(fullpath))
		{
			UE_LOG(VH_BioGears, VeryVerbose, TEXT("--> Exists"));

			outPath = fullpath;
			return true;
		}
		else
		{
			UE_LOG(VH_BioGears, VeryVerbose, TEXT("--> Doesn't Exist"));
		}
	}

	return false;
}

FString UVH_BioGearsEngine::ConvertProjectPathToFull(const FString& directory)
{
	FString path = FPaths::Combine(FPaths::ProjectContentDir(), directory);
	path = FixedCollapseRelativeDirectories(path);
	path = FPaths::ConvertRelativePathToFull(path);

	return path;
}

FString UVH_BioGearsEngine::FixedCollapseRelativeDirectories(const FString& path)
{
	FString parsePath = path.Replace(TEXT("/./"), TEXT("/"));
	if (parsePath.StartsWith(TEXT("./")))
	{
		// Skip over
		parsePath = parsePath.Mid(2);
	}

	FString driveLetter = TEXT("");
	if (path.Contains(TEXT(":/")))
	{
		int32 drivePos = path.Find(TEXT(":/")) + 1;
		driveLetter = path.Left(drivePos);
		parsePath = parsePath.Mid(drivePos);
	}

	FString newPath(TEXT(""));

	// Work backwards from end, treating "/.." as "skip next" counter
	int32 skipCount = 0;
	FString skipToken(TEXT("/.."));

	int32 pos = parsePath.Find(TEXT("/"), ESearchCase::IgnoreCase, ESearchDir::FromEnd);
	while (pos >= 0)
	{
		FString dir = parsePath.Mid(pos);
		if (dir.Compare(skipToken) == 0)
		{
			skipCount++;
		}
		else
		{
			if (skipCount > 0)
			{
				skipCount--;
			}
			else
			{
				newPath = dir + newPath;
			}
		}

		parsePath = parsePath.Left(pos);
		pos = parsePath.Find(TEXT("/"), ESearchCase::IgnoreCase, ESearchDir::FromEnd);
	}

	FString prefix = parsePath.StartsWith(TEXT("..")) ? TEXT("..") : TEXT("");
	for (; skipCount > 0; skipCount--)
	{
		prefix = prefix + skipToken;
	}

	return (driveLetter + prefix + newPath);
}

void UVH_BioGearsEngine::BeginDestroy()
{

	Stop();
    Super::BeginDestroy();
	
	if (BGEngine != nullptr)
	{
		FScopeLock lock(&EngineCriticalSection);
		biogears::destroy_biogears_engine(&BGEngine);
	}
}
