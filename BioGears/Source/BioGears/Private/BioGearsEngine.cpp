#include "BioGearsEngine.h"

// BioGears
#include <biogears/cdm/patient/SEPatient.h>
#include <biogears/cdm/properties/SEScalar.h>
#include <biogears/cdm/properties/SEScalarTypes.h>
#include <biogears/cdm/scenario/SEScenario.h>
#include <biogears/cdm/scenario/SESerializeState.h>
#include <biogears/cdm/substance/SESubstanceCompound.h>
#include <biogears/cdm/substance/SESubstanceManager.h>
#include <biogears/cdm/system/environment/SEActiveHeating.h>
#include <biogears/cdm/system/environment/SEAppliedTemperature.h>
#include <biogears/cdm/system/environment/SEEnvironment.h>
#include <biogears/cdm/system/equipment/Anesthesia/SEAnesthesiaMachine.h>
#include <biogears/cdm/system/equipment/Anesthesia/SEAnesthesiaMachineOxygenBottle.h>
#include <biogears/cdm/system/equipment/ElectroCardioGram/SEElectroCardioGram.h>
#include <biogears/cdm/system/physiology/SEBloodChemistrySystem.h>
#include <biogears/cdm/system/physiology/SECardiovascularSystem.h>
#include <biogears/cdm/system/physiology/SEEnergySystem.h>
#include <biogears/cdm/system/physiology/SERespiratorySystem.h>

// Engine
#include <map>

// VH BioGears Plugin
#include "BioGears_UE4Module.h"
#include "BioGearsDriver.h"


// ---------------------------------
// --- Constructors
// ---------------------------------

FBioGearsEngine::FBioGearsEngine()
	:
	BGEngine(nullptr),
	Thread(nullptr),
	ScenarioPlayMode(EScenarioPlayMode::Paused),
	bInitialized(false),
	bTrackingData(false),
	bStopping(true)
{}

FBioGearsEngine::~FBioGearsEngine()
{
	Thread->Kill();
}


// ---------------------------------
// --- Inherited Methods (FRunnable)
// ---------------------------------

bool FBioGearsEngine::Init()
{
	UE_LOG(BioGears, VeryVerbose, TEXT("-- FBioGearsEngine::Init()"));

	bStopping = false;

	return true;
}

uint32 FBioGearsEngine::Run()
{
	UWorld* world = GetVHWorld();
	float timeOfLastAdvancment = (world != nullptr) ? world->GetTimeSeconds() : 0.0f;
	float timeBetweenAdvancements = (1.0f / 60.0f);
	float timeOfLastDataRequest = (world != nullptr) ? world->GetTimeSeconds() : 0.0f;

	bool bAppendDataRequests = false;
	bool bPatientAlive = true;

	while (!bStopping)
	{
		float currentTime = (world != nullptr) ? world->GetTimeSeconds() : 0.0f;

		if (bInitialized && BGEngine.IsValid() && bPatientAlive && GetPlayMode() != EScenarioPlayMode::Paused)
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
				UpdateEngineData();

				// Advance Time
				float step = (ScenarioPlayMode == EScenarioPlayMode::Play) ? dTime : dTime * 6.0f;
				AdvanceTime(step);

				// Update time of engine update
				timeOfLastAdvancment = currentTime;

				// Check is patient is still alive
				if (BGEngine->GetPatient().GetEventStates().at(CDM::enumPatientEvent::IrreversibleState))
				{
					bPatientAlive = false;

					AsyncTask(ENamedThreads::GameThread, [this]()
					{
						OnBioGearsPatientDeath.ExecuteIfBound();
					});
				}
			}
		}
	}

	return 0;
}

void FBioGearsEngine::Stop()
{
	UE_LOG(BioGears, VeryVerbose, TEXT("-- FBioGearsEngine::Stop()"));

	bStopping = true;
}

void FBioGearsEngine::Exit()
{
	UE_LOG(BioGears, VeryVerbose, TEXT("-- FBioGearsEngine::Exit()"));
}


// ---------------------------------
// --- Public Methods
// ---------------------------------

bool FBioGearsEngine::InitializeEngine(UBioGearsDriver* driver, const FString& workingDir, const FString& logFile)
{
	// Initialize Physiology Engine
	biogears::Logger* logger = new biogears::Logger(TCHAR_TO_ANSI(*logFile));
	BGEngine = MakeUnique<biogears::BioGearsEngine>(logger, TCHAR_TO_ANSI(*workingDir));
	
	// Set Forward Logger
	if (driver != nullptr)
	{
		logger->SetForward(driver->GetVHLogger());
	}

	// Create Worker Thread to advance engine
	Thread = FRunnableThread::Create(this, TEXT("BioGears Worker"));

	// Broadcast the initialiation of the engine
	if (driver != nullptr)
	{
		driver->OnBioGearsEngineInitialized.Broadcast();
	}

	return true;
}

bool FBioGearsEngine::LoadPatient(UBioGearsDriver* driver, const FString& patientFile)
{
	// Pause Engine Updates
	SetPlayMode(EScenarioPlayMode::Paused);

	// Create a New Engine
	bInitialized = BGEngine->InitializeEngine(TCHAR_TO_ANSI(*patientFile));

	// Set Forward Logger
	if (driver != nullptr)
	{
		BGEngine->GetLogger()->SetForward(driver->GetVHLogger());
	}

	if (bInitialized)
	{
		SetPlayMode(EScenarioPlayMode::Play);

		if (driver != nullptr)
		{
			driver->OnBioGearsScenarioBegin.Broadcast();
		}
	}

	return bInitialized;
}

bool FBioGearsEngine::LoadPatientState(UBioGearsDriver* driver, const FString& stateFile)
{
	// Pause Engine Updates
	SetPlayMode(EScenarioPlayMode::Paused);

	// Load State
	bInitialized = BGEngine->LoadState(TCHAR_TO_ANSI(*stateFile));

	// Set Forward Logger
	if (driver != nullptr)
	{
		BGEngine->GetLogger()->SetForward(driver->GetVHLogger());
	}

	// Broadcast new state
	if (bInitialized)
	{
		SetPlayMode(EScenarioPlayMode::Play);

		if (driver != nullptr)
		{
			driver->OnBioGearsScenarioBegin.Broadcast();
		}
	}

	return bInitialized;
}

void FBioGearsEngine::TrackData(const FString& outputFile, TMap<FString, biogears::CCompoundUnit>& trackedData)
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

biogears::Logger* FBioGearsEngine::GetLogger()
{
	return BGEngine->GetLogger();
}

// ------------ Engine State ------------ //

bool FBioGearsEngine::IsEngineReady()
{
	return bInitialized && BGEngine.IsValid();
}

bool FBioGearsEngine::IsEngineActive()
{
	return BGEngine.IsValid() && Thread != nullptr;
}

// -------------- Play Mode -------------- //

EScenarioPlayMode FBioGearsEngine::GetPlayMode()
{
	FScopeLock lock(&ModeCriticalSection);
	return ScenarioPlayMode;
}

void FBioGearsEngine::SetPlayMode(EScenarioPlayMode playMode)
{
	FScopeLock lock(&ModeCriticalSection);
	ScenarioPlayMode = playMode;
}

// ----------------- Actions ----------------- //

FThreadSafeBool FBioGearsEngine::AddAction(TSharedPtr<biogears::SEAction> action)
{
	FScopeLock lock(&ActionsCriticalSection);
	return FThreadSafeBool(ActionQueue.Enqueue(action));
}

bool FBioGearsEngine::ProcessPatientAssessment(biogears::SEPatientAssessment& assessment)
{
	return BGEngine->GetPatientAssessment(assessment);
}

void FBioGearsEngine::GetPatientAssessment(biogears::SEPatientAssessment& assessment)
{
	if (BGEngine.IsValid())
	{
		FScopeLock actionLock(&ActionsCriticalSection);
		FScopeLock dataLock(&DataCriticalSection);
		FScopeLock modeLock(&ModeCriticalSection);

		BGEngine->GetPatientAssessment(assessment);
	}
}

void FBioGearsEngine::GetPatientAssessmentRequest(biogears::SEPatientAssessmentRequest& request)
{
	if (BGEngine.IsValid())
	{
		FScopeLock actionLock(&ActionsCriticalSection);
		FScopeLock dataLock(&DataCriticalSection);
		FScopeLock modeLock(&ModeCriticalSection);

		BGEngine->ProcessAction(request);
	}
}

