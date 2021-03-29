#include "BioGearsDriver.h"

// BioGears
#include <biogears/cdm/substance/SESubstanceCompound.h>

// Engine
#include "Misc/ScopeLock.h"

// VH BioGears Plugin
#include "BioGears_UE4Module.h"


// ---------------------------------
// --- Constructors
// ---------------------------------

UBioGearsDriver::UBioGearsDriver(const FObjectInitializer& objectInitializer) :
	Super(objectInitializer),
	BGLoggerClass(UBioGearsLogger::StaticClass()),
	BGLogger(nullptr),
	WorkingDirectory("BioGears/DataFiles/ThirdParty"),
	DataFilesDirectory("BioGears/DataFiles"),
	TempDirectory("Temp/BioGears"),
	DataFilesSearchDirectories(TArray<FString>()),
	ModuleName("Module1"),
	LogFile("BioGears.log")
{
}

UBioGearsDriver::~UBioGearsDriver()
{
	BGLogger = nullptr;
	BGEngine = nullptr;
} 


// ---------------------------------
// --- Public Methods
// ---------------------------------

void UBioGearsDriver::InitializeDriver()
{
	LogFile = (!LogFile.IsEmpty()) ? LogFile : "BioGearsEngineLog.txt";
	InitializeDriver(LogFile);
}

void UBioGearsDriver::InitializeDriver(const FString& logFile)
{
	if (BGEngine.IsValid())
	{
		BGEngine->Stop();
		BGEngine->Exit();

		BGEngine = nullptr;
	}

	// Working Directory
	FString absWorkingDirectory = GetWorkingDirectory(true);

	// Log File
	FString logFilePath = FPaths::Combine(GetModuleTempDirectory(true), TEXT("logs"), logFile);
	logFilePath = FPaths::SetExtension(logFilePath, TEXT(".log"));

	// Create Logger
	BGLogger = NewObject<UBioGearsLogger>(this, BGLoggerClass, TEXT("BioGearsLogger"));
	BGLogger->Initialize();

	// Intialize Engine
	BGEngine = TSharedPtr<FBioGearsEngine>(new FBioGearsEngine());
	BGEngine->InitializeEngine(this, absWorkingDirectory, logFilePath);
	BGEngine->OnBioGearsPatientDeath.BindUObject(this, &UBioGearsDriver::BroadcastPatientDeath);
}

bool UBioGearsDriver::LoadPatient(const FString& patientFile)
{
	// Get Patient File
	FString patientFileFullPath;
	if (FindDataFile(patientFile, patientFileFullPath, true))
	{
		return BGEngine->LoadPatient(this, patientFileFullPath);
	}

	// Patient File Doesn't Exist
	return false;
}

bool UBioGearsDriver::LoadPatientState(const FString& stateFile)
{
	FString stateFileFullPath;
	if (FindDataFile(stateFile, stateFileFullPath, true))
	{
		return BGEngine->LoadPatientState(this, stateFileFullPath);
	}

	// Patient File Doesn't Exist
	return false;
}

void UBioGearsDriver::StopBioGearsEngine()
{
	if (BGEngine.IsValid())
	{
		BGEngine->Stop();
		BGEngine->Exit();

		BGEngine = nullptr;
	}
}

// ----------------- Logging ----------------- //

UBioGearsLogger* UBioGearsDriver::GetVHLogger()
{
	return BGLogger;
}

biogears::Logger* UBioGearsDriver::GetLogger()
{
	return BGEngine.IsValid() ? BGEngine->GetLogger() : nullptr;
}

void UBioGearsDriver::SetLogLevel(log4cpp::Priority::Value logLevel)
{
	if (BGEngine.IsValid())
	{
		BGEngine->GetLogger()->SetLogLevel(logLevel);
	}
}

bool UBioGearsDriver::TrackData(const FString& outputFile, TMap<FString, biogears::CCompoundUnit>& data)
{
	if (BGEngine.IsValid())
	{
		BGEngine->TrackData(outputFile, data);
		return true;
	}

	return false;
}

// ---------------- Play Mode ---------------- //

bool UBioGearsDriver::SetPlayMode(EScenarioPlayMode mode)
{
	 if (BGEngine.IsValid())
	 {
		 BGEngine->SetPlayMode(mode);
		 return true;
	 }

	 return false;
}

EScenarioPlayMode UBioGearsDriver::GetPlayMode()
{
	if (BGEngine.IsValid())
	{
		return BGEngine->GetPlayMode();
	}

	return EScenarioPlayMode::None;
}

bool UBioGearsDriver::IsEngineActive()
{
	if (BGEngine.IsValid())
	{
		return BGEngine->IsEngineActive();
	}

	return false;
}

// ----------------- Actions ----------------- //

