#pragma once

// BioGears
#include "BioGearsPreHeaderBlock.inl"
#include <biogears/cdm/scenario/SEAction.h>
#include <biogears/cdm/substance/SESubstanceManager.h>
#include "schema/biogears/BioGears.hxx"
#include "BioGearsPostHeaderBlock.inl"

// Engine
#include "UObject/ObjectMacros.h"
#include "SharedPointer.h"

// VH BioGears Plugin
#include "BioGearsTypes_Enums.h"

#include "BioGearsStructs.generated.h"


// --------------- Patient Data --------------- //

USTRUCT(BlueprintType)
struct FBioGearsAnesthesiaMachine
{
	GENERATED_BODY()

public:
	UPROPERTY(BlueprintReadOnly)
	bool bConnected;
	
	UPROPERTY(BlueprintReadOnly)
	float InletFlow;
	
	UPROPERTY(BlueprintReadOnly)
	float InspiratoryExpiratoryRatio;
	
	UPROPERTY(BlueprintReadOnly)
	float OxygenBottleOneVolume;
	
	UPROPERTY(BlueprintReadOnly)
	float OxygenBottleTwoVolume;
	
	UPROPERTY(BlueprintReadOnly)
	float OxygenFraction;
	
	UPROPERTY(BlueprintReadOnly)
	EBioGearsGas PrimaryGas;
	
	UPROPERTY(BlueprintReadOnly)
	float ReliefValvePressure;
	
	UPROPERTY(BlueprintReadOnly)
	float RespiratoryRate;
	
	UPROPERTY(BlueprintReadOnly)
	float VentilatorPressure;
};

USTRUCT(BlueprintType)
struct FBioGearsBloodChemistry
{
	GENERATED_BODY()

public:
	/** Measured in ? */
	UPROPERTY(BlueprintReadOnly)
	float ArterialBloodPH;

	/** Measured in ?*/
	UPROPERTY(BlueprintReadOnly)
	float ArterialBloodPHBaseline;

	/** Measured in ?*/
	UPROPERTY(BlueprintReadOnly)
	float BloodDensity;

	/** Measured in ? */
	UPROPERTY(BlueprintReadOnly)
	float BloodSpecificHeat;

	/**Measured in ? */
	UPROPERTY(BlueprintReadOnly)
	float BloodUreaNitrogenConcentration;

	/** Measured in ? */
	UPROPERTY(BlueprintReadOnly)
	float CarbonDioxideSaturation;

	/** Measured in ? */
	UPROPERTY(BlueprintReadOnly)
	float CarbonMonoxideSaturation;

	/** Measured in ? */
	UPROPERTY(BlueprintReadOnly)
	float Hematocrit;

	/**Measured in ? */
	UPROPERTY(BlueprintReadOnly)
	float HemoglobinContent;

	/** Measure in ? */
	UPROPERTY(BlueprintReadOnly)
	float OxygenSaturation;

	/** Measured in ? */
	UPROPERTY(BlueprintReadOnly)
	float Phosphate;

	/** Measured in ? */
	UPROPERTY(BlueprintReadOnly)
	float PlasmaVolume;

	/** Measured in ? */
	UPROPERTY(BlueprintReadOnly)
	float PulseOximetry;

	/** Measured in ? */
	UPROPERTY(BlueprintReadOnly)
	float RedBloodCellAcetylcholinesterase;

	/***/
	UPROPERTY(BlueprintReadOnly)
	float RedBloodCellCount;

	/***/
	UPROPERTY(BlueprintReadOnly)
	float ShuntFraction;

	/***/
	UPROPERTY(BlueprintReadOnly)
	float StrongIonDifference;

	/** Measured in ? */
	UPROPERTY(BlueprintReadOnly)
	float TotalBilirubin;

	/** Measured in ? */
	UPROPERTY(BlueprintReadOnly)
	float TotalProteinConcentration;

	/***/
	UPROPERTY(BlueprintReadOnly)
	float VenousBloodPH;

	/***/
	UPROPERTY(BlueprintReadOnly)
	float VolumeFractionNeutralPhospholipidInPlasma;

	/***/
	UPROPERTY(BlueprintReadOnly)
	float VolumeFractionNeutralLipidInPlasma;

	/***/
	UPROPERTY(BlueprintReadOnly)
	float ArterialCarbonDioxidePressure;

	/***/
	UPROPERTY(BlueprintReadOnly)
	float ArterialOxygenPressure;

	/***/
	UPROPERTY(BlueprintReadOnly)
	float PulmonaryArterialCarbonDioxidePressure;

	/***/
	UPROPERTY(BlueprintReadOnly)
	float PulmonaryArterialOxygenPressure;

	/***/
	UPROPERTY(BlueprintReadOnly)
	float PulmonaryVenousCarbonDioxidePressure;

