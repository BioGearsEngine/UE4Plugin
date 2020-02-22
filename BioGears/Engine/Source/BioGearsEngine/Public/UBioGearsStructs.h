#pragma once

#include <UnrealString.h>
#include "UObject/ObjectMacros.h"

#include <vector>
#include <utility>

#include "UBioGearsEnums.h"

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
	UPROPERTY(BlueprintReadOnly)
		FString Name;
	UPROPERTY(BlueprintReadOnly)
		float AirDensity_kg_Per_m3;
	UPROPERTY(BlueprintReadOnly)
		float AirVelocity_m_Per_s;
	UPROPERTY(BlueprintReadOnly)
		float AmbientTemperature_c;
	UPROPERTY(BlueprintReadOnly)
		float AtmosphericPressure_mmHg;
	UPROPERTY(BlueprintReadOnly)
		float ClothingResistance_clo;
	UPROPERTY(BlueprintReadOnly)
		float Emissivity;
	UPROPERTY(BlueprintReadOnly)
		float MeanRadiantTemperature_c;
	UPROPERTY(BlueprintReadOnly)
		float RelativeHumidity_pct;
	UPROPERTY(BlueprintReadOnly)
		float RespirationAmbientTemperature_c;

	std::vector<std::pair<FString, float>> AmbientGases;
	std::vector<std::pair<FString, float>> AmbientAerosols;
};

USTRUCT(BlueprintType)
struct FBiogearsBloodChemistry {
	GENERATED_BODY()

public:
	//Blood Chemistry
	UPROPERTY(BlueprintReadOnly)
		float arterialBloodPH;
	UPROPERTY(BlueprintReadOnly)
		float arterialBloodPHBaseline;
	UPROPERTY(BlueprintReadOnly)
		float bloodDensity;
	UPROPERTY(BlueprintReadOnly)
		float bloodSpecificHeat;
	UPROPERTY(BlueprintReadOnly)
		float bloodUreaNitrogenConcentration;
	UPROPERTY(BlueprintReadOnly)
		float carbonDioxideSaturation;
	UPROPERTY(BlueprintReadOnly)
		float carbonMonoxideSaturation;
	UPROPERTY(BlueprintReadOnly)
		float hematocrit;
	UPROPERTY(BlueprintReadOnly)
		float hemoglobinContent;
	UPROPERTY(BlueprintReadOnly)
		float oxygenSaturation;
	UPROPERTY(BlueprintReadOnly)
		float phosphate;
	UPROPERTY(BlueprintReadOnly)
		float plasmaVolume;
	UPROPERTY(BlueprintReadOnly)
		float pulseOximetry;
	UPROPERTY(BlueprintReadOnly)
		float redBloodCellAcetylcholinesterase;
	UPROPERTY(BlueprintReadOnly)
		float redBloodCellCount;
	UPROPERTY(BlueprintReadOnly)
		float shuntFraction;
	UPROPERTY(BlueprintReadOnly)
		float strongIonDifference;
	UPROPERTY(BlueprintReadOnly)
		float totalBilirubin;
	UPROPERTY(BlueprintReadOnly)
		float totalProteinConcentration;
	UPROPERTY(BlueprintReadOnly)
		float venousBloodPH;
	UPROPERTY(BlueprintReadOnly)
		float volumeFractionNeutralPhospholipidInPlasma;
	UPROPERTY(BlueprintReadOnly)
		float volumeFractionNeutralLipidInPlasma;
	UPROPERTY(BlueprintReadOnly)
		float arterialCarbonDioxidePressure;
	UPROPERTY(BlueprintReadOnly)
		float arterialOxygenPressure;
	UPROPERTY(BlueprintReadOnly)
		float pulmonaryArterialCarbonDioxidePressure;
	UPROPERTY(BlueprintReadOnly)
		float pulmonaryArterialOxygenPressure;
	UPROPERTY(BlueprintReadOnly)
		float pulmonaryVenousCarbonDioxidePressure;
	UPROPERTY(BlueprintReadOnly)
		float pulmonaryVenousOxygenPressure;
	UPROPERTY(BlueprintReadOnly)
		float venousCarbonDioxidePressure;
	UPROPERTY(BlueprintReadOnly)
		float venousOxygenPressure;
};

