#include "VH_PatientRespiratorySystem.h"

// VH BioGears Plugin
#include "VH_BioGears.h"


// ---------------------------------
// --- Constructors
// ---------------------------------

UVH_PatientRespiratorySystem::UVH_PatientRespiratorySystem(const FObjectInitializer& objectInitializer) :
	Super(objectInitializer)
{
}

UVH_PatientRespiratorySystem::~UVH_PatientRespiratorySystem()
{
}


// ---------------------------------
// --- API
// ---------------------------------

void UVH_PatientRespiratorySystem::InitializeRespiratory()
{
	ExpiratoryFlow = 0.0f;;

	// --------------- Inspiratory --------------- //

	InspiratoryExpiratoryRatio = 0.0f;;
	InspiratoryFlow = 0.0f;;

	// --------------- Pressure --------------- //
	EndTidalCarbonDioxidePressure = 0.0f;;
	RespirationDriverPressure = 0.0f;;
	RespirationMusclePressure = 0.0f;;
	TranspulmonaryPressure = 0.0f;;

	// --------------- Pulmonary --------------- //

	PulmonaryCompliance = 0.0f;;
	PulmonaryResistance = 0.0f;;
	TotalPulmonaryVentilation = 0.0f;;

	// --------------- Ventilation --------------- //
	
	SpecificVentilation = 0.0f;;
	TargetPulmonaryVentilation = 0.0f;;
	TotalAlveolarVentilation = 0.0f;;
	TotalDeadSpaceVentilation = 0.0f;;

	// --------------- Volume --------------- //
	
	TidalVolume = 0.0f;;
	TotalLungVolume = 0.0f;;

	// --------------- Other --------------- //
	
	AlveolarArterialGradient = 0.0f;;
	CarricoIndex = 0.0f;;
	EndTidalCarbonDioxideFraction = 0.0f;;
	RespirationRate = 0.0f;;
}

#if  defined(WITH_BIOGEARS_BINDING) // TODO: Remove when biogears works on android
void UVH_PatientRespiratorySystem::UpdateValues(const biogears::SERespiratorySystem* respiratory)
{
	FScopeLock lock(&CriticalSection);

	if (respiratory != nullptr)
	{
		AlveolarArterialGradient = (respiratory->HasAlveolarArterialGradient()) ? respiratory->GetAlveolarArterialGradient(biogears::PressureUnit::mmHg) : 0.0f;
		CarricoIndex = (respiratory->HasCarricoIndex()) ? respiratory->GetCarricoIndex(biogears::PressureUnit::mmHg) : 0.0f;
		EndTidalCarbonDioxideFraction = (respiratory->HasEndTidalCarbonDioxideFraction()) ? respiratory->GetEndTidalCarbonDioxideFraction() : 0.0f;
		EndTidalCarbonDioxidePressure = (respiratory->HasEndTidalCarbonDioxidePressure()) ? respiratory->GetEndTidalCarbonDioxidePressure(biogears::PressureUnit::mmHg) : 0.0f;
		ExpiratoryFlow = (respiratory->HasExpiratoryFlow()) ? respiratory->GetExpiratoryFlow(biogears::VolumePerTimeUnit::mL_Per_min) : 0.0f;
		InspiratoryExpiratoryRatio = (respiratory->HasInspiratoryExpiratoryRatio()) ? respiratory->GetInspiratoryExpiratoryRatio() : 0.0f;
		InspiratoryFlow = (respiratory->HasInspiratoryFlow()) ? respiratory->GetInspiratoryFlow(biogears::VolumePerTimeUnit::mL_Per_min) : 0.0f;
		PulmonaryCompliance = (respiratory->HasPulmonaryCompliance()) ? respiratory->GetPulmonaryCompliance(biogears::FlowComplianceUnit::mL_Per_mmHg) : 0.0f;
		PulmonaryResistance = (respiratory->HasPulmonaryResistance()) ? respiratory->GetPulmonaryResistance(biogears::FlowResistanceUnit::mmHg_s_Per_mL) : 0.0f;
		RespirationDriverPressure = (respiratory->HasRespirationDriverPressure()) ? respiratory->GetRespirationDriverPressure(biogears::PressureUnit::mmHg) : 0.0f;
		RespirationMusclePressure = (respiratory->HasRespirationMusclePressure()) ? respiratory->GetRespirationMusclePressure(biogears::PressureUnit::mmHg) : 0.0f;
		RespirationRate = (respiratory->HasRespirationRate()) ? respiratory->GetRespirationRate(biogears::FrequencyUnit::Per_min) : 0.0f;
		SpecificVentilation = (respiratory->HasSpecificVentilation()) ? respiratory->GetSpecificVentilation() : 0.0f;
		TargetPulmonaryVentilation = (respiratory->HasTargetPulmonaryVentilation()) ? respiratory->GetTargetPulmonaryVentilation(biogears::VolumePerTimeUnit::mL_Per_min) : 0.0f;
		TidalVolume = (respiratory->HasTidalVolume()) ? respiratory->GetTidalVolume(biogears::VolumeUnit::mL) : 0.0f;
		TotalAlveolarVentilation = (respiratory->HasTotalAlveolarVentilation()) ? respiratory->GetTotalAlveolarVentilation(biogears::VolumePerTimeUnit::mL_Per_min) : 0.0f;
		TotalDeadSpaceVentilation = (respiratory->HasTotalDeadSpaceVentilation()) ? respiratory->GetTotalDeadSpaceVentilation(biogears::VolumePerTimeUnit::mL_Per_min) : 0.0f;
		TotalLungVolume = (respiratory->HasTotalLungVolume()) ? respiratory->GetTotalLungVolume(biogears::VolumeUnit::mL) : 0.0f;
		TotalPulmonaryVentilation = (respiratory->HasTotalPulmonaryVentilation()) ? respiratory->GetTotalPulmonaryVentilation(biogears::VolumePerTimeUnit::mL_Per_min) : 0.0f;
		TranspulmonaryPressure = (respiratory->HasTranspulmonaryPressure()) ? respiratory->GetTranspulmonaryPressure(biogears::PressureUnit::mmHg) : 0.0f;
	}
}
#endif