	/***/
	UPROPERTY(BlueprintReadOnly)
	float PulmonaryVenousOxygenPressure;

	/***/
	UPROPERTY(BlueprintReadOnly)
	float VenousCarbonDioxidePressure;

	/***/
	UPROPERTY(BlueprintReadOnly)
	float VenousOxygenPressure;
};

USTRUCT(BlueprintType)
struct FBioGearsBloodCount
{
	GENERATED_BODY()

public:
	/***/
	UPROPERTY(BlueprintReadOnly)
	float Hematocrit;

	/***/
	UPROPERTY(BlueprintReadOnly)
	float Hemoglobin;

	/***/
	UPROPERTY(BlueprintReadOnly)
	float PlateletCount;

	/***/
	UPROPERTY(BlueprintReadOnly)
	float MeanCorpusularHemoglobin;

	/***/
	UPROPERTY(BlueprintReadOnly)
	float MeanCorpuscularHemoglobinConcentration;

	/***/
	UPROPERTY(BlueprintReadOnly)
	float MeanCorpuscularVolume;

	/***/
	UPROPERTY(BlueprintReadOnly)
	float RedBloodCellCount;

	/***/
	UPROPERTY(BlueprintReadOnly)
	float WhiteBloodCellCount;
};

USTRUCT(BlueprintType)
struct FBioGearsCardiovascular
{
	GENERATED_BODY()


public:	
	/***/
	UPROPERTY(BlueprintReadOnly)
	float ArterialPressure;

	/***/
	UPROPERTY(BlueprintReadOnly)
	float BloodVolume;

	/***/
	UPROPERTY(BlueprintReadOnly)
	float CardiacIndex;

	/***/
	UPROPERTY(BlueprintReadOnly)
	float CardiacOutput;

	/***/
	UPROPERTY(BlueprintReadOnly)
	float CentralVenousPressure;

	/***/
	UPROPERTY(BlueprintReadOnly)
	float CerebralBloodFlow;

	/***/
	UPROPERTY(BlueprintReadOnly)
	float CerebralPerfusionPressure;

	/***/
	UPROPERTY(BlueprintReadOnly)
	float DiastolicArterialPressure;

	/***/
	UPROPERTY(BlueprintReadOnly)
	float HeartEjectionFraction;

	/***/
	UPROPERTY(BlueprintReadOnly)
	float HeartRate;

	/***/
	UPROPERTY(BlueprintReadOnly)
	float HeartStrokeVolume;

	/***/
	UPROPERTY(BlueprintReadOnly)
	float IntracranialPressure;

	/***/
	UPROPERTY(BlueprintReadOnly)
	float MeanArterialPressure;

	/***/
	UPROPERTY(BlueprintReadOnly)
	float MeanArterialCarbonDioxidePartialPressure;

	/***/
	UPROPERTY(BlueprintReadOnly)
	float MeanArterialCarbonDioxidePartialPressureDelta;

	/***/
	UPROPERTY(BlueprintReadOnly)
	float MeanCentralVenousPressure;

	/***/
	UPROPERTY(BlueprintReadOnly)
	float MeanSkinFlow;

	/***/
	UPROPERTY(BlueprintReadOnly)
	float PulmonaryArterialPressure;

	/***/
	UPROPERTY(BlueprintReadOnly)
	float PulmonaryCapillariesWedgePressure;

	/***/
	UPROPERTY(BlueprintReadOnly)
	float PulmonaryDiastolicArterialPressure;

	/***/
	UPROPERTY(BlueprintReadOnly)
	float PulmonaryMeanArterialPressure;

	/***/
	UPROPERTY(BlueprintReadOnly)
	float PulmonaryMeanCapillaryFlow;

	/***/
	UPROPERTY(BlueprintReadOnly)
	float PulmonaryMeanShuntFlow;

	/***/
	UPROPERTY(BlueprintReadOnly)
	float PulmonarySystolicArterialPressure;

	/***/
	UPROPERTY(BlueprintReadOnly)
	float PulmonaryVascularResistance;

	/***/
	UPROPERTY(BlueprintReadOnly)
	float PulmonaryVascularResistanceIndex;

	/***/
	UPROPERTY(BlueprintReadOnly)
	float PulsePressure;

	/***/
	UPROPERTY(BlueprintReadOnly)
	float SystemicVascularResistance;

	/***/
	UPROPERTY(BlueprintReadOnly)
	float SystolicArterialPressure;
};

USTRUCT(BlueprintType)
struct FBioGearsDrugs
{
	GENERATED_BODY()

public:
	/***/
	UPROPERTY(BlueprintReadOnly)
	float BronchodilationLevel;

	/***/
	UPROPERTY(BlueprintReadOnly)
	float HeartRateChange;

	/***/
	UPROPERTY(BlueprintReadOnly)
	float HemorrhageChange;

	/***/
	UPROPERTY(BlueprintReadOnly)
	float MeanBloodPressureChange;

