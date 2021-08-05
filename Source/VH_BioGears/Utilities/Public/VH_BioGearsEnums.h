#pragma once

// Engine
#include "UObject/ObjectMacros.h"

UENUM(BlueprintType)
enum class EAnesthesia : uint8
{
	None,
	Air,
	Nitrogen
};

UENUM(BlueprintType)
enum class EBrainInjuryType : uint8
{
	None,
	Diffuse,
	LeftFocal,
	RightFocal
};

UENUM(BlueprintType)
enum class EEventSystemType : uint8
{
	None,
    Patient,
    AnesthesiaMachine UMETA(DisplayName = "Anesthesia Machine")
};

UENUM(BlueprintType)
enum class EOpenState : uint8
{
	None,
	Open,
	Closed
};

UENUM(BlueprintType)
enum class EPatientBloodType : uint8
{
	None,
	A,
	B,
	AB,
	O
};

UENUM(BlueprintType)
enum class EPatientChestSide : uint8
{
	None,
	Left,
	Right,
	Both
};

UENUM(BlueprintType)
enum class EPatientEvent : uint8
{
	AcuteLungInjury,
	AcuteRespiratoryDistress,
	Antidiuresis,
	Asystole,
	Bradycardia,
	Bradypnea,
	BrainOxygenDeficit,
	CardiacArrest,
	CardiogenicShock,
	CriticalBrainOxygenDeficit,
	Dehydration,
	Diuresis,
	Fasciculation,
	Fatigue,
	FunctionalIncontinence,
	HemolyticTransfusionReaction,
	Hypercapnia,
	Hyperglycemia,
	MildHyperkalemia,
	SevereHyperkalemia,
	MildHypernatremia,
	SevereHypernatremia,
	Hyperthermia,
	Hypoglycemia,
	HypoglycemicShock,
	HypoglycemicComa,
	Hypothermia,
	MildHypokalemia,
	SevereHypokalemia,
	MildHyponatremia,
	SevereHyponatremia,
	Hypoxia,
	HypovolemicShock,
	IntracranialHypertension,
	IntracranialHypotension,
	IrreversibleState,
	Ketoacidosis,
	LacticAcidosis,
	LiverGlycogenDepleted,
	MaximumPulmonaryVentilationRate,
	MetabolicAcidosis,
	MetabolicAlkalosis,
	MuscleCatabolism,
	MuscleGlycogenDepleted,
	MyocardiumOxygenDeficit,
	Natriuresis,
	NutritionDepleted,
	PulselessRhythm,
	RenalHypoperfusion,
	RespiratoryAcidosis,
	RespiratoryAlkalosis,
	SevereAcuteRespiratoryDistress,
	StartOfCardiacCycle,
	StartOfExhale,
	StartOfInhale,
	SevereSepsis,
	Tachycardia,
	Tachypnea,
	TotalPatientEvents
};

UENUM(BlueprintType)
enum class EPatientSex : uint8
{
	None,
	Male,
	Female,
	Other
};

UENUM(BlueprintType)
enum class EPatientSleep : uint8
{
	Awake,
	Asleep
};

UENUM(BlueprintType)
enum class EScenarioPlayMode : uint8
{
	None,
    Paused,
    Play,
    FastForward UMETA(DisplayName = "Fast Forward")
};

UENUM(BlueprintType)
enum class ETourniquetLevel : uint8
{
	NotApplied,
	Misapplied,
	Applied
};
