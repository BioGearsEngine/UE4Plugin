#include "VH_PatientActions.h"

// BioGears
#if  defined(WITH_BIOGEARS_BINDING) // TODO: Remove when biogears works on android
#include "VH_BioGearsPreHeaderBlock.inl"
#include "biogears/cdm/patient/actions/SEHemorrhage.h"
#include "biogears/cdm/properties/SEScalarTypes.h"
#include "biogears/cdm/substance/SESubstanceCompound.h"
#include "VH_BioGearsPostHeaderBlock.inl"
#endif

// VH BioGears Plugin
#include "VH_BioGears.h"


// ---------------------------------
// --- Constructors
// ---------------------------------

UVH_PatientActions::UVH_PatientActions(const FObjectInitializer& objectInitializer) :
	Super(objectInitializer)
{
}

UVH_PatientActions::~UVH_PatientActions()
{
}


// ---------------------------------
// --- API
// ---------------------------------

void UVH_PatientActions::InitializeActions()
{
	ActiveCompoundInfusions = TArray<FBioGearsCompound>();
	ActiveSubstanceInfusions = TArray<FBioGearsSubstance>();
	bAcuteRespiratoryDistress = false;
	AcuteRespiratoryDistressSeverity = 0.0f;
	bAcuteStress = false;
	AcuteStressSeverity = 0.0f;
	bAirwayObstruction = false;
	AirwayObstructionSeverity = 0.0f;
	bApnea = false;
	ApneaSeverity = 0.0f;
	bAsthmaAttack = false;
	AsthmaAttackSeverity = 0.0f;
	BrainInjury = EBrainInjuryType::None;
	BrainInjurySeverity = 0.0f;
	bBronchoconstriction = false;
	bBurnWound = false;
	BurnWoundTotalBodySurfaceArea = 0.0f;
	bBurnWoundInflammation = false;
	bCardiacArrest = false;
	bChestCompression = false;
	ChestCompressionForce = 0.0f;
	ChestCompressionForceScale = 0.0f;
	ChestCompressionForcePeriod = 0.0f;
	bChestOcclusiveDressingLeft = false;
	bChestOcclusiveDressingRight = false;
	bConsciousRespiration = false;
	bConsumeNutrients = false;
	bExercise = false;
	Hemorrhages = TMap<FString, FBioGearsHemorrhage>();
	bInfection = false;
	bIntubation = false;
	bMechanicalVentilation = false;
	NeedleDecompression = EPatientChestSide::None;
	PainStimuli = TMap<FString, FBioGearsPainStimulus>();
	bPericardialEffusion = false;
	bSleepState = false;
	TensionPneumothorax = EPatientChestSide::None;
	Tourniquets = TMap<FString, ETourniquetLevel>();
	bUrinate = false;
}