	/***/
	UPROPERTY(BlueprintReadOnly)
	float NeuromuscularBlockLevel;

	/***/
	UPROPERTY(BlueprintReadOnly)
	float PulsePressureChange;

	/***/
	UPROPERTY(BlueprintReadOnly)
	float RespirationRateChange;

	/***/
	UPROPERTY(BlueprintReadOnly)
	float SedationLevel;

	/***/
	UPROPERTY(BlueprintReadOnly)
	float TidalVolumeChange;

	/***/
	UPROPERTY(BlueprintReadOnly)
	float TubularPermeabilityChange;

	/***/
	UPROPERTY(BlueprintReadOnly)
	float CentralNervousResponse;
};

USTRUCT(BlueprintType)
struct FBioGearsEnvironmentalConditions
{
	GENERATED_BODY()

public:
	UPROPERTY(BlueprintReadOnly)
	FString Name;

	/** Measured in kg/m^3 */
	UPROPERTY(BlueprintReadOnly)
	float AirDensity;
	
	/* Measured in m/s */
	UPROPERTY(BlueprintReadOnly)
	float AirVelocity;
	
	/* Measured in C */
	UPROPERTY(BlueprintReadOnly)
	float AmbientTemperature;

	/* Measured in C */
	UPROPERTY(BlueprintReadOnly)
	float AppliedTemperature;
	
	/** Measured in mmHg */
	UPROPERTY(BlueprintReadOnly)
	float AtmosphericPressure;
	
	/** Measured in CLO*/
	UPROPERTY(BlueprintReadOnly)
	float ClothingResistance;
	
	/** Measued in ? */
	UPROPERTY(BlueprintReadOnly)
	float Emissivity;
	
	/** Measured in C */
	UPROPERTY(BlueprintReadOnly)
	float MeanRadiantTemperature;
	
	/** Measured in PCT*/
	UPROPERTY(BlueprintReadOnly)
	float RelativeHumidity;
	
	/** Measured in C*/
	UPROPERTY(BlueprintReadOnly)
	float RespirationAmbientTemperature;

	//std::vector<std::pair<FString, float>> AmbientGases;
	//std::vector<std::pair<FString, float>> AmbientAerosols;
};

USTRUCT(BlueprintType)
struct FBioGearsEndocrine
{
	GENERATED_BODY()

public:
	/***/
	UPROPERTY(BlueprintReadOnly)
	float InsulinSynthesisRate;

	/***/
	UPROPERTY(BlueprintReadOnly)
	float GlucagonSynthesisRate;
};

USTRUCT(BlueprintType)
struct FBioGearsEnergy
{
	GENERATED_BODY()

public:
	/***/
	UPROPERTY(BlueprintReadOnly)
	float AchievedExerciseLevel;

	/***/
	UPROPERTY(BlueprintReadOnly)
	float ChlorideLostToSweat;

	/***/
	UPROPERTY(BlueprintReadOnly)
	float CoreTemperature;

	/***/
	UPROPERTY(BlueprintReadOnly)
	float CreatinineProductionRate;

	/***/
	UPROPERTY(BlueprintReadOnly)
	float ExerciseMeanArterialPressureDelta;

	/***/
	UPROPERTY(BlueprintReadOnly)
	float FatigueLevel;

	/***/
	UPROPERTY(BlueprintReadOnly)
	float LactateProductionRate;

	/***/
	UPROPERTY(BlueprintReadOnly)
	float PotassiumLostToSweat;

	/***/
	UPROPERTY(BlueprintReadOnly)
	float SkinTemperature;

	/***/
	UPROPERTY(BlueprintReadOnly)
	float SodiumLostToSweat;

	/***/
	UPROPERTY(BlueprintReadOnly)
	float SweatRate;

	/***/
	UPROPERTY(BlueprintReadOnly)
	float TotalMetabolicRate;

	/***/
	UPROPERTY(BlueprintReadOnly)
	float TotalWorkRateLevel;
};

USTRUCT(BlueprintType)
struct FBioGearsGastrointestinal
{
	GENERATED_BODY()

public:
	/***/
	UPROPERTY(BlueprintReadOnly)
	float ChymeAbsorptionRate;

	/***/
	UPROPERTY(BlueprintReadOnly)
	float StomachContents_Calcium;

	/***/
	UPROPERTY(BlueprintReadOnly)
	float StomachContents_Carbohydrates;

	/***/
	UPROPERTY(BlueprintReadOnly)
	float StomachContents_Fat;

	/***/
	UPROPERTY(BlueprintReadOnly)
	float StomachContents_Protein;

	/***/
	UPROPERTY(BlueprintReadOnly)
	float StomachContents_Sodium;

	/***/
	UPROPERTY(BlueprintReadOnly)
	float StomachContents_Water;
};

