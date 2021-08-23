#include "VH_PatientBody.h"

// VH BioGears Plugin
#include "VH_BioGears.h"


// ---------------------------------
// --- Constructors
// ---------------------------------

UVH_PatientBody::UVH_PatientBody(const FObjectInitializer& objectInitializer) :
	Super(objectInitializer),
	Actions(nullptr),
	BloodChemistry(nullptr),
	CardiovascularSystem(nullptr),
	Conditions(nullptr),
	DrugSystem(nullptr),
	EndocrineSystem(nullptr),
	Energy(nullptr),
	Events(nullptr),
	GastrointestinalSystem(nullptr),
	HepaticSystem(nullptr),
	NervousSystem(nullptr),
	PatientInfo(nullptr),
	RenalSystem(nullptr),
	RespiratorySystem(nullptr),
	Tissue(nullptr)
{
	ActionsClass = UVH_PatientActions::StaticClass();
	BloodChemistryClass = UVH_PatientBloodChemistry::StaticClass();
	CardiovascularSystemClass = UVH_PatientCardiovascularSystem::StaticClass();
	ConditionsClass = UVH_PatientConditions::StaticClass();
	DrugSystemClass = UVH_PatientDrugSystem::StaticClass();
	EndocrineSystemClass = UVH_PatientEndocrineSystem::StaticClass();
	EnergyClass = UVH_PatientEnergy::StaticClass();
	EventsClass = UVH_PatientEvents::StaticClass();
	GastrointestinalSystemClass = UVH_PatientGastrointestinalSystem::StaticClass();
	HepaticSystemClass = UVH_PatientHepaticSystem::StaticClass();
	MetabolicPanelClass = UVH_PatientMetabolicPanel::StaticClass();
	NervousSystemClass = UVH_PatientNervousSystem::StaticClass();
	PatientInfoClass = UVH_PatientInfo::StaticClass();
	RenalSystemClass = UVH_PatientRenalSystem::StaticClass();
	RespiratorySystemClass = UVH_PatientRespiratorySystem::StaticClass();
	TissueClass = UVH_PatientTissue::StaticClass();
}

UVH_PatientBody::~UVH_PatientBody()
{
}


// ---------------------------------
// --- API
// ---------------------------------

void UVH_PatientBody::InitializePatientBody()
{
	Actions = NewObject<UVH_PatientActions>(ActionsClass);
	Actions->InitializeActions();

	BloodChemistry = NewObject<UVH_PatientBloodChemistry>(BloodChemistryClass);
	BloodChemistry->InitializeBlood();

	CardiovascularSystem = NewObject<UVH_PatientCardiovascularSystem>(CardiovascularSystemClass);
	CardiovascularSystem->InitializeCardiovascular();

	Conditions = NewObject<UVH_PatientConditions>(ConditionsClass);
	Conditions->InitializeConditions();

	DrugSystem = NewObject<UVH_PatientDrugSystem>(DrugSystemClass);
	DrugSystem->InitializeDrugs();

	EndocrineSystem = NewObject<UVH_PatientEndocrineSystem>(EndocrineSystemClass);
	EndocrineSystem->InitializeEndocrine();
	
	Energy = NewObject<UVH_PatientEnergy>(EnergyClass);
	Energy->InitializeEnergy();

	Events = NewObject<UVH_PatientEvents>(EventsClass);
	Events->InitializeEvents();
	
	GastrointestinalSystem = NewObject<UVH_PatientGastrointestinalSystem>(GastrointestinalSystemClass);
	GastrointestinalSystem->InitializeGastrointestinal();
	
	HepaticSystem = NewObject<UVH_PatientHepaticSystem>(HepaticSystemClass);
	HepaticSystem->InitializeHepatic();

	PatientInfo = NewObject<UVH_PatientInfo>(PatientInfoClass);
	PatientInfo->InitializeInfo();
	
	MetabolicPanel = NewObject<UVH_PatientMetabolicPanel>(MetabolicPanelClass);
	MetabolicPanel->InitializeMetabolic();
	
	NervousSystem = NewObject<UVH_PatientNervousSystem>(NervousSystemClass);
	NervousSystem->InitializeNervous();
	
	RenalSystem = NewObject<UVH_PatientRenalSystem>(RenalSystemClass);
	RenalSystem->InitializeRenal();
	
	RespiratorySystem = NewObject<UVH_PatientRespiratorySystem>(RespiratorySystemClass);
	RespiratorySystem->InitializeRespiratory();
	
	Tissue = NewObject<UVH_PatientTissue>(TissueClass);
	Tissue->InitializeTissue();
}