#if  defined(WITH_BIOGEARS_BINDING) // TODO: Remove when biogears works on android
void UVH_PatientActions::UpdateValues(biogears::SEPatientActionCollection& actions)
{
	FScopeLock lock(&CriticalSection);
    UE_LOG(VH_BioGears, Verbose, TEXT("Biogears UVH_PatientActions::UpdateValues Probing TYPE"));
	bAcuteRespiratoryDistress = actions.HasAcuteRespiratoryDistress();
	UE_LOG(VH_BioGears, Verbose, TEXT("Biogears UVH_PatientActions::UpdateValues Probing TYPE"));
	AcuteRespiratoryDistressSeverity = (bAcuteRespiratoryDistress && actions.GetAcuteRespiratoryDistress()->HasSeverity()) ? actions.GetAcuteRespiratoryDistress()->GetSeverity().GetValue() : 0.0f;
	UE_LOG(VH_BioGears, Verbose, TEXT("Biogears UVH_PatientActions::UpdateValues Probing bAcuteStress"));
	bAcuteStress = actions.HasAcuteStress();
	UE_LOG(VH_BioGears, Verbose, TEXT("Biogears UVH_PatientActions::UpdateValues Probing AcuteStressSeverity"));
	AcuteStressSeverity = (bAcuteStress && actions.GetAcuteStress()->HasSeverity()) ? actions.GetAcuteStress()->GetSeverity().GetValue() : 0.0f;
	UE_LOG(VH_BioGears, Verbose, TEXT("Biogears UVH_PatientActions::UpdateValues Probing bAirwayObstruction"));
	bAirwayObstruction = actions.HasAirwayObstruction();
	UE_LOG(VH_BioGears, Verbose, TEXT("Biogears UVH_PatientActions::UpdateValues Probing AirwayObstructionSeverity"));
	AirwayObstructionSeverity = (bAirwayObstruction && actions.GetAirwayObstruction()->HasSeverity()) ? actions.GetAirwayObstruction()->GetSeverity().GetValue() : 0.0f;
	UE_LOG(VH_BioGears, Verbose, TEXT("Biogears UVH_PatientActions::UpdateValues Probing bApnea"));
	bApnea = actions.HasApnea();
	UE_LOG(VH_BioGears, Verbose, TEXT("Biogears UVH_PatientActions::UpdateValues Probing TYPE"));
	ApneaSeverity = (bApnea && actions.GetApnea()->HasSeverity()) ? actions.GetApnea()->GetSeverity().GetValue() : 0.0f;
	UE_LOG(VH_BioGears, Verbose, TEXT("Biogears UVH_PatientActions::UpdateValues Probing bAsthmaAttack"));
	bAsthmaAttack = actions.HasAsthmaAttack();
	UE_LOG(VH_BioGears, Verbose, TEXT("Biogears UVH_PatientActions::UpdateValues Probing AsthmaAttackSeverity"));
	AsthmaAttackSeverity = (bAsthmaAttack && actions.GetAsthmaAttack()->HasSeverity()) ? actions.GetAsthmaAttack()->GetSeverity().GetValue() : 0.0f;
	UE_LOG(VH_BioGears, Verbose, TEXT("Biogears UVH_PatientActions::UpdateValues Probing bBronchoconstriction"));
	bBronchoconstriction = actions.HasBronchoconstriction();
	UE_LOG(VH_BioGears, Verbose, TEXT("Biogears UVH_PatientActions::UpdateValues Probing bBurnWound"));
	bBurnWound = actions.HasBurnWound();
	UE_LOG(VH_BioGears, Verbose, TEXT("Biogears UVH_PatientActions::UpdateValues Probing BurnWoundTotalBodySurfaceArea"));
	BurnWoundTotalBodySurfaceArea = (bBurnWound && actions.GetBurnWound()->HasTotalBodySurfaceArea()) ? actions.GetBurnWound()->GetTotalBodySurfaceArea().GetValue() : 0.0f;
	UE_LOG(VH_BioGears, Verbose, TEXT("Biogears UVH_PatientActions::UpdateValues Probing bBurnWoundInflammation"));
	bBurnWoundInflammation = bBurnWound && actions.GetBurnWound()->HasInflammation();
	UE_LOG(VH_BioGears, Verbose, TEXT("Biogears UVH_PatientActions::UpdateValues Probing bCardiacArrest"));
	bCardiacArrest = actions.HasCardiacArrest();
	UE_LOG(VH_BioGears, Verbose, TEXT("Biogears UVH_PatientActions::UpdateValues Probing bChestCompression"));
	bChestCompression = actions.HasChestCompression();
	UE_LOG(VH_BioGears, Verbose, TEXT("Biogears UVH_PatientActions::UpdateValues Probing ChestCompressionForce"));
	ChestCompressionForce = (actions.HasChestCompressionForce() && actions.GetChestCompressionForce()->HasForce()) ? actions.GetChestCompressionForce()->GetForce().GetValue() : 0.0f;
	UE_LOG(VH_BioGears, Verbose, TEXT("Biogears UVH_PatientActions::UpdateValues Probing ChestCompressionForceScale"));
	ChestCompressionForceScale = (actions.HasChestCompressionForceScale() && actions.GetChestCompressionForceScale()->HasForceScale()) ? actions.GetChestCompressionForceScale()->GetForceScale().GetValue() : 0.0f;
	UE_LOG(VH_BioGears, Verbose, TEXT("Biogears UVH_PatientActions::UpdateValues Probing ChestCompressionForcePeriod"));
	ChestCompressionForcePeriod = (actions.HasChestCompressionForceScale() && actions.GetChestCompressionForceScale()->HasForcePeriod()) ? actions.GetChestCompressionForceScale()->GetForcePeriod().GetValue() : 0.0f;
	UE_LOG(VH_BioGears, Verbose, TEXT("Biogears UVH_PatientActions::UpdateValues Probing bChestOcclusiveDressingLeft"));
	bChestOcclusiveDressingLeft = actions.HasLeftChestOcclusiveDressing();
	UE_LOG(VH_BioGears, Verbose, TEXT("Biogears UVH_PatientActions::UpdateValues Probing bChestOcclusiveDressingRight"));
	bChestOcclusiveDressingRight = actions.HasRightChestOcclusiveDressing();
	UE_LOG(VH_BioGears, Verbose, TEXT("Biogears UVH_PatientActions::UpdateValues Probing bConsciousRespiration"));
	bConsciousRespiration = actions.HasConsciousRespiration();
	UE_LOG(VH_BioGears, Verbose, TEXT("Biogears UVH_PatientActions::UpdateValues Probing bConsumeNutrients"));
	bConsumeNutrients = actions.HasConsumeNutrients();
	UE_LOG(VH_BioGears, Verbose, TEXT("Biogears UVH_PatientActions::UpdateValues Probing bExercise"));
	bExercise = actions.HasExercise();
	UE_LOG(VH_BioGears, Verbose, TEXT("Biogears UVH_PatientActions::UpdateValues Probing bInfection"));
	bInfection = actions.HasInfection();
	UE_LOG(VH_BioGears, Verbose, TEXT("Biogears UVH_PatientActions::UpdateValues Probing bIntubation"));
	bIntubation = actions.HasIntubation();
	UE_LOG(VH_BioGears, Verbose, TEXT("Biogears UVH_PatientActions::UpdateValues Probing bMechanicalVentilation"));
	bMechanicalVentilation = actions.HasMechanicalVentilation();
	UE_LOG(VH_BioGears, Verbose, TEXT("Biogears UVH_PatientActions::UpdateValues Probing bPericardialEffusion"));
	bPericardialEffusion = actions.HasPericardialEffusion();
	UE_LOG(VH_BioGears, Verbose, TEXT("Biogears UVH_PatientActions::UpdateValues Probing bSleepState"));
	bSleepState = actions.HasSleepState();
	UE_LOG(VH_BioGears, Verbose, TEXT("Biogears UVH_PatientActions::UpdateValues Probing bUrinate"));
	bUrinate = actions.HasUrinate();


	UE_LOG(VH_BioGears, Verbose, TEXT("Biogears UVH_PatientActions::UpdateValues HasLeftOpenTensionPneumothorax"));
	if (actions.HasLeftOpenTensionPneumothorax())
	{
		TensionPneumothorax = actions.HasRightOpenTensionPneumothorax() ? EPatientChestSide::Both : EPatientChestSide::Left;
	}
	else
	{
		TensionPneumothorax = actions.HasRightOpenTensionPneumothorax() ? EPatientChestSide::Right : EPatientChestSide::None;
	}

	UE_LOG(VH_BioGears, Verbose, TEXT("Biogears UVH_PatientActions::UpdateValues HasLeftNeedleDecompression"));
	if (actions.HasLeftNeedleDecompression())
	{
		NeedleDecompression = actions.HasRightNeedleDecompression() ? EPatientChestSide::Both : EPatientChestSide::Left;
	}
	else
	{
		NeedleDecompression = actions.HasRightNeedleDecompression() ? EPatientChestSide::Right : NeedleDecompression = EPatientChestSide::None;
	}

	UE_LOG(VH_BioGears, Verbose, TEXT("Biogears UVH_PatientActions::UpdateValues HasBrainInjury && HasType"));
	if (actions.HasBrainInjury() && actions.GetBrainInjury()->HasType())
	{
		switch (actions.GetBrainInjury()->GetType())
		{
			case CDM::enumBrainInjuryType::Diffuse:
				BrainInjury = EBrainInjuryType::Diffuse;
				break;
			case CDM::enumBrainInjuryType::LeftFocal:
				BrainInjury = EBrainInjuryType::LeftFocal;
				break;
			case CDM::enumBrainInjuryType::RightFocal:
				BrainInjury = EBrainInjuryType::RightFocal;
				break;
			default:
				BrainInjury = EBrainInjuryType::None;
		}
	}

	UE_LOG(VH_BioGears, Verbose, TEXT("Biogears UVH_PatientActions::UpdateValues HasBrainInjury && HasSeverity"));
	BrainInjurySeverity = (actions.HasBrainInjury() && actions.GetBrainInjury()->HasSeverity()) ? actions.GetBrainInjury()->GetSeverity().GetValue() : 0.0f;


\
	UE_LOG(VH_BioGears, Verbose, TEXT("Biogears UVH_PatientActions::UpdateValues For each Hemorrhage"));
	auto hemorrhages = actions.GetHemorrhageWrapper();
	for(auto itr = hemorrhages.begin(); itr != hemorrhages.end(); ++itr) {
		UE_LOG(VH_BioGears, Verbose, TEXT("Biogears UVH_PatientActions::UpdateValues hemorrhage->HasCompartment()"));
		auto hemorrhage = (*itr).second();
		if (hemorrhage != nullptr && hemorrhage->HasCompartment())
		{
			UE_LOG(VH_BioGears, Verbose, TEXT("Biogears UVH_PatientActions::UpdateValues hemorrhage->GetCompartment_cStr()"));
			FString compartment = FString(ANSI_TO_TCHAR(hemorrhage->GetCompartment_cStr()));
			UE_LOG(VH_BioGears, Verbose, TEXT("Biogears UVH_PatientActions::UpdateValues  hemorrhage->HasInitialRate() "));
			float rate = hemorrhage->HasInitialRate() ? hemorrhage->GetInitialRate().GetValue() : 0.0f;
			UE_LOG(VH_BioGears, Verbose, TEXT("Biogears UVH_PatientActions::UpdateValues hemorrhage->HasBleedResistance()"));
			float resistance = hemorrhage->HasBleedResistance() ? hemorrhage->GetBleedResistance().GetValue() : 0.0f;
			UE_LOG(VH_BioGears, Verbose, TEXT("Biogears UVH_PatientActions::UpdateValues Hemorrhages.Add"));
			Hemorrhages.Add(compartment, FBioGearsHemorrhage(rate, resistance));
		}
	}

	UE_LOG(VH_BioGears, Verbose, TEXT("Biogears UVH_PatientActions::UpdateValues For each PainStimulus"));
	auto stimuli = actions.GetPainStimuliWrapper();
	for (auto iter = stimuli.begin(); iter != stimuli.end(); ++iter)
	{
		auto pain = (*iter).second();
		if (pain != nullptr && pain->HasLocation())
		{
			FString location = FString(ANSI_TO_TCHAR(pain->GetLocation().c_str()));
			float severity = pain->HasSeverity() ? pain->GetSeverity().GetValue() : 0.0f;
			float halfLife = pain->HasHalfLife() ? pain->GetHalfLife().GetValue() : 0.0f;

			PainStimuli.Add(location, FBioGearsPainStimulus(severity, halfLife));
		}
	}

	UE_LOG(VH_BioGears, Verbose, TEXT("Biogears UVH_PatientActions::UpdateValues For each tourniquet"));
	auto tourniquets = actions.GetTourniquetsWrapper();
	for (auto iter = tourniquets.begin(); iter != tourniquets.end(); ++iter)
	{
		auto tourniquet = (*iter).second();

		if (tourniquet != nullptr && tourniquet->HasCompartment())
		{ 
			FString compartment = FString(ANSI_TO_TCHAR(tourniquet->GetCompartment_cStr()));
			
			ETourniquetLevel level = ETourniquetLevel::NotApplied;
			if (tourniquet->HasTourniquetLevel())
			{
				switch (tourniquet->GetTourniquetLevel())
				{
					case CDM::enumTourniquetApplicationLevel::Applied:
						level = ETourniquetLevel::Applied;
						break;
					case CDM::enumTourniquetApplicationLevel::Misapplied:
						level = ETourniquetLevel::Misapplied;
						break;
				}
			}
			UE_LOG(VH_BioGears, Verbose, TEXT("Biogears UVH_PatientActions::UpdateValues Tourniquets.Add"));
			Tourniquets.Add(compartment, level);
		}
	}
	UE_LOG(VH_BioGears, Verbose, TEXT("Biogears UVH_PatientActions::UpdateValues UpdateCompoundInfusions"));
	UpdateCompoundInfusions(actions.GetSubstanceCompoundInfusionsWrapper());
	UE_LOG(VH_BioGears, Verbose, TEXT("Biogears UVH_PatientActions::UpdateValues UpdateSubstanceInfusions"));
	UpdateSubstanceInfusions(actions.GetSubstanceInfusionsWrapper());
	UE_LOG(VH_BioGears, Verbose, TEXT("Biogears UVH_PatientActions::UpdateValues FINISHED"));
}
#endif

