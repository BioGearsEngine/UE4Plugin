#pragma once

#include "UObject/ObjectMacros.h"

//!
//! Implementation of Seraliztion layer structs for use 
//!

#include "UBioGearsEnums.generated.h"


UENUM(Blueprintable, DisplayName="Biogears::Gender")
enum class EBioGearsGender : uint8 {
	NONE,
	MALE,
	FEMALE,
	OTHER,
};

UENUM(Blueprintable)
enum class EBioGearsExerciseState : uint8 {
	SLEEPING,
	RESTING,
	SITTING,
	STANDING,
	WALKING,
	RUNNING,
};

UENUM(Blueprintable)
enum class EBioGearsBloodType : uint8 {
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
enum class EBioGearsIvSubstance : uint8 {
	Sub1,
	Sub2
};

UENUM(Blueprintable)
enum class EBioGearsIvCompound : uint8 {
	Sub1,
	Sub2
};



UENUM(Blueprintable)
enum class EBioGearsOralSubstance : uint8
{
	Fyntynal
};


UENUM(Blueprintable)
enum class EBioGearsOralAbsorption : uint8
{
	Instestine,
	Transmocuusal
};


UENUM(Blueprintable)
enum class EBioGearsInfectionSeverity : uint8 {
	Eliminated,
	Mild,
	Moderate,
	Severe
};


UENUM(Blueprintable)
enum class EBioGearsSide : uint8
{
	Left,
	Right
};


UENUM(Blueprintable)
enum class EBioGearsPneumothorax : uint8
{
	Open,
	Closed
};


UENUM(Blueprintable)
enum class EBioGearsTourniquet : uint8 {
	Applied,
	Misapplied,
	None
};


UENUM(Blueprintable)
enum class EBioGearsExtremity : uint8 {
	LeftLeg,
	RightLeg,
	LeftArm,
	RightArm,
};

UENUM(Blueprintable)
enum class EBioGearsCompartment : uint8 {
	LeftLeg,
	RightLeg,
	LeftArm,
	RightArm,
};

UENUM(Blueprintable)
enum class EBioGearsUrineColor : uint8 {
	PaleYellow,
	Yellow,
	DarkYellow,
	Pink
};

UENUM(Blueprintable)
enum class EBioGearsClarityIndicator : uint8 {
	Clear,
	SlightlyCloudy,
	Cloudy,
	Turbid
};

UENUM(Blueprintable)
enum class EBioGearsPresenceIndicator : uint8 {
	Positive,
	Negitive,
};

UENUM(Blueprintable)
enum class EBioGearsMicroscopicOpservationType : uint8 {
	LowPowerField,
	HighPowerField,
};

UENUM(Blueprintable)
enum class EBioGearsMicroscopicObservationAmount : uint8 {
	Few,
	Moderate,
	Many
};
