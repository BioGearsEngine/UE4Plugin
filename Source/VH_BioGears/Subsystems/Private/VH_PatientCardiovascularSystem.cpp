#include "VH_PatientCardiovascularSystem.h"

// BioGears
#if  defined(WITH_BIOGEARS_BINDING) // TODO: Remove when biogears works on android
#include "VH_BioGearsPreHeaderBlock.inl"
#include "biogears/cdm/properties/SEScalarTypes.h"
#include "VH_BioGearsPostHeaderBlock.inl"
#endif

// VH BioGears Plugin
#include "VH_BioGears.h"


// ---------------------------------
// --- Constructors
// ---------------------------------

UVH_PatientCardiovascularSystem::UVH_PatientCardiovascularSystem(const FObjectInitializer& objectInitializer) :
	Super(objectInitializer)
{
}

UVH_PatientCardiovascularSystem::~UVH_PatientCardiovascularSystem()
{
}


// ---------------------------------
// --- API
// ---------------------------------

void UVH_PatientCardiovascularSystem::InitializeCardiovascular()
{
	// --------------- Arterial --------------- //

	ArterialPressure = 0.0f;
	DiastolicArterialPressure = 0.0f;
	SystolicArterialPressure = 0.0f;
	MeanArterialPressure = 0.0f;
	MeanArterialCarbonDioxidePartialPressure = 0.0f;
	MeanArterialCarbonDioxidePartialPressureDelta = 0.0f;

	// --------------- Cardiac --------------- //

	CardiacIndex = 0.0f;
	CardiacOutput = 0.0f;
	HeartEjectionFraction = 0.0f;
	HeartRate = 0.0f;
	HeartStrokeVolume = 0.0f;

	// --------------- Cerebral --------------- //

	CentralVenousPressure = 0.0f;
	CerebralBloodFlow = 0.0f;
	CerebralPerfusionPressure = 0.0f;

	// --------------- Pulmonary --------------- //

	PulmonaryArterialPressure = 0.0f;
	PulmonaryCapillariesWedgePressure = 0.0f;
	PulmonaryDiastolicArterialPressure = 0.0f;
	PulmonaryMeanArterialPressure = 0.0f;
	PulmonaryMeanCapillaryFlow = 0.0f;
	PulmonaryMeanShuntFlow = 0.0f;
	PulmonarySystolicArterialPressure = 0.0f;
	PulmonaryVascularResistance = 0.0f;
	PulmonaryVascularResistanceIndex = 0.0f;

	// --------------- Vascular --------------- //

	BloodVolume = 0.0f;
	IntracranialPressure = 0.0f;
	MeanCentralVenousPressure = 0.0f;
	MeanSkinFlow = 0.0f;
	PulsePressure = 0.0f;
	SystemicVascularResistance = 0.0f;
}