TArray<FBioGearsCompound> UVH_PatientActions::GetActiveCompoundInfusions()
{
	FScopeLock lock(&CriticalSection);
	return ActiveCompoundInfusions;
}

TArray<FBioGearsSubstance> UVH_PatientActions::GetActiveSubstanceInfusions()
{
	FScopeLock lock(&CriticalSection);
	return ActiveSubstanceInfusions;
}


bool UVH_PatientActions::HasAcuteRespiratoryDistress()
{
	FScopeLock lock(&CriticalSection);
	return bAcuteRespiratoryDistress;
}

float UVH_PatientActions::GetAcuteRespiratoryDistressSeverity()
{
	FScopeLock lock(&CriticalSection);
	return AcuteRespiratoryDistressSeverity;
}


bool UVH_PatientActions::HasAcuteStress()
{
	FScopeLock lock(&CriticalSection);
	return bAcuteStress;
}

float UVH_PatientActions::GetAcuteStressSeverity()
{
	FScopeLock lock(&CriticalSection);
	return AcuteStressSeverity;
}


bool UVH_PatientActions::HasAirwayObstruction()
{
	FScopeLock lock(&CriticalSection);
	return bAirwayObstruction;
}

float UVH_PatientActions::GetAirwayObstructionSeverity()
{
	FScopeLock lock(&CriticalSection);
	return AirwayObstructionSeverity;
}


