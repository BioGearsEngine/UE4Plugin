#pragma once

UENUM(BlueprintType)
enum class EBioGearsChestSide : uint8
{
	None,
	Left,
	Right,
	Both
};

UENUM(BlueprintType)
enum class EBioGearsEventSystemType : uint8
{
	None,
    Patient,
    AnesthesiaMachine UMETA(DisplayName = "Anesthesia Machine")
};

UENUM(BlueprintType)
enum class EBioGearsGas : uint8
{
	None,
	Air,
	Nitrogen
};

UENUM(BlueprintType)
enum class EBioGearsPatientBloodType : uint8
{
	None,
	A,
	B,
	AB,
	O
};

UENUM(BlueprintType)
enum class EBioGearsPatientSex : uint8
{
	None,
	Male,
	Female,
	Other
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
enum class EBioGearsTourniquetLevel : uint8
{
	NotApplied,
	Misapplied,
	Applied
};
