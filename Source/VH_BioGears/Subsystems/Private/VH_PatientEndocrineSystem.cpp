#include "VH_PatientEndocrineSystem.h"

// VH BioGears Plugin
#include "VH_BioGears.h"


// ---------------------------------
// --- Constructors
// ---------------------------------

UVH_PatientEndocrineSystem::UVH_PatientEndocrineSystem(const FObjectInitializer& objectInitializer) :
	Super(objectInitializer)
{
}

UVH_PatientEndocrineSystem::~UVH_PatientEndocrineSystem()
{
}


// ---------------------------------
// --- API
// ---------------------------------

void UVH_PatientEndocrineSystem::InitializeEndocrine()
{
	InsulinSynthesisRate = 0.0f;
	GlucagonSynthesisRate = 0.0f;
}

#if  defined(WITH_BIOGEARS_BINDING) // TODO: Remove when biogears works on android
void UVH_PatientEndocrineSystem::UpdateValues(const biogears::SEEndocrineSystem* endocrine)
{
	FScopeLock lock(&CriticalSection);

	if (endocrine != nullptr)
	{
		GlucagonSynthesisRate = (endocrine->HasGlucagonSynthesisRate()) ? endocrine->GetGlucagonSynthesisRate(biogears::AmountPerTimeUnit::mol_Per_s) : 0.0f;
		InsulinSynthesisRate = (endocrine->HasInsulinSynthesisRate()) ? endocrine->GetInsulinSynthesisRate(biogears::AmountPerTimeUnit::mol_Per_s) : 0.0f;
	}
}
#endif

float UVH_PatientEndocrineSystem::GetInsulinSynthesisRate()
{
	FScopeLock lock(&CriticalSection);
	return InsulinSynthesisRate;
}

float UVH_PatientEndocrineSystem::GetGlucagonSynthesisRate()
{
	FScopeLock lock(&CriticalSection);
	return GlucagonSynthesisRate;
}