USTRUCT(BlueprintType)
struct FBioGearsHepatic
{
	GENERATED_BODY()

public:
	/***/
	UPROPERTY(BlueprintReadOnly)
	float KetoneProductionRate;

	/***/
	UPROPERTY(BlueprintReadOnly)
	float HepaticGluconeogenesisRate;
};

USTRUCT(BlueprintType)
struct FBioGearsInflamatoryRespose
{
	GENERATED_BODY()

public:
	/***/
	UPROPERTY(BlueprintReadOnly)
	float LocalPathogen;

	/***/
	UPROPERTY(BlueprintReadOnly)
	float LocalMacrophage;

	/***/
	UPROPERTY(BlueprintReadOnly)
	float LocalNeutrophil;

	/***/
	UPROPERTY(BlueprintReadOnly)
	float LocalBarrier;

	/***/
	UPROPERTY(BlueprintReadOnly)
	float BloodPathogen;

	/***/
	UPROPERTY(BlueprintReadOnly)
	float Trauma;

	/***/
	UPROPERTY(BlueprintReadOnly)
	float MacrophageResting;

	/***/
	UPROPERTY(BlueprintReadOnly)
	float MacrophageActive;

	/***/
	UPROPERTY(BlueprintReadOnly)
	float NeutrophilResting;

	/***/
	UPROPERTY(BlueprintReadOnly)
	float NeutrophilActive;

	/***/
	UPROPERTY(BlueprintReadOnly)
	float InducibleNOSPre;

	/***/
	UPROPERTY(BlueprintReadOnly)
	float InducibleNOS;

	/***/
	UPROPERTY(BlueprintReadOnly)
	float ConstitutiveNOS;

	/***/
	UPROPERTY(BlueprintReadOnly)
	float Nitrate;

	/***/
	UPROPERTY(BlueprintReadOnly)
	float NitricOxide;

	/***/
	UPROPERTY(BlueprintReadOnly)
	float TumorNecrosisFactor;

	/***/
	UPROPERTY(BlueprintReadOnly)
	float Interleukin6;

	/***/
	UPROPERTY(BlueprintReadOnly)
	float Interleukin10;

	/***/
	UPROPERTY(BlueprintReadOnly)
	float Interleukin12;

	/***/
	UPROPERTY(BlueprintReadOnly)
	float Catecholamines;

	/***/
	UPROPERTY(BlueprintReadOnly)
	float TissueIntegrity;
};

USTRUCT(BlueprintType)
struct FBioGearsMetabolicPanel
{
	GENERATED_BODY()

public:
	/***/
	UPROPERTY(BlueprintReadOnly)
	float Albumin;

	/***/
	UPROPERTY(BlueprintReadOnly)
	float ALP;

	/***/
	UPROPERTY(BlueprintReadOnly)
	float ALT;

	/***/
	UPROPERTY(BlueprintReadOnly)
	float AST;

	/***/
	UPROPERTY(BlueprintReadOnly)
	float BUN;

	/***/
	UPROPERTY(BlueprintReadOnly)
	float Calcium;

	/***/
	UPROPERTY(BlueprintReadOnly)
	float Chlordide;

	/***/
	UPROPERTY(BlueprintReadOnly)
	float Co2;

	/***/
	UPROPERTY(BlueprintReadOnly)
	float Creatine;

	/***/
	UPROPERTY(BlueprintReadOnly)
	float Glucose;

	/***/
	UPROPERTY(BlueprintReadOnly)
	float Potassium;

	/***/
	UPROPERTY(BlueprintReadOnly)
	float Sodium;

	/***/
	UPROPERTY(BlueprintReadOnly)
	float Bilirubin;

	/***/
	UPROPERTY(BlueprintReadOnly)
	float Protien;
};

USTRUCT(BlueprintType)
struct FBioGearsNervous
{
	GENERATED_BODY()

public:
	/***/
	UPROPERTY(BlueprintReadOnly)
	float ComplianceScale;

	/***/
	UPROPERTY(BlueprintReadOnly)
	float HeartRateScale;

	/***/
	UPROPERTY(BlueprintReadOnly)
	float HeartElastanceScale;

	/***/
	UPROPERTY(BlueprintReadOnly)
	float ResistanceScaleExtrasplanchnic;

	/***/
	UPROPERTY(BlueprintReadOnly)
	float ResistanceScaleMuscle;

	/***/
	UPROPERTY(BlueprintReadOnly)
	float ResistanceScaleMyocardium;

	/***/
	UPROPERTY(BlueprintReadOnly)
	float ResistanceScaleSplanchnic;

	/***/
	UPROPERTY(BlueprintReadOnly)
	float PainVisualAnalogueScale;

	/***/
	UPROPERTY(BlueprintReadOnly)
	float LeftEyePupillaryResponse;

	/***/
	UPROPERTY(BlueprintReadOnly)
	float RightEyePupillaryResponse;
};