USTRUCT(BlueprintType)
struct FBiogearsInflamatoryRespose {
	GENERATED_BODY()
public:
	//Inflamatory Response
	UPROPERTY(BlueprintReadOnly)
		float LocalPathogen;
	UPROPERTY(BlueprintReadOnly)
		float LocalMacrophage;
	UPROPERTY(BlueprintReadOnly)
		float LocalNeutrophil;
	UPROPERTY(BlueprintReadOnly)
		float LocalBarrier;
	UPROPERTY(BlueprintReadOnly)
		float BloodPathogen;
	UPROPERTY(BlueprintReadOnly)
		float Trauma;
	UPROPERTY(BlueprintReadOnly)
		float MacrophageResting;
	UPROPERTY(BlueprintReadOnly)
		float MacrophageActive;
	UPROPERTY(BlueprintReadOnly)
		float NeutrophilResting;
	UPROPERTY(BlueprintReadOnly)
		float NeutrophilActive;
	UPROPERTY(BlueprintReadOnly)
		float InducibleNOSPre;
	UPROPERTY(BlueprintReadOnly)
		float InducibleNOS;
	UPROPERTY(BlueprintReadOnly)
		float ConstitutiveNOS;
	UPROPERTY(BlueprintReadOnly)
		float Nitrate;
	UPROPERTY(BlueprintReadOnly)
		float NitricOxide;
	UPROPERTY(BlueprintReadOnly)
		float TumorNecrosisFactor;
	UPROPERTY(BlueprintReadOnly)
		float Interleukin6;
	UPROPERTY(BlueprintReadOnly)
		float Interleukin10;
	UPROPERTY(BlueprintReadOnly)
		float Interleukin12;
	UPROPERTY(BlueprintReadOnly)
		float Catecholamines;
	UPROPERTY(BlueprintReadOnly)
		float TissueIntegrity;
};

USTRUCT(BlueprintType)
struct FBiogearsCardiovascular {
	GENERATED_BODY()
public:
	//Cardiovascular
	UPROPERTY(BlueprintReadOnly)
		float arterialPressure;
	UPROPERTY(BlueprintReadOnly)
		float bloodVolume;
	UPROPERTY(BlueprintReadOnly)
		float cardiacIndex;
	UPROPERTY(BlueprintReadOnly)
		float cardiacOutput;
	UPROPERTY(BlueprintReadOnly)
		float centralVenousPressure;
	UPROPERTY(BlueprintReadOnly)
		float cerebralBloodFlow;
	UPROPERTY(BlueprintReadOnly)
		float cerebralPerfusionPressure;
	UPROPERTY(BlueprintReadOnly)
		float diastolicArterialPressure;
	UPROPERTY(BlueprintReadOnly)
		float heartEjectionFraction;
	UPROPERTY(BlueprintReadOnly)
		float heartRate;
	UPROPERTY(BlueprintReadOnly)
		float heartStrokeVolume;
	UPROPERTY(BlueprintReadOnly)
		float intracranialPressure;
	UPROPERTY(BlueprintReadOnly)
		float meanArterialPressure;
	UPROPERTY(BlueprintReadOnly)
		float meanArterialCarbonDioxidePartialPressure;
	UPROPERTY(BlueprintReadOnly)
		float meanArterialCarbonDioxidePartialPressureDelta;
	UPROPERTY(BlueprintReadOnly)
		float meanCentralVenousPressure;
	UPROPERTY(BlueprintReadOnly)
		float meanSkinFlow;
	UPROPERTY(BlueprintReadOnly)
		float pulmonaryArterialPressure;
	UPROPERTY(BlueprintReadOnly)
		float pulmonaryCapillariesWedgePressure;
	UPROPERTY(BlueprintReadOnly)
		float pulmonaryDiastolicArterialPressure;
	UPROPERTY(BlueprintReadOnly)
		float pulmonaryMeanArterialPressure;
	UPROPERTY(BlueprintReadOnly)
		float pulmonaryMeanCapillaryFlow;
	UPROPERTY(BlueprintReadOnly)
		float pulmonaryMeanShuntFlow;
	UPROPERTY(BlueprintReadOnly)
		float pulmonarySystolicArterialPressure;
	UPROPERTY(BlueprintReadOnly)
		float pulmonaryVascularResistance;
	UPROPERTY(BlueprintReadOnly)
		float pulmonaryVascularResistanceIndex;
	UPROPERTY(BlueprintReadOnly)
		float pulsePressure;
	UPROPERTY(BlueprintReadOnly)
		float systemicVascularResistance;
	UPROPERTY(BlueprintReadOnly)
		float systolicArterialPressure;

public:
};

