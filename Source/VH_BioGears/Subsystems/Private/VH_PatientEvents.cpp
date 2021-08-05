#include "VH_PatientEvents.h"

// VH BioGears Plugin
#include "VH_BioGears.h"


// ---------------------------------
// --- Constructors
// ---------------------------------

UVH_PatientEvents::UVH_PatientEvents(const FObjectInitializer& objectInitializer) :
	Super(objectInitializer)
{
}

UVH_PatientEvents::~UVH_PatientEvents()
{
}


// ---------------------------------
// --- API
// ---------------------------------

void UVH_PatientEvents::InitializeEvents()
{
	bAcuteLungInjury = false;
	bAcuteRespiratoryDistress = false;
	bAntidiuresis = false;
	bAsystole = false;
	bBradycardia = false;
	bBradypnea = false;
	bBrainOxygenDeficit = false;
	bCardiacArrest = false;
	bCardiogenicShock = false;
	bCriticalBrainOxygenDeficit = false;
	bDehydration = false;
	bDiuresis = false;
	bFasciculation = false;
	bFatigue = false;
	bFunctionalIncontinence = false;
	bHemolyticTransfusionReaction = false;
	bHypercapnia = false;
	bHyperglycemia = false;
	bMildHyperkalemia = false;
	bSevereHyperkalemia = false;
	bMildHypernatremia = false;
	bSevereHypernatremia = false;
	bHyperthermia = false;
	bHypoglycemia = false;
	bHypoglycemicShock = false;
	bHypoglycemicComa = false;
	bHypothermia = false;
	bMildHypokalemia = false;
	bSevereHypokalemia = false;
	bMildHyponatremia = false;
	bSevereHyponatremia = false;
	bHypoxia = false;
	bHypovolemicShock = false;
	bIntracranialHypertension = false;
	bIntracranialHypotension = false;
	bIrreversibleState = false;
	bKetoacidosis = false;
	bLacticAcidosis = false;
	bLiverGlycogenDepleted = false;
	bMaximumPulmonaryVentilationRate = false;
	bMetabolicAcidosis = false;
	bMetabolicAlkalosis = false;
	bMuscleCatabolism = false;
	bMuscleGlycogenDepleted = false;
	bMyocardiumOxygenDeficit = false;
	bNatriuresis = false;
	bNutritionDepleted = false;
	bPulselessRhythm = false;
	bRenalHypoperfusion = false;
	bRespiratoryAcidosis = false;
	bRespiratoryAlkalosis = false;
	bSevereAcuteRespiratoryDistress = false;
	bStartOfCardiacCycle = false;
	bStartOfExhale = false;
	bStartOfInhale = false;
	bSevereSepsis = false;
	bTachycardia = false;
	bTachypnea = false;
}

