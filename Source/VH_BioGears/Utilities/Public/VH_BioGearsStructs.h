#pragma once

// Generated
#include "VH_BioGearsStructs.generated.h"


// ---------------- Substance ---------------- //

/*
 * Information about an active custom compound solution
 * Compunds are made of different ratios of substances
 */
USTRUCT(BlueprintType)
struct FBioGearsCompound
{
	GENERATED_BODY()

public:
	/***/
	UPROPERTY(BlueprintReadOnly)
	FString Name = TEXT("Unknown");

	/***/
	UPROPERTY(BlueprintReadOnly)
	float Volume;

	/***/
	UPROPERTY(BlueprintReadOnly)
	float InfusionRate;

	FBioGearsCompound()
	{
		Name = "";
		Volume = 0.0f;
		InfusionRate = 0.0f;
	}

	FBioGearsCompound(FString name, float volume, float rate)
	{
		Name = name;
		Volume = volume;
		InfusionRate = rate;
	}
};

/*
 * Information about an active substance solution
 * Substance diluted by pure water
 */
USTRUCT(BlueprintType)
struct FBioGearsSubstance
{
	GENERATED_BODY()

public:
	/***/
	UPROPERTY(BlueprintReadOnly)
	FString Name = TEXT("Unknown");

	/***/
	UPROPERTY(BlueprintReadOnly)
	float InfusionRate;

	/***/
	UPROPERTY(BlueprintReadOnly)
	float Concentration;

	FBioGearsSubstance()
	{
		Name = FString("");
		InfusionRate = 0.0f;
		Concentration = 0.0f;
	}

	FBioGearsSubstance(FString inName, float inInfusionRate, float inConcentration)
	{
		Name = inName;
		InfusionRate = inInfusionRate;
		Concentration = inConcentration;
	}
};

/*
 * Concentration of a BioGears Substance
 * Useful for combining substances into compounds
 */
USTRUCT(BlueprintType)
struct FBioGearsSubstanceConcentration
{
	GENERATED_BODY()

public:
	/***/
	UPROPERTY(BlueprintReadWrite)
	FString Name;

	/** Measured in g/l */
	UPROPERTY(BlueprintReadWrite)
	float Concentration;

	FBioGearsSubstanceConcentration()
	{
		Name = FString("");
		Concentration = 0.0f;
	}

	FBioGearsSubstanceConcentration(FString inName, float inConcentration)
	{
		Name = inName;
		Concentration = inConcentration;
	}
};

// ---------------- Actions ---------------- //

/*
 * BioGears Hemorrhage information
 *
 */
USTRUCT(BlueprintType)
struct FBioGearsHemorrhage
{
	GENERATED_BODY()

public:
	UPROPERTY()
	float BleedResistance;
	
	UPROPERTY()
	float InitialRate;

	FBioGearsHemorrhage()
	{
		BleedResistance = 0.0f;
		InitialRate = 0.0f;
	}

	FBioGearsHemorrhage(float resistance, float rate)
	{
		BleedResistance = resistance;
		InitialRate = rate;
	}
};

/*
 * BioGears Pain Stimulus information
 * 
 */
USTRUCT(BlueprintType)
struct FBioGearsPainStimulus
{
	GENERATED_BODY()

public:
	float Severity;
	float HalfLife;

	FBioGearsPainStimulus()
	{
		Severity = 0.0f;
		HalfLife = 0.0f;
	}

	FBioGearsPainStimulus(float severity, float halfLife)
	{
		Severity = severity;
		HalfLife = halfLife;
	}
};