#if  defined(WITH_BIOGEARS_BINDING) // TODO: Remove when biogears works on android
void UVH_PatientCardiovascularSystem::UpdateValues(const biogears::SECardiovascularSystem* cardiovascular)
{
	if (cardiovascular != nullptr)
	{
		ArterialPressure = (cardiovascular->HasArterialPressure()) ? cardiovascular->GetArterialPressure(biogears::PressureUnit::mmHg) : 0.0f;
		BloodVolume = (cardiovascular->HasBloodVolume()) ? cardiovascular->GetBloodVolume(biogears::VolumeUnit::mL) : 0.0f;
		CardiacIndex = (cardiovascular->HasCardiacIndex()) ? cardiovascular->GetCardiacIndex(biogears::VolumePerTimeAreaUnit::mL_Per_min_m2) : 0.0f;
		CardiacOutput = (cardiovascular->HasCardiacOutput()) ? cardiovascular->GetCardiacOutput(biogears::VolumePerTimeUnit::mL_Per_min) : 0.0f;
		CentralVenousPressure = (cardiovascular->HasCentralVenousPressure()) ? cardiovascular->GetCentralVenousPressure(biogears::PressureUnit::mmHg) : 0.0f;
		CerebralBloodFlow = (cardiovascular->HasCerebralBloodFlow()) ? cardiovascular->GetCerebralBloodFlow(biogears::VolumePerTimeUnit::mL_Per_min) : 0.0f;
		CerebralPerfusionPressure = (cardiovascular->HasCerebralPerfusionPressure()) ? cardiovascular->GetCerebralPerfusionPressure(biogears::PressureUnit::mmHg) : 0.0f;
		DiastolicArterialPressure = (cardiovascular->HasDiastolicArterialPressure()) ? cardiovascular->GetDiastolicArterialPressure(biogears::PressureUnit::mmHg) : 0.0f;
		HeartEjectionFraction = (cardiovascular->HasHeartEjectionFraction()) ? cardiovascular->GetHeartEjectionFraction() : 0.0f;
		HeartRate = (cardiovascular->HasHeartRate()) ? cardiovascular->GetHeartRate(biogears::FrequencyUnit::Per_min) : 0.0f;
		HeartStrokeVolume = (cardiovascular->HasHeartStrokeVolume()) ? cardiovascular->GetHeartStrokeVolume(biogears::VolumeUnit::mL) : 0.0f;
		IntracranialPressure = (cardiovascular->HasIntracranialPressure()) ? cardiovascular->GetIntracranialPressure(biogears::PressureUnit::mmHg) : 0.0f;
		MeanArterialPressure = (cardiovascular->HasMeanArterialPressure()) ? cardiovascular->GetMeanArterialPressure(biogears::PressureUnit::mmHg) : 0.0f;
		MeanArterialCarbonDioxidePartialPressure = (cardiovascular->HasMeanArterialCarbonDioxidePartialPressure()) ? cardiovascular->GetMeanArterialCarbonDioxidePartialPressure(biogears::PressureUnit::mmHg) : 0.0f;
		MeanArterialCarbonDioxidePartialPressureDelta = (cardiovascular->HasMeanArterialCarbonDioxidePartialPressureDelta()) ? cardiovascular->GetMeanArterialCarbonDioxidePartialPressureDelta(biogears::PressureUnit::mmHg) : 0.0f;
		MeanCentralVenousPressure = (cardiovascular->HasMeanCentralVenousPressure()) ? cardiovascular->GetMeanCentralVenousPressure(biogears::PressureUnit::mmHg) : 0.0f;
		MeanSkinFlow = (cardiovascular->HasMeanSkinFlow()) ? cardiovascular->GetMeanSkinFlow(biogears::VolumePerTimeUnit::mL_Per_min) : 0.0f;
		PulmonaryArterialPressure = (cardiovascular->HasPulmonaryArterialPressure()) ? cardiovascular->GetPulmonaryArterialPressure(biogears::PressureUnit::mmHg) : 0.0f;
		PulmonaryCapillariesWedgePressure = (cardiovascular->HasPulmonaryCapillariesWedgePressure()) ? cardiovascular->GetPulmonaryCapillariesWedgePressure(biogears::PressureUnit::mmHg) : 0.0f;
		PulmonaryDiastolicArterialPressure = (cardiovascular->HasPulmonaryDiastolicArterialPressure()) ? cardiovascular->GetPulmonaryDiastolicArterialPressure(biogears::PressureUnit::mmHg) : 0.0f;
		PulmonaryMeanArterialPressure = (cardiovascular->HasPulmonaryMeanArterialPressure()) ? cardiovascular->GetPulmonaryMeanArterialPressure(biogears::PressureUnit::mmHg) : 0.0f;
		PulmonaryMeanCapillaryFlow = (cardiovascular->HasPulmonaryMeanCapillaryFlow()) ? cardiovascular->GetPulmonaryMeanCapillaryFlow(biogears::VolumePerTimeUnit::mL_Per_min) : 0.0f;
		PulmonaryMeanShuntFlow = (cardiovascular->HasPulmonaryMeanShuntFlow()) ? cardiovascular->GetPulmonaryMeanShuntFlow(biogears::VolumePerTimeUnit::mL_Per_min) : 0.0f;
		PulmonarySystolicArterialPressure = (cardiovascular->HasPulmonarySystolicArterialPressure()) ? cardiovascular->GetPulmonarySystolicArterialPressure(biogears::PressureUnit::mmHg) : 0.0f;
		PulmonaryVascularResistance = (cardiovascular->HasPulmonaryVascularResistance()) ? cardiovascular->GetPulmonaryVascularResistance(biogears::FlowResistanceUnit::mmHg_s_Per_mL) : 0.0f;
		PulmonaryVascularResistanceIndex = (cardiovascular->HasPulmonaryVascularResistanceIndex()) ? cardiovascular->GetPulmonaryVascularResistanceIndex(biogears::PressureTimePerVolumeAreaUnit::mmHg_s_Per_mL_m2) : 0.0f;
		PulsePressure = (cardiovascular->HasPulsePressure()) ? cardiovascular->GetPulsePressure(biogears::PressureUnit::mmHg) : 0.0f;
		SystemicVascularResistance = (cardiovascular->HasSystemicVascularResistance()) ? cardiovascular->GetSystemicVascularResistance(biogears::FlowResistanceUnit::mmHg_s_Per_mL) : 0.0f;
		SystolicArterialPressure = (cardiovascular->HasSystolicArterialPressure()) ? cardiovascular->GetSystolicArterialPressure(biogears::PressureUnit::mmHg) : 0.0f;
	}
}
#endif

// --------------- Arterial --------------- //

float UVH_PatientCardiovascularSystem::GetArterialPressure()
{
	FScopeLock lock(&CriticalSection);
	return ArterialPressure;
}

float UVH_PatientCardiovascularSystem::GetDiastolicArterialPressure()
{
	FScopeLock lock(&CriticalSection);
	return DiastolicArterialPressure;
}

float UVH_PatientCardiovascularSystem::GetSystolicArterialPressure()
{
	FScopeLock lock(&CriticalSection);
	return SystolicArterialPressure;
}