USTRUCT(BlueprintType)
struct FBiogearsDrugs {
	GENERATED_BODY()
public:
	//Drugs
	UPROPERTY(BlueprintReadOnly)
		float bronchodilationLevel;
	UPROPERTY(BlueprintReadOnly)
		float heartRateChange;
	UPROPERTY(BlueprintReadOnly)
		float hemorrhageChange;
	UPROPERTY(BlueprintReadOnly)
		float meanBloodPressureChange;
	UPROPERTY(BlueprintReadOnly)
		float neuromuscularBlockLevel;
	UPROPERTY(BlueprintReadOnly)
		float pulsePressureChange;
	UPROPERTY(BlueprintReadOnly)
		float respirationRateChange;
	UPROPERTY(BlueprintReadOnly)
		float sedationLevel;
	UPROPERTY(BlueprintReadOnly)
		float tidalVolumeChange;
	UPROPERTY(BlueprintReadOnly)
		float tubularPermeabilityChange;
	UPROPERTY(BlueprintReadOnly)
		float centralNervousResponse;
};

USTRUCT(BlueprintType)
struct FBiogearsEndocrine {
	GENERATED_BODY()

public:
	//Endocrine
	UPROPERTY(BlueprintReadOnly)
		float insulinSynthesisRate;
	UPROPERTY(BlueprintReadOnly)
		float glucagonSynthesisRate;
};

USTRUCT(BlueprintType)
struct FBiogearsEnergy {
	GENERATED_BODY()
public:
	//Energy
	UPROPERTY(BlueprintReadOnly)
		float achievedExerciseLevel;
	UPROPERTY(BlueprintReadOnly)
		float chlorideLostToSweat;
	UPROPERTY(BlueprintReadOnly)
		float coreTemperature;
	UPROPERTY(BlueprintReadOnly)
		float creatinineProductionRate;
	UPROPERTY(BlueprintReadOnly)
		float exerciseMeanArterialPressureDelta;
	UPROPERTY(BlueprintReadOnly)
		float fatigueLevel;
	UPROPERTY(BlueprintReadOnly)
		float lactateProductionRate;
	UPROPERTY(BlueprintReadOnly)
		float potassiumLostToSweat;
	UPROPERTY(BlueprintReadOnly)
		float skinTemperature;
	UPROPERTY(BlueprintReadOnly)
		float sodiumLostToSweat;
	UPROPERTY(BlueprintReadOnly)
		float sweatRate;
	UPROPERTY(BlueprintReadOnly)
		float totalMetabolicRate;
	UPROPERTY(BlueprintReadOnly)
		float totalWorkRateLevel;
};