#if  defined(WITH_BIOGEARS_BINDING) // TODO: Remove when biogears works on android
void UVH_PatientEvents::UpdateValues(const std::map<CDM::enumPatientEvent::value, bool> events)
{
	FScopeLock lock(&CriticalSection);

	bAcuteLungInjury = (events.at(CDM::enumPatientEvent::AcuteLungInjury));
	bAcuteRespiratoryDistress = (events.at(CDM::enumPatientEvent::AcuteRespiratoryDistress));
	bAntidiuresis = (events.at(CDM::enumPatientEvent::Antidiuresis));
	bAsystole = (events.at(CDM::enumPatientEvent::Asystole));
	bBradycardia = (events.at(CDM::enumPatientEvent::Bradycardia));
	bBradypnea = (events.at(CDM::enumPatientEvent::Bradypnea));
	bBrainOxygenDeficit = (events.at(CDM::enumPatientEvent::BrainOxygenDeficit));
	bCardiacArrest = (events.at(CDM::enumPatientEvent::CardiacArrest));
	bCardiogenicShock = (events.at(CDM::enumPatientEvent::CardiogenicShock));
	bCriticalBrainOxygenDeficit = (events.at(CDM::enumPatientEvent::CriticalBrainOxygenDeficit));
	bDehydration = (events.at(CDM::enumPatientEvent::Dehydration));
	bDiuresis = (events.at(CDM::enumPatientEvent::Diuresis));
	bFasciculation = (events.at(CDM::enumPatientEvent::Fasciculation));
	bFatigue = (events.at(CDM::enumPatientEvent::Fatigue));
	bFunctionalIncontinence = (events.at(CDM::enumPatientEvent::FunctionalIncontinence));
	bHemolyticTransfusionReaction = (events.at(CDM::enumPatientEvent::HemolyticTransfusionReaction));
	bHypercapnia = (events.at(CDM::enumPatientEvent::Hypercapnia));
	bHyperglycemia = (events.at(CDM::enumPatientEvent::Hyperglycemia));
	bMildHyperkalemia = (events.at(CDM::enumPatientEvent::MildHyperkalemia));
	bSevereHyperkalemia = (events.at(CDM::enumPatientEvent::SevereHyperkalemia));
	bMildHypernatremia = (events.at(CDM::enumPatientEvent::MildHypernatremia));
	bSevereHypernatremia = (events.at(CDM::enumPatientEvent::SevereHypernatremia));
	bHyperthermia = (events.at(CDM::enumPatientEvent::Hyperthermia));
	bHypoglycemia = (events.at(CDM::enumPatientEvent::Hypoglycemia));
	bHypoglycemicShock = (events.at(CDM::enumPatientEvent::HypoglycemicShock));
	bHypoglycemicComa = (events.at(CDM::enumPatientEvent::HypoglycemicComa));
	bHypothermia = (events.at(CDM::enumPatientEvent::Hypothermia));
	bMildHypokalemia = (events.at(CDM::enumPatientEvent::MildHypokalemia));
	bSevereHypokalemia = (events.at(CDM::enumPatientEvent::SevereHypokalemia));
	bMildHyponatremia = (events.at(CDM::enumPatientEvent::MildHyponatremia));
	bSevereHyponatremia = (events.at(CDM::enumPatientEvent::SevereHyponatremia));
	bHypoxia = (events.at(CDM::enumPatientEvent::Hypoxia));
	bHypovolemicShock = (events.at(CDM::enumPatientEvent::HypovolemicShock));
	bIntracranialHypertension = (events.at(CDM::enumPatientEvent::IntracranialHypertension));
	bIntracranialHypotension = (events.at(CDM::enumPatientEvent::IntracranialHypotension));
	bIrreversibleState = (events.at(CDM::enumPatientEvent::IrreversibleState));
	bKetoacidosis = (events.at(CDM::enumPatientEvent::Ketoacidosis));
	bLacticAcidosis = (events.at(CDM::enumPatientEvent::LacticAcidosis));
	bLiverGlycogenDepleted = (events.at(CDM::enumPatientEvent::LiverGlycogenDepleted));
	bMaximumPulmonaryVentilationRate = (events.at(CDM::enumPatientEvent::MaximumPulmonaryVentilationRate));
	bMetabolicAcidosis = (events.at(CDM::enumPatientEvent::MetabolicAcidosis));
	bMetabolicAlkalosis = (events.at(CDM::enumPatientEvent::MetabolicAlkalosis));
	bMuscleCatabolism = (events.at(CDM::enumPatientEvent::MuscleCatabolism));
	bMuscleGlycogenDepleted = (events.at(CDM::enumPatientEvent::MuscleGlycogenDepleted));
	bMyocardiumOxygenDeficit = (events.at(CDM::enumPatientEvent::MyocardiumOxygenDeficit));
	bNatriuresis = (events.at(CDM::enumPatientEvent::Natriuresis));
	bNutritionDepleted = (events.at(CDM::enumPatientEvent::NutritionDepleted));
	bPulselessRhythm = (events.at(CDM::enumPatientEvent::PulselessRhythm));
	bRenalHypoperfusion = (events.at(CDM::enumPatientEvent::RenalHypoperfusion));
	bRespiratoryAcidosis = (events.at(CDM::enumPatientEvent::RespiratoryAcidosis));
	bRespiratoryAlkalosis = (events.at(CDM::enumPatientEvent::RespiratoryAlkalosis));
	bSevereAcuteRespiratoryDistress = (events.at(CDM::enumPatientEvent::SevereAcuteRespiratoryDistress));
	bStartOfCardiacCycle = (events.at(CDM::enumPatientEvent::StartOfCardiacCycle));
	bStartOfExhale = (events.at(CDM::enumPatientEvent::StartOfExhale));
	bStartOfInhale = (events.at(CDM::enumPatientEvent::StartOfInhale));
	bSevereSepsis = (events.at(CDM::enumPatientEvent::SevereSepsis));
	bTachycardia = (events.at(CDM::enumPatientEvent::Tachycardia));
	bTachypnea = (events.at(CDM::enumPatientEvent::Tachycardia));
}
#endif