bool UVH_PatientActions::HasApnea()
{
	FScopeLock lock(&CriticalSection);
	return bApnea;
}

float UVH_PatientActions::GetApneaSeverity()
{
	FScopeLock lock(&CriticalSection);
	return ApneaSeverity;
}


bool UVH_PatientActions::HasAsthmaAttack()
{
	FScopeLock lock(&CriticalSection);
	return bAsthmaAttack;
}

float UVH_PatientActions::GetAsthmaAttackSeverity()
{
	FScopeLock lock(&CriticalSection);
	return AsthmaAttackSeverity;
}


EBrainInjuryType UVH_PatientActions::GetBrainInjury()
{
	FScopeLock lock(&CriticalSection);
	return BrainInjury;
}

float UVH_PatientActions::GetBrainInjurySeverity()
{
	FScopeLock lock(&CriticalSection);
	return BrainInjurySeverity;
}


bool UVH_PatientActions::HasBronchoconstriction()
{
	FScopeLock lock(&CriticalSection);
	return bBronchoconstriction;
}


bool UVH_PatientActions::HasBurnWound()
{
	FScopeLock lock(&CriticalSection);
	return bBurnWound;
}

float UVH_PatientActions::GetBurnWoundTotalBodySurfaceArea()
{
	FScopeLock lock(&CriticalSection);
	return BurnWoundTotalBodySurfaceArea;
}