USTRUCT(BlueprintType)
struct FBioGearsPatient
{
	GENERATED_BODY()

public:
	UPROPERTY(BlueprintReadOnly)
	float Age;

	UPROPERTY(BlueprintReadOnly)
	float BloodRh;

	UPROPERTY(BlueprintReadOnly)
	EBioGearsPatientBloodType BloodType;

	UPROPERTY(BlueprintReadOnly)
	float BloodVolumeBaseline;

	UPROPERTY(BlueprintReadOnly)
	float BodyFatFraction;

	UPROPERTY(BlueprintReadOnly)
	float ExpiratoryReserveVolume;

	UPROPERTY(BlueprintReadOnly)
	EBioGearsPatientSex Gender;

	UPROPERTY(BlueprintReadOnly)
	float HeartRateBaseline;

	UPROPERTY(BlueprintReadOnly)
	float HeartRateMaximum;

	UPROPERTY(BlueprintReadOnly)
	float HeartRateMinimum;

	UPROPERTY(BlueprintReadOnly)
	float Height;

	UPROPERTY(BlueprintReadOnly)
	float InspiratoryCapacity;

	UPROPERTY(BlueprintReadOnly)
	float LeanBodyMass;

	UPROPERTY(BlueprintReadOnly)
	float MuscleMass;

	UPROPERTY(BlueprintReadOnly)
	FString Name;

	UPROPERTY(BlueprintReadOnly)
	float PainSusceptibility;

	UPROPERTY(BlueprintReadOnly)
	float RespirationRateBaseline;

	UPROPERTY(BlueprintReadOnly)
	EBioGearsPatientSex Sex;

	UPROPERTY(BlueprintReadOnly)
	float SystolicArterialPressureBaseline;

	UPROPERTY(BlueprintReadOnly)
	float TotalLungCapacity;

	UPROPERTY(BlueprintReadOnly)
	float VitalCapacity;

	UPROPERTY(BlueprintReadOnly)
	float Weight;
};

USTRUCT(BlueprintType)
struct FBioGearsRenal
{
	GENERATED_BODY()

public:
	/***/
	UPROPERTY(BlueprintReadOnly)
	float GlomerularFiltrationRate;

	/***/
	UPROPERTY(BlueprintReadOnly)
	float FiltrationFraction;

	/***/
	UPROPERTY(BlueprintReadOnly)
	float LeftAfferentArterioleResistance;

	/***/
	UPROPERTY(BlueprintReadOnly)
	float LeftBowmansCapsulesHydrostaticPressure;

	/***/
	UPROPERTY(BlueprintReadOnly)
	float LeftBowmansCapsulesOsmoticPressure;

	/***/
	UPROPERTY(BlueprintReadOnly)
	float LeftEfferentArterioleResistance;

	/***/
	UPROPERTY(BlueprintReadOnly)
	float LeftGlomerularCapillariesHydrostaticPressure;

	/***/
	UPROPERTY(BlueprintReadOnly)
	float LeftGlomerularCapillariesOsmoticPressure;

	/***/
	UPROPERTY(BlueprintReadOnly)
	float LeftGlomerularFiltrationCoefficient;

	/***/
	UPROPERTY(BlueprintReadOnly)
	float LeftGlomerularFiltrationRate;

	/***/
	UPROPERTY(BlueprintReadOnly)
	float LeftGlomerularFiltrationSurfaceArea;

	/***/
	UPROPERTY(BlueprintReadOnly)
	float LeftGlomerularFluidPermeability;

	/***/
	UPROPERTY(BlueprintReadOnly)
	float LeftFiltrationFraction;

	/***/
	UPROPERTY(BlueprintReadOnly)
	float LeftNetFiltrationPressure;

	/***/
	UPROPERTY(BlueprintReadOnly)
	float LeftNetReabsorptionPressure;

	/***/
	UPROPERTY(BlueprintReadOnly)
	float LeftPeritubularCapillariesHydrostaticPressure;

	/***/
	UPROPERTY(BlueprintReadOnly)
	float LeftPeritubularCapillariesOsmoticPressure;

	/***/
	UPROPERTY(BlueprintReadOnly)
	float LeftReabsorptionFiltrationCoefficient;

	/***/
	UPROPERTY(BlueprintReadOnly)
	float LeftReabsorptionRate;

	/***/
	UPROPERTY(BlueprintReadOnly)
	float LeftTubularReabsorptionFiltrationSurfaceArea;

	/***/
	UPROPERTY(BlueprintReadOnly)
	float LeftTubularReabsorptionFluidPermeability;

	/***/
	UPROPERTY(BlueprintReadOnly)
	float LeftTubularHydrostaticPressure;

	/***/
	UPROPERTY(BlueprintReadOnly)
	float LeftTubularOsmoticPressure;

	/***/
	UPROPERTY(BlueprintReadOnly)
	float MaxUrineVolume = 400.0f;

