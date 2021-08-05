#include "VH_PatientNervousSystem.h"

// VH BioGears Plugin
#include "VH_BioGears.h"


// ---------------------------------
// --- Constructors
// ---------------------------------

UVH_PatientNervousSystem::UVH_PatientNervousSystem(const FObjectInitializer& objectInitializer) :
	Super(objectInitializer)
{
	PupillaryResponseClass = UVH_PatientPupillaryResponse::StaticClass();
}

UVH_PatientNervousSystem::~UVH_PatientNervousSystem()
{
}


// ---------------------------------
// --- API
// ---------------------------------

void UVH_PatientNervousSystem::InitializeNervous()
{
	AttentionLapses = 0.0f;
	BiologicalDebt = 0.0f;
	ComplianceScale = 0.0f;
	HeartRateScale = 0.0f;
	HeartElastanceScale = 0.0f;
	PainVisualAnalogueScale = 0.0f;
	ReactionTime = 0.0f;
	ResistanceScaleExtrasplanchnic = 0.0f;
	ResistanceScaleMuscle = 0.0f;
	ResistanceScaleMyocardium = 0.0f;
	ResistanceScaleSplanchnic = 0.0f;
	RichmondAgitationSedationScale = 0.0f;
	SleepTime = 0.0f;
	WakeTime = 0.0f;
	SleepState = EPatientSleep::Awake;

	LeftEyePupillaryResponse = NewObject<UVH_PatientPupillaryResponse>(PupillaryResponseClass);
	LeftEyePupillaryResponse->InitializePupillaryResponse();

	RightEyePupillaryResponse = NewObject<UVH_PatientPupillaryResponse>(PupillaryResponseClass);
	RightEyePupillaryResponse->InitializePupillaryResponse();
}

#if  defined(WITH_BIOGEARS_BINDING) // TODO: Remove when biogears works on android
void UVH_PatientNervousSystem::UpdateValues(const biogears::SENervousSystem* nervous)
{
	FScopeLock lock(&CriticalSection);
	
	if (nervous != nullptr)
	{
		AttentionLapses = (nervous->HasAttentionLapses()) ? nervous->GetAttentionLapses() : 0.0f;
		BiologicalDebt = (nervous->HasBiologicalDebt()) ? nervous->GetBiologicalDebt() : 0.0f;
		ComplianceScale = (nervous->HasComplianceScale()) ? nervous->GetComplianceScale() : 0.0f;
		HeartRateScale = (nervous->HasHeartRateScale()) ? nervous->GetHeartRateScale() : 0.0f;
		HeartElastanceScale = (nervous->HasHeartElastanceScale()) ? nervous->GetHeartElastanceScale() : 0.0f;
		PainVisualAnalogueScale = (nervous->HasPainVisualAnalogueScale()) ? nervous->GetPainVisualAnalogueScale() : 0.0f;
		ReactionTime = (nervous->HasReactionTime()) ? nervous->GetReactionTime(biogears::TimeUnit::s) : 0.0f;
		ResistanceScaleExtrasplanchnic = (nervous->HasResistanceScaleExtrasplanchnic()) ? nervous->GetResistanceScaleExtrasplanchnic() : 0.0f;
		ResistanceScaleMuscle = (nervous->HasResistanceScaleMuscle()) ? nervous->GetResistanceScaleMuscle() : 0.0f;
		ResistanceScaleMyocardium = (nervous->HasResistanceScaleMyocardium()) ? nervous->GetResistanceScaleMyocardium() : 0.0f;
		ResistanceScaleSplanchnic = (nervous->HasResistanceScaleSplanchnic()) ? nervous->GetResistanceScaleSplanchnic() : 0.0f;
		RichmondAgitationSedationScale = (nervous->HasRichmondAgitationSedationScale()) ? nervous->GetRichmondAgitationSedationScale() : 0.0f;
		SleepState = (nervous->HasSleepState() && nervous->GetSleepState() == CDM::enumSleepState::Awake) ? EPatientSleep::Awake : EPatientSleep::Asleep;
		SleepTime = nervous->GetSleepTime(biogears::TimeUnit::s);
		WakeTime = nervous->GetWakeTime(biogears::TimeUnit::s);

		if (LeftEyePupillaryResponse != nullptr && nervous->HasRightEyePupillaryResponse())
		{
			LeftEyePupillaryResponse->UpdateValues(nervous->GetLeftEyePupillaryResponse());
		}

		if (RightEyePupillaryResponse != nullptr && nervous->HasRightEyePupillaryResponse())
		{
			RightEyePupillaryResponse->UpdateValues(nervous->GetRightEyePupillaryResponse());
		}
	}
}
#endif

float UVH_PatientNervousSystem::GetAttentionLapses()
{
	FScopeLock lock(&CriticalSection);
	return AttentionLapses;
}

float UVH_PatientNervousSystem::GetBiologicalDebt()
{
	FScopeLock lock(&CriticalSection);
	return BiologicalDebt;
}

float UVH_PatientNervousSystem::GetComplianceScale()
{
	FScopeLock lock(&CriticalSection); 
	return ComplianceScale;
}

float UVH_PatientNervousSystem::GetHeartRateScale()
{
	FScopeLock lock(&CriticalSection);
	return HeartRateScale;
}

float UVH_PatientNervousSystem::GetHeartElastanceScale()
{
	FScopeLock lock(&CriticalSection);
	return HeartElastanceScale;
}

float UVH_PatientNervousSystem::GetPainVisualAnalogueScale()
{
	FScopeLock lock(&CriticalSection);
	return PainVisualAnalogueScale;
}

float UVH_PatientNervousSystem::GetReactionTime()
{
	FScopeLock lock(&CriticalSection);
	return ReactionTime;
}

float UVH_PatientNervousSystem::GetResistanceScaleExtrasplanchnic()
{
	FScopeLock lock(&CriticalSection);
	return ResistanceScaleExtrasplanchnic;
}

float UVH_PatientNervousSystem::GetResistanceScaleMuscle()
{
	FScopeLock lock(&CriticalSection);
	return ResistanceScaleMuscle;
}

float UVH_PatientNervousSystem::GetResistanceScaleMyocardium()
{
	FScopeLock lock(&CriticalSection);
	return ResistanceScaleMyocardium;
}

float UVH_PatientNervousSystem::GetResistanceScaleSplanchnic()
{
	FScopeLock lock(&CriticalSection);
	return ResistanceScaleSplanchnic;
}

float UVH_PatientNervousSystem::GetRichmondAgitationSedationScale()
{
	FScopeLock lock(&CriticalSection);
	return RichmondAgitationSedationScale;
}

EPatientSleep UVH_PatientNervousSystem::GetSleepState()
{
	FScopeLock lock(&CriticalSection);
	return SleepState;
}

float UVH_PatientNervousSystem::GetSleepTime()
{
	FScopeLock lock(&CriticalSection);
	return SleepTime;
}

float UVH_PatientNervousSystem::GetWakeTime()
{
	FScopeLock lock(&CriticalSection);
	return WakeTime;
}
