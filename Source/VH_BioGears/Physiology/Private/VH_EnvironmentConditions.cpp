#include "VH_EnvironmentConditions.h"

#if  defined(WITH_BIOGEARS_BINDING) // TODO: Remove when biogears works on android
// BioGears
#include "VH_BioGearsPreHeaderBlock.inl"
#include "biogears/cdm/properties/SEScalarTypes.h"
#include "biogears/cdm/system/environment/SEAppliedTemperature.h"
#include "VH_BioGearsPostHeaderBlock.inl"
#endif

// Plugin
#include "VH_BioGears.h"


// ---------------------------------
// --- Constructors
// ---------------------------------

UVH_EnvironmentConditions::UVH_EnvironmentConditions(const FObjectInitializer& objectInitializer) :
	Super(objectInitializer)
{
}

UVH_EnvironmentConditions::~UVH_EnvironmentConditions()
{
}


// ---------------------------------
// --- API
// ---------------------------------

void UVH_EnvironmentConditions::InitializeEnvironment()
{
	Name = FString("");
	AirDensity = 0.0f;
	AirVelocity = 0.0f;
	AmbientTemperature = 0.0f;
	AppliedTemperature = 0.0f;
	AtmosphericPressure = 0.0f;
	ClothingResistance = 0.0f;
	Emissivity = 0.0f;
	MeanRadiantTemperature = 0.0f;
	RelativeHumidity = 0.0f;
	RespirationAmbientTemperature = 0.0f;
}

#if  defined(WITH_BIOGEARS_BINDING) // TODO: Remove when biogears works on android
void UVH_EnvironmentConditions::UpdateValues(const biogears::SEEnvironment* environment, const biogears::SEEnvironmentActionCollection& actions)
{
	FScopeLock lock(&CriticalSection);

	if (environment != nullptr && environment->HasConditions())
	{
		const biogears::SEEnvironmentalConditions* conditions = environment->GetConditions();

		AirDensity = (conditions->HasAirDensity()) ? conditions->GetAirDensity(biogears::MassPerVolumeUnit::g_Per_mL) : 0.0f;
		AirVelocity = (conditions->HasAirVelocity()) ? conditions->GetAirVelocity(biogears::LengthPerTimeUnit::m_Per_s) : 0.0f;
		AmbientTemperature = (conditions->HasAmbientTemperature()) ? conditions->GetAmbientTemperature(biogears::TemperatureUnit::C) : 0.0f;
		AtmosphericPressure = (conditions->HasAtmosphericPressure()) ? conditions->GetAtmosphericPressure(biogears::PressureUnit::mmHg) : 0.0f;
		ClothingResistance = (conditions->HasClothingResistance()) ? conditions->GetClothingResistance(biogears::HeatResistanceAreaUnit::rsi) : 0.0f;
		Emissivity = (conditions->HasEmissivity()) ? conditions->GetEmissivity() : 0.0f;
		MeanRadiantTemperature = (conditions->HasMeanRadiantTemperature()) ? conditions->GetMeanRadiantTemperature(biogears::TemperatureUnit::C) : 0.0f;
		RelativeHumidity = (conditions->HasRelativeHumidity()) ? conditions->GetRelativeHumidity() : 0.0f;
		RespirationAmbientTemperature = (conditions->HasRespirationAmbientTemperature()) ? conditions->GetRespirationAmbientTemperature(biogears::TemperatureUnit::C) : 0.0f;
	}

	if (actions.HasThermalApplication())
	{
		biogears::SEThermalApplication* thermal = actions.GetThermalApplication();
		AppliedTemperature = (thermal->HasAppliedTemperature()) ? thermal->GetAppliedTemperature().GetTemperature(biogears::TemperatureUnit::C) : 0.0f;
	}
}
#endif

FString UVH_EnvironmentConditions::GetName()
{
	FScopeLock lock(&CriticalSection);
	return Name;
}

float UVH_EnvironmentConditions::GetAirDensity()
{
	FScopeLock lock(&CriticalSection);
	return AirDensity;
}

float UVH_EnvironmentConditions::GetAirVelocity()
{
	FScopeLock lock(&CriticalSection);
	return AirVelocity;
}

float UVH_EnvironmentConditions::GetAmbientTemperature()
{
	FScopeLock lock(&CriticalSection);
	return AmbientTemperature;
}

float UVH_EnvironmentConditions::GetAppliedTemperature()
{
	FScopeLock lock(&CriticalSection);
	return AppliedTemperature;
}

float UVH_EnvironmentConditions::GetAtmosphericPressure()
{
	FScopeLock lock(&CriticalSection);
	return AtmosphericPressure;
}

float UVH_EnvironmentConditions::GetClothingResistance()
{
	FScopeLock lock(&CriticalSection);
	return ClothingResistance;
}

float UVH_EnvironmentConditions::GetEmissivity()
{
	FScopeLock lock(&CriticalSection);
	return Emissivity;
}

float UVH_EnvironmentConditions::GetMeanRadiantTemperature()
{
	FScopeLock lock(&CriticalSection);
	return MeanRadiantTemperature;
}

float UVH_EnvironmentConditions::GetRelativeHumidity()
{
	FScopeLock lock(&CriticalSection);
	return RelativeHumidity;
}

float UVH_EnvironmentConditions::GetRespirationAmbientTemperature()
{
	FScopeLock lock(&CriticalSection);
	return RespirationAmbientTemperature;
}