	/***/
	UPROPERTY(BlueprintReadOnly)
	float RenalBloodFlow;

	/***/
	UPROPERTY(BlueprintReadOnly)
	float RenalPlasmaFlow;

	/***/
	UPROPERTY(BlueprintReadOnly)
	float RenalVascularResistance;

	/***/
	UPROPERTY(BlueprintReadOnly)
	float RightAfferentArterioleResistance;

	/***/
	UPROPERTY(BlueprintReadOnly)
	float RightBowmansCapsulesHydrostaticPressure;

	/***/
	UPROPERTY(BlueprintReadOnly)
	float RightBowmansCapsulesOsmoticPressure;

	/***/
	UPROPERTY(BlueprintReadOnly)
	float RightEfferentArterioleResistance;

	/***/
	UPROPERTY(BlueprintReadOnly)
	float RightGlomerularCapillariesHydrostaticPressure;

	/***/
	UPROPERTY(BlueprintReadOnly)
	float RightGlomerularCapillariesOsmoticPressure;

	/***/
	UPROPERTY(BlueprintReadOnly)
	float RightGlomerularFiltrationCoefficient;

	/***/
	UPROPERTY(BlueprintReadOnly)
	float RightGlomerularFiltrationRate;

	/***/
	UPROPERTY(BlueprintReadOnly)
	float RightGlomerularFiltrationSurfaceArea;

	/***/
	UPROPERTY(BlueprintReadOnly)
	float RightGlomerularFluidPermeability;

	/***/
	UPROPERTY(BlueprintReadOnly)
	float RightFiltrationFraction;

	/***/
	UPROPERTY(BlueprintReadOnly)
	float RightNetFiltrationPressure;

	/***/
	UPROPERTY(BlueprintReadOnly)
	float RightNetReabsorptionPressure;

	/***/
	UPROPERTY(BlueprintReadOnly)
	float RightPeritubularCapillariesHydrostaticPressure;

	/***/
	UPROPERTY(BlueprintReadOnly)
	float RightPeritubularCapillariesOsmoticPressure;

	/***/
	UPROPERTY(BlueprintReadOnly)
	float RightReabsorptionFiltrationCoefficient;

	/***/
	UPROPERTY(BlueprintReadOnly)
	float RightReabsorptionRate;

	/***/
	UPROPERTY(BlueprintReadOnly)
	float RightTubularReabsorptionFiltrationSurfaceArea;

	/***/
	UPROPERTY(BlueprintReadOnly)
	float RightTubularReabsorptionFluidPermeability;

	/***/
	UPROPERTY(BlueprintReadOnly)
	float RightTubularHydrostaticPressure;

	/***/
	UPROPERTY(BlueprintReadOnly)
	float RightTubularOsmoticPressure;

	/***/
	UPROPERTY(BlueprintReadOnly)
	float UrinationRate;

	/***/
	UPROPERTY(BlueprintReadOnly)
	float UrineOsmolality;

	/***/
	UPROPERTY(BlueprintReadOnly)
	float UrineOsmolarity;

	/***/
	UPROPERTY(BlueprintReadOnly)
	float UrineProductionRate;

	/***/
	UPROPERTY(BlueprintReadOnly)
	float MeanUrineOutput;

	/***/
	UPROPERTY(BlueprintReadOnly)
	float UrineSpecificGravity;

	/***/
	UPROPERTY(BlueprintReadOnly)
	float UrineVolume;

	/***/
	UPROPERTY(BlueprintReadOnly)
	float UrineUreaNitrogenConcentration;
};

USTRUCT(BlueprintType)
struct FBioGearsRespiratory
{
	GENERATED_BODY()

public:
	/***/
	UPROPERTY(BlueprintReadOnly)
	float AlveolarArterialGradient;

	/***/
	UPROPERTY(BlueprintReadOnly)
	float CarricoIndex;

	/***/
	UPROPERTY(BlueprintReadOnly)
	float EndTidalCarbonDioxideFraction;

	/***/
	UPROPERTY(BlueprintReadOnly)
	float EndTidalCarbonDioxidePressure;

	/***/
	UPROPERTY(BlueprintReadOnly)
	float ExpiratoryFlow;

	/***/
	UPROPERTY(BlueprintReadOnly)
	float InspiratoryExpiratoryRatio;

	/***/
	UPROPERTY(BlueprintReadOnly)
	float InspiratoryFlow;

	/***/
	UPROPERTY(BlueprintReadOnly)
	float PulmonaryCompliance;

	/***/
	UPROPERTY(BlueprintReadOnly)
	float PulmonaryResistance;

	/***/
	UPROPERTY(BlueprintReadOnly)
	float RespirationDriverPressure;

	/***/
	UPROPERTY(BlueprintReadOnly)
	float RespirationMusclePressure;

