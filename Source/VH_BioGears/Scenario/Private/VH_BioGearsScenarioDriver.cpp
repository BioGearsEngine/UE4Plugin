#include "VH_BioGearsScenarioDriver.h"

#if  defined(WITH_BIOGEARS_BINDING) // TODO: Remove when biogears works on android
// BioGears
#include "VH_BioGearsPreHeaderBlock.inl"
#include "biogears/cdm/substance/SESubstanceCompound.h"
#include "VH_BioGearsPostHeaderBlock.inl"
#endif

// Engine
#include "Misc/ScopeLock.h"

// VH BioGears Plugin
#include "VH_BioGears.h"


// ---------------------------------
// --- Constructors
// ---------------------------------

UVH_BioGearsScenarioDriver::UVH_BioGearsScenarioDriver(const FObjectInitializer& objectInitializer) :
	Super(objectInitializer),
	Engine(nullptr),
#if  defined(WITH_BIOGEARS_BINDING) // TODO: Remove when biogears works on android
	Actions(TArray<CDM::ActionData*>()),
#endif
	ScenarioFile(""),
	ActionIndex(0),
	bRunningScenario(false),
	ActionDelay(0.0f)
{
}

UVH_BioGearsScenarioDriver::~UVH_BioGearsScenarioDriver()
{} 


// ---------------------------------
// --- Inherited (FTickableGameObject)
// ---------------------------------

void UVH_BioGearsScenarioDriver::Tick(float deltaTime)
{
	if (bRunningScenario)
	{
		if (ActionDelay > 0.0f)
		{
			ActionDelay -= deltaTime;
		}
		else
		{
#if  defined(WITH_BIOGEARS_BINDING) // TODO: Remove when biogears works on android
			ProcessNextAction();
#endif
		}
	}
}

TStatId UVH_BioGearsScenarioDriver::GetStatId() const
{
	return TStatId();
}


// ---------------------------------
// --- API
// ---------------------------------

void UVH_BioGearsScenarioDriver::InitializeDriver(UVH_BioGearsEngine* inEngine, const FString& scenarioFile)
{
	Engine = inEngine;
	ScenarioFile = scenarioFile;
#if  defined(WITH_BIOGEARS_BINDING) // TODO: Remove when biogears works on android
	Actions = PopulateActionList();
#endif
}

void UVH_BioGearsScenarioDriver::StartScenario()
{
#if  defined(WITH_BIOGEARS_BINDING) // TODO: Remove when biogears works on android
	UE_LOG(VH_BioGears, Verbose, TEXT("Begin Automated Scenario. Processing %d Actions..."), Actions.Num());
#endif

	bRunningScenario = true;
	ActionIndex = 0;
	ActionDelay = 0.0f;
}

FString UVH_BioGearsScenarioDriver::GetScenarioFile()
{
	return ScenarioFile;
}

bool UVH_BioGearsScenarioDriver::IsScenarioValid()
{
#if  defined(WITH_BIOGEARS_BINDING) // TODO: Remove when biogears works on android
	return Actions.Num() > 0;
#else
	return false;
#endif
}


// ---------------------------------
// --- Implementation
// ---------------------------------

#if  defined(WITH_BIOGEARS_BINDING) // TODO: Remove when biogears works on android
TArray<CDM::ActionData*> UVH_BioGearsScenarioDriver::PopulateActionList()
{
	if (Engine != nullptr)
	{
		return Engine->GetActionsFromScenarioFile(ScenarioFile);
	}

	return TArray<CDM::ActionData*>();
}

void UVH_BioGearsScenarioDriver::ProcessNextAction()
{
	if (ActionIndex >= 0 && ActionIndex < Actions.Num())
	{
		UE_LOG(VH_BioGears, Log, TEXT("Processing Action %d/%d"), ActionIndex + 1, Actions.Num());

		CDM::ActionData* action = Actions[ActionIndex];
		ProcessAction(action);
		ActionIndex++;
	}
	else
	{
		UE_LOG(VH_BioGears, Log, TEXT("End of automated scenario."));
		bRunningScenario = false;
	}
}

void UVH_BioGearsScenarioDriver::DelayNextActionBy(float seconds)
{
	ActionDelay = seconds;
}