bool UVH_PatientEvents::HasAcuteLungInjury()
{
	FScopeLock lock(&CriticalSection);
	return bAcuteLungInjury;
}

bool UVH_PatientEvents::HasAcuteRespiratoryDistress()
{
	FScopeLock lock(&CriticalSection);
	return bAcuteRespiratoryDistress;
}

bool UVH_PatientEvents::HasAntidiuresis()
{
	FScopeLock lock(&CriticalSection);
	return bAntidiuresis;
}

bool UVH_PatientEvents::HasAsystole()
{
	FScopeLock lock(&CriticalSection);
	return bAsystole;
}

bool UVH_PatientEvents::HasBradycardia()
{
	FScopeLock lock(&CriticalSection);
	return bBradycardia;
}

bool UVH_PatientEvents::HasBradypnea()
{
	FScopeLock lock(&CriticalSection);
	return bBradypnea;
}

bool UVH_PatientEvents::HasBrainOxygenDeficit()
{
	FScopeLock lock(&CriticalSection);
	return bBrainOxygenDeficit;
}

bool UVH_PatientEvents::HasCardiacArrest()
{
	FScopeLock lock(&CriticalSection);
	return bCardiacArrest;
}

bool UVH_PatientEvents::HasCardiogenicShock()
{
	FScopeLock lock(&CriticalSection);
	return bCardiogenicShock;
}

bool UVH_PatientEvents::HasCriticalBrainOxygenDeficit()
{
	FScopeLock lock(&CriticalSection);
	return bCriticalBrainOxygenDeficit;
}

bool UVH_PatientEvents::HasDehydration()
{
	FScopeLock lock(&CriticalSection);
	return bDehydration;
}

bool UVH_PatientEvents::HasDiuresis()
{
	FScopeLock lock(&CriticalSection);
	return bDiuresis;
}

bool UVH_PatientEvents::HasFasciculation()
{
	FScopeLock lock(&CriticalSection);
	return bFasciculation;
}

bool UVH_PatientEvents::HasFatigue()
{
	FScopeLock lock(&CriticalSection);
	return bFatigue;
}

bool UVH_PatientEvents::HasFunctionalIncontinence()
{
	FScopeLock lock(&CriticalSection);
	return bFunctionalIncontinence;
}

bool UVH_PatientEvents::HasHemolyticTransfusionReaction()
{
	FScopeLock lock(&CriticalSection);
	return bHemolyticTransfusionReaction;
}

bool UVH_PatientEvents::HasHypercapnia()
{
	FScopeLock lock(&CriticalSection);
	return bHypercapnia;
}

bool UVH_PatientEvents::HasHyperglycemia()
{
	FScopeLock lock(&CriticalSection);
	return bHyperglycemia;
}

bool UVH_PatientEvents::HasMildHyperkalemia()
{
	FScopeLock lock(&CriticalSection);
	return bMildHyperkalemia;
}

bool UVH_PatientEvents::HasSevereHyperkalemia()
{
	FScopeLock lock(&CriticalSection);
	return bSevereHyperkalemia;
}

bool UVH_PatientEvents::HasMildHypernatremia()
{
	FScopeLock lock(&CriticalSection);
	return bMildHypernatremia;
}

bool UVH_PatientEvents::HasSevereHypernatremia()
{
	FScopeLock lock(&CriticalSection);
	return bSevereHypernatremia;
}

bool UVH_PatientEvents::HasHyperthermia()
{
	FScopeLock lock(&CriticalSection);
	return bHyperthermia;
}

bool UVH_PatientEvents::HasHypoglycemia()
{
	FScopeLock lock(&CriticalSection);
	return bHypoglycemia;
}

bool UVH_PatientEvents::HasHypoglycemicShock()
{
	FScopeLock lock(&CriticalSection);
	return bHypoglycemicShock;
}

bool UVH_PatientEvents::HasHypoglycemicComa()
{
	FScopeLock lock(&CriticalSection);
	return bHypoglycemicComa;
}

bool UVH_PatientEvents::HasHypothermia()
{
	FScopeLock lock(&CriticalSection);
	return bHypothermia;
}

bool UVH_PatientEvents::HasMildHypokalemia()
{
	FScopeLock lock(&CriticalSection);
	return bMildHypokalemia;
}

bool UVH_PatientEvents::HasSevereHypokalemia()
{
	FScopeLock lock(&CriticalSection);
	return bSevereHypokalemia;
}

bool UVH_PatientEvents::HasMildHyponatremia()
{
	FScopeLock lock(&CriticalSection);
	return bMildHyponatremia;
}