	/***/
	UPROPERTY(BlueprintReadOnly)
	float RespirationRate;

	/***/
	UPROPERTY(BlueprintReadOnly)
	float SpecificVentilation;

	/***/
	UPROPERTY(BlueprintReadOnly)
	float TargetPulmonaryVentilation;

	/***/
	UPROPERTY(BlueprintReadOnly)
	float TidalVolume;

	/***/
	UPROPERTY(BlueprintReadOnly)
	float TotalAlveolarVentilation;

	/***/
	UPROPERTY(BlueprintReadOnly)
	float TotalDeadSpaceVentilation;

	/***/
	UPROPERTY(BlueprintReadOnly)
	float TotalLungVolume;

	/***/
	UPROPERTY(BlueprintReadOnly)
	float TotalPulmonaryVentilation;

	/***/
	UPROPERTY(BlueprintReadOnly)
	float TranspulmonaryPressure;
};

USTRUCT(BlueprintType)
struct FBioGearsTissue
{
	GENERATED_BODY()

public:
	/***/
	UPROPERTY(BlueprintReadOnly)
	float CarbonDioxideProductionRate;

	/***/
	UPROPERTY(BlueprintReadOnly)
	float DehydrationFraction;

	/***/
	UPROPERTY(BlueprintReadOnly)
	float ExtracellularFluidVolume;

	/***/
	UPROPERTY(BlueprintReadOnly)
	float ExtravascularFluidVolume;

	/***/
	UPROPERTY(BlueprintReadOnly)
	float IntracellularFluidPH;

	/***/
	UPROPERTY(BlueprintReadOnly)
	float IntracellularFluidVolume;

	/***/
	UPROPERTY(BlueprintReadOnly)
	float TotalBodyFluidVolume;

	/***/
	UPROPERTY(BlueprintReadOnly)
	float OxygenConsumptionRate;

	/***/
	UPROPERTY(BlueprintReadOnly)
	float RespiratoryExchangeRatio;

	/***/
	UPROPERTY(BlueprintReadOnly)
	float LiverInsulinSetPoint;

	/***/
	UPROPERTY(BlueprintReadOnly)
	float LiverGlucagonSetPoint;

	/***/
	UPROPERTY(BlueprintReadOnly)
	float MuscleInsulinSetPoint;

	/***/
	UPROPERTY(BlueprintReadOnly)
	float MuscleGlucagonSetPoint;

	/***/
	UPROPERTY(BlueprintReadOnly)
	float FatInsulinSetPoint;

	/***/
	UPROPERTY(BlueprintReadOnly)
	float FatGlucagonSetPoint;

	/***/
	UPROPERTY(BlueprintReadOnly)
	float LiverGlycogen;

	/***/
	UPROPERTY(BlueprintReadOnly)
	float MuscleGlycogen;

	/***/
	UPROPERTY(BlueprintReadOnly)
	float StoredProtein;

	/***/
	UPROPERTY(BlueprintReadOnly)
	float StoredFat;
};

// ---------------- Substance ---------------- //

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
};

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

// -------------- Infusion Data -------------- //

USTRUCT(BlueprintType)
struct FBioGearsSubstanceInfusions
{
	GENERATED_BODY()

public:
	/***/
	UPROPERTY(BlueprintReadOnly)
	TArray<FBioGearsSubstance> Infusions;
};

USTRUCT(BlueprintType)
struct FBioGearsCompoundInfusions
{
	GENERATED_BODY()

public:
	/***/
	UPROPERTY(BlueprintReadOnly)
		TArray<FBioGearsCompound> Infusions;
};

// -------------- BioGears Data -------------- //

USTRUCT(BlueprintType)
struct FBioGearsMetrics
{
	GENERATED_BODY()

public:
	/***/
	UPROPERTY(BlueprintReadOnly)
	float SimulationTime;

	/***/
	UPROPERTY(BlueprintReadOnly)
	float TimeStep;
};

USTRUCT(BlueprintType)
struct FBioGearsState
{
	GENERATED_BODY()

public:
	/***/
	UPROPERTY(BlueprintReadOnly)
	FString Name;

	/***/
	UPROPERTY(BlueprintReadOnly, Meta = (DisplayName = "IsPatientAlive"))
	bool bLiving;

	/***/
	UPROPERTY(BlueprintReadOnly, Meta = (DisplayName = "IsPatientTacycardic"))
	bool bTacycardia;

	/** Measured in Years */
	UPROPERTY(BlueprintReadOnly)
	float Age;

	/** Measured in cm */
	UPROPERTY(BlueprintReadOnly)
	float Height;

	/***/
	//UPROPERTY(BlueprintReadOnly)
	//EBioGearsGender gender;

	/** Measured in kg */
	UPROPERTY(BlueprintReadOnly)
	float Weight;

	/** Measured in m^2*/
	UPROPERTY(BlueprintReadOnly)
	float BodySurfaceArea;

