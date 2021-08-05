#include "VH_PatientTissue.h"

// VH BioGears Plugin
#include "VH_BioGears.h"


// ---------------------------------
// --- Constructors
// ---------------------------------

UVH_PatientTissue::UVH_PatientTissue(const FObjectInitializer& objectInitializer) :
	Super(objectInitializer)
{
}

UVH_PatientTissue::~UVH_PatientTissue()
{
}


// ---------------------------------
// --- API
// ---------------------------------

void UVH_PatientTissue::InitializeTissue()
{
	// --------------- Cellular --------------- //

	ExtracellularFluidVolume = 0.0f;
	IntracellularFluidPH = 0.0f;
	IntracellularFluidVolume = 0.0f;

	// --------------- Fat --------------- //

	FatGlucagonSetPoint = 0.0f;
	FatInsulinSetPoint = 0.0f;
	StoredFat = 0.0f;

	// --------------- Liver --------------- //
	
	LiverGlucagonSetPoint = 0.0f;
	LiverGlycogen = 0.0f;
	LiverInsulinSetPoint = 0.0f;

	// --------------- Muscle --------------- //

	MuscleGlucagonSetPoint = 0.0f;
	MuscleGlycogen = 0.0f;
	MuscleInsulinSetPoint = 0.0f;

	// --------------- Other --------------- //

	CarbonDioxideProductionRate = 0.0f;
	DehydrationFraction = 0.0f;
	ExtravascularFluidVolume = 0.0f;
	OxygenConsumptionRate = 0.0f;
	RespiratoryExchangeRatio = 0.0f;
	StoredProtein = 0.0f;
	TotalBodyFluidVolume = 0.0f;
}

#if  defined(WITH_BIOGEARS_BINDING) // TODO: Remove when biogears works on android
void UVH_PatientTissue::UpdateValues(const biogears::SETissueSystem* tissue)
{
	FScopeLock lock(&CriticalSection);
	
	if (tissue != nullptr)
	{
		CarbonDioxideProductionRate = (tissue->HasCarbonDioxideProductionRate()) ? tissue->GetCarbonDioxideProductionRate(biogears::VolumePerTimeUnit::mL_Per_min) : 0.0f;
		DehydrationFraction = (tissue->HasDehydrationFraction()) ? tissue->GetDehydrationFraction() : 0.0f;
		ExtracellularFluidVolume = (tissue->HasExtracellularFluidVolume()) ? tissue->GetExtracellularFluidVolume(biogears::VolumeUnit::mL) : 0.0f;
		ExtravascularFluidVolume = (tissue->HasExtravascularFluidVolume()) ? tissue->GetExtravascularFluidVolume(biogears::VolumeUnit::mL) : 0.0f;
		FatGlucagonSetPoint = (tissue->HasFatGlucagonSetPoint()) ? tissue->GetFatGlucagonSetPoint(biogears::MassPerVolumeUnit::g_Per_mL) : 0.0f;
		FatInsulinSetPoint = (tissue->HasFatInsulinSetPoint()) ? tissue->GetFatInsulinSetPoint(biogears::AmountPerVolumeUnit::mol_Per_mL) : 0.0f;
		IntracellularFluidPH = (tissue->HasIntracellularFluidPH()) ? tissue->GetIntracellularFluidPH() : 0.0f;
		IntracellularFluidVolume = (tissue->HasIntracellularFluidVolume()) ? tissue->GetIntracellularFluidVolume(biogears::VolumeUnit::mL) : 0.0f;
		LiverGlucagonSetPoint = (tissue->HasLiverGlucagonSetPoint()) ? tissue->GetLiverGlucagonSetPoint(biogears::MassPerVolumeUnit::g_Per_mL) : 0.0f;
		LiverGlycogen = (tissue->HasLiverGlycogen()) ? tissue->GetLiverGlycogen(biogears::MassUnit::g) : 0.0f;
		LiverInsulinSetPoint = (tissue->HasLiverInsulinSetPoint()) ? tissue->GetLiverInsulinSetPoint(biogears::AmountPerVolumeUnit::mol_Per_mL) : 0.0f;
		MuscleGlucagonSetPoint = (tissue->HasMuscleGlucagonSetPoint()) ? tissue->GetMuscleGlucagonSetPoint(biogears::MassPerVolumeUnit::g_Per_mL) : 0.0f;
		MuscleGlycogen = (tissue->HasMuscleGlycogen()) ? tissue->GetMuscleGlycogen(biogears::MassUnit::g) : 0.0f;
		MuscleInsulinSetPoint = (tissue->HasMuscleInsulinSetPoint()) ? tissue->GetMuscleInsulinSetPoint(biogears::AmountPerVolumeUnit::mol_Per_mL) : 0.0f;
		OxygenConsumptionRate = (tissue->HasOxygenConsumptionRate()) ? tissue->GetOxygenConsumptionRate(biogears::VolumePerTimeUnit::mL_Per_min) : 0.0f;
		RespiratoryExchangeRatio = (tissue->HasRespiratoryExchangeRatio()) ? tissue->GetRespiratoryExchangeRatio() : 0.0f;
		StoredFat = (tissue->HasStoredFat()) ? tissue->GetStoredFat(biogears::MassUnit::g) : 0.0f;
		StoredProtein = (tissue->HasStoredProtein()) ? tissue->GetStoredProtein(biogears::MassUnit::g) : 0.0f;
		TotalBodyFluidVolume = (tissue->HasTotalBodyFluidVolume()) ? tissue->GetTotalBodyFluidVolume(biogears::VolumeUnit::mL) : 0.0f;
	}
}
#endif

