#pragma once

#include "UObject/ObjectMacros.h"

//!
//! Implementation of Seraliztion layer structs for use 
//!

#include "UBioGearsEnums.generated.h"


UENUM(Blueprintable)
	enum class EBloodType : uint8	{
		O_Negitive,
		O_Positive,
		A_Negitive,
		A_Positive,
		B_Negative,
		B_Positive,
		A_B_Negative,
		A_B_Positive
	};

UENUM(Blueprintable)
	enum class EIvSubstance : uint8	{
		Sub1,
		Sub2
	};

UENUM(Blueprintable)
	enum class EIvCompound : uint8	{
		Sub1,
		Sub2
	};



UENUM(Blueprintable)
	enum class EOralSubstance : uint8
	{
		Fyntynal
	};


UENUM(Blueprintable)
	enum class EOralAbsorption : uint8
	{
		Instestine,
		Transmocuusal
	};


UENUM(Blueprintable)
	enum class EInfectionSeverity : uint8	{
		Eliminated,
		Mild,
		Moderate,
		Severe
	};


UENUM(Blueprintable)
	enum class ESide : uint8
	{
		Left,
		Right
	};


UENUM(Blueprintable)
	enum class EPneumothorax : uint8
	{
		Open,
		Closed
	};


UENUM(Blueprintable)
	enum class ETourniquet : uint8	{
		Applied,
		Misapplied,
		None
	};


UENUM(Blueprintable)
	enum class EExtremity : uint8	{
		LeftLeg,
		RightLeg,
		LeftArm,
		RightArm,
	};

UENUM(Blueprintable)
enum class ECompartment : uint8{
	LeftLeg,
	RightLeg,
	LeftArm,
	RightArm,
};

UENUM(Blueprintable)
enum class EUrineColor : uint8
{
	PaleYellow,
	Yellow,
	DarkYellow,
	Pink
};