bool UVH_PatientEvents::HasSevereHyponatremia()
{
	FScopeLock lock(&CriticalSection);
	return bSevereHyponatremia;
}

bool UVH_PatientEvents::HasHypoxia()
{
	FScopeLock lock(&CriticalSection);
	return bHypoxia;
}

bool UVH_PatientEvents::HasHypovolemicShock()
{
	FScopeLock lock(&CriticalSection);
	return bHypovolemicShock;
}

bool UVH_PatientEvents::HasIntracranialHypertension()
{
	FScopeLock lock(&CriticalSection);
	return bIntracranialHypertension;
}

bool UVH_PatientEvents::HasIntracranialHypotension()
{
	FScopeLock lock(&CriticalSection);
	return bIntracranialHypotension;
}

bool UVH_PatientEvents::HasIrreversibleState()
{
	FScopeLock lock(&CriticalSection);
	return bIrreversibleState;
}

bool UVH_PatientEvents::HasKetoacidosis()
{
	FScopeLock lock(&CriticalSection);
	return bKetoacidosis;
}

bool UVH_PatientEvents::HasLacticAcidosis()
{
	FScopeLock lock(&CriticalSection);
	return bLacticAcidosis;
}

bool UVH_PatientEvents::HasLiverGlycogenDepleted()
{
	FScopeLock lock(&CriticalSection);
	return bLiverGlycogenDepleted;
}

bool UVH_PatientEvents::HasMaximumPulmonaryVentilationRate()
{
	FScopeLock lock(&CriticalSection);
	return bMaximumPulmonaryVentilationRate;
}

bool UVH_PatientEvents::HasMetabolicAcidosis()
{
	FScopeLock lock(&CriticalSection);
	return bMetabolicAcidosis;
}

bool UVH_PatientEvents::HasMetabolicAlkalosis()
{
	FScopeLock lock(&CriticalSection);
	return bMetabolicAlkalosis;
}

bool UVH_PatientEvents::HasMuscleCatabolism()
{
	FScopeLock lock(&CriticalSection);
	return bMuscleCatabolism;
}

bool UVH_PatientEvents::HasMuscleGlycogenDepleted()
{
	FScopeLock lock(&CriticalSection);
	return bMuscleGlycogenDepleted;
}

bool UVH_PatientEvents::HasMyocardiumOxygenDeficit()
{
	FScopeLock lock(&CriticalSection);
	return bMyocardiumOxygenDeficit;
}

bool UVH_PatientEvents::HasNatriuresis()
{
	FScopeLock lock(&CriticalSection);
	return bNatriuresis;
}

bool UVH_PatientEvents::HasNutritionDepleted()
{
	FScopeLock lock(&CriticalSection);
	return bNutritionDepleted;
}

bool UVH_PatientEvents::HasPulselessRhythm()
{
	FScopeLock lock(&CriticalSection);
	return bPulselessRhythm;
}

bool UVH_PatientEvents::HasRenalHypoperfusion()
{
	FScopeLock lock(&CriticalSection);
	return bRenalHypoperfusion;
}

bool UVH_PatientEvents::HasRespiratoryAcidosis()
{
	FScopeLock lock(&CriticalSection);
	return bRespiratoryAcidosis;
}

bool UVH_PatientEvents::HasRespiratoryAlkalosis()
{
	FScopeLock lock(&CriticalSection);
	return bRespiratoryAlkalosis;
}

bool UVH_PatientEvents::HasSevereAcuteRespiratoryDistress()
{
	FScopeLock lock(&CriticalSection);
	return bSevereAcuteRespiratoryDistress;
}

bool UVH_PatientEvents::HasStartOfCardiacCycle()
{
	FScopeLock lock(&CriticalSection);
	return bStartOfCardiacCycle;
}

bool UVH_PatientEvents::HasStartOfExhale()
{
	FScopeLock lock(&CriticalSection);
	return bStartOfExhale;
}

bool UVH_PatientEvents::HasStartOfInhale()
{
	FScopeLock lock(&CriticalSection);
	return bStartOfInhale;
}

bool UVH_PatientEvents::HasSevereSepsis()
{
	FScopeLock lock(&CriticalSection);
	return bSevereSepsis;
}

bool UVH_PatientEvents::HasTachycardia(){
	FScopeLock lock(&CriticalSection);
	return bTachycardia;
}

bool UVH_PatientEvents::HasTachypnea()
{
	FScopeLock lock(&CriticalSection);
	return bTachypnea;
}
