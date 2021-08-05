#include "VH_PatientRenalSystem.h"

// VH BioGears Plugin
#include "VH_BioGears.h"


// ---------------------------------
// --- Constructors
// ---------------------------------

UVH_PatientRenalSystem::UVH_PatientRenalSystem(const FObjectInitializer& objectInitializer) :
	Super(objectInitializer)
{
	KidneyClass = UVH_PatientKidney::StaticClass();
	UrinarySystemClass = UVH_PatientUrinarySystem::StaticClass();
}

UVH_PatientRenalSystem::~UVH_PatientRenalSystem()
{
}


// ---------------------------------
// --- API
// ---------------------------------

void UVH_PatientRenalSystem::InitializeRenal()
{
	FiltrationFraction = 0.0f;
	GlomerularFiltrationRate = 0.0f;
	RenalBloodFlow = 0.0f;
	RenalPlasmaFlow = 0.0f;
	RenalVascularResistance = 0.0f;

	LeftKidney = NewObject<UVH_PatientKidney>(KidneyClass);
	LeftKidney->InitializeKidney();

	RightKidney = NewObject<UVH_PatientKidney>(KidneyClass);
	RightKidney->InitializeKidney();

	UrinarySystem = NewObject<UVH_PatientUrinarySystem>(UrinarySystemClass);
	UrinarySystem->InitializeUrinary();
}

#if  defined(WITH_BIOGEARS_BINDING) // TODO: Remove when biogears works on android
void UVH_PatientRenalSystem::UpdateValues(const biogears::SERenalSystem* renal)
{
	if (renal != nullptr)
	{
		FiltrationFraction = (renal->HasFiltrationFraction()) ? renal->GetFiltrationFraction() : 0.0f;
		GlomerularFiltrationRate = (renal->HasGlomerularFiltrationRate()) ? renal->GetGlomerularFiltrationRate(biogears::VolumePerTimeUnit::mL_Per_min) : 0.0f;
		RenalBloodFlow = (renal->HasRenalBloodFlow()) ? renal->GetRenalBloodFlow(biogears::VolumePerTimeUnit::mL_Per_min) : 0.0f;
		RenalPlasmaFlow = (renal->HasRenalPlasmaFlow()) ? renal->GetRenalPlasmaFlow(biogears::VolumePerTimeUnit::mL_Per_min) : 0.0f;
		RenalVascularResistance = (renal->HasRenalVascularResistance()) ? renal->GetRenalVascularResistance(biogears::FlowResistanceUnit::mmHg_min_Per_mL) : 0.0f;

		if (UrinarySystem != nullptr)
		{
			UrinarySystem->UpdateValues(renal);
		}

		if (LeftKidney != nullptr)
		{
			LeftKidney->UpdateValues(renal, true);
		}

		if (RightKidney != nullptr)
		{
			RightKidney->UpdateValues(renal, false);
		}
	}
}
#endif

float UVH_PatientRenalSystem::GetFiltrationFraction()
{
	FScopeLock lock(&CriticalSection);
	return FiltrationFraction;
}

float UVH_PatientRenalSystem::GetGlomerularFiltrationRate()
{
	FScopeLock lock(&CriticalSection);
	return GlomerularFiltrationRate;
}

float UVH_PatientRenalSystem::GetRenalBloodFlow()
{
	FScopeLock lock(&CriticalSection);
	return RenalBloodFlow;
}

float UVH_PatientRenalSystem::GetRenalPlasmaFlow()
{
	FScopeLock lock(&CriticalSection);
	return RenalPlasmaFlow;
}

float UVH_PatientRenalSystem::GetRenalVascularResistance()
{
	FScopeLock lock(&CriticalSection);
	return RenalVascularResistance;
}