float UVH_PatientCardiovascularSystem::GetMeanArterialPressure()
{
	FScopeLock lock(&CriticalSection);
	return ArterialPressure;
}

float UVH_PatientCardiovascularSystem::GetMeanArterialCarbonDioxidePartialPressure()
{
	FScopeLock lock(&CriticalSection);
	return MeanArterialCarbonDioxidePartialPressure;
}

float UVH_PatientCardiovascularSystem::GetMeanArterialCarbonDioxidePartialPressureDelta()
{
	FScopeLock lock(&CriticalSection);
	return MeanArterialCarbonDioxidePartialPressureDelta;
}

// --------------- Cardiac --------------- //

float UVH_PatientCardiovascularSystem::GetCardiacIndex()
{
	FScopeLock lock(&CriticalSection);
	return CardiacIndex;
}

float UVH_PatientCardiovascularSystem::GetCardiacOutput()
{
	FScopeLock lock(&CriticalSection);
	return CardiacOutput;
}

float UVH_PatientCardiovascularSystem::GetHeartEjectionFraction()
{
	FScopeLock lock(&CriticalSection);
	return HeartEjectionFraction;
}

float UVH_PatientCardiovascularSystem::GetHeartRate()
{
	FScopeLock lock(&CriticalSection);
	return HeartRate;
}

float UVH_PatientCardiovascularSystem::GetHeartStrokeVolume()
{
	FScopeLock lock(&CriticalSection);
	return HeartStrokeVolume;
}

// --------------- Cerebral --------------- //

float UVH_PatientCardiovascularSystem::GetCerebralBloodFlow()
{
	FScopeLock lock(&CriticalSection);
	return CerebralBloodFlow;
}

float UVH_PatientCardiovascularSystem::GetCerebralPerfusionPressure()
{
	FScopeLock lock(&CriticalSection);
	return CerebralPerfusionPressure;
}

float UVH_PatientCardiovascularSystem::GetIntracranialPressure()
{
	FScopeLock lock(&CriticalSection);
	return IntracranialPressure;
}

// --------------- Pulmonary --------------- //

float UVH_PatientCardiovascularSystem::GetPulmonaryArterialPressure()
{
	FScopeLock lock(&CriticalSection);
	return PulmonaryArterialPressure;
}

float UVH_PatientCardiovascularSystem::GetPulmonaryCapillariesWedgePressure()
{
	FScopeLock lock(&CriticalSection);
	return PulmonaryCapillariesWedgePressure;
}

float UVH_PatientCardiovascularSystem::GetPulmonaryDiastolicArterialPressure()
{
	FScopeLock lock(&CriticalSection);
	return PulmonaryDiastolicArterialPressure;
}

float UVH_PatientCardiovascularSystem::GetPulmonaryMeanArterialPressure()
{
	FScopeLock lock(&CriticalSection);
	return PulmonaryMeanArterialPressure;
}

float UVH_PatientCardiovascularSystem::GetPulmonaryMeanCapillaryFlow()
{
	FScopeLock lock(&CriticalSection);
	return PulmonaryMeanCapillaryFlow;
}

float UVH_PatientCardiovascularSystem::GetPulmonaryMeanShuntFlow()
{
	FScopeLock lock(&CriticalSection);
	return PulmonaryMeanShuntFlow;
}

float UVH_PatientCardiovascularSystem::GetPulmonarySystolicArterialPressure()
{
	FScopeLock lock(&CriticalSection);
	return PulmonarySystolicArterialPressure;
}

float UVH_PatientCardiovascularSystem::GetPulmonaryVascularResistance()
{
	FScopeLock lock(&CriticalSection);
	return PulmonaryVascularResistance;
}

float UVH_PatientCardiovascularSystem::GetPulmonaryVascularResistanceIndex()
{
	FScopeLock lock(&CriticalSection);
	return PulmonaryVascularResistanceIndex;
}

// --------------- Vascular --------------- //

float UVH_PatientCardiovascularSystem::GetBloodVolume()
{
	FScopeLock lock(&CriticalSection);
	return BloodVolume;
}

float UVH_PatientCardiovascularSystem::GetCentralVenousPressure()
{
	FScopeLock lock(&CriticalSection);
	return CentralVenousPressure;
}

float UVH_PatientCardiovascularSystem::GetMeanCentralVenousPressure()
{
	FScopeLock lock(&CriticalSection);
	return MeanCentralVenousPressure;
}

float UVH_PatientCardiovascularSystem::GetMeanSkinFlow()
{
	FScopeLock lock(&CriticalSection);
	return MeanSkinFlow;
}

float UVH_PatientCardiovascularSystem::GetPulsePressure()
{
	FScopeLock lock(&CriticalSection);
	return PulsePressure;
}

float UVH_PatientCardiovascularSystem::GetSystemicVascularResistance()
{
	FScopeLock lock(&CriticalSection);
	return SystemicVascularResistance;
}