bool UVH_BioGearsScenarioDriver::ProcessAction(CDM::ActionData* action)
{
	if (action == nullptr)
	{
		UE_LOG(VH_BioGears, Log, TEXT("Action: Invalid"));
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

	UE_LOG(VH_BioGears, Log, TEXT("Action: Unknown Type"));
	return false;
}

bool UVH_BioGearsScenarioDriver::ProcessTimeAdvancement(const CDM::AdvanceTimeData* advancementData)
{
	biogears::SEAdvanceTime advancement;

	advancement.Load(*advancementData);

	double seconds = 	advancement.GetTime(biogears::TimeUnit::s);
	DelayNextActionBy(seconds);

	UE_LOG(VH_BioGearsScenario, Log, TEXT("Scenario Action: Advance Time (%f seconds)"), seconds);
	return true;
}

bool UVH_BioGearsScenarioDriver::ProcessPatientSerialization(const CDM::SerializeStateData* serializeData)
{
	// TODO: Process Serialization of Patient State
	UE_LOG(VH_BioGearsScenario, Log, TEXT("Scenario Action: Serialize Patient State"));
	
	return false;
}

bool UVH_BioGearsScenarioDriver::ProcessPatientAssessment(const CDM::PatientAssessmentRequestData* assessmentData)
{
	if (Engine != nullptr)
	{
		biogears::SEPatientAssessmentRequest assessment = biogears::SEPatientAssessmentRequest();
		assessment.Load(*assessmentData);
		Engine->ProcessPatientAssessmentRequest(assessment);

		return true;
	}

	return false;
}

bool UVH_BioGearsScenarioDriver::ProcessPatientAction(const CDM::PatientActionData* actionData)
{
	const CDM::ConsumeNutrientsData* nutrientsData = dynamic_cast<const CDM::ConsumeNutrientsData*>(actionData);
	if (nutrientsData != nullptr)
	{
		return ProcessConsumeNutrients(nutrientsData);
	}

	const CDM::SubstanceInfusionData* substanceData = dynamic_cast<const CDM::SubstanceInfusionData*>(actionData);
	if (substanceData != nullptr)
	{
		return ProcessSubstanceInfusion(substanceData);
	}

	const CDM::SubstanceCompoundInfusionData* compoundData = dynamic_cast<const CDM::SubstanceCompoundInfusionData*>(actionData);
	if (compoundData != nullptr)
	{
		return ProcessSubstanceCompoundInfusion(compoundData);
	}

	const CDM::SubstanceBolusData* bolusData = dynamic_cast<const CDM::SubstanceBolusData*>(actionData);
	if (bolusData != nullptr)
	{
		return ProcessSubstanceBolus(bolusData);
	}

	const CDM::ThermalApplicationData* thermalData = dynamic_cast<const CDM::ThermalApplicationData*>(actionData);
	if (thermalData != nullptr)
	{
		return ProcessThermalApplication(thermalData);
	}

	const CDM::TourniquetData* tourniquetData = dynamic_cast<const CDM::TourniquetData*>(actionData);
	if (tourniquetData != nullptr)
	{
		return ProcessTourniquet(tourniquetData);
	}

	const CDM::NeedleDecompressionData* needleData = dynamic_cast<const CDM::NeedleDecompressionData*>(actionData);
	if (needleData != nullptr)
	{
		return ProcessNeedleDecompression(needleData);
	}

	const CDM::InfectionData* infectionData = dynamic_cast<const CDM::InfectionData*>(actionData);
	if (infectionData != nullptr)
	{
		return ProcessInfection(infectionData);
	}

	const CDM::TensionPneumothoraxData* pneumothoraxData = dynamic_cast<const CDM::TensionPneumothoraxData*>(actionData);
	if (pneumothoraxData != nullptr)
	{
		return ProcessTensionPneumothorax(pneumothoraxData);
	}

	const CDM::HemorrhageData* hemorrhageData = dynamic_cast<const CDM::HemorrhageData*>(actionData);
	if (hemorrhageData != nullptr)
	{
		return ProcessHemorrhage(hemorrhageData);
	}

	const CDM::PainStimulusData* painData = dynamic_cast<const CDM::PainStimulusData*>(actionData);
	if (painData != nullptr)
	{
		return ProcessPainStimulus(painData);
	}

	const CDM::UrinateData* urinateData = dynamic_cast<const CDM::UrinateData*>(actionData);
	if (urinateData != nullptr)
	{
		return ProcessUrinate(urinateData);
	}

	const CDM::AnesthesiaMachineConfigurationData* anesthesiaData = dynamic_cast<const CDM::AnesthesiaMachineConfigurationData*>(actionData);
	if (anesthesiaData != nullptr)
	{
		return ProcessAnesthesiaMachineConfiguration(anesthesiaData);
	}

	return false;
}

bool UVH_BioGearsScenarioDriver::ProcessAnesthesiaMachineAction(const CDM::AnesthesiaMachineActionData* actionData)
{
	// TODO: Anesthesia stuff
	return false;
}

bool UVH_BioGearsScenarioDriver::ProcessEnvironmentAction(const CDM::EnvironmentActionData* actionData)
{
	// TODO: Environment stuff
	return false;
}


bool UVH_BioGearsScenarioDriver::ProcessConsumeNutrients(const CDM::ConsumeNutrientsData* nutrientsData)
{
	if (Engine != nullptr && nutrientsData != nullptr)
	{
		TSharedPtr<biogears::SEConsumeNutrients> nutrients = TSharedPtr<biogears::SEConsumeNutrients>(new biogears::SEConsumeNutrients());
		if (nutrients->Load(*nutrientsData))
		{
			UE_LOG(VH_BioGearsScenario, Log, TEXT("\tConsumed Nutrients"));
			Engine->AddAction(nutrients);

			return true;
		}
	}

	return false;
}

bool UVH_BioGearsScenarioDriver::ProcessSubstanceInfusion(const CDM::SubstanceInfusionData* infusionData)
{
	if (Engine != nullptr && infusionData != nullptr)
	{
		biogears::SESubstance* substance = Engine->GetSubstanceManager()->GetSubstance(infusionData->Substance());

		TSharedPtr<biogears::SESubstanceInfusion> infusion = TSharedPtr<biogears::SESubstanceInfusion>(new biogears::SESubstanceInfusion(*substance));
		if (infusion->Load(*infusionData))
		{
			UE_LOG(VH_BioGearsScenario, Log, TEXT("\tInfused Substance"));
			Engine->AddAction(infusion);

			return true;
		}
	}

	return false;
}

bool UVH_BioGearsScenarioDriver::ProcessSubstanceCompoundInfusion(const CDM::SubstanceCompoundInfusionData* infusionData)
{
	if (Engine != nullptr && infusionData != nullptr)
	{
		biogears::SESubstanceCompound* compound = Engine->GetSubstanceManager()->GetCompound(infusionData->SubstanceCompound());

		TSharedPtr<biogears::SESubstanceCompoundInfusion> infusion = TSharedPtr<biogears::SESubstanceCompoundInfusion>(new biogears::SESubstanceCompoundInfusion(*compound));
		if (infusion->Load(*infusionData))
		{
			UE_LOG(VH_BioGearsScenario, Log, TEXT("\tInfused Compound"));
			Engine->AddAction(infusion);
		
			return true;
		}
	}

	return false;
}

bool UVH_BioGearsScenarioDriver::ProcessSubstanceBolus(const CDM::SubstanceBolusData* bolusData)
{
	if (Engine != nullptr && bolusData != nullptr)
	{
		biogears::SESubstance* substance = Engine->GetSubstanceManager()->GetSubstance(bolusData->Substance());

		TSharedPtr<biogears::SESubstanceBolus> bolus = TSharedPtr<biogears::SESubstanceBolus>(new biogears::SESubstanceBolus(*substance));
		if (bolus->Load(*bolusData))
		{
			UE_LOG(VH_BioGearsScenario, Log, TEXT("\tInjected Substance"));
			Engine->AddAction(bolus);

			return true;
		}
	}

	return false;
}

bool UVH_BioGearsScenarioDriver::ProcessThermalApplication(const CDM::ThermalApplicationData* thermalData)
{
	if (Engine != nullptr && thermalData != nullptr)
	{
		TSharedPtr<biogears::SEThermalApplication> thermal = TSharedPtr<biogears::SEThermalApplication>(new biogears::SEThermalApplication());
		if (thermal->Load(*thermalData))
		{
			UE_LOG(VH_BioGearsScenario, Log, TEXT("\tThermal Applied"));
			Engine->AddAction(thermal);
			
			return true;
		}
	}

	return false;
}

bool UVH_BioGearsScenarioDriver::ProcessTourniquet(const CDM::TourniquetData* tourniquetData)
{
	if (Engine != nullptr && tourniquetData != nullptr)
	{
		TSharedPtr<biogears::SETourniquet> tourniquet = TSharedPtr<biogears::SETourniquet>(new biogears::SETourniquet());
		if (tourniquet->Load(*tourniquetData))
		{
			UE_LOG(VH_BioGearsScenario, Log, TEXT("\tTourniquet Applied"));
			Engine->AddAction(tourniquet);
			
			return true;
		}
	}

	return false;
}

bool UVH_BioGearsScenarioDriver::ProcessNeedleDecompression(const CDM::NeedleDecompressionData* needleData)
{
	if (Engine != nullptr && needleData != nullptr)
	{
		TSharedPtr<biogears::SENeedleDecompression> needle = TSharedPtr<biogears::SENeedleDecompression>(new biogears::SENeedleDecompression());
		if (needle->Load(*needleData))
		{
			UE_LOG(VH_BioGearsScenario, Log, TEXT("\tNeedle Decompression"));
			Engine->AddAction(needle);
		
			return true;
		}
	}

	return false;
}

bool UVH_BioGearsScenarioDriver::ProcessInfection(const CDM::InfectionData* infectionData)
{
	if (Engine != nullptr && infectionData != nullptr)
	{
		TSharedPtr<biogears::SEInfection> infection = TSharedPtr<biogears::SEInfection>(new biogears::SEInfection());
		if (infection->Load(*infectionData))
		{
			UE_LOG(VH_BioGearsScenario, Log, TEXT("\tInfection Applied"));
			Engine->AddAction(infection);
			
			return true;
		}
	}

	return false;
}

bool UVH_BioGearsScenarioDriver::ProcessTensionPneumothorax(const CDM::TensionPneumothoraxData* pneumothoraxData)
{
	if (Engine != nullptr && pneumothoraxData != nullptr)
	{
		TSharedPtr<biogears::SETensionPneumothorax> pneumothorax = TSharedPtr<biogears::SETensionPneumothorax>(new biogears::SETensionPneumothorax());
		if (pneumothorax->Load(*pneumothoraxData))
		{
			UE_LOG(VH_BioGearsScenario, Log, TEXT("\tTension Pneumothorax Applied"));
			Engine->AddAction(pneumothorax);
			return true;
		}
	}

	return false;
}

bool UVH_BioGearsScenarioDriver::ProcessHemorrhage(const CDM::HemorrhageData* hemorrhageData)
{
	if (Engine != nullptr && hemorrhageData != nullptr)
	{
		TSharedPtr<biogears::SEHemorrhage> hemorrhage = TSharedPtr<biogears::SEHemorrhage>(new biogears::SEHemorrhage());
		if (hemorrhage->Load(*hemorrhageData))
		{
			UE_LOG(VH_BioGearsScenario, Log, TEXT("\tHemorrhage Applied"));
			Engine->AddAction(hemorrhage);

			return true;
		}
	}

	return false;
}

bool UVH_BioGearsScenarioDriver::ProcessPainStimulus(const CDM::PainStimulusData* painData)
{
	if (Engine != nullptr && painData != nullptr)
	{
		TSharedPtr<biogears::SEPainStimulus> pain = TSharedPtr<biogears::SEPainStimulus>(new biogears::SEPainStimulus());
		if (pain->Load(*painData))
		{
			UE_LOG(VH_BioGearsScenario, Log, TEXT("\tPain Stimulus Applied"));
			Engine->AddAction(pain);
			
			return true;
		}
	}

	return false;
}

bool UVH_BioGearsScenarioDriver::ProcessUrinate(const CDM::UrinateData* urinateData)
{
	if (Engine != nullptr && urinateData != nullptr)
	{
		TSharedPtr<biogears::SEUrinate> urinate = TSharedPtr<biogears::SEUrinate>(new biogears::SEUrinate());
		if (urinate->Load(*urinateData))
		{
			UE_LOG(VH_BioGearsScenario, Log, TEXT("\tUrinate"));
			Engine->AddAction(urinate);
			
			return true;
		}
	}

	return false;
}

bool UVH_BioGearsScenarioDriver::ProcessAnesthesiaMachineConfiguration(const CDM::AnesthesiaMachineConfigurationData* anesthesiaData)
{
	if (Engine != nullptr && anesthesiaData != nullptr)
	{
		biogears::SESubstanceManager* substanceManager = Engine->GetSubstanceManager();

		TSharedPtr<biogears::SEAnesthesiaMachineConfiguration> anesthesia = TSharedPtr<biogears::SEAnesthesiaMachineConfiguration>(new biogears::SEAnesthesiaMachineConfiguration(*substanceManager));
		if (anesthesia->Load(*anesthesiaData))
		{
			UE_LOG(VH_BioGearsScenario, Log, TEXT("\tNutrient Consumed"));
			Engine->AddAction(anesthesia);
			
			return true;
		}
	}

	return false;
}
#endif