bool UBioGearsDriver::AddAction(TSharedPtr<biogears::SEAction> action)
{
	if (BGEngine.IsValid())
	{
		BGEngine->AddAction(action);
		return true;
	}

	return false;
}

bool UBioGearsDriver::GetPatientAssessment(biogears::SEPatientAssessment& assessment)
{
	if (BGEngine.IsValid())
	{
		BGEngine->GetPatientAssessment(assessment);
		return true;
	}

	return false;
}

bool UBioGearsDriver::GetPatientAssessmentRequest(biogears::SEPatientAssessmentRequest& request)
{
	if (BGEngine.IsValid())
	{
		BGEngine->GetPatientAssessmentRequest(request);
		return true;
	}

	return false;
}

TArray<CDM::ActionData*> UBioGearsDriver::GetActionsFromScenarioFile(const FString& scenarioFile)
{
	if (BGEngine.IsValid())
	{
		FString fileFullName = "";
		if (UBioGearsDriver::FindDataFile(scenarioFile, fileFullName, true))
		{
			return BGEngine->GetActionsFromScenarioFile(fileFullName);
		}
	}

	return TArray<CDM::ActionData*>();
}

EBioGearsTourniquetLevel UBioGearsDriver::IsTourniquetApplied(const FString& compartment)
{
	if (BGEngine.IsValid())
	{
		return BGEngine->IsTourniquetApplied(compartment);
	}

	return EBioGearsTourniquetLevel::NotApplied;
}

// -------------- BioGears Access ------------- //

biogears::SESubstanceManager* UBioGearsDriver::GetSubstanceManager()
{
	if (BGEngine.IsValid())
	{
		return BGEngine->GetSubstanceManager();
	}

	return nullptr;
}

const biogears::SESubstanceCompound* UBioGearsDriver::GetCompound(const FString& compoundName)
{
	if (BGEngine.IsValid())
	{
		return BGEngine->GetCompound(compoundName);
	}

	return nullptr;
}

// --------------- Patient Data --------------- //

FBioGearsAnesthesiaMachine UBioGearsDriver::GetAnesthesiaData()
{
	if (BGEngine.IsValid())
	{
		return BGEngine->GetAnesthesiaMachine();
	}

	return FBioGearsAnesthesiaMachine();
}

FBioGearsBloodChemistry UBioGearsDriver::GetBloodChemistryData()
{
	if (BGEngine.IsValid())
	{
		return BGEngine->GetBloodChemistryData();
	}

	return FBioGearsBloodChemistry();
}

FBioGearsBloodCount UBioGearsDriver::GetBloodCountData()
{
	if (BGEngine.IsValid())
	{
		return BGEngine->GetBloodCountData();
	}

	return FBioGearsBloodCount();
}

FBioGearsCardiovascular UBioGearsDriver::GetCardiovascularSystemData()
{
	if (BGEngine.IsValid())
	{
		return BGEngine->GetCardiovascularSystemData();
	}

	return FBioGearsCardiovascular();
}

FBioGearsDrugs UBioGearsDriver::GetDrugSystemData()
{
	if (BGEngine.IsValid())
	{
		return BGEngine->GetDrugSystemData();
	}

	return FBioGearsDrugs();
}

FBioGearsEndocrine UBioGearsDriver::GetEndocrineSystemData()
{
	if (BGEngine.IsValid())
	{
		return BGEngine->GetEndocrineSystemData();
	}

	return FBioGearsEndocrine();
}

FBioGearsEnergy UBioGearsDriver::GetEnergySystemData()
{
	if (BGEngine.IsValid())
	{
		return BGEngine->GetEnergySystemData();
	}

	return FBioGearsEnergy();
}

FBioGearsEnvironmentalConditions UBioGearsDriver::GetEnvironmentConditions()
{
	if (BGEngine.IsValid())
	{
		return BGEngine->GetEnvironmentConditions();
	}

	return FBioGearsEnvironmentalConditions();
}

FBioGearsGastrointestinal UBioGearsDriver::GetGastrointestinalSystemData()
{
	if (BGEngine.IsValid())
	{
		return BGEngine->GetGastrointestinalSystemData();
	}

	return FBioGearsGastrointestinal();
}

FBioGearsHepatic UBioGearsDriver::GetHepaticSystemData()
{
	if (BGEngine.IsValid())
	{
		return BGEngine->GetHepaticSystemData();
	}

	return FBioGearsHepatic();
}

FBioGearsInflamatoryRespose UBioGearsDriver::GetInflammatoryResponseData()
{
	if (BGEngine.IsValid())
	{
		return BGEngine->GetInflammatoryResponseData();
	}

	return FBioGearsInflamatoryRespose();
}

FBioGearsNervous UBioGearsDriver::GetNervousSystemData()
{
	if (BGEngine.IsValid())
	{
		return BGEngine->GetNervousSystemData();
	}

	return FBioGearsNervous();
}