bool UVH_PatientActions::HasBurnWoundInflammation()
{
	FScopeLock lock(&CriticalSection);
	return bBurnWoundInflammation;
}


bool UVH_PatientActions::HasCardiacArrest()
{
	FScopeLock lock(&CriticalSection);
	return bCardiacArrest;
}


bool UVH_PatientActions::HasChestCompression()
{
	FScopeLock lock(&CriticalSection);
	return bChestCompression;
}

float UVH_PatientActions::GetChestCompressionForce()
{
	FScopeLock lock(&CriticalSection);
	return ChestCompressionForce;
}

float UVH_PatientActions::GetChestCompressionForceScale()
{
	FScopeLock lock(&CriticalSection);
	return ChestCompressionForceScale;
}

float UVH_PatientActions::GetChestCompressionForcePeriod()
{
	FScopeLock lock(&CriticalSection);
	return ChestCompressionForcePeriod;
}

bool UVH_PatientActions::HasChestOcclusiveDressingLeft()
{
	FScopeLock lock(&CriticalSection);
	return bChestOcclusiveDressingLeft;
}

bool UVH_PatientActions::HasChestOcclusiveDressingRight()
{
	FScopeLock lock(&CriticalSection);
	return bChestOcclusiveDressingRight;
}


bool UVH_PatientActions::HasConsciousRespiration()
{
	FScopeLock lock(&CriticalSection);
	return bConsciousRespiration;
}

