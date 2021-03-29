#include "BioGearsScenarioDriver.h"

// BioGears
#include <biogears/cdm/substance/SESubstanceCompound.h>

// Engine
#include "Misc/ScopeLock.h"

// VH BioGears Plugin
#include "BioGears_UE4Module.h"
#include "BioGearsDriver.h"

// ---------------------------------
// --- Constructors
// ---------------------------------

UBioGearsScenarioDriver::UBioGearsScenarioDriver(const FObjectInitializer& objectInitializer) :
	Super(objectInitializer),
	BGDriver(nullptr),
	Actions(TArray<CDM::ActionData*>()),
	ScenarioFile(""),
	ActionIndex(0),
	bRunningScenario(false),
	bProcessAction(false),
	DelayedActionSimTime(0.0f)
{
}

UBioGearsScenarioDriver::~UBioGearsScenarioDriver()
{} 


// ---------------------------------
// --- Inherited Methods (FTickableGameObject)
// ---------------------------------

void UBioGearsScenarioDriver::Tick(float deltaTime)
{
	if (bRunningScenario)
	{
		if (bProcessAction)
		{
			ProcessNextAction();
		}
		else
		{
			// Check
			if (BGDriver != nullptr)
			{
				bProcessAction  = BGDriver->GetBioGearsMetrics().SimulationTime >= DelayedActionSimTime;
			}
		}
	}
}

TStatId UBioGearsScenarioDriver::GetStatId(void) const
{
	return TStatId();
}


// ---------------------------------
// --- Public Methods
// ---------------------------------

void UBioGearsScenarioDriver::InitializeDriver(UBioGearsDriver* driver, const FString& scenarioFile)
{
	ScenarioFile = scenarioFile;
	Actions = PopulateActionList();
	BGDriver = driver;
}

void UBioGearsScenarioDriver::StartScenario()
{
	UE_LOG(BioGears, Verbose, TEXT("Automated Scenario Start. There are %d actions to process"), Actions.Num());
	ActionIndex = 0;
	bRunningScenario = true;
	bProcessAction = true;

	DelayedActionSimTime = 0;
}

FString UBioGearsScenarioDriver::GetScenarioFile()
{
	return ScenarioFile;
}

bool UBioGearsScenarioDriver::IsValid()
{
	return Actions.Num() > 0;
}


// ---------------------------------
// --- Implementation
// ---------------------------------

TArray<CDM::ActionData*> UBioGearsScenarioDriver::PopulateActionList()
{
	if (BGDriver != nullptr)
	{
		return BGDriver->GetActionsFromScenarioFile(ScenarioFile);
	}

	return TArray<CDM::ActionData*>();
}

void UBioGearsScenarioDriver::ProcessNextAction()
{
	if (ActionIndex >= 0 && ActionIndex < Actions.Num())
	{
		UE_LOG(BioGears, Log, TEXT("Processing Action %d/%d"), ActionIndex + 1, Actions.Num());
		CDM::ActionData* action = Actions[ActionIndex];
		ProcessAction(action);
		ActionIndex++;
	}
	else
	{
		bRunningScenario = false;
		UE_LOG(BioGears, Log, TEXT("End of automated scenario."));
	}
}

void UBioGearsScenarioDriver::DelayNextActionBy(float seconds)
{
	bProcessAction = false;

	DelayedActionSimTime = (BGDriver != nullptr) ? BGDriver->GetBioGearsMetrics().SimulationTime + seconds : 0.0f;
}

bool UBioGearsScenarioDriver::ProcessAction(CDM::ActionData* action)
{
	if (action == nullptr)
	{
		UE_LOG(BioGears, Log, TEXT("Action: Null"));
		return false;
	}

	const CDM::AdvanceTimeData* advancement = dynamic_cast<const CDM::AdvanceTimeData*>(action);
	if (advancement != nullptr)
	{
		return ProcessTimeAdvancement(advancement);
	}

	const CDM::SerializeStateData* serialize = dynamic_cast<const CDM::SerializeStateData*>(action);
	if (serialize != nullptr)
	{
		return ProcessPatientSerialization(serialize);
	}

	const CDM::PatientAssessmentRequestData* assessment = dynamic_cast<const CDM::PatientAssessmentRequestData*>(action);
	if (assessment != nullptr)
	{
		return ProcessPatientAssessment(assessment);
	}

	const CDM::PatientActionData* patient = dynamic_cast<const CDM::PatientActionData*>(action);
	if (patient != nullptr)
	{
		return ProcessPatientAction(patient);
	}

	const CDM::AnesthesiaMachineActionData* anesthesia = dynamic_cast<const CDM::AnesthesiaMachineActionData*>(action);
	if (anesthesia != nullptr)
	{
		return ProcessAnesthesiaMachineAction(anesthesia);
	}

	const CDM::EnvironmentActionData* environment = dynamic_cast<const CDM::EnvironmentActionData*>(action);
	if (environment != nullptr)
	{
		return ProcessEnvironmentAction(environment);
	}

	UE_LOG(BioGears, Log, TEXT("Action: Unknown Type"));
	return false;
}

bool UBioGearsScenarioDriver::ProcessTimeAdvancement(const CDM::AdvanceTimeData* advancement)
{
	UE_LOG(BioGears, Log, TEXT("Action: Advance Time"));
	return false;
}

bool UBioGearsScenarioDriver::ProcessPatientSerialization(const CDM::SerializeStateData* serialize)
{
	UE_LOG(BioGears, Log, TEXT("Action: Patient Serialization"));
	return false;
}

bool UBioGearsScenarioDriver::ProcessPatientAssessment(const CDM::PatientAssessmentRequestData* assessment)
{
	UE_LOG(BioGears, Log, TEXT("Action: Patient Assessment"));
	return false;
}

bool UBioGearsScenarioDriver::ProcessPatientAction(const CDM::PatientActionData* action)
{
	UE_LOG(BioGears, Log, TEXT("Action: Patient Action"));
	return false;
}

bool UBioGearsScenarioDriver::ProcessAnesthesiaMachineAction(const CDM::AnesthesiaMachineActionData* action)
{
	UE_LOG(BioGears, Log, TEXT("Action: Anesthesia Machine"));
	return false;
}

bool UBioGearsScenarioDriver::ProcessEnvironmentAction(const CDM::EnvironmentActionData* action)
{
	UE_LOG(BioGears, Log, TEXT("Action: Environment Action"));
	return false;
}