USTRUCT(BlueprintType)
struct FBiogearsGastrointestinal {
	GENERATED_BODY()
public:
	//Gastronintestinal
	UPROPERTY(BlueprintReadOnly)
		float chymeAbsorptionRate;
	UPROPERTY(BlueprintReadOnly)
		float stomachContents_calcium;
	UPROPERTY(BlueprintReadOnly)
		float stomachContents_carbohydrates;
	UPROPERTY(BlueprintReadOnly)
		float stomachContents_carbohydrateDigationRate;
	UPROPERTY(BlueprintReadOnly)
		float stomachContents_fat;
	UPROPERTY(BlueprintReadOnly)
		float stomachContents_fatDigtationRate;
	UPROPERTY(BlueprintReadOnly)
		float stomachContents_protien;
	UPROPERTY(BlueprintReadOnly)
		float stomachContents_protienDigtationRate;
	UPROPERTY(BlueprintReadOnly)
		float stomachContents_sodium;
	UPROPERTY(BlueprintReadOnly)
		float stomachContents_water;
};

USTRUCT(BlueprintType)
struct FBiogearsHepatic {
	GENERATED_BODY()
public:
	//Heptic
	UPROPERTY(BlueprintReadOnly)
		float ketoneproductionRate;
	UPROPERTY(BlueprintReadOnly)
		float hepaticGluconeogenesisRate;
};

USTRUCT(BlueprintType)
struct FBiogearsNervous {
	GENERATED_BODY()
public:
	//Nervous
	UPROPERTY(BlueprintReadOnly)
		float baroreceptorHeartRateScale;
	UPROPERTY(BlueprintReadOnly)
		float baroreceptorHeartElastanceScale;
	UPROPERTY(BlueprintReadOnly)
		float baroreceptorResistanceScale;
	UPROPERTY(BlueprintReadOnly)
		float baroreceptorComplianceScale;
	UPROPERTY(BlueprintReadOnly)
		float chemoreceptorHeartRateScale;
	UPROPERTY(BlueprintReadOnly)
		float chemoreceptorHeartElastanceScale;
	UPROPERTY(BlueprintReadOnly)
		float painVisualAnalogueScale;
	UPROPERTY(BlueprintReadOnly)
		float leftEyePupillaryResponse;
	UPROPERTY(BlueprintReadOnly)
		float rightEyePupillaryResponse;
};

