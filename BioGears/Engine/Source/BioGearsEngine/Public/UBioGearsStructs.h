#pragma once

#include <UnrealString.h>
#include "UObject/ObjectMacros.h"

#include <vector>
#include <utility>

#include "UBioGearsStructs.generated.h"
//!
//! Collection of UE4 Mirrored types from the CDM
//! Mostly used to simplify apply actions functions
//! May be refactored out.
//!
USTRUCT(BlueprintType)
struct FEnvironmentalConditions
{
	GENERATED_BODY()
public:
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


USTRUCT(BlueprintType)
struct FBiogearsMetrics
{
	GENERATED_BODY()
public:
};

USTRUCT(BlueprintType)
struct FBiogearsState
{
	GENERATED_BODY()
public:
	bool living;
};

USTRUCT(BlueprintType)
struct FBiogearsConditions
{
	GENERATED_BODY()
	public:
};