// --------------- Cellular --------------- //

float UVH_PatientTissue::GetExtracellularFluidVolume()
{
	FScopeLock lock(&CriticalSection);
	return ExtracellularFluidVolume;
}

float UVH_PatientTissue::GetIntracellularFluidPH()
{
	FScopeLock lock(&CriticalSection);
	return IntracellularFluidPH;
}

float UVH_PatientTissue::GetIntracellularFluidVolume()
{
	FScopeLock lock(&CriticalSection);
	return IntracellularFluidVolume;
}

// --------------- Fat --------------- //

float UVH_PatientTissue::GetFatInsulinSetPoint()
{
	FScopeLock lock(&CriticalSection);
	return FatInsulinSetPoint;
}

float UVH_PatientTissue::GetFatGlucagonSetPoint()
{
	FScopeLock lock(&CriticalSection);
	return FatGlucagonSetPoint;
}

float UVH_PatientTissue::GetStoredFat()
{
	FScopeLock lock(&CriticalSection);
	return StoredFat;
}

// --------------- Liver --------------- //

float UVH_PatientTissue::GetLiverInsulinSetPoint()
{
	FScopeLock lock(&CriticalSection);
	return LiverInsulinSetPoint;
}

float UVH_PatientTissue::GetLiverGlucagonSetPoint()
{
	FScopeLock lock(&CriticalSection);
	return LiverGlucagonSetPoint;
}

float UVH_PatientTissue::GetLiverGlycogen()
{
	FScopeLock lock(&CriticalSection);
	return LiverGlycogen;
}

// --------------- Muscle --------------- //

float UVH_PatientTissue::GetMuscleInsulinSetPoint()
{
	FScopeLock lock(&CriticalSection);
	return MuscleInsulinSetPoint;
}

float UVH_PatientTissue::GetMuscleGlucagonSetPoint()
{
	FScopeLock lock(&CriticalSection);
	return MuscleGlucagonSetPoint;
}

float UVH_PatientTissue::GetMuscleGlycogen()
{
	FScopeLock lock(&CriticalSection);
	return MuscleGlycogen;
}

// --------------- Other --------------- //

float UVH_PatientTissue::GetCarbonDioxideProductionRate()
{
	FScopeLock lock(&CriticalSection);
	return CarbonDioxideProductionRate;
}

float UVH_PatientTissue::GetDehydrationFraction()
{
	FScopeLock lock(&CriticalSection);
	return DehydrationFraction;
}

float UVH_PatientTissue::GetExtravascularFluidVolume()
{
	FScopeLock lock(&CriticalSection);
	return ExtravascularFluidVolume;
}

float UVH_PatientTissue::GetTotalBodyFluidVolume()
{
	FScopeLock lock(&CriticalSection);
	return TotalBodyFluidVolume;
}

float UVH_PatientTissue::GetOxygenConsumptionRate()
{
	FScopeLock lock(&CriticalSection);
	return OxygenConsumptionRate;
};

float UVH_PatientTissue::GetRespiratoryExchangeRatio()
{
	FScopeLock lock(&CriticalSection);
	return RespiratoryExchangeRatio;
}

float UVH_PatientTissue::GetStoredProtein()
{
	FScopeLock lock(&CriticalSection);
	return StoredProtein;
}