USTRUCT(BlueprintType)
struct FBiogearsRenal {
	GENERATED_BODY()
public:
	//Renal
	UPROPERTY(BlueprintReadOnly)
		float glomerularFiltrationRate;
	UPROPERTY(BlueprintReadOnly)
		float filtrationFraction;
	UPROPERTY(BlueprintReadOnly)
		float leftAfferentArterioleResistance;
	UPROPERTY(BlueprintReadOnly)
		float leftBowmansCapsulesHydrostaticPressure;
	UPROPERTY(BlueprintReadOnly)
		float leftBowmansCapsulesOsmoticPressure;
	UPROPERTY(BlueprintReadOnly)
		float leftEfferentArterioleResistance;
	UPROPERTY(BlueprintReadOnly)
		float leftGlomerularCapillariesHydrostaticPressure;
	UPROPERTY(BlueprintReadOnly)
		float leftGlomerularCapillariesOsmoticPressure;
	UPROPERTY(BlueprintReadOnly)
		float leftGlomerularFiltrationCoefficient;
	UPROPERTY(BlueprintReadOnly)
		float leftGlomerularFiltrationRate;
	UPROPERTY(BlueprintReadOnly)
		float leftGlomerularFiltrationSurfaceArea;
	UPROPERTY(BlueprintReadOnly)
		float leftGlomerularFluidPermeability;
	UPROPERTY(BlueprintReadOnly)
		float leftFiltrationFraction;
	UPROPERTY(BlueprintReadOnly)
		float leftNetFiltrationPressure;
	UPROPERTY(BlueprintReadOnly)
		float leftNetReabsorptionPressure;
	UPROPERTY(BlueprintReadOnly)
		float leftPeritubularCapillariesHydrostaticPressure;
	UPROPERTY(BlueprintReadOnly)
		float leftPeritubularCapillariesOsmoticPressure;
	UPROPERTY(BlueprintReadOnly)
		float leftReabsorptionFiltrationCoefficient;
	UPROPERTY(BlueprintReadOnly)
		float leftReabsorptionRate;
	UPROPERTY(BlueprintReadOnly)
		float leftTubularReabsorptionFiltrationSurfaceArea;
	UPROPERTY(BlueprintReadOnly)
		float leftTubularReabsorptionFluidPermeability;
	UPROPERTY(BlueprintReadOnly)
		float leftTubularHydrostaticPressure;
	UPROPERTY(BlueprintReadOnly)
		float leftTubularOsmoticPressure;
	UPROPERTY(BlueprintReadOnly)
		float renalBloodFlow;
	UPROPERTY(BlueprintReadOnly)
		float renalPlasmaFlow;
	UPROPERTY(BlueprintReadOnly)
		float renalVascularResistance;
	UPROPERTY(BlueprintReadOnly)
		float rightAfferentArterioleResistance;
	UPROPERTY(BlueprintReadOnly)
		float rightBowmansCapsulesHydrostaticPressure;
	UPROPERTY(BlueprintReadOnly)
		float rightBowmansCapsulesOsmoticPressure;
	UPROPERTY(BlueprintReadOnly)
		float rightEfferentArterioleResistance;
	UPROPERTY(BlueprintReadOnly)
		float rightGlomerularCapillariesHydrostaticPressure;
	UPROPERTY(BlueprintReadOnly)
		float rightGlomerularCapillariesOsmoticPressure;
	UPROPERTY(BlueprintReadOnly)
		float rightGlomerularFiltrationCoefficient;
	UPROPERTY(BlueprintReadOnly)
		float rightGlomerularFiltrationRate;
	UPROPERTY(BlueprintReadOnly)
		float rightGlomerularFiltrationSurfaceArea;
	UPROPERTY(BlueprintReadOnly)
		float rightGlomerularFluidPermeability;
	UPROPERTY(BlueprintReadOnly)
		float rightFiltrationFraction;
	UPROPERTY(BlueprintReadOnly)
		float rightNetFiltrationPressure;
	UPROPERTY(BlueprintReadOnly)
		float rightNetReabsorptionPressure;
	UPROPERTY(BlueprintReadOnly)
		float rightPeritubularCapillariesHydrostaticPressure;
	UPROPERTY(BlueprintReadOnly)
		float rightPeritubularCapillariesOsmoticPressure;
	UPROPERTY(BlueprintReadOnly)
		float rightReabsorptionFiltrationCoefficient;
	UPROPERTY(BlueprintReadOnly)
		float rightReabsorptionRate;
	UPROPERTY(BlueprintReadOnly)
		float rightTubularReabsorptionFiltrationSurfaceArea;
	UPROPERTY(BlueprintReadOnly)
		float rightTubularReabsorptionFluidPermeability;
	UPROPERTY(BlueprintReadOnly)
		float rightTubularHydrostaticPressure;
	UPROPERTY(BlueprintReadOnly)
		float rightTubularOsmoticPressure;
	UPROPERTY(BlueprintReadOnly)
		float urinationRate;
	UPROPERTY(BlueprintReadOnly)
		float urineOsmolality;
	UPROPERTY(BlueprintReadOnly)
		float urineOsmolarity;
	UPROPERTY(BlueprintReadOnly)
		float urineProductionRate;
	UPROPERTY(BlueprintReadOnly)
		float meanUrineOutput;
	UPROPERTY(BlueprintReadOnly)
		float urineSpecificGravity;
	UPROPERTY(BlueprintReadOnly)
		float urineVolume;
	UPROPERTY(BlueprintReadOnly)
		float urineUreaNitrogenConcentration;
};

