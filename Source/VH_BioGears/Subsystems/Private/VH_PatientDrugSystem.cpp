#include "VH_PatientDrugSystem.h"

// VH BioGears Plugin
#include "VH_BioGears.h"


// ---------------------------------
// --- Constructors
// ---------------------------------

UVH_PatientDrugSystem::UVH_PatientDrugSystem(const FObjectInitializer& objectInitializer) :
	Super(objectInitializer)
{
}

UVH_PatientDrugSystem::~UVH_PatientDrugSystem()
{
}


// ---------------------------------
// --- API
// ---------------------------------

void UVH_PatientDrugSystem::InitializeDrugs()
{
	BronchodilationLevel = 0.0f;
	HeartRateChange = 0.0f;
	HemorrhageChange = 0.0f;
	MeanBloodPressureChange = 0.0f;
	NeuromuscularBlockLevel = 0.0f;
	PulsePressureChange = 0.0f;
	RespirationRateChange = 0.0f;
	SedationLevel = 0.0f;
	TidalVolumeChange = 0.0f;
	TubularPermeabilityChange = 0.0f;
	CentralNervousResponse = 0.0f;
}

#if  defined(WITH_BIOGEARS_BINDING) // TODO: Remove when biogears works on android
void UVH_PatientDrugSystem::UpdateValues(const biogears::SEDrugSystem* drugs)
{
	FScopeLock lock(&CriticalSection);

	if (drugs != nullptr)
	{
		BronchodilationLevel = (drugs->HasBronchodilationLevel()) ? drugs->GetBronchodilationLevel() : 0.0f;
		CentralNervousResponse = (drugs->HasCentralNervousResponse()) ? drugs->GetCentralNervousResponse() : 0.0f;
		HeartRateChange = (drugs->HasHeartRateChange()) ? drugs->GetHeartRateChange(biogears::FrequencyUnit::Per_min) : 0.0f;
		MeanBloodPressureChange = (drugs->HasMeanBloodPressureChange()) ? drugs->GetMeanBloodPressureChange(biogears::PressureUnit::mmHg) : 0.0f;
		NeuromuscularBlockLevel = (drugs->HasNeuromuscularBlockLevel()) ? drugs->GetNeuromuscularBlockLevel() : 0.0f;
		PulsePressureChange = (drugs->HasPulsePressureChange()) ? drugs->GetPulsePressureChange(biogears::PressureUnit::mmHg) : 0.0f;
		RespirationRateChange = (drugs->HasRespirationRateChange()) ? drugs->GetRespirationRateChange(biogears::FrequencyUnit::Per_min) : 0.0f;
		SedationLevel = (drugs->HasSedationLevel()) ? drugs->GetSedationLevel() : 0.0f;
		TidalVolumeChange = (drugs->HasTidalVolumeChange()) ? drugs->GetTidalVolumeChange(biogears::VolumeUnit::mL) : 0.0f;
		TubularPermeabilityChange = (drugs->HasTubularPermeabilityChange()) ? drugs->GetTubularPermeabilityChange() : 0.0f;
	}
}
#endif

float UVH_PatientDrugSystem::GetBronchodilationLevel()
{
	FScopeLock lock(&CriticalSection);
	return BronchodilationLevel;
}

float UVH_PatientDrugSystem::GetCentralNervousResponse()
{
	FScopeLock lock(&CriticalSection);
	return CentralNervousResponse;
}

float UVH_PatientDrugSystem::GetHeartRateChange()
{
	FScopeLock lock(&CriticalSection);
	return HeartRateChange;
}

float UVH_PatientDrugSystem::GetHemorrhageChange()
{
	FScopeLock lock(&CriticalSection);
	return HemorrhageChange;
}

float UVH_PatientDrugSystem::GetMeanBloodPressureChange()
{
	FScopeLock lock(&CriticalSection);
	return MeanBloodPressureChange;
}

float UVH_PatientDrugSystem::GetNeuromuscularBlockLevel()
{
	FScopeLock lock(&CriticalSection);
	return NeuromuscularBlockLevel;
}

float UVH_PatientDrugSystem::GetPulsePressureChange()
{
	FScopeLock lock(&CriticalSection);
	return PulsePressureChange;
}

float UVH_PatientDrugSystem::GetRespirationRateChange()
{
	FScopeLock lock(&CriticalSection);
	return RespirationRateChange;
}

float UVH_PatientDrugSystem::GetSedationLevel()
{
	FScopeLock lock(&CriticalSection);
	return SedationLevel;
}

float UVH_PatientDrugSystem::GetTidalVolumeChange()
{
	FScopeLock lock(&CriticalSection);
	return TidalVolumeChange;
}

float UVH_PatientDrugSystem::GetTubularPermeabilityChange()
{
	FScopeLock lock(&CriticalSection);
	return TubularPermeabilityChange;
}