#if  defined(WITH_BIOGEARS_BINDING) // TODO: Remove when biogears works on android
void UVH_PatientBody::UpdateValues(biogears::BioGearsEngine* engine)
{
	if (engine != nullptr)
	{
		
		UpdateActions(engine->GetActions().GetPatientActions());
		
		UpdateBloodChemistry(engine->GetBloodChemistrySystem());
		
		UpdateCardiovascularSystem(engine->GetCardiovascularSystem());
		
		UpdateConditions(engine->GetConditions());
		
		UpdateDrugSystem(engine->GetDrugSystem());
		
		UpdateEndocrineSystem(engine->GetEndocrineSystem());
		
		UpdateEnergy(engine->GetEnergySystem());
		
		UpdateEvents(engine->GetPatient().GetEventStates());
		
		UpdateGastrointestinalSystem(engine->GetGastrointestinalSystem());
		
		UpdateHepaticSystem(engine->GetHepaticSystem());
		
		UpdateInfo(engine->GetPatient());
		
		UpdateMetabolicPanel();
		
		UpdateNervousSystem(engine->GetNervousSystem());
		
		UpdateRenalSystem(engine->GetRenalSystem());
		
		UpdateRespiratorySystem(engine->GetRespiratorySystem());
		
		UpdateTissue(engine->GetTissueSystem());
		
	}
}
#endif


// ---------------------------------
// --- Implementation
// ---------------------------------

#if  defined(WITH_BIOGEARS_BINDING) // TODO: Remove when biogears works on android
void UVH_PatientBody::UpdateActions(biogears::SEPatientActionCollection& actions)
{
	if (Actions != nullptr)
	{
		Actions->UpdateValues(actions);
	}
}

void UVH_PatientBody::UpdateBloodChemistry(const biogears::SEBloodChemistrySystem* blood)
{
	if (BloodChemistry != nullptr)
	{
		BloodChemistry->UpdateValues(blood);
	}
}

void UVH_PatientBody::UpdateCardiovascularSystem(const biogears::SECardiovascularSystem* cardiovascular)
{
	if (CardiovascularSystem != nullptr)
	{
		CardiovascularSystem->UpdateValues(cardiovascular);
	}
}

void UVH_PatientBody::UpdateConditions(const biogears::SEConditionManager& conditions)
{
	if (Conditions != nullptr)
	{
		Conditions->UpdateValues(conditions);
	}
}

void UVH_PatientBody::UpdateDrugSystem(const biogears::SEDrugSystem* drugs)
{
	if (DrugSystem != nullptr)
	{
		DrugSystem->UpdateValues(drugs);
	}
}

void UVH_PatientBody::UpdateEndocrineSystem(const biogears::SEEndocrineSystem* endocrine)
{
	if (EndocrineSystem != nullptr)
	{
		EndocrineSystem->UpdateValues(endocrine);
	}
}

void UVH_PatientBody::UpdateEnergy(const biogears::SEEnergySystem* energy)
{
	if (Energy != nullptr)
	{
		Energy->UpdateValues(energy);
	}
}

void UVH_PatientBody::UpdateEvents(const std::map<CDM::enumPatientEvent::value, bool> events)
{
	if (Events != nullptr)
	{
		Events->UpdateValues(events);
	}
}

void UVH_PatientBody::UpdateGastrointestinalSystem(const biogears::SEGastrointestinalSystem* gastrointestinal)
{
	if (GastrointestinalSystem != nullptr)
	{
		GastrointestinalSystem->UpdateValues(gastrointestinal);
	}
}

void UVH_PatientBody::UpdateHepaticSystem(const biogears::SEHepaticSystem* hepatic)
{
	if (HepaticSystem != nullptr)
	{
		HepaticSystem->UpdateValues(hepatic);
	}
}

void UVH_PatientBody::UpdateInfo(const biogears::SEPatient& patient)
{
	if (PatientInfo != nullptr)
	{
		PatientInfo->UpdateValues(patient);
	}
}

void UVH_PatientBody::UpdateMetabolicPanel()
{
	if (MetabolicPanel != nullptr)
	{
		MetabolicPanel->UpdateValues();
	}
}

void UVH_PatientBody::UpdateNervousSystem(const biogears::SENervousSystem* nervous)
{
	if (NervousSystem != nullptr)
	{
		NervousSystem->UpdateValues(nervous);
	}
}

void UVH_PatientBody::UpdateRenalSystem(const biogears::SERenalSystem* renal)
{
	if (RenalSystem != nullptr)
	{
		RenalSystem->UpdateValues(renal);
	}
}

void UVH_PatientBody::UpdateRespiratorySystem(const biogears::SERespiratorySystem* respiratory)
{
	if (RespiratorySystem != nullptr)
	{
		RespiratorySystem->UpdateValues(respiratory);
	}
}

void UVH_PatientBody::UpdateTissue(const biogears::SETissueSystem* tissue)
{
	if (Tissue != nullptr)
	{
		Tissue->UpdateValues(tissue);
	}
}
#endif
