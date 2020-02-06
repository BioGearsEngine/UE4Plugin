#pragma once

#include <UnrealString.h>

#include <vector>
#include <utility>

//!
//! Collection of UE4 Mirrored types from the CDM
//! Mostly used to simplify apply actions functions
//! May be refactored out.
//!
namespace biogears
{
	struct sEnvironmentalConditions
	{
		FString Name;
		double AirDensity_kg_Per_m3;
		double AirVelocity_m_Per_s;
		double AmbientTemperature_c;
		double AtmosphericPressure_mmHg;
		double ClothingResistance_clo;
		double Emissivity;
		double MeanRadiantTemperature_c;
		double RelativeHumidity_pct;
		double RespirationAmbientTemperature_c;

		std::vector<std::pair<FString, double>> AmbientGases;
		std::vector<std::pair<FString, double>> AmbientAerosols;
	};

	struct BiogearsMetrics
	{

	};

	struct BiogearsState
	{
		bool living;
	};

	struct BiogearsConditions
	{

	};
}