FBioGearsPatient UBioGearsDriver::GetPatientData()
{
	if (BGEngine.IsValid())
	{
		return BGEngine->GetPatientData();
	}

	return FBioGearsPatient();
}

FBioGearsRenal UBioGearsDriver::GetRenalSystemData()
{
	if (BGEngine.IsValid())
	{
		return BGEngine->GetRenalSystemData();
	}

	return FBioGearsRenal();
}

FBioGearsRespiratory UBioGearsDriver::GetRespiratorySystemData()
{
	if (BGEngine.IsValid())
	{
		return BGEngine->GetRespiratorySystemData();
	}

	return FBioGearsRespiratory();
}

FBioGearsTissue UBioGearsDriver::GetTissueSystemData()
{
	if (BGEngine.IsValid())
	{
		return BGEngine->GetTissueSystemData();
	}

	return FBioGearsTissue();
}

// -------------- Infusion Data -------------- //

FBioGearsSubstanceInfusions UBioGearsDriver::GetSubstanceInfusions()
{
	if (BGEngine.IsValid())
	{
		return BGEngine->GetSubstanceInfusions();
	}

	return FBioGearsSubstanceInfusions();
}

FBioGearsCompoundInfusions UBioGearsDriver::GetCompoundInfusions()
{
	if (BGEngine.IsValid())
	{
		return BGEngine->GetCompoundInfusions();
	}

	return FBioGearsCompoundInfusions();
}

// -------------- BioGears Data -------------- //

FBioGearsConditions UBioGearsDriver::GetBioGearsConditionsData()
{
	if (BGEngine.IsValid())
	{
		return BGEngine->GetBioGearsConditionsData();
	}

	return FBioGearsConditions();
}

FBioGearsMetrics UBioGearsDriver::GetBioGearsMetrics()
{
	if (BGEngine.IsValid())
	{
		return BGEngine->GetBioGearsMetrics();
	}

	return FBioGearsMetrics();
}

FBioGearsState UBioGearsDriver::GetBioGearsStateData()
{
	if (BGEngine.IsValid())
	{
		return BGEngine->GetBioGearsStateData();
	}

	return FBioGearsState();
}


// ---------------------------------
// --- Implementation Methods
// ---------------------------------

void UBioGearsDriver::BroadcastPatientDeath()
{
	UE_LOG(BioGears, Verbose, TEXT("Patient has died."));
	OnBioGearsPatientDeath.Broadcast();
}

// ------------- File Structure ------------- //

bool UBioGearsDriver::FindDataFile(const FString& file, FString& result, bool bGetFullPath)
{
	result = FString(TEXT(""));

	TArray<FString> searchPaths;
	searchPaths.Add(ModuleName);
	searchPaths.Append(DataFilesSearchDirectories);

	for (FString path : searchPaths)
	{
		FString fullPath = FPaths::Combine(GetDataFilesDirectory(bGetFullPath), path, file);
		UE_LOG(BioGears, VeryVerbose, TEXT("Checking for file: %s"), *fullPath);

		if (FPaths::FileExists(fullPath))
		{
			UE_LOG(BioGears, VeryVerbose, TEXT("		Exists"), *fullPath);

			result = fullPath;
			return true;
		}
	}

	return false;
}

FString UBioGearsDriver::GetWorkingDirectory(bool bAbsolutePath)
{
	FString directory = WorkingDirectory;

	if (bAbsolutePath && FPaths::IsRelative(directory))
	{
		directory = FPaths::ConvertRelativePathToFull(FPaths::Combine(FPaths::ProjectContentDir(), directory));
	}

	// Ensure trailing '/' (NOTE: There is a bug in MakePathRelativeTo() that strips off the last dir if there is no '/' on the end!)
	return FPaths::Combine(directory, TEXT(""));
}

FString UBioGearsDriver::GetDataFilesDirectory(bool bGetFullPath)
{
	return (bGetFullPath && FPaths::IsRelative(DataFilesDirectory)) ? ConvertProjectPathToFull(DataFilesDirectory) : DataFilesDirectory;
}

FString UBioGearsDriver::GetTempDirectory(bool bGetFullPath)
{
	return (bGetFullPath && FPaths::IsRelative(TempDirectory)) ? ConvertProjectPathToFull(TempDirectory) : TempDirectory;
}

FString UBioGearsDriver::GetModuleTempDirectory(bool bGetFullPath)
{
	return FPaths::Combine(GetTempDirectory(bGetFullPath), ModuleName);
}


FString UBioGearsDriver::ConvertProjectPathToFull(const FString& directory)
{
	FString path = FPaths::Combine(FPaths::ProjectContentDir(), directory);
	path = FixedCollapseRelativeDirectories(path);
	path = FPaths::ConvertRelativePathToFull(path);

	return path;
}

FString UBioGearsDriver::FixedCollapseRelativeDirectories(const FString& path)
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