USTRUCT(BlueprintType)
struct FBiogearsRespiratory
{
	GENERATED_BODY()
public:
	//Respiratory
	UPROPERTY(BlueprintReadOnly)
		float alveolarArterialGradient;
	UPROPERTY(BlueprintReadOnly)
		float carricoIndex;
	UPROPERTY(BlueprintReadOnly)
		float endTidalCarbonDioxideFraction;
	UPROPERTY(BlueprintReadOnly)
		float endTidalCarbonDioxidePressure;
	UPROPERTY(BlueprintReadOnly)
		float expiratoryFlow;
	UPROPERTY(BlueprintReadOnly)
		float inspiratoryExpiratoryRatio;
	UPROPERTY(BlueprintReadOnly)
		float inspiratoryFlow;
	UPROPERTY(BlueprintReadOnly)
		float pulmonaryCompliance;
	UPROPERTY(BlueprintReadOnly)
		float pulmonaryResistance;
	UPROPERTY(BlueprintReadOnly)
		float respirationDriverPressure;
	UPROPERTY(BlueprintReadOnly)
		float respirationMusclePressure;
	UPROPERTY(BlueprintReadOnly)
		float respirationRate;
	UPROPERTY(BlueprintReadOnly)
		float specificVentilation;
	UPROPERTY(BlueprintReadOnly)
		float targetPulmonaryVentilation;
	UPROPERTY(BlueprintReadOnly)
		float tidalVolume;
	UPROPERTY(BlueprintReadOnly)
		float totalAlveolarVentilation;
	UPROPERTY(BlueprintReadOnly)
		float totalDeadSpaceVentilation;
	UPROPERTY(BlueprintReadOnly)
		float totalLungVolume;
	UPROPERTY(BlueprintReadOnly)
		float totalPulmonaryVentilation;
	UPROPERTY(BlueprintReadOnly)
		float transpulmonaryPressure;
	USTRUCT(BlueprintType)
};

USTRUCT(BlueprintType)
struct FBiogearsTissue
{
	GENERATED_BODY()
public:
	//Tissue
	UPROPERTY(BlueprintReadOnly)
		float carbonDioxideProductionRate;
	UPROPERTY(BlueprintReadOnly)
		float dehydrationFraction;
	UPROPERTY(BlueprintReadOnly)
		float extracellularFluidVolume;
	UPROPERTY(BlueprintReadOnly)
		float extravascularFluidVolume;
	UPROPERTY(BlueprintReadOnly)
		float intracellularFluidPH;
	UPROPERTY(BlueprintReadOnly)
		float intracellularFluidVolume;
	UPROPERTY(BlueprintReadOnly)
		float totalBodyFluidVolume;
	UPROPERTY(BlueprintReadOnly)
		float oxygenConsumptionRate;
	UPROPERTY(BlueprintReadOnly)
		float respiratoryExchangeRatio;
	UPROPERTY(BlueprintReadOnly)
		float liverInsulinSetPoint;
	UPROPERTY(BlueprintReadOnly)
		float liverGlucagonSetPoint;
	UPROPERTY(BlueprintReadOnly)
		float muscleInsulinSetPoint;
	UPROPERTY(BlueprintReadOnly)
		float muscleGlucagonSetPoint;
	UPROPERTY(BlueprintReadOnly)
		float fatInsulinSetPoint;
	UPROPERTY(BlueprintReadOnly)
		float fatGlucagonSetPoint;
	UPROPERTY(BlueprintReadOnly)
		float liverGlycogen;
	UPROPERTY(BlueprintReadOnly)
		float muscleGlycogen;
	UPROPERTY(BlueprintReadOnly)
		float storedProtein;
	UPROPERTY(BlueprintReadOnly)
		float storedFat;
};

USTRUCT(BlueprintType)
struct FBiogearsMetrics
{
	GENERATED_BODY()
public:

	UPROPERTY(BlueprintReadOnly)
		float simulationTime;
	UPROPERTY(BlueprintReadOnly)
		float timeStep;