TArray<CDM::ActionData*> FBioGearsEngine::GetActionsFromScenarioFile(const FString& scenarioFile)
{
	TArray<CDM::ActionData*> actions = TArray<CDM::ActionData*>();

	if (BGEngine.IsValid())
	{
		// Load Actions
		biogears::SEScenario scenario = biogears::SEScenario(BGEngine->GetSubstanceManager());
		scenario.Load(TCHAR_TO_ANSI(*scenarioFile));
		CDM::ScenarioData* scenarioData = scenario.Unload();
		mil::tatrc::physiology::datamodel::ScenarioData::Action_sequence scenarioActions = scenarioData->Action();

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

// --------- BioGears Patient Condition --------- //

EBioGearsTourniquetLevel FBioGearsEngine::IsTourniquetApplied(const FString& compartment)
{
	const std::map<std::string, biogears::SETourniquet*> tourniquets = BGEngine->GetActions().GetPatientActions().GetTourniquets();
	if (tourniquets.find(TCHAR_TO_ANSI(*compartment)) != tourniquets.end())
	{
		biogears::SETourniquet* tourniquet = tourniquets.at(TCHAR_TO_ANSI(*compartment));

		switch (tourniquet->GetTourniquetLevel())
		{
			case CDM::enumTourniquetApplicationLevel::Applied:
				return EBioGearsTourniquetLevel::Applied;

			case CDM::enumTourniquetApplicationLevel::Misapplied:
				return EBioGearsTourniquetLevel::Misapplied;

			default:
				return EBioGearsTourniquetLevel::NotApplied;
		}
	}

	return EBioGearsTourniquetLevel::NotApplied;
}

EBioGearsChestSide FBioGearsEngine::HasTensionPneumothorax()
{
	biogears::SEPatientActionCollection& actions = BGEngine->GetActions().GetPatientActions();

	bool bLeft = actions.HasLeftOpenTensionPneumothorax();
	bool bRight = actions.HasRightOpenTensionPneumothorax();
	
	if (bLeft && bRight)
	{
		return EBioGearsChestSide::Both;
	}

	if (bLeft)
	{
		return EBioGearsChestSide::Left;
	}

	if (bRight)
	{
		return EBioGearsChestSide::Right;
	}

	return EBioGearsChestSide::None;
}

EBioGearsChestSide FBioGearsEngine::HasNeedleDecompression()
{
	biogears::SEPatientActionCollection& actions = BGEngine->GetActions().GetPatientActions();

	bool bLeft = actions.HasLeftNeedleDecompression();
	bool bRight = actions.HasRightNeedleDecompression();

	if (bLeft && bRight)
	{
		return EBioGearsChestSide::Both;
	}

	if (bLeft)
	{
		return EBioGearsChestSide::Left;
	}

	if (bRight)
	{
		return EBioGearsChestSide::Right;
	}

	return EBioGearsChestSide::None;
}

// -------------- Substance Access ------------- //

biogears::SESubstanceManager* FBioGearsEngine::GetSubstanceManager()
{
	if (BGEngine.IsValid())
	{
		return &BGEngine->GetSubstanceManager();
	}

	return nullptr;
}

const biogears::SESubstance* const FBioGearsEngine::GetSubstance(const FString& substanceName)
{
	if (BGEngine.IsValid())
	{
		return BGEngine->GetSubstanceManager().GetSubstance(TCHAR_TO_ANSI(*substanceName));
	}

	return nullptr;
}

const biogears::SESubstanceCompound* const FBioGearsEngine::GetCompound(const FString& compoundName)
{
	if (BGEngine.IsValid())
	{
		return BGEngine->GetSubstanceManager().GetCompound(TCHAR_TO_ANSI(*compoundName));
	}

	return nullptr;
}

// --------------- Patient Data --------------- //

FBioGearsAnesthesiaMachine FBioGearsEngine::GetAnesthesiaMachine()
{
	return BioGearsAnesthesiaMachine;
}

FBioGearsBloodChemistry FBioGearsEngine::GetBloodChemistryData()
{
	return BloodChemistry;
}

FBioGearsBloodCount FBioGearsEngine::GetBloodCountData()
{
	return BloodSystem;
}

FBioGearsInflamatoryRespose FBioGearsEngine::GetInflammatoryResponseData()
{
	return InflammatoryResponse;
}

FBioGearsCardiovascular FBioGearsEngine::GetCardiovascularSystemData()
{
	return CardiovascularSystem;
}

FBioGearsDrugs FBioGearsEngine::GetDrugSystemData()
{
	return DrugSystem;
}

FBioGearsEndocrine FBioGearsEngine::GetEndocrineSystemData()
{
	return EndocrineSystem;
}

FBioGearsEnergy FBioGearsEngine::GetEnergySystemData()
{
	return EnergySystem;
}

FBioGearsEnvironmentalConditions FBioGearsEngine::GetEnvironmentConditions()
{
	return EnvironmentConditions;
}

FBioGearsGastrointestinal FBioGearsEngine::GetGastrointestinalSystemData()
{
	return GastrointestinalSystem;
}

FBioGearsHepatic FBioGearsEngine::GetHepaticSystemData()
{
	return HepaticSystem;
}

FBioGearsNervous FBioGearsEngine::GetNervousSystemData()
{
	return NervousSystem;
}

FBioGearsPatient FBioGearsEngine::GetPatientData()
{
	return PatientData;
}

FBioGearsRenal FBioGearsEngine::GetRenalSystemData()
{
	return RenalSystem;
}

FBioGearsRespiratory FBioGearsEngine::GetRespiratorySystemData()
{
	return RespiratorySystem;
}

FBioGearsTissue FBioGearsEngine::GetTissueSystemData()
{
	return TissueSystem;
}

// -------------- Infusion Data -------------- //

FBioGearsCompoundInfusions FBioGearsEngine::GetCompoundInfusions()
{
	return CompoundInfusions;
}

FBioGearsSubstanceInfusions FBioGearsEngine::GetSubstanceInfusions()
{
	return SubstanceInfusions;
}

// -------------- BioGears Data -------------- //

FBioGearsConditions FBioGearsEngine::GetBioGearsConditionsData()
{
	return BioGearsConditions;
}

FBioGearsMetrics FBioGearsEngine::GetBioGearsMetrics()
{
	return BioGearsMetrics;
}

FBioGearsState FBioGearsEngine::GetBioGearsStateData()
{
	return BioGearsState;
}


// ---------------------------------
// --- Implementation Methods
// ---------------------------------

UWorld* FBioGearsEngine::GetVHWorld()
{
	if (GEngine && GEngine->GameViewport)
	{
		return GEngine->GameViewport->GetWorld();
	}

	return nullptr;
}

void FBioGearsEngine::AdvanceTime(float seconds)
{
	FScopeLock actionLock(&ActionsCriticalSection);
	FScopeLock dataLock(&DataCriticalSection);
	FScopeLock modeLock(&ModeCriticalSection);

	BGEngine->AdvanceModelTime(seconds, biogears::TimeUnit::s);
}

// --------------- Actions --------------- //

FThreadSafeBool FBioGearsEngine::IsActionQueueEmpty()
{
	FScopeLock lock(&ActionsCriticalSection);
	return FThreadSafeBool(ActionQueue.IsEmpty());
}

TSharedPtr<biogears::SEAction> FBioGearsEngine::GetTopAction()
{
	FScopeLock lock(&ActionsCriticalSection);

	TSharedPtr<biogears::SEAction> action;
	if (ActionQueue.Dequeue(action))
	{
		return action;
	}

	return nullptr;
}

void FBioGearsEngine::ClearActions()
{
	FScopeLock lock(&ActionsCriticalSection);
	ActionQueue.Empty();
}

bool FBioGearsEngine::ProcessAction(const biogears::SEAction& action)
{
	return BGEngine->ProcessAction(action);
}

// ---------------- Data ---------------- //

void FBioGearsEngine::UpdateEngineData()
{
	FScopeLock lock(&DataCriticalSection);

	UpdateBioGearsConditions();
	UpdateBioGearsMetrics();
	UpdateBioGearsState();

	UpdateSubstanceInfusions();
	UpdateCompoundInfusions();

	UpdateAnesthesiaMachine();
	UpdateBloodChemistry();
	UpdateInflammatoryResponse();
	UpdateCardiovascularSystem();
	UpdateDrugSystem();
	UpdateEndocrineSystem();
	UpdateEnergySystem();
	UpdateEnvironmentConditions();
	UpdateGastrointestinalSystem();
	UpdateHepaticSystem();
	UpdateNervousSystem();
	UpdatePatientData();
	UpdateRenalSystem();
	UpdateRespiratorySystem();
	UpdateTissueSystem();
}

// --------------- Patient Data --------------- //

void FBioGearsEngine::UpdateAnesthesiaMachine()
{
	const biogears::SEAnesthesiaMachine* machine = BGEngine->GetAnesthesiaMachine();

	if (machine != nullptr)
	{
		BioGearsAnesthesiaMachine.bConnected = (machine->HasConnection()) ? machine->GetConnection() : false;
		BioGearsAnesthesiaMachine.InletFlow = (machine->HasInletFlow()) ? machine->GetInletFlow(biogears::VolumePerTimeUnit::mL_Per_min) : 0.0f;
		BioGearsAnesthesiaMachine.InspiratoryExpiratoryRatio = (machine->HasInspiratoryExpiratoryRatio()) ? machine->GetInspiratoryExpiratoryRatio() : 0.0f;
		BioGearsAnesthesiaMachine.OxygenBottleOneVolume = (machine->HasOxygenBottleOne()) ? machine->GetOxygenBottleOne()->GetVolume(biogears::VolumeUnit::mL) : 0.0f;
		BioGearsAnesthesiaMachine.OxygenBottleTwoVolume = (machine->HasOxygenBottleTwo()) ? machine->GetOxygenBottleTwo()->GetVolume(biogears::VolumeUnit::mL) : 0.0f;
		BioGearsAnesthesiaMachine.OxygenFraction = (machine->HasOxygenFraction()) ? machine->GetOxygenFraction() : 0.0f;
		BioGearsAnesthesiaMachine.ReliefValvePressure = (machine->HasReliefValvePressure()) ? machine->GetReliefValvePressure(biogears::PressureUnit::mmHg) : 0.0f;
		BioGearsAnesthesiaMachine.RespiratoryRate = (machine->HasRespiratoryRate()) ? machine->GetRespiratoryRate(biogears::FrequencyUnit::Per_min) : 0.0f;
		BioGearsAnesthesiaMachine.VentilatorPressure = (machine->HasVentilatorPressure()) ? machine->GetVentilatorPressure(biogears::PressureUnit::mmHg) : 0.0f;

		if (machine->HasPrimaryGas())
		{
			mil::tatrc::physiology::datamodel::enumAnesthesiaMachinePrimaryGas gas = machine->GetPrimaryGas();

			if (gas == mil::tatrc::physiology::datamodel::enumAnesthesiaMachinePrimaryGas::Air)
			{
				BioGearsAnesthesiaMachine.PrimaryGas = EBioGearsGas::Air;
			}
			else
			{
				BioGearsAnesthesiaMachine.PrimaryGas = EBioGearsGas::Nitrogen;
			}
		}
		else
		{
			BioGearsAnesthesiaMachine.PrimaryGas = EBioGearsGas::None;
		}
	}
}

void FBioGearsEngine::UpdateBloodChemistry()
{
	const biogears::SEBloodChemistrySystem* bloodChemistry = BGEngine->GetBloodChemistrySystem();

	if (bloodChemistry != nullptr)
	{
		BloodChemistry.ArterialBloodPH = (bloodChemistry->HasArterialBloodPH()) ? bloodChemistry->GetArterialBloodPH() : 0.0f;
		BloodChemistry.ArterialBloodPHBaseline = (bloodChemistry->HasArterialBloodPHBaseline()) ? bloodChemistry->GetArterialBloodPHBaseline() : 0.0f;
		BloodChemistry.ArterialCarbonDioxidePressure = (bloodChemistry->HasArterialCarbonDioxidePressure()) ? bloodChemistry->GetArterialCarbonDioxidePressure(biogears::PressureUnit::mmHg) : 0.0f;
		BloodChemistry.ArterialOxygenPressure = (bloodChemistry->HasArterialOxygenPressure()) ? bloodChemistry->GetArterialOxygenPressure(biogears::PressureUnit::mmHg) : 0.0f;
		BloodChemistry.BloodDensity = (bloodChemistry->HasBloodDensity()) ? bloodChemistry->GetBloodDensity(biogears::MassPerVolumeUnit::g_Per_cm3) : 0.0f;
		BloodChemistry.BloodSpecificHeat = (bloodChemistry->HasBloodSpecificHeat()) ? bloodChemistry->GetBloodSpecificHeat(biogears::HeatCapacitancePerMassUnit::kcal_Per_C_kg) : 0.0f;
		BloodChemistry.BloodUreaNitrogenConcentration = (bloodChemistry->HasBloodUreaNitrogenConcentration()) ? bloodChemistry->GetBloodUreaNitrogenConcentration(biogears::MassPerVolumeUnit::g_Per_cm3) : 0.0f;
		BloodChemistry.CarbonDioxideSaturation = (bloodChemistry->HasCarbonDioxideSaturation()) ? bloodChemistry->GetCarbonDioxideSaturation() : 0.0f;
		BloodChemistry.CarbonMonoxideSaturation = (bloodChemistry->HasCarbonMonoxideSaturation()) ? bloodChemistry->GetCarbonMonoxideSaturation() : 0.0f;
		BloodChemistry.Hematocrit = (bloodChemistry->HasHematocrit()) ? bloodChemistry->GetHematocrit() : 0.0f;
		BloodChemistry.HemoglobinContent = (bloodChemistry->HasHemoglobinContent()) ? bloodChemistry->GetHemoglobinContent(biogears::MassUnit::g) : 0.0f;
		BloodChemistry.OxygenSaturation = (bloodChemistry->HasOxygenSaturation()) ? bloodChemistry->GetOxygenSaturation() : 0.0f;
		BloodChemistry.Phosphate = (bloodChemistry->HasPhosphate()) ? bloodChemistry->GetPhosphate(biogears::AmountPerVolumeUnit::ct_Per_L) : 0.0f;
		BloodChemistry.PlasmaVolume = (bloodChemistry->HasPlasmaVolume()) ? bloodChemistry->GetPlasmaVolume(biogears::VolumeUnit::mL) : 0.0f;
		BloodChemistry.PulmonaryArterialCarbonDioxidePressure = (bloodChemistry->HasPulmonaryArterialCarbonDioxidePressure()) ? bloodChemistry->GetPulmonaryArterialCarbonDioxidePressure(biogears::PressureUnit::mmHg) : 0.0f;
		BloodChemistry.PulmonaryArterialOxygenPressure = (bloodChemistry->HasPulmonaryArterialOxygenPressure()) ? bloodChemistry->GetPulmonaryArterialOxygenPressure(biogears::PressureUnit::mmHg) : 0.0f;
		BloodChemistry.PulmonaryVenousCarbonDioxidePressure = (bloodChemistry->HasPulmonaryVenousCarbonDioxidePressure()) ? bloodChemistry->GetPulmonaryVenousCarbonDioxidePressure(biogears::PressureUnit::mmHg) : 0.0f;
		BloodChemistry.PulmonaryVenousOxygenPressure = (bloodChemistry->HasPulmonaryVenousOxygenPressure()) ? bloodChemistry->GetPulmonaryVenousOxygenPressure(biogears::PressureUnit::mmHg) : 0.0f;
		BloodChemistry.PulseOximetry = (bloodChemistry->HasPulseOximetry()) ? bloodChemistry->GetPulseOximetry() : 0.0f;
		BloodChemistry.RedBloodCellAcetylcholinesterase = (bloodChemistry->HasRedBloodCellAcetylcholinesterase()) ? bloodChemistry->GetRedBloodCellAcetylcholinesterase(biogears::AmountPerVolumeUnit::ct_Per_L) : 0.0f;
		BloodChemistry.RedBloodCellCount = (bloodChemistry->HasRedBloodCellCount()) ? bloodChemistry->GetRedBloodCellCount(biogears::AmountPerVolumeUnit::ct_Per_L) : 0.0f;
		BloodChemistry.ShuntFraction = (bloodChemistry->HasShuntFraction()) ? bloodChemistry->GetShuntFraction() : 0.0f;
		BloodChemistry.StrongIonDifference = (bloodChemistry->HasStrongIonDifference()) ? bloodChemistry->GetStrongIonDifference(biogears::AmountPerVolumeUnit::ct_Per_L) : 0.0f;
		BloodChemistry.TotalBilirubin = (bloodChemistry->HasTotalBilirubin()) ? bloodChemistry->GetTotalBilirubin(biogears::MassPerVolumeUnit::g_Per_mL) : 0.0f;
		BloodChemistry.TotalProteinConcentration = (bloodChemistry->HasTotalProteinConcentration()) ? bloodChemistry->GetTotalProteinConcentration(biogears::MassPerVolumeUnit::g_Per_mL) : 0.0f;
		BloodChemistry.VenousBloodPH = (bloodChemistry->HasVenousBloodPH()) ? bloodChemistry->GetVenousBloodPH() : 0.0f;
		BloodChemistry.VenousCarbonDioxidePressure = (bloodChemistry->HasVenousCarbonDioxidePressure()) ? bloodChemistry->GetVenousCarbonDioxidePressure(biogears::PressureUnit::mmHg) : 0.0f;
		BloodChemistry.VenousOxygenPressure = (bloodChemistry->HasVenousOxygenPressure()) ? bloodChemistry->GetVenousOxygenPressure(biogears::PressureUnit::mmHg) : 0.0f;
		BloodChemistry.VolumeFractionNeutralLipidInPlasma = (bloodChemistry->HasVolumeFractionNeutralLipidInPlasma()) ? bloodChemistry->GetVolumeFractionNeutralLipidInPlasma() : 0.0f;
		BloodChemistry.VolumeFractionNeutralPhospholipidInPlasma = (bloodChemistry->HasVolumeFractionNeutralPhospholipidInPlasma()) ? bloodChemistry->GetVolumeFractionNeutralPhospholipidInPlasma() : 0.0f;
	}
}

void FBioGearsEngine::UpdateBloodCountData()
{
	// TODO: Implement this
}

void FBioGearsEngine::UpdateCardiovascularSystem()
{
	const biogears::SECardiovascularSystem* cardiovascular = BGEngine->GetCardiovascularSystem();

	if (cardiovascular != nullptr)
	{
		CardiovascularSystem.ArterialPressure = (cardiovascular->HasArterialPressure()) ? cardiovascular->GetArterialPressure(biogears::PressureUnit::mmHg) : 0.0f;
		CardiovascularSystem.BloodVolume = (cardiovascular->HasBloodVolume()) ? cardiovascular->GetBloodVolume(biogears::VolumeUnit::mL) : 0.0f;
		CardiovascularSystem.CardiacIndex = (cardiovascular->HasCardiacIndex()) ? cardiovascular->GetCardiacIndex(biogears::VolumePerTimeAreaUnit::mL_Per_min_m2) : 0.0f;
		CardiovascularSystem.CardiacOutput = (cardiovascular->HasCardiacOutput()) ? cardiovascular->GetCardiacOutput(biogears::VolumePerTimeUnit::mL_Per_min) : 0.0f;
		CardiovascularSystem.CentralVenousPressure = (cardiovascular->HasCentralVenousPressure()) ? cardiovascular->GetCentralVenousPressure(biogears::PressureUnit::mmHg) : 0.0f;
		CardiovascularSystem.CerebralBloodFlow = (cardiovascular->HasCerebralBloodFlow()) ? cardiovascular->GetCerebralBloodFlow(biogears::VolumePerTimeUnit::mL_Per_min) : 0.0f;
		CardiovascularSystem.CerebralPerfusionPressure = (cardiovascular->HasCerebralPerfusionPressure()) ? cardiovascular->GetCerebralPerfusionPressure(biogears::PressureUnit::mmHg) : 0.0f;
		CardiovascularSystem.DiastolicArterialPressure = (cardiovascular->HasDiastolicArterialPressure()) ? cardiovascular->GetDiastolicArterialPressure(biogears::PressureUnit::mmHg) : 0.0f;
		CardiovascularSystem.HeartEjectionFraction = (cardiovascular->HasHeartEjectionFraction()) ? cardiovascular->GetHeartEjectionFraction() : 0.0f;
		CardiovascularSystem.HeartRate = (cardiovascular->HasHeartRate()) ? cardiovascular->GetHeartRate(biogears::FrequencyUnit::Per_min) : 0.0f;
		CardiovascularSystem.HeartStrokeVolume = (cardiovascular->HasHeartStrokeVolume()) ? cardiovascular->GetHeartStrokeVolume(biogears::VolumeUnit::mL) : 0.0f;
		CardiovascularSystem.IntracranialPressure = (cardiovascular->HasIntracranialPressure()) ? cardiovascular->GetIntracranialPressure(biogears::PressureUnit::mmHg) : 0.0f;
		CardiovascularSystem.MeanArterialPressure = (cardiovascular->HasMeanArterialPressure()) ? cardiovascular->GetMeanArterialPressure(biogears::PressureUnit::mmHg) : 0.0f;
		CardiovascularSystem.MeanArterialCarbonDioxidePartialPressure = (cardiovascular->HasMeanArterialCarbonDioxidePartialPressure()) ? cardiovascular->GetMeanArterialCarbonDioxidePartialPressure(biogears::PressureUnit::mmHg) : 0.0f;
		CardiovascularSystem.MeanArterialCarbonDioxidePartialPressureDelta = (cardiovascular->HasMeanArterialCarbonDioxidePartialPressureDelta()) ? cardiovascular->GetMeanArterialCarbonDioxidePartialPressureDelta(biogears::PressureUnit::mmHg) : 0.0f;
		CardiovascularSystem.MeanCentralVenousPressure = (cardiovascular->HasMeanCentralVenousPressure()) ? cardiovascular->GetMeanCentralVenousPressure(biogears::PressureUnit::mmHg) : 0.0f;
		CardiovascularSystem.MeanSkinFlow = (cardiovascular->HasMeanSkinFlow()) ? cardiovascular->GetMeanSkinFlow(biogears::VolumePerTimeUnit::mL_Per_min) : 0.0f;
		CardiovascularSystem.PulmonaryArterialPressure = (cardiovascular->HasPulmonaryArterialPressure()) ? cardiovascular->GetPulmonaryArterialPressure(biogears::PressureUnit::mmHg) : 0.0f;
		CardiovascularSystem.PulmonaryCapillariesWedgePressure = (cardiovascular->HasPulmonaryCapillariesWedgePressure()) ? cardiovascular->GetPulmonaryCapillariesWedgePressure(biogears::PressureUnit::mmHg) : 0.0f;
		CardiovascularSystem.PulmonaryDiastolicArterialPressure = (cardiovascular->HasPulmonaryDiastolicArterialPressure()) ? cardiovascular->GetPulmonaryDiastolicArterialPressure(biogears::PressureUnit::mmHg) : 0.0f;
		CardiovascularSystem.PulmonaryMeanArterialPressure = (cardiovascular->HasPulmonaryMeanArterialPressure()) ? cardiovascular->GetPulmonaryMeanArterialPressure(biogears::PressureUnit::mmHg) : 0.0f;
		CardiovascularSystem.PulmonaryMeanCapillaryFlow = (cardiovascular->HasPulmonaryMeanCapillaryFlow()) ? cardiovascular->GetPulmonaryMeanCapillaryFlow(biogears::VolumePerTimeUnit::mL_Per_min) : 0.0f;
		CardiovascularSystem.PulmonaryMeanShuntFlow = (cardiovascular->HasPulmonaryMeanShuntFlow()) ? cardiovascular->GetPulmonaryMeanShuntFlow(biogears::VolumePerTimeUnit::mL_Per_min) : 0.0f;
		CardiovascularSystem.PulmonarySystolicArterialPressure = (cardiovascular->HasPulmonarySystolicArterialPressure()) ? cardiovascular->GetPulmonarySystolicArterialPressure(biogears::PressureUnit::mmHg) : 0.0f;
		CardiovascularSystem.PulmonaryVascularResistance = (cardiovascular->HasPulmonaryVascularResistance()) ? cardiovascular->GetPulmonaryVascularResistance(biogears::FlowResistanceUnit::mmHg_s_Per_mL) : 0.0f;
		CardiovascularSystem.PulmonaryVascularResistanceIndex = (cardiovascular->HasPulmonaryVascularResistanceIndex()) ? cardiovascular->GetPulmonaryVascularResistanceIndex(biogears::PressureTimePerVolumeAreaUnit::mmHg_s_Per_mL_m2) : 0.0f;
		CardiovascularSystem.PulsePressure = (cardiovascular->HasPulsePressure()) ? cardiovascular->GetPulsePressure(biogears::PressureUnit::mmHg) : 0.0f;
		CardiovascularSystem.SystemicVascularResistance = (cardiovascular->HasSystemicVascularResistance()) ? cardiovascular->GetSystemicVascularResistance(biogears::FlowResistanceUnit::mmHg_s_Per_mL) : 0.0f;
		CardiovascularSystem.SystolicArterialPressure = (cardiovascular->HasSystolicArterialPressure()) ? cardiovascular->GetSystolicArterialPressure(biogears::PressureUnit::mmHg) : 0.0f;
	}
}

void FBioGearsEngine::UpdateDrugSystem()
{
	const biogears::SEDrugSystem* drugs = BGEngine->GetDrugSystem();

	if (drugs != nullptr)
	{
		DrugSystem.BronchodilationLevel = (drugs->HasBronchodilationLevel()) ? drugs->GetBronchodilationLevel() : 0.0f;
		DrugSystem.CentralNervousResponse = (drugs->HasCentralNervousResponse()) ? drugs->GetCentralNervousResponse() : 0.0f;
		DrugSystem.HeartRateChange = (drugs->HasHeartRateChange()) ? drugs->GetHeartRateChange(biogears::FrequencyUnit::Per_min) : 0.0f;
		DrugSystem.MeanBloodPressureChange = (drugs->HasMeanBloodPressureChange()) ? drugs->GetMeanBloodPressureChange(biogears::PressureUnit::mmHg) : 0.0f;
		DrugSystem.NeuromuscularBlockLevel = (drugs->HasNeuromuscularBlockLevel()) ? drugs->GetNeuromuscularBlockLevel() : 0.0f;
		DrugSystem.PulsePressureChange = (drugs->HasPulsePressureChange()) ? drugs->GetPulsePressureChange(biogears::PressureUnit::mmHg) : 0.0f;
		DrugSystem.RespirationRateChange = (drugs->HasRespirationRateChange()) ? drugs->GetRespirationRateChange(biogears::FrequencyUnit::Per_min) : 0.0f;
		DrugSystem.SedationLevel = (drugs->HasSedationLevel()) ? drugs->GetSedationLevel() : 0.0f;
		DrugSystem.TidalVolumeChange = (drugs->HasTidalVolumeChange()) ? drugs->GetTidalVolumeChange(biogears::VolumeUnit::mL) : 0.0f;
		DrugSystem.TubularPermeabilityChange = (drugs->HasTubularPermeabilityChange()) ? drugs->GetTubularPermeabilityChange() : 0.0f;
	}
}

void FBioGearsEngine::UpdateEndocrineSystem()
{
	const biogears::SEEndocrineSystem* endocrine = BGEngine->GetEndocrineSystem();

	if (endocrine != nullptr)
	{
		EndocrineSystem.GlucagonSynthesisRate = (endocrine->HasGlucagonSynthesisRate()) ? endocrine->GetGlucagonSynthesisRate(biogears::AmountPerTimeUnit::mol_Per_s) : 0.0f;
		EndocrineSystem.InsulinSynthesisRate = (endocrine->HasInsulinSynthesisRate()) ? endocrine->GetInsulinSynthesisRate(biogears::AmountPerTimeUnit::mol_Per_s) : 0.0f;
	}
}

void FBioGearsEngine::UpdateEnergySystem()
{
	const biogears::SEEnergySystem* energy = BGEngine->GetEnergySystem();

	if (energy != nullptr)
	{
		EnergySystem.AchievedExerciseLevel = (energy->HasAchievedExerciseLevel()) ? energy->GetAchievedExerciseLevel() : 0.0f;
		EnergySystem.ChlorideLostToSweat = (energy->HasChlorideLostToSweat()) ? energy->GetChlorideLostToSweat(biogears::MassUnit::g) : 0.0f;
		EnergySystem.CoreTemperature = (energy->HasCoreTemperature()) ? energy->GetCoreTemperature(biogears::TemperatureUnit::C) : 0.0f;
		EnergySystem.CreatinineProductionRate = (energy->HasCreatinineProductionRate()) ? energy->GetCreatinineProductionRate(biogears::AmountPerTimeUnit::mol_Per_s) : 0.0f;
		EnergySystem.ExerciseMeanArterialPressureDelta = (energy->HasExerciseMeanArterialPressureDelta()) ? energy->GetExerciseMeanArterialPressureDelta(biogears::PressureUnit::mmHg) : 0.0f;
		EnergySystem.FatigueLevel = (energy->HasFatigueLevel()) ? energy->GetFatigueLevel() : 0.0f;
		EnergySystem.LactateProductionRate = (energy->HasLactateProductionRate()) ? energy->GetLactateProductionRate(biogears::AmountPerTimeUnit::mol_Per_s) : 0.0f;
		EnergySystem.PotassiumLostToSweat = (energy->HasPotassiumLostToSweat()) ? energy->GetPotassiumLostToSweat(biogears::MassUnit::g) : 0.0f;
		EnergySystem.SkinTemperature = (energy->HasSkinTemperature()) ? energy->GetSkinTemperature(biogears::TemperatureUnit::C) : 0.0f;
		EnergySystem.SodiumLostToSweat = (energy->HasSodiumLostToSweat()) ? energy->GetSodiumLostToSweat(biogears::MassUnit::g) : 0.0f;
		EnergySystem.SweatRate = (energy->HasSweatRate()) ? energy->GetSweatRate(biogears::MassPerTimeUnit::g_Per_s) : 0.0f;
		EnergySystem.TotalMetabolicRate = (energy->HasTotalMetabolicRate()) ? energy->GetTotalMetabolicRate(biogears::PowerUnit::W) : 0.0f;
		EnergySystem.TotalWorkRateLevel = (energy->HasTotalWorkRateLevel()) ? energy->GetTotalWorkRateLevel() : 0.0f;
	}
}

void FBioGearsEngine::UpdateEnvironmentConditions()
{
	const biogears::SEEnvironment* environment = BGEngine->GetEnvironment();

	if (environment != nullptr && environment->HasConditions())
	{
		const biogears::SEEnvironmentalConditions* conditions = environment->GetConditions();

		EnvironmentConditions.AirDensity = (conditions->HasAirDensity()) ? conditions->GetAirDensity(biogears::MassPerVolumeUnit::g_Per_mL) : 0.0f;
		EnvironmentConditions.AirVelocity = (conditions->HasAirVelocity()) ? conditions->GetAirVelocity(biogears::LengthPerTimeUnit::m_Per_s) : 0.0f;
		EnvironmentConditions.AmbientTemperature = (conditions->HasAmbientTemperature()) ? conditions->GetAmbientTemperature(biogears::TemperatureUnit::C) : 0.0f;
		EnvironmentConditions.AtmosphericPressure = (conditions->HasAtmosphericPressure()) ? conditions->GetAtmosphericPressure(biogears::PressureUnit::mmHg) : 0.0f;
		EnvironmentConditions.ClothingResistance = (conditions->HasClothingResistance()) ? conditions->GetClothingResistance(biogears::HeatResistanceAreaUnit::rsi) : 0.0f;
		EnvironmentConditions.Emissivity = (conditions->HasEmissivity()) ? conditions->GetEmissivity() : 0.0f;
		EnvironmentConditions.MeanRadiantTemperature = (conditions->HasMeanRadiantTemperature()) ? conditions->GetMeanRadiantTemperature(biogears::TemperatureUnit::C) : 0.0f;
		EnvironmentConditions.RelativeHumidity = (conditions->HasRelativeHumidity()) ? conditions->GetRelativeHumidity() : 0.0f;
		EnvironmentConditions.RespirationAmbientTemperature = (conditions->HasRespirationAmbientTemperature()) ? conditions->GetRespirationAmbientTemperature(biogears::TemperatureUnit::C) : 0.0f;
	}

	biogears::SEEnvironmentActionCollection& environmentActions = BGEngine->GetActions().GetEnvironmentActions();
	if (environmentActions.HasThermalApplication())
	{
		biogears::SEThermalApplication* thermal = environmentActions.GetThermalApplication();
		EnvironmentConditions.AppliedTemperature = (thermal->HasAppliedTemperature()) ? thermal->GetAppliedTemperature().GetTemperature(biogears::TemperatureUnit::C) : 0.0f;
	}
}

void FBioGearsEngine::UpdateGastrointestinalSystem()
{
	const biogears::SEGastrointestinalSystem* gastrointestinal = BGEngine->GetGastrointestinalSystem();

	if (gastrointestinal != nullptr)
	{
		GastrointestinalSystem.ChymeAbsorptionRate = (gastrointestinal->HasChymeAbsorptionRate()) ? gastrointestinal->GetChymeAbsorptionRate(biogears::VolumePerTimeUnit::mL_Per_min) : 0.0f;

		if (gastrointestinal->HasStomachContents())
		{
			const biogears::SENutrition* nutrition = gastrointestinal->GetStomachContents();

			GastrointestinalSystem.StomachContents_Calcium = (nutrition->HasCalcium()) ? nutrition->GetCalcium(biogears::MassUnit::g) : 0.0f;
			GastrointestinalSystem.StomachContents_Carbohydrates = (nutrition->HasCarbohydrate()) ? nutrition->GetCarbohydrate(biogears::MassUnit::g) : 0.0f;
			GastrointestinalSystem.StomachContents_Fat = (nutrition->HasFat()) ? nutrition->GetFat(biogears::MassUnit::g) : 0.0f;
			GastrointestinalSystem.StomachContents_Protein = (nutrition->HasProtein()) ? nutrition->GetProtein(biogears::MassUnit::g) : 0.0f;
			GastrointestinalSystem.StomachContents_Sodium = (nutrition->HasSodium()) ? nutrition->GetSodium(biogears::MassUnit::g) : 0.0f;
			GastrointestinalSystem.StomachContents_Water = (nutrition->HasWater()) ? nutrition->GetWater(biogears::VolumeUnit::mL) : 0.0f;
		}
	}
}

void FBioGearsEngine::UpdateHepaticSystem()
{
	const biogears::SEHepaticSystem* hepatic = BGEngine->GetHepaticSystem();

	if (hepatic != nullptr)
	{
		HepaticSystem.HepaticGluconeogenesisRate = (hepatic->HasHepaticGluconeogenesisRate()) ? hepatic->GetHepaticGluconeogenesisRate(biogears::MassPerTimeUnit::g_Per_s) : 0.0f;
		HepaticSystem.KetoneProductionRate = (hepatic->HasKetoneProductionRate()) ? hepatic->GetKetoneProductionRate(biogears::AmountPerTimeUnit::mol_Per_s) : 0.0f;
	}
}

void FBioGearsEngine::UpdateInflammatoryResponse()
{
	const biogears::SEBloodChemistrySystem* bloodChemistry = BGEngine->GetBloodChemistrySystem();

	if (bloodChemistry != nullptr && bloodChemistry->HasInflammatoryResponse())
	{
		const biogears::SEInflammatoryResponse& inflammatoryResponse = BGEngine->GetBloodChemistrySystem()->GetInflammatoryResponse();

		InflammatoryResponse.BloodPathogen = (inflammatoryResponse.HasBloodPathogen()) ? inflammatoryResponse.GetBloodPathogen() : 0.0f;
		InflammatoryResponse.Catecholamines = (inflammatoryResponse.HasCatecholamines()) ? inflammatoryResponse.GetCatecholamines() : 0.0f;
		InflammatoryResponse.ConstitutiveNOS = (inflammatoryResponse.HasConstitutiveNOS()) ? inflammatoryResponse.GetConstitutiveNOS() : 0.0f;
		InflammatoryResponse.InducibleNOS = (inflammatoryResponse.HasInducibleNOS()) ? inflammatoryResponse.GetInducibleNOS() : 0.0f;
		InflammatoryResponse.InducibleNOSPre = (inflammatoryResponse.HasInducibleNOSPre()) ? inflammatoryResponse.GetInducibleNOSPre() : 0.0f;
		InflammatoryResponse.Interleukin6 = (inflammatoryResponse.HasInterleukin6()) ? inflammatoryResponse.GetInterleukin6() : 0.0f;
		InflammatoryResponse.Interleukin10 = (inflammatoryResponse.HasInterleukin10()) ? inflammatoryResponse.GetInterleukin10() : 0.0f;
		InflammatoryResponse.Interleukin12 = (inflammatoryResponse.HasInterleukin12()) ? inflammatoryResponse.GetInterleukin12() : 0.0f;
		InflammatoryResponse.LocalPathogen = (inflammatoryResponse.HasLocalPathogen()) ? inflammatoryResponse.GetLocalPathogen() : 0.0f;
		InflammatoryResponse.LocalMacrophage = (inflammatoryResponse.HasLocalMacrophage()) ? inflammatoryResponse.GetLocalMacrophage() : 0.0f;
		InflammatoryResponse.LocalNeutrophil = (inflammatoryResponse.HasLocalNeutrophil()) ? inflammatoryResponse.GetLocalNeutrophil() : 0.0f;
		InflammatoryResponse.LocalBarrier = (inflammatoryResponse.HasLocalBarrier()) ? inflammatoryResponse.GetLocalBarrier() : 0.0f;
		InflammatoryResponse.MacrophageResting = (inflammatoryResponse.HasMacrophageResting()) ? inflammatoryResponse.GetMacrophageResting() : 0.0f;
		InflammatoryResponse.MacrophageActive = (inflammatoryResponse.HasMacrophageActive()) ? inflammatoryResponse.GetMacrophageActive() : 0.0f;
		InflammatoryResponse.NeutrophilResting = (inflammatoryResponse.HasNeutrophilResting()) ? inflammatoryResponse.GetNeutrophilResting() : 0.0f;
		InflammatoryResponse.NeutrophilActive = (inflammatoryResponse.HasNeutrophilActive()) ? inflammatoryResponse.GetNeutrophilActive() : 0.0f;
		InflammatoryResponse.Nitrate = (inflammatoryResponse.HasNitrate()) ? inflammatoryResponse.GetNitrate() : 0.0f;
		InflammatoryResponse.NitricOxide = (inflammatoryResponse.HasNitricOxide()) ? inflammatoryResponse.GetNitricOxide() : 0.0f;
		InflammatoryResponse.TissueIntegrity = (inflammatoryResponse.HasTissueIntegrity()) ? inflammatoryResponse.GetTissueIntegrity() : 0.0f;
		InflammatoryResponse.Trauma = (inflammatoryResponse.HasTrauma()) ? inflammatoryResponse.GetTrauma() : 0.0f;
		InflammatoryResponse.TumorNecrosisFactor = (inflammatoryResponse.HasTumorNecrosisFactor()) ? inflammatoryResponse.GetTumorNecrosisFactor() : 0.0f;
	}
}

void FBioGearsEngine::UpdateNervousSystem()
{
	const biogears::SENervousSystem* nervous = BGEngine->GetNervousSystem();

	if (nervous != nullptr)
	{
		NervousSystem.ComplianceScale = (nervous->HasComplianceScale()) ? nervous->GetComplianceScale() : 0.0f;
		NervousSystem.HeartRateScale = (nervous->HasHeartRateScale()) ? nervous->GetHeartRateScale() : 0.0f;
		NervousSystem.HeartElastanceScale = (nervous->HasHeartElastanceScale()) ? nervous->GetHeartElastanceScale() : 0.0f;
		NervousSystem.ResistanceScaleExtrasplanchnic = (nervous->HasResistanceScaleExtrasplanchnic()) ? nervous->GetResistanceScaleExtrasplanchnic() : 0.0f;
		NervousSystem.ResistanceScaleMuscle = (nervous->HasResistanceScaleMuscle()) ? nervous->GetResistanceScaleMuscle() : 0.0f;
		NervousSystem.ResistanceScaleMyocardium = (nervous->HasResistanceScaleMyocardium()) ? nervous->GetResistanceScaleMyocardium() : 0.0f;
		NervousSystem.ResistanceScaleSplanchnic = (nervous->HasResistanceScaleSplanchnic()) ? nervous->GetResistanceScaleSplanchnic() : 0.0f;

		NervousSystem.PainVisualAnalogueScale = (nervous->HasPainVisualAnalogueScale()) ? nervous->GetPainVisualAnalogueScale() : 0.0f;

		//TODO: Implement Pupillary Response  ReactivityModifier  ShapeModifier  SizeModifier;
		NervousSystem.LeftEyePupillaryResponse = 0.0;
		NervousSystem.RightEyePupillaryResponse = 0.0;
	}

}

void FBioGearsEngine::UpdatePatientData()
{
	const biogears::SEPatient& patient = BGEngine->GetPatient();

	PatientData.Age = (patient.HasAge()) ? patient.GetAge(biogears::TimeUnit::yr) : 0.0f;
	PatientData.BloodRh = (patient.HasBloodRh()) ? patient.GetBloodRh() : 0.0f;
	PatientData.BloodVolumeBaseline = (patient.HasBloodVolumeBaseline()) ? patient.GetBloodVolumeBaseline(biogears::VolumeUnit::mL) : 0.0f;
	PatientData.BodyFatFraction = (patient.HasBodyFatFraction()) ? patient.GetBodyFatFraction() : 0.0f;
	PatientData.ExpiratoryReserveVolume = (patient.HasExpiratoryReserveVolume()) ? patient.GetExpiratoryReserveVolume(biogears::VolumeUnit::mL) : 0.0f;
	PatientData.HeartRateBaseline = (patient.HasHeartRateBaseline()) ? patient.GetHeartRateBaseline(biogears::FrequencyUnit::Per_min) : 0.0f;
	PatientData.HeartRateMaximum = (patient.HasHeartRateMaximum()) ? patient.GetHeartRateMaximum(biogears::FrequencyUnit::Per_min) : 0.0f;
	PatientData.HeartRateMinimum = (patient.HasHeartRateMinimum()) ? patient.GetHeartRateMinimum(biogears::FrequencyUnit::Per_min) : 0.0f;
	PatientData.Height = (patient.HasHeight()) ? patient.GetHeight(biogears::LengthUnit::m) : 0.0f;
	PatientData.InspiratoryCapacity = (patient.HasInspiratoryCapacity()) ? patient.GetInspiratoryCapacity(biogears::VolumeUnit::mL) : 0.0f;
	PatientData.LeanBodyMass = (patient.HasLeanBodyMass()) ? patient.GetLeanBodyMass(biogears::MassUnit::g) : 0.0f;
	PatientData.MuscleMass = (patient.HasMuscleMass()) ? patient.GetMuscleMass(biogears::MassUnit::g) : 0.0f;
	PatientData.Name = (patient.HasName()) ? ANSI_TO_TCHAR(patient.GetName_cStr()) : FString("");
	PatientData.PainSusceptibility = (patient.HasPainSusceptibility()) ? patient.GetPainSusceptibility() : 0.0f;
	PatientData.RespirationRateBaseline = (patient.HasRespirationRateBaseline()) ? patient.GetRespirationRateBaseline(biogears::FrequencyUnit::Per_min) : 0.0f;
	PatientData.SystolicArterialPressureBaseline = (patient.HasSystolicArterialPressureBaseline()) ? patient.GetSystolicArterialPressureBaseline(biogears::PressureUnit::mmHg) : 0.0f;
	PatientData.TotalLungCapacity = (patient.HasTotalLungCapacity()) ? patient.GetTotalLungCapacity(biogears::VolumeUnit::mL) : 0.0f;
	PatientData.VitalCapacity = (patient.HasVitalCapacity()) ? patient.GetVitalCapacity(biogears::VolumeUnit::mL) : 0.0f;
	PatientData.Weight = (patient.HasWeight()) ? patient.GetWeight(biogears::MassUnit::lb) : 0.0f;

	if (patient.HasBloodType())
	{
		CDM::enumBloodType::value type = patient.GetBloodType();
		switch (type)
		{
		case CDM::enumBloodType::A:
			PatientData.BloodType = EBioGearsPatientBloodType::A;
			break;
		case CDM::enumBloodType::AB:
			PatientData.BloodType = EBioGearsPatientBloodType::AB;
			break;
		case CDM::enumBloodType::B:
			PatientData.BloodType = EBioGearsPatientBloodType::B;
			break;
		case CDM::enumBloodType::O:
			PatientData.BloodType = EBioGearsPatientBloodType::O;
			break;
		}
	}
	else
	{
		PatientData.BloodType = EBioGearsPatientBloodType::None;
	}

	if (patient.HasGender())
	{
		CDM::enumSex::value sex = patient.GetGender();
		switch (sex)
		{
		case CDM::enumSex::Female:
			PatientData.Gender = EBioGearsPatientSex::Female;
			break;
		case CDM::enumSex::Male:
			PatientData.Gender = EBioGearsPatientSex::Male;
			break;
		}
	}
	else
	{
		PatientData.Gender = EBioGearsPatientSex::None;
	}

	if (patient.HasSex())
	{
		CDM::enumSex::value sex = patient.GetSex();
		switch (sex)
		{
		case CDM::enumSex::Female:
			PatientData.Sex = EBioGearsPatientSex::Female;
			break;
		case CDM::enumSex::Male:
			PatientData.Sex = EBioGearsPatientSex::Male;
			break;
		}
	}
	else
	{
		PatientData.Sex = EBioGearsPatientSex::None;
	}
}

void FBioGearsEngine::UpdateRenalSystem()
{
	const biogears::SERenalSystem* renal = BGEngine->GetRenalSystem();

	if (renal != nullptr)
	{
		RenalSystem.FiltrationFraction = (renal->HasFiltrationFraction()) ? renal->GetFiltrationFraction() : 0.0f;
		RenalSystem.GlomerularFiltrationRate = (renal->HasGlomerularFiltrationRate()) ? renal->GetGlomerularFiltrationRate(biogears::VolumePerTimeUnit::mL_Per_min) : 0.0f;
		RenalSystem.LeftAfferentArterioleResistance = (renal->HasLeftAfferentArterioleResistance()) ? renal->GetLeftAfferentArterioleResistance(biogears::FlowResistanceUnit::mmHg_min_Per_mL) : 0.0f;
		RenalSystem.LeftBowmansCapsulesHydrostaticPressure = (renal->HasLeftBowmansCapsulesHydrostaticPressure()) ? renal->GetLeftBowmansCapsulesHydrostaticPressure(biogears::PressureUnit::mmHg) : 0.0f;
		RenalSystem.LeftBowmansCapsulesOsmoticPressure = (renal->HasLeftBowmansCapsulesOsmoticPressure()) ? renal->GetLeftBowmansCapsulesOsmoticPressure(biogears::PressureUnit::mmHg) : 0.0f;
		RenalSystem.LeftEfferentArterioleResistance = (renal->HasLeftEfferentArterioleResistance()) ? renal->GetLeftEfferentArterioleResistance(biogears::FlowResistanceUnit::mmHg_min_Per_mL) : 0.0f;
		RenalSystem.LeftGlomerularCapillariesHydrostaticPressure = (renal->HasLeftGlomerularCapillariesHydrostaticPressure()) ? renal->GetLeftGlomerularCapillariesHydrostaticPressure(biogears::PressureUnit::mmHg) : 0.0f;
		RenalSystem.LeftGlomerularCapillariesOsmoticPressure = (renal->HasLeftGlomerularCapillariesOsmoticPressure()) ? renal->GetLeftGlomerularCapillariesOsmoticPressure(biogears::PressureUnit::mmHg) : 0.0f;
		RenalSystem.LeftGlomerularFiltrationCoefficient = (renal->HasLeftGlomerularFiltrationCoefficient()) ? renal->GetLeftGlomerularFiltrationCoefficient(biogears::VolumePerTimePressureUnit::mL_Per_min_mmHg) : 0.0f;
		RenalSystem.LeftGlomerularFiltrationRate = (renal->HasLeftGlomerularFiltrationRate()) ? renal->GetLeftGlomerularFiltrationRate(biogears::VolumePerTimeUnit::mL_Per_min) : 0.0f;
		RenalSystem.LeftGlomerularFiltrationSurfaceArea = (renal->HasLeftGlomerularFiltrationSurfaceArea()) ? renal->GetLeftGlomerularFiltrationSurfaceArea(biogears::AreaUnit::cm2) : 0.0f;
		RenalSystem.LeftGlomerularFluidPermeability = (renal->HasLeftGlomerularFluidPermeability()) ? renal->GetLeftGlomerularFluidPermeability(biogears::VolumePerTimePressureAreaUnit::mL_Per_min_mmHg_m2) : 0.0f;
		RenalSystem.LeftFiltrationFraction = (renal->HasLeftFiltrationFraction()) ? renal->GetLeftFiltrationFraction() : 0.0f;
		RenalSystem.LeftNetFiltrationPressure = (renal->HasLeftNetFiltrationPressure()) ? renal->GetLeftNetFiltrationPressure(biogears::PressureUnit::mmHg) : 0.0f;
		RenalSystem.LeftNetReabsorptionPressure = (renal->HasLeftNetReabsorptionPressure()) ? renal->GetLeftNetReabsorptionPressure(biogears::PressureUnit::mmHg) : 0.0f;
		RenalSystem.LeftPeritubularCapillariesHydrostaticPressure = (renal->HasLeftPeritubularCapillariesHydrostaticPressure()) ? renal->GetLeftPeritubularCapillariesHydrostaticPressure(biogears::PressureUnit::mmHg) : 0.0f;
		RenalSystem.LeftPeritubularCapillariesOsmoticPressure = (renal->HasLeftPeritubularCapillariesOsmoticPressure()) ? renal->GetLeftPeritubularCapillariesOsmoticPressure(biogears::PressureUnit::mmHg) : 0.0f;
		RenalSystem.LeftReabsorptionFiltrationCoefficient = (renal->HasLeftReabsorptionFiltrationCoefficient()) ? renal->GetLeftReabsorptionFiltrationCoefficient(biogears::VolumePerTimePressureUnit::mL_Per_min_mmHg) : 0.0f;
		RenalSystem.LeftReabsorptionRate = (renal->HasLeftReabsorptionRate()) ? renal->GetLeftReabsorptionRate(biogears::VolumePerTimeUnit::mL_Per_min) : 0.0f;
		RenalSystem.LeftTubularReabsorptionFiltrationSurfaceArea = (renal->HasLeftTubularReabsorptionFiltrationSurfaceArea()) ? renal->GetLeftTubularReabsorptionFiltrationSurfaceArea(biogears::AreaUnit::cm2) : 0.0f;
		RenalSystem.LeftTubularReabsorptionFluidPermeability = (renal->HasLeftTubularReabsorptionFluidPermeability()) ? renal->GetLeftTubularReabsorptionFluidPermeability(biogears::VolumePerTimePressureAreaUnit::mL_Per_min_mmHg_m2) : 0.0f;
		RenalSystem.LeftTubularHydrostaticPressure = (renal->HasLeftTubularHydrostaticPressure()) ? renal->GetLeftTubularHydrostaticPressure(biogears::PressureUnit::mmHg) : 0.0f;
		RenalSystem.LeftTubularOsmoticPressure = (renal->HasLeftTubularOsmoticPressure()) ? renal->GetLeftTubularOsmoticPressure(biogears::PressureUnit::mmHg) : 0.0f;
		RenalSystem.MeanUrineOutput = (renal->HasMeanUrineOutput()) ? renal->GetMeanUrineOutput(biogears::VolumePerTimeUnit::mL_Per_min) : 0.0f;
		RenalSystem.RenalBloodFlow = (renal->HasRenalBloodFlow()) ? renal->GetRenalBloodFlow(biogears::VolumePerTimeUnit::mL_Per_min) : 0.0f;
		RenalSystem.RenalPlasmaFlow = (renal->HasRenalPlasmaFlow()) ? renal->GetRenalPlasmaFlow(biogears::VolumePerTimeUnit::mL_Per_min) : 0.0f;
		RenalSystem.RenalVascularResistance = (renal->HasRenalVascularResistance()) ? renal->GetRenalVascularResistance(biogears::FlowResistanceUnit::mmHg_min_Per_mL) : 0.0f;
		RenalSystem.RightAfferentArterioleResistance = (renal->HasRightAfferentArterioleResistance()) ? renal->GetRightAfferentArterioleResistance(biogears::FlowResistanceUnit::mmHg_min_Per_mL) : 0.0f;
		RenalSystem.RightBowmansCapsulesHydrostaticPressure = (renal->HasRightBowmansCapsulesHydrostaticPressure()) ? renal->GetRightBowmansCapsulesHydrostaticPressure(biogears::PressureUnit::mmHg) : 0.0f;
		RenalSystem.RightBowmansCapsulesOsmoticPressure = (renal->HasRightBowmansCapsulesOsmoticPressure()) ? renal->GetRightBowmansCapsulesOsmoticPressure(biogears::PressureUnit::mmHg) : 0.0f;
		RenalSystem.RightEfferentArterioleResistance = (renal->HasRightEfferentArterioleResistance()) ? renal->GetRightEfferentArterioleResistance(biogears::FlowResistanceUnit::mmHg_min_Per_mL) : 0.0f;
		RenalSystem.RightGlomerularCapillariesHydrostaticPressure = (renal->HasRightGlomerularCapillariesHydrostaticPressure()) ? renal->GetRightGlomerularCapillariesHydrostaticPressure(biogears::PressureUnit::mmHg) : 0.0f;
		RenalSystem.RightGlomerularCapillariesOsmoticPressure = (renal->HasRightGlomerularCapillariesOsmoticPressure()) ? renal->GetRightGlomerularCapillariesOsmoticPressure(biogears::PressureUnit::mmHg) : 0.0f;
		RenalSystem.RightGlomerularFiltrationCoefficient = (renal->HasRightGlomerularFiltrationCoefficient()) ? renal->GetRightGlomerularFiltrationCoefficient(biogears::VolumePerTimePressureUnit::mL_Per_min_mmHg) : 0.0f;
		RenalSystem.RightGlomerularFiltrationRate = (renal->HasRightGlomerularFiltrationRate()) ? renal->GetRightGlomerularFiltrationRate(biogears::VolumePerTimeUnit::mL_Per_min) : 0.0f;
		RenalSystem.RightGlomerularFiltrationSurfaceArea = (renal->HasRightGlomerularFiltrationSurfaceArea()) ? renal->GetRightGlomerularFiltrationSurfaceArea(biogears::AreaUnit::cm2) : 0.0f;
		RenalSystem.RightGlomerularFluidPermeability = (renal->HasRightGlomerularFluidPermeability()) ? renal->GetRightGlomerularFluidPermeability(biogears::VolumePerTimePressureAreaUnit::mL_Per_min_mmHg_m2) : 0.0f;
		RenalSystem.RightFiltrationFraction = (renal->HasRightFiltrationFraction()) ? renal->GetRightFiltrationFraction() : 0.0f;
		RenalSystem.RightNetFiltrationPressure = (renal->HasRightNetFiltrationPressure()) ? renal->GetRightNetFiltrationPressure(biogears::PressureUnit::mmHg) : 0.0f;
		RenalSystem.RightNetReabsorptionPressure = (renal->HasRightNetReabsorptionPressure()) ? renal->GetRightNetReabsorptionPressure(biogears::PressureUnit::mmHg) : 0.0f;
		RenalSystem.RightPeritubularCapillariesHydrostaticPressure = (renal->HasRightPeritubularCapillariesHydrostaticPressure()) ? renal->GetRightPeritubularCapillariesHydrostaticPressure(biogears::PressureUnit::mmHg) : 0.0f;
		RenalSystem.RightPeritubularCapillariesOsmoticPressure = (renal->HasRightPeritubularCapillariesOsmoticPressure()) ? renal->GetRightPeritubularCapillariesOsmoticPressure(biogears::PressureUnit::mmHg) : 0.0f;
		RenalSystem.RightReabsorptionFiltrationCoefficient = (renal->HasRightReabsorptionFiltrationCoefficient()) ? renal->GetRightReabsorptionFiltrationCoefficient(biogears::VolumePerTimePressureUnit::mL_Per_min_mmHg) : 0.0f;
		RenalSystem.RightReabsorptionRate = (renal->HasRightReabsorptionRate()) ? renal->GetRightReabsorptionRate(biogears::VolumePerTimeUnit::mL_Per_min) : 0.0f;
		RenalSystem.RightTubularReabsorptionFiltrationSurfaceArea = (renal->HasRightTubularReabsorptionFiltrationSurfaceArea()) ? renal->GetRightTubularReabsorptionFiltrationSurfaceArea(biogears::AreaUnit::cm2) : 0.0f;
		RenalSystem.RightTubularReabsorptionFluidPermeability = (renal->HasRightTubularReabsorptionFluidPermeability()) ? renal->GetRightTubularReabsorptionFluidPermeability(biogears::VolumePerTimePressureAreaUnit::mL_Per_min_mmHg_m2) : 0.0f;
		RenalSystem.RightTubularHydrostaticPressure = (renal->HasRightTubularHydrostaticPressure()) ? renal->GetRightTubularHydrostaticPressure(biogears::PressureUnit::mmHg) : 0.0f;
		RenalSystem.RightTubularOsmoticPressure = (renal->HasRightTubularOsmoticPressure()) ? renal->GetRightTubularOsmoticPressure(biogears::PressureUnit::mmHg) : 0.0f;
		RenalSystem.UrinationRate = (renal->HasUrinationRate()) ? renal->GetUrinationRate(biogears::VolumePerTimeUnit::mL_Per_min) : 0.0f;
		RenalSystem.UrineOsmolality = (renal->HasUrineOsmolality()) ? renal->GetUrineOsmolality(biogears::OsmolalityUnit::Osm_Per_kg) : 0.0f;
		RenalSystem.UrineProductionRate = (renal->HasUrineProductionRate()) ? renal->GetUrineProductionRate(biogears::VolumePerTimeUnit::mL_Per_min) : 0.0f;
		RenalSystem.UrineSpecificGravity = (renal->HasUrineSpecificGravity()) ? renal->GetUrineSpecificGravity() : 0.0f;
		RenalSystem.UrineUreaNitrogenConcentration = (renal->HasUrineUreaNitrogenConcentration()) ? renal->GetUrineUreaNitrogenConcentration(biogears::MassPerVolumeUnit::g_Per_mL) : 0.0f;
		RenalSystem.UrineVolume = (renal->HasUrineVolume()) ? renal->GetUrineVolume(biogears::VolumeUnit::mL) : 0.0f;
	}
}

void FBioGearsEngine::UpdateRespiratorySystem()
{
	const biogears::SERespiratorySystem* respiratory = BGEngine->GetRespiratorySystem();

	if (respiratory != nullptr)
	{
		RespiratorySystem.AlveolarArterialGradient = (respiratory->HasAlveolarArterialGradient()) ? respiratory->GetAlveolarArterialGradient(biogears::PressureUnit::mmHg) : 0.0f;
		RespiratorySystem.CarricoIndex = (respiratory->HasCarricoIndex()) ? respiratory->GetCarricoIndex(biogears::PressureUnit::mmHg) : 0.0f;
		RespiratorySystem.EndTidalCarbonDioxideFraction = (respiratory->HasEndTidalCarbonDioxideFraction()) ? respiratory->GetEndTidalCarbonDioxideFraction() : 0.0f;
		RespiratorySystem.EndTidalCarbonDioxidePressure = (respiratory->HasEndTidalCarbonDioxidePressure()) ? respiratory->GetEndTidalCarbonDioxidePressure(biogears::PressureUnit::mmHg) : 0.0f;
		RespiratorySystem.ExpiratoryFlow = (respiratory->HasExpiratoryFlow()) ? respiratory->GetExpiratoryFlow(biogears::VolumePerTimeUnit::mL_Per_min) : 0.0f;
		RespiratorySystem.InspiratoryExpiratoryRatio = (respiratory->HasInspiratoryExpiratoryRatio()) ? respiratory->GetInspiratoryExpiratoryRatio() : 0.0f;
		RespiratorySystem.InspiratoryFlow = (respiratory->HasInspiratoryFlow()) ? respiratory->GetInspiratoryFlow(biogears::VolumePerTimeUnit::mL_Per_min) : 0.0f;
		RespiratorySystem.PulmonaryCompliance = (respiratory->HasPulmonaryCompliance()) ? respiratory->GetPulmonaryCompliance(biogears::FlowComplianceUnit::mL_Per_mmHg) : 0.0f;
		RespiratorySystem.PulmonaryResistance = (respiratory->HasPulmonaryResistance()) ? respiratory->GetPulmonaryResistance(biogears::FlowResistanceUnit::mmHg_s_Per_mL) : 0.0f;
		RespiratorySystem.RespirationDriverPressure = (respiratory->HasRespirationDriverPressure()) ? respiratory->GetRespirationDriverPressure(biogears::PressureUnit::mmHg) : 0.0f;
		RespiratorySystem.RespirationMusclePressure = (respiratory->HasRespirationMusclePressure()) ? respiratory->GetRespirationMusclePressure(biogears::PressureUnit::mmHg) : 0.0f;
		RespiratorySystem.RespirationRate = (respiratory->HasRespirationRate()) ? respiratory->GetRespirationRate(biogears::FrequencyUnit::Per_min) : 0.0f;
		RespiratorySystem.SpecificVentilation = (respiratory->HasSpecificVentilation()) ? respiratory->GetSpecificVentilation() : 0.0f;
		RespiratorySystem.TargetPulmonaryVentilation = (respiratory->HasTargetPulmonaryVentilation()) ? respiratory->GetTargetPulmonaryVentilation(biogears::VolumePerTimeUnit::mL_Per_min) : 0.0f;
		RespiratorySystem.TidalVolume = (respiratory->HasTidalVolume()) ? respiratory->GetTidalVolume(biogears::VolumeUnit::mL) : 0.0f;
		RespiratorySystem.TotalAlveolarVentilation = (respiratory->HasTotalAlveolarVentilation()) ? respiratory->GetTotalAlveolarVentilation(biogears::VolumePerTimeUnit::mL_Per_min) : 0.0f;
		RespiratorySystem.TotalDeadSpaceVentilation = (respiratory->HasTotalDeadSpaceVentilation()) ? respiratory->GetTotalDeadSpaceVentilation(biogears::VolumePerTimeUnit::mL_Per_min) : 0.0f;
		RespiratorySystem.TotalLungVolume = (respiratory->HasTotalLungVolume()) ? respiratory->GetTotalLungVolume(biogears::VolumeUnit::mL) : 0.0f;
		RespiratorySystem.TotalPulmonaryVentilation = (respiratory->HasTotalPulmonaryVentilation()) ? respiratory->GetTotalPulmonaryVentilation(biogears::VolumePerTimeUnit::mL_Per_min) : 0.0f;
		RespiratorySystem.TranspulmonaryPressure = (respiratory->HasTranspulmonaryPressure()) ? respiratory->GetTranspulmonaryPressure(biogears::PressureUnit::mmHg) : 0.0f;
	}
}

void FBioGearsEngine::UpdateTissueSystem()
{
	const biogears::SETissueSystem* tissue = BGEngine->GetTissueSystem();

	if (tissue != nullptr)
	{
		TissueSystem.CarbonDioxideProductionRate = (tissue->HasCarbonDioxideProductionRate()) ? tissue->GetCarbonDioxideProductionRate(biogears::VolumePerTimeUnit::mL_Per_min) : 0.0f;
		TissueSystem.DehydrationFraction = (tissue->HasDehydrationFraction()) ? tissue->GetDehydrationFraction() : 0.0f;
		TissueSystem.ExtracellularFluidVolume = (tissue->HasExtracellularFluidVolume()) ? tissue->GetExtracellularFluidVolume(biogears::VolumeUnit::mL) : 0.0f;
		TissueSystem.ExtravascularFluidVolume = (tissue->HasExtravascularFluidVolume()) ? tissue->GetExtravascularFluidVolume(biogears::VolumeUnit::mL) : 0.0f;
		TissueSystem.FatInsulinSetPoint = (tissue->HasFatInsulinSetPoint()) ? tissue->GetFatInsulinSetPoint(biogears::AmountPerVolumeUnit::mol_Per_mL) : 0.0f;
		TissueSystem.FatGlucagonSetPoint = (tissue->HasFatGlucagonSetPoint()) ? tissue->GetFatGlucagonSetPoint(biogears::MassPerVolumeUnit::g_Per_mL) : 0.0f;
		TissueSystem.IntracellularFluidPH = (tissue->HasIntracellularFluidPH()) ? tissue->GetIntracellularFluidPH() : 0.0f;
		TissueSystem.IntracellularFluidVolume = (tissue->HasIntracellularFluidVolume()) ? tissue->GetIntracellularFluidVolume(biogears::VolumeUnit::mL) : 0.0f;
		TissueSystem.LiverInsulinSetPoint = (tissue->HasLiverInsulinSetPoint()) ? tissue->GetLiverInsulinSetPoint(biogears::AmountPerVolumeUnit::mol_Per_mL) : 0.0f;
		TissueSystem.LiverGlycogen = (tissue->HasLiverGlycogen()) ? tissue->GetLiverGlycogen(biogears::MassUnit::g) : 0.0f;
		TissueSystem.LiverGlucagonSetPoint = (tissue->HasLiverGlucagonSetPoint()) ? tissue->GetLiverGlucagonSetPoint(biogears::MassPerVolumeUnit::g_Per_mL) : 0.0f;
		TissueSystem.MuscleGlycogen = (tissue->HasMuscleGlycogen()) ? tissue->GetMuscleGlycogen(biogears::MassUnit::g) : 0.0f;
		TissueSystem.MuscleGlucagonSetPoint = (tissue->HasMuscleGlucagonSetPoint()) ? tissue->GetMuscleGlucagonSetPoint(biogears::MassPerVolumeUnit::g_Per_mL) : 0.0f;
		TissueSystem.MuscleInsulinSetPoint = (tissue->HasMuscleInsulinSetPoint()) ? tissue->GetMuscleInsulinSetPoint(biogears::AmountPerVolumeUnit::mol_Per_mL) : 0.0f;
		TissueSystem.OxygenConsumptionRate = (tissue->HasOxygenConsumptionRate()) ? tissue->GetOxygenConsumptionRate(biogears::VolumePerTimeUnit::mL_Per_min) : 0.0f;
		TissueSystem.RespiratoryExchangeRatio = (tissue->HasRespiratoryExchangeRatio()) ? tissue->GetRespiratoryExchangeRatio() : 0.0f;
		TissueSystem.StoredProtein = (tissue->HasStoredProtein()) ? tissue->GetStoredProtein(biogears::MassUnit::g) : 0.0f;
		TissueSystem.StoredFat = (tissue->HasStoredFat()) ? tissue->GetStoredFat(biogears::MassUnit::g) : 0.0f;
		TissueSystem.TotalBodyFluidVolume = (tissue->HasTotalBodyFluidVolume()) ? tissue->GetTotalBodyFluidVolume(biogears::VolumeUnit::mL) : 0.0f;
	}
}

// -------------- Infusion Data -------------- //

void FBioGearsEngine::UpdateSubstanceInfusions()
{
	SubstanceInfusions.Infusions.Empty();

	const std::map<const biogears::SESubstance*, biogears::SESubstanceInfusion*> infusionMap = BGEngine->GetActions().GetPatientActions().GetSubstanceInfusions();
	for (auto infusion = infusionMap.begin(); infusion != infusionMap.end(); infusion++)
	{
		FBioGearsSubstance substance;
		substance.Name = ANSI_TO_TCHAR(infusion->first->GetName_cStr());
		substance.InfusionRate = infusion->second->GetRate().GetValue(biogears::VolumePerTimeUnit::mL_Per_hr);
		substance.Concentration = infusion->second->GetConcentration().GetValue(biogears::MassPerVolumeUnit::g_Per_mL);

		SubstanceInfusions.Infusions.Add(substance);
	}
}

void FBioGearsEngine::UpdateCompoundInfusions()
{
	CompoundInfusions.Infusions.Empty();

	const std::map<const biogears::SESubstanceCompound*, biogears::SESubstanceCompoundInfusion*> infusionMap = BGEngine->GetActions().GetPatientActions().GetSubstanceCompoundInfusions();
	for (auto infusion = infusionMap.begin(); infusion != infusionMap.end(); infusion++)
	{
		FBioGearsCompound compound;
		compound.Name = ANSI_TO_TCHAR(infusion->first->GetName_cStr());
		compound.InfusionRate = infusion->second->GetRate().GetValue(biogears::VolumePerTimeUnit::mL_Per_hr);
		compound.Volume = infusion->second->GetBagVolume().GetValue(biogears::VolumeUnit::mL);

		CompoundInfusions.Infusions.Add(compound);
	}
}

// -------------- BioGears Data -------------- //

void FBioGearsEngine::UpdateBioGearsConditions()
{
	BioGearsConditions.bDiabieties = BGEngine->GetConditions().HasDiabetesType1() || BGEngine->GetConditions().HasDiabetesType2();
}

void FBioGearsEngine::UpdateBioGearsMetrics()
{
	BioGearsMetrics.SimulationTime = BGEngine->GetSimulationTime(biogears::TimeUnit::s);
	BioGearsMetrics.TimeStep = BGEngine->GetTimeStep(biogears::TimeUnit::s);
}

void FBioGearsEngine::UpdateBioGearsState()
{
	const biogears::SEPatient& patient = BGEngine->GetPatient();

	// TODO: Implement IsAlive
	BioGearsState.bLiving = true;

	// TODO: Implement Tacycardia HR > 100
	BioGearsState.bTacycardia = false;

	BioGearsState.Age = (patient.HasAge()) ? patient.GetAge(biogears::TimeUnit::yr) : 0.0f;
	BioGearsState.Height = (patient.HasHeight()) ? patient.GetHeight(biogears::LengthUnit::cm) : 0.0f;
	//BioGearsState.Gender = (!patient.HasGender()) ? EBioGearsGender::NONE : (patient.GetGender() == CDM::enumSex::Male) ? EBioGearsGender::MALE : EBioGearsGender::OTHER;
	BioGearsState.Weight = (patient.HasWeight()) ? patient.GetWeight(biogears::MassUnit::kg) : 0.0f;
	BioGearsState.BodyFat = (patient.HasBodyFatFraction()) ? patient.GetBodyFatFraction() : 0.0f;

	if (patient.HasWeight() && patient.HasWeight())
	{
		BioGearsState.BodySurfaceArea = std::sqrt(patient.GetHeight(biogears::LengthUnit::cm) * patient.GetWeight(biogears::MassUnit::kg) / 3600.0);
		BioGearsState.BodyMassIndex = patient.GetWeight(biogears::MassUnit::kg) / std::pow(patient.GetHeight(biogears::LengthUnit::m), 2);
	}
	else
	{
		BioGearsState.BodySurfaceArea = 0.0;
		BioGearsState.BodyMassIndex = 0.0;
	}

	// TODO: Lets take intensity and make a series of animated GIFs inspired off vault-boy
	//BioGearsState.ExerciseState = (_bg->GetActions().GetPatientActions().HasExercise()) ? EBioGearsExerciseState::STANDING : EBioGearsExerciseState::RUNNING;
}