float UVH_PatientRespiratorySystem::GetAlveolarArterialGradient()
{
	FScopeLock lock(&CriticalSection);
	return AlveolarArterialGradient;
}

float UVH_PatientRespiratorySystem::GetCarricoIndex()
{
	FScopeLock lock(&CriticalSection);
	return CarricoIndex;
}

float UVH_PatientRespiratorySystem::GetEndTidalCarbonDioxideFraction()
{
	FScopeLock lock(&CriticalSection);
	return EndTidalCarbonDioxideFraction;
}

float UVH_PatientRespiratorySystem::GetEndTidalCarbonDioxidePressure()
{
	FScopeLock lock(&CriticalSection);
	return EndTidalCarbonDioxidePressure;
}

float UVH_PatientRespiratorySystem::GetExpiratoryFlow()
{
	FScopeLock lock(&CriticalSection);
	return ExpiratoryFlow;
}

float UVH_PatientRespiratorySystem::GetInspiratoryExpiratoryRatio()
{
	FScopeLock lock(&CriticalSection);
	return InspiratoryExpiratoryRatio;
}

float UVH_PatientRespiratorySystem::GetInspiratoryFlow()
{
	FScopeLock lock(&CriticalSection);
	return InspiratoryFlow;
}

float UVH_PatientRespiratorySystem::GetPulmonaryCompliance()
{
	FScopeLock lock(&CriticalSection);
	return PulmonaryCompliance;
}

float UVH_PatientRespiratorySystem::GetPulmonaryResistance()
{
	FScopeLock lock(&CriticalSection);
	return PulmonaryResistance;
}

float UVH_PatientRespiratorySystem::GetRespirationDriverPressure()
{
	FScopeLock lock(&CriticalSection);
	return RespirationDriverPressure;
}

float UVH_PatientRespiratorySystem::GetRespirationMusclePressure()
{
	FScopeLock lock(&CriticalSection);
	return RespirationMusclePressure;
}

float UVH_PatientRespiratorySystem::GetRespirationRate()
{
	FScopeLock lock(&CriticalSection);
	return RespirationRate;
}

float UVH_PatientRespiratorySystem::GetSpecificVentilation()
{
	FScopeLock lock(&CriticalSection);
	return SpecificVentilation;
}

float UVH_PatientRespiratorySystem::GetTargetPulmonaryVentilation()
{
	FScopeLock lock(&CriticalSection);
	return TargetPulmonaryVentilation;
}

float UVH_PatientRespiratorySystem::GetTidalVolume()
{
	FScopeLock lock(&CriticalSection);
	return TidalVolume;
}

float UVH_PatientRespiratorySystem::GetTotalAlveolarVentilation()
{
	FScopeLock lock(&CriticalSection);
	return TotalAlveolarVentilation;
}

float UVH_PatientRespiratorySystem::GetTotalDeadSpaceVentilation()
{
	FScopeLock lock(&CriticalSection);
	return TotalAlveolarVentilation;
}

float UVH_PatientRespiratorySystem::GetTotalLungVolume()
{
	FScopeLock lock(&CriticalSection);
	return TotalLungVolume;
}

float UVH_PatientRespiratorySystem::GetTotalPulmonaryVentilation()
{
	FScopeLock lock(&CriticalSection);
	return TotalPulmonaryVentilation;
}

float UVH_PatientRespiratorySystem::GetTranspulmonaryPressure()
{
	FScopeLock lock(&CriticalSection);
	return TranspulmonaryPressure;
}