	/** Measured in kg/m^2 */
	UPROPERTY(BlueprintReadOnly)
	float BodyMassIndex;

	/**Meaured in Pct */
	UPROPERTY(BlueprintReadOnly)
	float BodyFat;

	/***/
	//UPROPERTY(BlueprintReadOnly)
	//EBioGearsExerciseState exercise_state;
};

USTRUCT(BlueprintType)
struct FBioGearsConditions
{
	GENERATED_BODY()

public:
	/***/
	UPROPERTY(BlueprintReadOnly)
	bool bDiabieties = false;
};

// ------------------ Tests ------------------ //

USTRUCT(BlueprintType)
struct FBioGearsPulmonaryTest
{
	GENERATED_BODY()

public:
	/***/
	UPROPERTY(BlueprintReadOnly)
	float PlotPointCount;

	/***/
	UPROPERTY(BlueprintReadOnly)
	float ExpiratoryReserveVolume;

	/***/
	UPROPERTY(BlueprintReadOnly)
	float ForcedVitalCapacity;

	/***/
	UPROPERTY(BlueprintReadOnly)
	float ForcedExpiratoryVolume;

	/***/
	UPROPERTY(BlueprintReadOnly)
	float FunctionalResidualCapacity;

	/***/
	UPROPERTY(BlueprintReadOnly)
	float InspiratoryCapacity;

	/***/
	UPROPERTY(BlueprintReadOnly)
	float InspiratoryReserveVolume;

	/***/
	UPROPERTY(BlueprintReadOnly)
	float MaximumVolunataryVentilation;

	/***/
	UPROPERTY(BlueprintReadOnly)
	float PeekExpitatoryFlow;

	/***/
	UPROPERTY(BlueprintReadOnly)
	float ResidualVolume;

	/***/
	UPROPERTY(BlueprintReadOnly)
	float SlowVitalCapacity;

	/***/
	UPROPERTY(BlueprintReadOnly)
	float TotalLungCapacity;

	/***/
	UPROPERTY(BlueprintReadOnly)
	float VitalCapacity;

	//TODO: Support Lung Volume Plot
	//float Lung_volume_plot;
};

USTRUCT(BlueprintType)
struct FBioGearsUrinalysisMicroscopic
{
	GENERATED_BODY()

public:
	///***/
	//UPROPERTY(BlueprintReadOnly)
	//EBioGearsMicroscopicOpservationType Type;

	///***/
	//UPROPERTY(BlueprintReadOnly)
	//float RedBloodCells;

	///***/
	//UPROPERTY(BlueprintReadOnly)
	//float WhiteBloodCells;

	///***/
	//UPROPERTY(BlueprintReadOnly)
	//EBioGearsMicroscopicObservationAmount EpitheliaCells;

	///***/
	//UPROPERTY(BlueprintReadOnly)
	//float Casts;

	///***/
	//UPROPERTY(BlueprintReadOnly)
	//EBioGearsMicroscopicObservationAmount Crystals;

	///***/
	//UPROPERTY(BlueprintReadOnly)
	//EBioGearsMicroscopicObservationAmount Bacteria;

	///***/
	//UPROPERTY(BlueprintReadOnly)
	//EBioGearsMicroscopicObservationAmount Trichomonads;

	///***/
	//UPROPERTY(BlueprintReadOnly)
	//EBioGearsMicroscopicObservationAmount Yeast;
};

USTRUCT(BlueprintType)
struct FBioGearsUrineAnalysis
{
	GENERATED_BODY()

public:
	/***/
	//UPROPERTY(BlueprintReadOnly)
	//EBioGearsUrineColor Color;

	///***/
	//UPROPERTY(BlueprintReadOnly)
	//EBioGearsClarityIndicator Appearance;

	///***/
	//UPROPERTY(BlueprintReadOnly)
	//EBioGearsPresenceIndicator Glucose;

	///***/
	//UPROPERTY(BlueprintReadOnly)
	//EBioGearsPresenceIndicator Ketone;

	///***/
	//UPROPERTY(BlueprintReadOnly)
	//EBioGearsPresenceIndicator Blood;

	///***/
	//UPROPERTY(BlueprintReadOnly)
	//EBioGearsPresenceIndicator Protien;

	///***/
	//UPROPERTY(BlueprintReadOnly)
	//EBioGearsPresenceIndicator Nitrite;

	///***/
	//UPROPERTY(BlueprintReadOnly)
	//EBioGearsPresenceIndicator LeukocyteEsterase;

	/***/
	UPROPERTY(BlueprintReadOnly)
	float Bilirubin;

	/***/
	UPROPERTY(BlueprintReadOnly)
	float Specificgravity;

	/***/
	UPROPERTY(BlueprintReadOnly)
	float Ph;

	/***/
	UPROPERTY(BlueprintReadOnly)
	float Urobilinogen;
};
