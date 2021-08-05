#include "VH_PatientHepaticSystem.h"

// VH BioGears Plugin
#include "VH_BioGears.h"


// ---------------------------------
// --- Constructors
// ---------------------------------

UVH_PatientHepaticSystem::UVH_PatientHepaticSystem(const FObjectInitializer& objectInitializer) :
	Super(objectInitializer),
	KetoneProductionRate(0.0f),
	GluconeogenesisRate(0.0f)
{
}

UVH_PatientHepaticSystem::~UVH_PatientHepaticSystem()
{
}


// ---------------------------------
// --- API
// ---------------------------------

void UVH_PatientHepaticSystem::InitializeHepatic()
{
	KetoneProductionRate = 0.0f;
	GluconeogenesisRate = 0.0f;
}

#if  defined(WITH_BIOGEARS_BINDING) // TODO: Remove when biogears works on android
void UVH_PatientHepaticSystem::UpdateValues(const biogears::SEHepaticSystem* hepatic)
{
	FScopeLock lock(&CriticalSection);

	if (hepatic != nullptr)
	{
		GluconeogenesisRate = (hepatic->HasHepaticGluconeogenesisRate()) ? hepatic->GetHepaticGluconeogenesisRate(biogears::MassPerTimeUnit::g_Per_s) : 0.0f;
		KetoneProductionRate = (hepatic->HasKetoneProductionRate()) ? hepatic->GetKetoneProductionRate(biogears::AmountPerTimeUnit::mol_Per_s) : 0.0f;
	}
}
#endif

float UVH_PatientHepaticSystem::GetGluconeogenesisRate()
{
	FScopeLock lock(&CriticalSection);
	return GluconeogenesisRate;
}

float UVH_PatientHepaticSystem::GetKetoneProductionRate()
{
	FScopeLock lock(&CriticalSection);
	return KetoneProductionRate;
}