	UPROPERTY(BlueprintReadOnly)
		FBiogearsBloodChemistry bloodChemistry;
	UPROPERTY(BlueprintReadOnly)
		bool hasInflammatoryResponse;
	UPROPERTY(BlueprintReadOnly)
		FBiogearsInflamatoryRespose inflamatroyReponse;
	UPROPERTY(BlueprintReadOnly)
		FBiogearsCardiovascular cardiovascular;
	UPROPERTY(BlueprintReadOnly)
		FBiogearsDrugs drugs;
	UPROPERTY(BlueprintReadOnly)
		FBiogearsEndocrine endocrine;
	UPROPERTY(BlueprintReadOnly)
		FBiogearsEnergy energy;
	UPROPERTY(BlueprintReadOnly)
		FBiogearsGastrointestinal gastrointestinal;
	UPROPERTY(BlueprintReadOnly)
		FBiogearsHepatic hepatic;
	UPROPERTY(BlueprintReadOnly)
		FBiogearsNervous nervous;
	UPROPERTY(BlueprintReadOnly)
		FBiogearsRenal renal;
	UPROPERTY(BlueprintReadOnly)
		FBiogearsRespiratory respiratory;
	UPROPERTY(BlueprintReadOnly)
		FBiogearsTissue tissue;

};

USTRUCT(BlueprintType)
struct FBiogearsState
{
	GENERATED_BODY()
public:
	UPROPERTY(BlueprintReadOnly)
		FString name;
	UPROPERTY(BlueprintReadOnly, Meta = (DisplayName = "IsPatientAlive"))
		bool living;
	UPROPERTY(BlueprintReadOnly, Meta = (DisplayName = "IsPatientTacycardic"))
		bool tacycardia;

	UPROPERTY(BlueprintReadOnly)
		float age_yr;
	UPROPERTY(BlueprintReadOnly)
		float height_cm;
	UPROPERTY(BlueprintReadOnly)
		EGender gender;
	UPROPERTY(BlueprintReadOnly)
		float weight_kg;
	UPROPERTY(BlueprintReadOnly)
		float body_surface_area_m_sq;
	UPROPERTY(BlueprintReadOnly)
		float body_mass_index_kg_per_m_sq;
	UPROPERTY(BlueprintReadOnly)
		float body_fat_pct;
	UPROPERTY(BlueprintReadOnly)
		EExerciseState exercise_state;

};

USTRUCT(BlueprintType)
struct FBiogearsConditions
{
	GENERATED_BODY()

public:
	UPROPERTY(BlueprintReadOnly)
		bool diabieties = false;
};

USTRUCT(BlueprintType)
struct FBiogearsSubstanceConcentration
{
	GENERATED_BODY()

public:
	UPROPERTY(BlueprintReadWrite)
		FString name = TEXT("Unknown");
	float   concentration_g_per_l = 0.0;
};


USTRUCT(BlueprintType)
struct FBiogearsCompound
{
	GENERATED_BODY()

public:
	UPROPERTY(BlueprintReadWrite)
		FString name = TEXT("Unknown");
	UPROPERTY(BlueprintReadWrite)
		TArray<FBiogearsSubstanceConcentration> concentrations;
};

USTRUCT(BlueprintType)
struct 	FBiogearsUrineAnalysis {
	GENERATED_BODY()

public:
	UPROPERTY(BlueprintReadOnly)
		EUrineColor color;
	UPROPERTY(BlueprintReadOnly)
		EClarityIndicator appearance;
	UPROPERTY(BlueprintReadOnly)
		EPresenceIndicator glucose;
	UPROPERTY(BlueprintReadOnly)
		EPresenceIndicator ketone;
	UPROPERTY(BlueprintReadOnly)
		EPresenceIndicator blood;
	UPROPERTY(BlueprintReadOnly)
		EPresenceIndicator protien;
	UPROPERTY(BlueprintReadOnly)
		EPresenceIndicator nitrite;
	UPROPERTY(BlueprintReadOnly)
		EPresenceIndicator leukocyteEsterase;

	UPROPERTY(BlueprintReadOnly)
		float bilirubin;
	UPROPERTY(BlueprintReadOnly)
		float specificgravity;
	UPROPERTY(BlueprintReadOnly)
		float ph;
	UPROPERTY(BlueprintReadOnly)
		float urobilinogen;
};

