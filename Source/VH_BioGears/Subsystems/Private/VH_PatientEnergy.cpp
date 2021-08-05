#include "VH_PatientEnergy.h"

// VH BioGears Plugin
#include "VH_BioGears.h"


// ---------------------------------
// --- Constructors
// ---------------------------------

UVH_PatientEnergy::UVH_PatientEnergy(const FObjectInitializer& objectInitializer) :
	Super(objectInitializer)
{
}

UVH_PatientEnergy::~UVH_PatientEnergy()
{
}


// ---------------------------------
// --- API
// ---------------------------------

void UVH_PatientEnergy::InitializeEnergy()
{
	AchievedExerciseLevel = 0.0f;
	FatigueLevel = 0.0f;
	TotalWorkRateLevel = 0.0f;

	// --------------- Other --------------- //

	ExerciseMeanArterialPressureDelta = 0.0f;

	// --------------- Production Rate --------------- //

	CreatinineProductionRate = 0.0f;
	TotalMetabolicRate = 0.0f;
	LactateProductionRate = 0.0f;

	// --------------- Sweat --------------- //

	SweatRate = 0.0f;
	ChlorideLostToSweat = 0.0f;
	PotassiumLostToSweat = 0.0f;
	SodiumLostToSweat = 0.0f;

	// --------------- Temperature --------------- //

	CoreTemperature = 0.0f;
	SkinTemperature = 0.0f;
}

#if  defined(WITH_BIOGEARS_BINDING) // TODO: Remove when biogears works on android
void UVH_PatientEnergy::UpdateValues(const biogears::SEEnergySystem* energy)
{
	FScopeLock lock(&CriticalSection);

	if (energy != nullptr)
	{
		AchievedExerciseLevel = (energy->HasAchievedExerciseLevel()) ? energy->GetAchievedExerciseLevel() : 0.0f;
		ChlorideLostToSweat = (energy->HasChlorideLostToSweat()) ? energy->GetChlorideLostToSweat(biogears::MassUnit::g) : 0.0f;
		CoreTemperature = (energy->HasCoreTemperature()) ? energy->GetCoreTemperature(biogears::TemperatureUnit::C) : 0.0f;
		CreatinineProductionRate = (energy->HasCreatinineProductionRate()) ? energy->GetCreatinineProductionRate(biogears::AmountPerTimeUnit::mol_Per_s) : 0.0f;
		ExerciseMeanArterialPressureDelta = (energy->HasExerciseMeanArterialPressureDelta()) ? energy->GetExerciseMeanArterialPressureDelta(biogears::PressureUnit::mmHg) : 0.0f;
		FatigueLevel = (energy->HasFatigueLevel()) ? energy->GetFatigueLevel() : 0.0f;
		LactateProductionRate = (energy->HasLactateProductionRate()) ? energy->GetLactateProductionRate(biogears::AmountPerTimeUnit::mol_Per_s) : 0.0f;
		PotassiumLostToSweat = (energy->HasPotassiumLostToSweat()) ? energy->GetPotassiumLostToSweat(biogears::MassUnit::g) : 0.0f;
		SkinTemperature = (energy->HasSkinTemperature()) ? energy->GetSkinTemperature(biogears::TemperatureUnit::C) : 0.0f;
		SodiumLostToSweat = (energy->HasSodiumLostToSweat()) ? energy->GetSodiumLostToSweat(biogears::MassUnit::g) : 0.0f;
		SweatRate = (energy->HasSweatRate()) ? energy->GetSweatRate(biogears::MassPerTimeUnit::g_Per_s) : 0.0f;
		TotalMetabolicRate = (energy->HasTotalMetabolicRate()) ? energy->GetTotalMetabolicRate(biogears::PowerUnit::W) : 0.0f;
		TotalWorkRateLevel = (energy->HasTotalWorkRateLevel()) ? energy->GetTotalWorkRateLevel() : 0.0f;
	}
}
#endif

// --------------- Levels --------------- //

float UVH_PatientEnergy::GetAchievedExerciseLevel()
{
	FScopeLock lock(&CriticalSection);
	return AchievedExerciseLevel;
}

float UVH_PatientEnergy::GetFatigueLevel()
{
	FScopeLock lock(&CriticalSection);
	return FatigueLevel;
}

float UVH_PatientEnergy::GetTotalWorkRateLevel()
{
	FScopeLock lock(&CriticalSection);
	return TotalWorkRateLevel;
}

// --------------- Production Rates --------------- //

float UVH_PatientEnergy::GetCreatinineProductionRate()
{
	FScopeLock lock(&CriticalSection);
	return CreatinineProductionRate;
}

float UVH_PatientEnergy::GetLactateProductionRate()
{
	FScopeLock lock(&CriticalSection);
	return LactateProductionRate;
}

float UVH_PatientEnergy::GetTotalMetabolicRate()
{
	FScopeLock lock(&CriticalSection);
	return TotalMetabolicRate;
}


// --------------- Sweat --------------- //

float UVH_PatientEnergy::GetSweatRate()
{
	FScopeLock lock(&CriticalSection);
	return SweatRate;
}

float UVH_PatientEnergy::GetChlorideLostToSweat()
{
	FScopeLock lock(&CriticalSection);
	return ChlorideLostToSweat;
}

float UVH_PatientEnergy::GetPotassiumLostToSweat()
{
	FScopeLock lock(&CriticalSection);
	return PotassiumLostToSweat;
}

float UVH_PatientEnergy::GetSodiumLostToSweat()
{
	FScopeLock lock(&CriticalSection);
	return SodiumLostToSweat;
}

// --------------- Temperature --------------- //

float UVH_PatientEnergy::GetCoreTemperature()
{
	FScopeLock lock(&CriticalSection);
	return CoreTemperature;
}

float UVH_PatientEnergy::GetSkinTemperature()
{
	FScopeLock lock(&CriticalSection);
	return SkinTemperature;
}

// --------------- Other --------------- //

float UVH_PatientEnergy::GetExerciseMeanArterialPressureDelta()
{
	FScopeLock lock(&CriticalSection);
	return ExerciseMeanArterialPressureDelta;
}