bool UVH_PatientActions::HasConsumeNutrients()
{
	FScopeLock lock(&CriticalSection);
	return bConsumeNutrients;
}

bool UVH_PatientActions::HasExercise()
{
	FScopeLock lock(&CriticalSection);
	return bExercise;
}

const TMap<FString, FBioGearsHemorrhage> UVH_PatientActions::GetHemorrhages()
{
	FScopeLock lock(&CriticalSection);
	return Hemorrhages;
}

bool UVH_PatientActions::HasInfection()
{
	FScopeLock lock(&CriticalSection);
	return bInfection;
}

bool UVH_PatientActions::HasIntubation()
{
	FScopeLock lock(&CriticalSection);
	return bIntubation;
}

bool UVH_PatientActions::HasMechanicalVentilation()
{
	FScopeLock lock(&CriticalSection);
	return bMechanicalVentilation;
}

EPatientChestSide UVH_PatientActions::HasNeedleDecompression()
{
	FScopeLock lock(&CriticalSection);
	return NeedleDecompression;
}

const TMap<FString, FBioGearsPainStimulus> UVH_PatientActions::GetPainStimuli()
{
	FScopeLock lock(&CriticalSection);
	return PainStimuli;
}

bool UVH_PatientActions::HasPericardialEffusion()
{
	FScopeLock lock(&CriticalSection);
	return bPericardialEffusion;
}

bool UVH_PatientActions::HasSleepState()
{
	FScopeLock lock(&CriticalSection);
	return bSleepState;
}

EPatientChestSide UVH_PatientActions::GetTensionPneumothorax()
{
	FScopeLock lock(&CriticalSection);
	return TensionPneumothorax;
}

const TMap<FString, ETourniquetLevel> UVH_PatientActions::GetTourniquets()
{
	FScopeLock lock(&CriticalSection);
	return Tourniquets;
}

bool UVH_PatientActions::HasToUrinate()
{
	FScopeLock lock(&CriticalSection);
	return bUrinate;
}


// ---------------------------------
// --- Implementation
// ---------------------------------

#if  defined(WITH_BIOGEARS_BINDING) // TODO: Remove when biogears works on android
void UVH_PatientActions::UpdateCompoundInfusions(const biogears::MapWrapper<const biogears::SESubstanceCompound*, biogears::SESubstanceCompoundInfusion*> infusions)
{
	ActiveCompoundInfusions.Empty();

	for (auto infusion = infusions.begin(); infusion != infusions.end(); infusion++)
	{
		FString name = FString(ANSI_TO_TCHAR((*infusion).first()->GetName_cStr()));
		float rate = (*infusion).second()->GetRate().GetValue(biogears::VolumePerTimeUnit::mL_Per_hr);
		float volume = (*infusion).second()->GetBagVolume().GetValue(biogears::VolumeUnit::mL);

		ActiveCompoundInfusions.Add(FBioGearsCompound(name, rate, volume));
	}
}

void UVH_PatientActions::UpdateSubstanceInfusions(const biogears::MapWrapper<const biogears::SESubstance*, biogears::SESubstanceInfusion*> infusions)
{
	ActiveSubstanceInfusions.Empty();

	for (auto infusion = infusions.begin(); infusion != infusions.end(); infusion++)
	{
		FString name = FString(ANSI_TO_TCHAR((*infusion).first()->GetName_cStr()));
		float rate = (*infusion).second()->GetRate().GetValue(biogears::VolumePerTimeUnit::mL_Per_hr);
		float concentration = (*infusion).second()->GetConcentration().GetValue(biogears::MassPerVolumeUnit::g_Per_mL);

		ActiveSubstanceInfusions.Add(FBioGearsSubstance(name, rate, concentration));
	}
}
#endif