USTRUCT(BlueprintType)
struct 	FBiogearsMetabolicPanel {
	GENERATED_BODY()

public:
	UPROPERTY(BlueprintReadOnly)
		float albumin;
	UPROPERTY(BlueprintReadOnly)
		float ALP;
	UPROPERTY(BlueprintReadOnly)
		float ALT;
	UPROPERTY(BlueprintReadOnly)
		float AST;
	UPROPERTY(BlueprintReadOnly)
		float BUN;
	UPROPERTY(BlueprintReadOnly)
		float calcium;
	UPROPERTY(BlueprintReadOnly)
		float chlordide;
	UPROPERTY(BlueprintReadOnly)
		float co2;
	UPROPERTY(BlueprintReadOnly)
		float creatine;
	UPROPERTY(BlueprintReadOnly)
		float glucose;
	UPROPERTY(BlueprintReadOnly)
		float potassium;
	UPROPERTY(BlueprintReadOnly)
		float sodium;
	UPROPERTY(BlueprintReadOnly)
		float bilirubin;
	UPROPERTY(BlueprintReadOnly)
		float protien;
};

USTRUCT(BlueprintType)
struct 	FBiogearsBloodCount {
	GENERATED_BODY()

public:
	UPROPERTY(BlueprintReadOnly)
		float hematocrit;
	UPROPERTY(BlueprintReadOnly)
		float hemoglobin;
	UPROPERTY(BlueprintReadOnly)
		float platelet_count;
	UPROPERTY(BlueprintReadOnly)
		float mean_corpusular_hemoglobin;
	UPROPERTY(BlueprintReadOnly)
		float mean_corpuscular_hemoglobin_concentration;
	UPROPERTY(BlueprintReadOnly)
		float mean_corpuscular_volume;
	UPROPERTY(BlueprintReadOnly)
		float red_blood_cell_count;
	UPROPERTY(BlueprintReadOnly)
		float white_blood_cell_count;
};

USTRUCT(BlueprintType)
struct 	FBiogearsPulmonaryTest {
	GENERATED_BODY()

public:
	UPROPERTY(BlueprintReadOnly)
		float number_of_plot_points;
	UPROPERTY(BlueprintReadOnly)
		float expiratory_reserve_volume;
	UPROPERTY(BlueprintReadOnly)
		float forced_vital_capacity;
	UPROPERTY(BlueprintReadOnly)
		float forced_expiratory_volume;
	UPROPERTY(BlueprintReadOnly)
		float functional_residual_capacity;
	UPROPERTY(BlueprintReadOnly)
		float inspiratory_capacity;
	UPROPERTY(BlueprintReadOnly)
		float inspiratory_reserve_volume;
	UPROPERTY(BlueprintReadOnly)
		float maximum_volunatary_ventilation;
	UPROPERTY(BlueprintReadOnly)
		float peek_expitatory_flow;
	UPROPERTY(BlueprintReadOnly)
		float residual_volume;
	UPROPERTY(BlueprintReadOnly)
		float slow_vital_capacity;
	UPROPERTY(BlueprintReadOnly)
		float total_lung_capacity;
	UPROPERTY(BlueprintReadOnly)
		float vital_capacity;
	//TODO: Support Lung Volume Plot
	//float lung_volume_plot;
};

USTRUCT(BlueprintType)
struct 	FUrinalysisMicroscopic {
	GENERATED_BODY()

public:
	UPROPERTY(BlueprintReadOnly)
	EMicroscopicOpservationType type;
	UPROPERTY(BlueprintReadOnly)
	float red_blood_cells;
	UPROPERTY(BlueprintReadOnly)
	float white_blood_cells;
	UPROPERTY(BlueprintReadOnly)
	EMicroscopicObservationAmount epithelia_cells;
	UPROPERTY(BlueprintReadOnly)
	float casts;
	UPROPERTY(BlueprintReadOnly)
	EMicroscopicObservationAmount crystals;
	UPROPERTY(BlueprintReadOnly)
	EMicroscopicObservationAmount bacteria;
	UPROPERTY(BlueprintReadOnly)
	EMicroscopicObservationAmount trichomonads;
	UPROPERTY(BlueprintReadOnly)
	EMicroscopicObservationAmount yeast;
};
