#include "VH_PatientGastrointestinalSystem.h"

// VH BioGears Plugin
#include "VH_BioGears.h"


// ---------------------------------
// --- Constructors
// ---------------------------------

UVH_PatientGastrointestinalSystem::UVH_PatientGastrointestinalSystem(const FObjectInitializer& objectInitializer) :
	Super(objectInitializer)
{
}

UVH_PatientGastrointestinalSystem::~UVH_PatientGastrointestinalSystem()
{
}


// ---------------------------------
// --- API
// ---------------------------------

void UVH_PatientGastrointestinalSystem::InitializeGastrointestinal()
{
	ChymeAbsorptionRate = 0.0f;
	StomachContents_Calcium = 0.0f;
	StomachContents_Carbohydrates = 0.0f;
	StomachContents_Fat = 0.0f;
	StomachContents_Protein = 0.0f;
	StomachContents_Sodium = 0.0f;
	StomachContents_Water = 0.0f;
}

#if  defined(WITH_BIOGEARS_BINDING) // TODO: Remove when biogears works on android
void UVH_PatientGastrointestinalSystem::UpdateValues(const biogears::SEGastrointestinalSystem* gastrointestinal)
{
	FScopeLock lock(&CriticalSection);

	if (gastrointestinal != nullptr)
	{
		ChymeAbsorptionRate = (gastrointestinal->HasChymeAbsorptionRate()) ? gastrointestinal->GetChymeAbsorptionRate(biogears::VolumePerTimeUnit::mL_Per_min) : 0.0f;

		if (gastrointestinal->HasStomachContents())
		{
			const biogears::SENutrition* nutrition = gastrointestinal->GetStomachContents();

			StomachContents_Calcium = (nutrition->HasCalcium()) ? nutrition->GetCalcium(biogears::MassUnit::g) : 0.0f;
			StomachContents_Carbohydrates = (nutrition->HasCarbohydrate()) ? nutrition->GetCarbohydrate(biogears::MassUnit::g) : 0.0f;
			StomachContents_Fat = (nutrition->HasFat()) ? nutrition->GetFat(biogears::MassUnit::g) : 0.0f;
			StomachContents_Protein = (nutrition->HasProtein()) ? nutrition->GetProtein(biogears::MassUnit::g) : 0.0f;
			StomachContents_Sodium = (nutrition->HasSodium()) ? nutrition->GetSodium(biogears::MassUnit::g) : 0.0f;
			StomachContents_Water = (nutrition->HasWater()) ? nutrition->GetWater(biogears::VolumeUnit::mL) : 0.0f;
		}
	}
}
#endif

float UVH_PatientGastrointestinalSystem::GetChymeAbsorptionRate()
{
	FScopeLock lock(&CriticalSection);
	return ChymeAbsorptionRate;
}

float UVH_PatientGastrointestinalSystem::GetStomachContents_Calcium()
{
	FScopeLock lock(&CriticalSection);
	return StomachContents_Calcium;
}

float UVH_PatientGastrointestinalSystem::GetStomachContents_Carbohydrates()
{
	FScopeLock lock(&CriticalSection);
	return StomachContents_Carbohydrates;
}

float UVH_PatientGastrointestinalSystem::GetStomachContents_Fat()
{
	FScopeLock lock(&CriticalSection);
	return StomachContents_Fat;
}

float UVH_PatientGastrointestinalSystem::GetStomachContents_Protein()
{
	FScopeLock lock(&CriticalSection);
	return StomachContents_Protein;
}

float UVH_PatientGastrointestinalSystem::GetStomachContents_Sodium()
{
	FScopeLock lock(&CriticalSection);
	return StomachContents_Sodium;
}

float UVH_PatientGastrointestinalSystem::GetStomachContents_Water()
{
	FScopeLock lock(&CriticalSection);
	return StomachContents_Water;
}
