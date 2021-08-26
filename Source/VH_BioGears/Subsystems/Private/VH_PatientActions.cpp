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
	bAcuteRespiratoryDistress = actions.HasAcuteRespiratoryDistress();
	AcuteRespiratoryDistressSeverity = (bAcuteRespiratoryDistress && actions.GetAcuteRespiratoryDistress()->HasSeverity()) ? actions.GetAcuteRespiratoryDistress()->GetSeverity().GetValue() : 0.0f;
	bAcuteStress = actions.HasAcuteStress();
	AcuteStressSeverity = (bAcuteStress && actions.GetAcuteStress()->HasSeverity()) ? actions.GetAcuteStress()->GetSeverity().GetValue() : 0.0f;
	bAirwayObstruction = actions.HasAirwayObstruction();
	AirwayObstructionSeverity = (bAirwayObstruction && actions.GetAirwayObstruction()->HasSeverity()) ? actions.GetAirwayObstruction()->GetSeverity().GetValue() : 0.0f;
	bApnea = actions.HasApnea();
	ApneaSeverity = (bApnea && actions.GetApnea()->HasSeverity()) ? actions.GetApnea()->GetSeverity().GetValue() : 0.0f;
	bAsthmaAttack = actions.HasAsthmaAttack();
	AsthmaAttackSeverity = (bAsthmaAttack && actions.GetAsthmaAttack()->HasSeverity()) ? actions.GetAsthmaAttack()->GetSeverity().GetValue() : 0.0f;
	bBronchoconstriction = actions.HasBronchoconstriction();
	bBurnWound = actions.HasBurnWound();
	BurnWoundTotalBodySurfaceArea = (bBurnWound && actions.GetBurnWound()->HasTotalBodySurfaceArea()) ? actions.GetBurnWound()->GetTotalBodySurfaceArea().GetValue() : 0.0f;
	bBurnWoundInflammation = bBurnWound && actions.GetBurnWound()->HasInflammation();
	bCardiacArrest = actions.HasCardiacArrest();
	bChestCompression = actions.HasChestCompression();
	ChestCompressionForce = (actions.HasChestCompressionForce() && actions.GetChestCompressionForce()->HasForce()) ? actions.GetChestCompressionForce()->GetForce().GetValue() : 0.0f;
	ChestCompressionForceScale = (actions.HasChestCompressionForceScale() && actions.GetChestCompressionForceScale()->HasForceScale()) ? actions.GetChestCompressionForceScale()->GetForceScale().GetValue() : 0.0f;
	ChestCompressionForcePeriod = (actions.HasChestCompressionForceScale() && actions.GetChestCompressionForceScale()->HasForcePeriod()) ? actions.GetChestCompressionForceScale()->GetForcePeriod().GetValue() : 0.0f;
	bChestOcclusiveDressingLeft = actions.HasLeftChestOcclusiveDressing();
	bChestOcclusiveDressingRight = actions.HasRightChestOcclusiveDressing();
	bConsciousRespiration = actions.HasConsciousRespiration();
	bConsumeNutrients = actions.HasConsumeNutrients();
	bExercise = actions.HasExercise();
	bInfection = actions.HasInfection();
	bIntubation = actions.HasIntubation();
	bMechanicalVentilation = actions.HasMechanicalVentilation();
	bPericardialEffusion = actions.HasPericardialEffusion();
	bSleepState = actions.HasSleepState();
	bUrinate = actions.HasUrinate();


	if (actions.HasLeftOpenTensionPneumothorax())
	{
		TensionPneumothorax = actions.HasRightOpenTensionPneumothorax() ? EPatientChestSide::Both : EPatientChestSide::Left;
	}
	else
	{
		TensionPneumothorax = actions.HasRightOpenTensionPneumothorax() ? EPatientChestSide::Right : EPatientChestSide::None;
	}

	if (actions.HasLeftNeedleDecompression())
	{
		NeedleDecompression = actions.HasRightNeedleDecompression() ? EPatientChestSide::Both : EPatientChestSide::Left;
	}
	else
	{
		NeedleDecompression = actions.HasRightNeedleDecompression() ? EPatientChestSide::Right : NeedleDecompression = EPatientChestSide::None;
	}

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

	BrainInjurySeverity = (actions.HasBrainInjury() && actions.GetBrainInjury()->HasSeverity()) ? actions.GetBrainInjury()->GetSeverity().GetValue() : 0.0f;

   auto hemorrhages = actions.GetHemorrhageWrapper();
	for(auto itr = hemorrhages.begin(); itr != hemorrhages.end(); ++itr) {
		auto hemorrhage = (*itr).second();
		if (hemorrhage != nullptr && hemorrhage->HasCompartment())
		{
			FString compartment = FString(ANSI_TO_TCHAR(hemorrhage->GetCompartment_cStr()));
			float rate = hemorrhage->HasInitialRate() ? hemorrhage->GetInitialRate().GetValue() : 0.0f;
			float resistance = hemorrhage->HasBleedResistance() ? hemorrhage->GetBleedResistance().GetValue() : 0.0f;
			Hemorrhages.Add(compartment, FBioGearsHemorrhage(rate, resistance));
		}
	}

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
			Tourniquets.Add(compartment, level);
		}
	}
	UpdateCompoundInfusions(actions.GetSubstanceCompoundInfusionsWrapper());
	UpdateSubstanceInfusions(actions.GetSubstanceInfusionsWrapper());
	
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
