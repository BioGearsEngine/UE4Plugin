#include "VH_PatientUrinarySystem.h"

#if  defined(WITH_BIOGEARS_BINDING) // TODO: Remove when biogears works on android
// BioGears
#include "VH_BioGearsPreHeaderBlock.inl"
#include "biogears/cdm/properties/SEScalar.h"
#include "biogears/cdm/properties/SEScalarTypes.h"
#include "VH_BioGearsPostHeaderBlock.inl"
#endif


// ---------------------------------
// --- Constructors
// ---------------------------------

UVH_PatientUrinarySystem::UVH_PatientUrinarySystem(const FObjectInitializer& objectInitializer) :
	MaxUrineVolume(400.0f)
{

}

UVH_PatientUrinarySystem::~UVH_PatientUrinarySystem()
{

}


// ---------------------------------
// --- API
// ---------------------------------

void UVH_PatientUrinarySystem::InitializeUrinary()
{
	MeanUrineOutput = 0.0f;
	MaxUrineVolume = 0.0f;
	UrinationRate = 0.0f;
	UrineOsmolality = 0.0f;
	UrineOsmolarity = 0.0f;
	UrineProductionRate = 0.0f;
	UrineSpecificGravity = 0.0f;
	UrineUreaNitrogenConcentration = 0.0f;
	UrineVolume = 0.0f;
}

#if  defined(WITH_BIOGEARS_BINDING) // TODO: Remove when biogears works on android
void UVH_PatientUrinarySystem::UpdateValues(const biogears::SERenalSystem* renal)
{
	FScopeLock lock(&CriticalSection);

	if (renal != nullptr)
	{
		MeanUrineOutput = (renal->HasMeanUrineOutput()) ? renal->GetMeanUrineOutput(biogears::VolumePerTimeUnit::mL_Per_min) : 0.0f;
		UrinationRate = (renal->HasUrinationRate()) ? renal->GetUrinationRate(biogears::VolumePerTimeUnit::mL_Per_min) : 0.0f;
		UrineOsmolality = (renal->HasUrineOsmolality()) ? renal->GetUrineOsmolality(biogears::OsmolalityUnit::Osm_Per_kg) : 0.0f;
		UrineOsmolarity = (renal->HasUrineOsmolarity()) ? renal->GetUrineOsmolarity(biogears::OsmolarityUnit::Osm_Per_L) : 0.0f;
		UrineProductionRate = (renal->HasUrineProductionRate()) ? renal->GetUrineProductionRate(biogears::VolumePerTimeUnit::mL_Per_min) : 0.0f;
		UrineSpecificGravity = (renal->HasUrineSpecificGravity()) ? renal->GetUrineSpecificGravity() : 0.0f;
		UrineUreaNitrogenConcentration = (renal->HasUrineUreaNitrogenConcentration()) ? renal->GetUrineUreaNitrogenConcentration(biogears::MassPerVolumeUnit::g_Per_mL) : 0.0f;
		UrineVolume = (renal->HasUrineVolume()) ? renal->GetUrineVolume(biogears::VolumeUnit::mL) : 0.0f;
	}
}
#endif

float UVH_PatientUrinarySystem::GetMaxUrineVolume()
{
	FScopeLock lock(&CriticalSection);
	return MaxUrineVolume;
}

float UVH_PatientUrinarySystem::GetUrinationRate()
{
	FScopeLock lock(&CriticalSection);
	return UrinationRate;
}

float UVH_PatientUrinarySystem::GetUrineOsmolality()
{
	FScopeLock lock(&CriticalSection);
	return UrineOsmolality;
}

float UVH_PatientUrinarySystem::GetUrineOsmolarity()
{
	FScopeLock lock(&CriticalSection);
	return UrineOsmolarity;
}

float UVH_PatientUrinarySystem::GetUrineProductionRate()
{
	FScopeLock lock(&CriticalSection);
	return UrineProductionRate;
}

float UVH_PatientUrinarySystem::GetMeanUrineOutput()
{
	FScopeLock lock(&CriticalSection);
	return MeanUrineOutput;
}

float UVH_PatientUrinarySystem::GetUrineSpecificGravity()
{
	FScopeLock lock(&CriticalSection);
	return UrineSpecificGravity;
}

float UVH_PatientUrinarySystem::GetUrineVolume()
{
	FScopeLock lock(&CriticalSection);
	return UrineVolume;
}

float UVH_PatientUrinarySystem::GetUrineUreaNitrogenConcentration()
{
	FScopeLock lock(&CriticalSection);
	return UrineUreaNitrogenConcentration;
}
