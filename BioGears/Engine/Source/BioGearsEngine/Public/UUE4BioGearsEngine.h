#pragma once

#include <memory>
#include <chrono>

#include <Misc/Paths.h>
#include <Templates/UniquePtr.h>


#include "UBioGearsLogger.h"
#include "UBioGearsEnums.h"
#include "UBioGearsStructs.h"

#include <thread>
#include <memory>
#include <mutex>
#include <atomic>

#include <biogears/cdm/scenario/SEAction.h>
#include <biogears/engine/BioGearsPhysiologyEngine.h>
#include <biogears/engine/controller/BioGears.h>
#include <biogears/engine/controller/BioGears.h>
#include <biogears/engine/controller/BioGearsEngine.h>
#include <biogears/cdm/properties/SEScalarTypes.h>

#include "UUE4BioGearsEngine.generated.h"

DECLARE_DYNAMIC_MULTICAST_DELEGATE_OneParam(FOnUrineAnalysisComplete , FBiogearsUrineAnalysis, results);
DECLARE_DYNAMIC_MULTICAST_DELEGATE_OneParam(FOnMetabolicPanelComplete, FBiogearsMetabolicPanel, results);
DECLARE_DYNAMIC_MULTICAST_DELEGATE_OneParam(FOnBloodCountComplete    , FBiogearsBloodCount, results);
DECLARE_DYNAMIC_MULTICAST_DELEGATE_OneParam(FOnPulmonaryTextComplete , FBiogearsPulmonaryTest, results);


UCLASS(BlueprintType, Config = "BioGears", meta = (DisplayName = "BioGearsEngine"))
class BIOGEARSENGINE_API UUE4BioGearsEngine : public UObject {
	GENERATED_BODY()
public:
	UUE4BioGearsEngine();

	UFUNCTION(BlueprintCallable, Category = "Physiology", meta = (DisplayName = "Physiology::GetSimulationTime"))
	void initialize_here(FString name);
	UFUNCTION(BlueprintCallable, Category = "Physiology", meta = (DisplayName = "Physiology::GetSimulationTime"))
	void initialize_with_path(FString dataRoot, FString name);
	UFUNCTION(BlueprintCallable, Category = "Physiology", meta = (DisplayName = "Physiology::GetSimulationTime"))
	void initialize_with_logger(FString dataRoot, UBioGearsLogger* logger);

	~UUE4BioGearsEngine() override;


	UFUNCTION(BlueprintCallable, Category = "Physiology", meta = (DisplayName = "Physiology::GetSimulationTime"))
	float getSimulationTime() const;
	UFUNCTION(BlueprintCallable, Category = "Physiology", meta = (DisplayName = "Physiology::GetMetrics"))
	FBiogearsMetrics    getMetrics() const;
	UFUNCTION(BlueprintCallable, Category = "Physiology", meta = (DisplayName = "Physiology::GetConditions"))
	FBiogearsConditions getConditions() const;
	UFUNCTION(BlueprintCallable, Category = "Physiology", meta = (DisplayName = "Physiology::GetState"))
	FBiogearsState      getState() const;

	UFUNCTION(BlueprintCallable, Category = "Physiology|Control", meta = (DisplayName = "Physiology::LoadPatient"))
	bool load_patient(FString patient);
	UFUNCTION(BlueprintCallable, Category = "Physiology|Control", meta = (DisplayName = "Physiology::LoadPatientState"))
	bool load_patient_state(FString state);
	
	UFUNCTION(BlueprintCallable, Category = "Physiology|Control", meta = (DisplayName = "Physiology::AdvanceTime"))
	void advance_time(float seconds);


	UFUNCTION(BlueprintCallable, Category = "Physiology", meta = (DisplayName = "Physiology::IsReady"))
	bool isReady() const;

	UFUNCTION(BlueprintCallable, Category = "Physiology|Action", meta = (DisplayName = "Physiology::Action::Urinate"))
	bool action_urinate();
	UFUNCTION(BlueprintCallable, Category = "Physiology|Action", meta = (DisplayName = "Physiology::Action::EnvironmentChange"))
	bool action_env_change(FEnvironmentalConditions conditons);
	UFUNCTION(BlueprintCallable, Category = "Physiology|Action", meta = (DisplayName = "Physiology::Action::Tourniquet"))
	bool action_apply_tourniquet(EExtremity limb, ETourniquet application);
	UFUNCTION(BlueprintCallable, Category = "Physiology|Action", meta = (DisplayName = "Physiology::Action::Hemorrhage"))
	bool action_apply_hemorrhage(EExtremity limb, float flowrate_ml_Per_min);
	UFUNCTION(BlueprintCallable, Category = "Physiology|Action", meta = (DisplayName = "Physiology::Action::TensionPnuemothorax"))
	bool action_tension_pneumothorax(ESide side , EPneumothorax type, float severity_0_to_1);
	UFUNCTION(BlueprintCallable, Category = "Physiology|Action", meta = (DisplayName = "Physiology::Action::NeedleDecompression"))
	bool action_needle_decompression(ESide side, bool active);
	UFUNCTION(BlueprintCallable, Category = "Physiology|Action", meta = (DisplayName = "Physiology::Action::O2Mask"))
	bool action_o2_mask(float o2_fraction, float o2_volume1, float o2_volume2);
	UFUNCTION(BlueprintCallable, Category = "Physiology|Action", meta = (DisplayName = "Physiology::Action::ActionInfection"))
	bool action_infection(EInfectionSeverity severity, FString location, float mic_mg_Per_l);
	UFUNCTION(BlueprintCallable, Category = "Physiology|Action", meta = (DisplayName = "Physiology::Action::BloodTransfusion"))
	bool action_bloodtransfusion(EBloodType type, float blood_volume_ml, float flowrate_ml_Per_min);
	UFUNCTION(BlueprintCallable, Category = "Physiology|Action", meta = (DisplayName = "Physiology::Action::ThermalBlanket"))
	bool action_thermal_blanket(float watt, float surface_area_fraction);
	UFUNCTION(BlueprintCallable, Category = "Physiology|Action", meta = (DisplayName = "Physiology::Action::PainStimulus"))
	bool action_pain_stimulus(ECompartment compartment, float severity);
	UFUNCTION(BlueprintCallable, Category = "Physiology|Action", meta = (DisplayName = "Physiology::Action::SubstanceInfusion"))
	bool action_substanceInfusion(EIvSubstance substance, float substance_volume_ml, float flowrate_ml_Per_min);
	UFUNCTION(BlueprintCallable, Category = "Physiology|Action", meta = (DisplayName = "Physiology::Action::SubstanceCompoundInfusion"))
	bool action_substanceCompoundInfusion(EIvCompound compound, float compound_volume_ml, float flowrate_ml_Per_min);
	UFUNCTION(BlueprintCallable, Category = "Physiology|Action", meta = (DisplayName = "Physiology::Action::OralSubstanceAdministration"))
	bool action_oralSubstanceAdministration(EOralSubstance type, EOralAbsorption route, float dosage_mg);
	
	//Query Actions
	UFUNCTION(BlueprintCallable, Category = "Physiology|Panel", meta = (DisplayName = "Physiology::Panel::UrineAnalyis"))
	bool get_urine_analysis();
	UFUNCTION(BlueprintCallable, Category = "Physiology|Panel", meta = (DisplayName = "Physiology::Panel::ComprehensiveMetabolicPanel"))
	bool get_comprehensive_metabolic_panel();
	UFUNCTION(BlueprintCallable, Category = "Physiology|Panel", meta = (DisplayName = "Physiology::Panel::CompleteBloodCount"))
	bool get_complete_blood_count();
	UFUNCTION(BlueprintCallable, Category = "Physiology|Panel", meta = (DisplayName = "Physiology::Panel::PulmonaryFunctionTest"))
	bool get_pulmonary_function_test ();
	

	//TODO: I want to play with the concept of managing environments for quick change
	//TODO: If this works I would like to do it with patients, substances and such
	UFUNCTION(BlueprintCallable, Category = "Physiology|Panel", meta = (DisplayName = "Physiology::EnvirEnvironmentoment::Create"))
	bool new_environment(FString key, FEnvironmentalConditions conditions);
	UFUNCTION(BlueprintCallable, Category = "Physiology|Panel", meta = (DisplayName = "Physiology::Environment::Set"))
	bool set_environment(FString key);

	//TODO: Add Custom Substances to the engine while running (You should never change an existing compound and we will make sure of that)
	UFUNCTION(BlueprintCallable, Category = "Physiology|Panel", meta = (DisplayName = "Physiology::CustomCompound::Create"))
		bool new_custom_compound(FString key, FBiogearsCompound compound);
	UFUNCTION(BlueprintCallable, Category = "Physiology|Panel", meta = (DisplayName = "Physiology::CustomCompoun::Infusion"))
		bool custom_compound_infusion(FString key, float substance_volume_ml, float flowrate_ml_Per_min);
	

	UPROPERTY(BlueprintAssignable, Category="Events")
		FOnUrineAnalysisComplete on_urine_analysis_completed;
	UPROPERTY(BlueprintAssignable, Category = "Events")
		FOnMetabolicPanelComplete on_metabolic_panel_completed;
	UPROPERTY(BlueprintAssignable, Category = "Events")
		FOnBloodCountComplete on_blood_count_completed;
	UPROPERTY(BlueprintAssignable, Category = "Events")
		FOnPulmonaryTextComplete on_pulmonary_test_completed;

	//Destructor Functions
	void BeginDestroy() override;
	bool IsReadyForFinishDestroy() override;
	void FinishDestroy() override;
private:

		UBioGearsLogger* _logger;     //<! Only Used if logger not passed to system
		TUniquePtr<biogears::BioGearsEngine> _bg;

		std::mutex _mutex;
		std::string _name;
		std::string _log_name;
		std::string _log_root;
		std::string _data_root;

		FBiogearsMetrics _metrics;
		FBiogearsConditions _conditions;
		FBiogearsState _state;

		std::atomic_bool _ready{ false };

		biogears::SEScalar* _arterialBloodPH;
		biogears::SEScalar* _arterialBloodPHBaseline;
		biogears::SEUnitScalar* _bloodDensity;
		biogears::SEUnitScalar* _bloodSpecificHeat;
		biogears::SEUnitScalar* _bloodUreaNitrogenConcentration;
		biogears::SEScalar* _carbonDioxideSaturation;
		biogears::SEScalar* _carbonMonoxideSaturation;
		biogears::SEScalar* _hematocrit;
		biogears::SEUnitScalar* _hemoglobinContent;
		biogears::SEScalar* _oxygenSaturation;
		biogears::SEUnitScalar* _phosphate;
		biogears::SEUnitScalar* _plasmaVolume;
		biogears::SEScalar* _pulseOximetry;
		biogears::SEUnitScalar* _redBloodCellAcetylcholinesterase;
		biogears::SEUnitScalar* _redBloodCellCount;
		biogears::SEScalar* _shuntFraction;
		biogears::SEUnitScalar* _strongIonDifference;
		biogears::SEUnitScalar* _totalBilirubin;
		biogears::SEUnitScalar* _totalProteinConcentration;
		biogears::SEScalar* _venousBloodPH;
		biogears::SEScalar* _volumeFractionNeutralPhospholipidInPlasma;
		biogears::SEScalar* _volumeFractionNeutralLipidInPlasma;
		biogears::SEUnitScalar* _arterialCarbonDioxidePressure;
		biogears::SEUnitScalar* _arterialOxygenPressure;
		biogears::SEUnitScalar* _pulmonaryArterialCarbonDioxidePressure;
		biogears::SEUnitScalar* _pulmonaryArterialOxygenPressure;
		biogears::SEUnitScalar* _pulmonaryVenousCarbonDioxidePressure;
		biogears::SEUnitScalar* _pulmonaryVenousOxygenPressure;
		biogears::SEUnitScalar* _venousCarbonDioxidePressure;
		biogears::SEUnitScalar* _venousOxygenPressure;
		bool _inflammatoryResponse;

		biogears::SEScalar* _inflammatoryResponseLocalPathogen;
		biogears::SEScalar* _inflammatoryResponseLocalMacrophage;
		biogears::SEScalar* _inflammatoryResponseLocalNeutrophil;
		biogears::SEScalar* _inflammatoryResponseLocalBarrier;
		biogears::SEScalar* _inflammatoryResponseBloodPathogen;
		biogears::SEScalar* _inflammatoryResponseTrauma;
		biogears::SEScalar* _inflammatoryResponseMacrophageResting;
		biogears::SEScalar* _inflammatoryResponseMacrophageActive;
		biogears::SEScalar* _inflammatoryResponseNeutrophilResting;
		biogears::SEScalar* _inflammatoryResponseNeutrophilActive;
		biogears::SEScalar* _inflammatoryResponseInducibleNOSPre;
		biogears::SEScalar* _inflammatoryResponseInducibleNOS;
		biogears::SEScalar* _inflammatoryResponseConstitutiveNOS;
		biogears::SEScalar* _inflammatoryResponseNitrate;
		biogears::SEScalar* _inflammatoryResponseNitricOxide;
		biogears::SEScalar* _inflammatoryResponseTumorNecrosisFactor;
		biogears::SEScalar* _inflammatoryResponseInterleukin6;
		biogears::SEScalar* _inflammatoryResponseInterleukin10;
		biogears::SEScalar* _inflammatoryResponseInterleukin12;
		biogears::SEScalar* _inflammatoryResponseCatecholamines;
		biogears::SEScalar* _inflammatoryResponseTissueIntegrity;

		biogears::SEUnitScalar* _arterialPressure;
		biogears::SEUnitScalar* _bloodVolume;
		biogears::SEUnitScalar* _cardiacIndex;
		biogears::SEUnitScalar* _cardiacOutput;
		biogears::SEUnitScalar* _centralVenousPressure;
		biogears::SEUnitScalar* _cerebralBloodFlow;
		biogears::SEUnitScalar* _cerebralPerfusionPressure;
		biogears::SEUnitScalar* _diastolicArterialPressure;
		biogears::SEScalar* _heartEjectionFraction;
		biogears::SEUnitScalar* _heartRate;
		biogears::SEUnitScalar* _heartStrokeVolume;
		biogears::SEUnitScalar* _intracranialPressure;
		biogears::SEUnitScalar* _meanArterialPressure;
		biogears::SEUnitScalar* _meanArterialCarbonDioxidePartialPressure;
		biogears::SEUnitScalar* _meanArterialCarbonDioxidePartialPressureDelta;
		biogears::SEUnitScalar* _meanCentralVenousPressure;
		biogears::SEUnitScalar* _meanSkinFlow;
		biogears::SEUnitScalar* _pulmonaryArterialPressure;
		biogears::SEUnitScalar* _pulmonaryCapillariesWedgePressure;
		biogears::SEUnitScalar* _pulmonaryDiastolicArterialPressure;
		biogears::SEUnitScalar* _pulmonaryMeanArterialPressure;
		biogears::SEUnitScalar* _pulmonaryMeanCapillaryFlow;
		biogears::SEUnitScalar* _pulmonaryMeanShuntFlow;
		biogears::SEUnitScalar* _pulmonarySystolicArterialPressure;
		biogears::SEUnitScalar* _pulmonaryVascularResistance;
		biogears::SEUnitScalar* _pulmonaryVascularResistanceIndex;
		biogears::SEUnitScalar* _pulsePressure;
		biogears::SEUnitScalar* _systemicVascularResistance;
		biogears::SEUnitScalar* _systolicArterialPressure;

		biogears::SEScalar* _bronchodilationLevel;
		biogears::SEUnitScalar* _heartRateChange;
		biogears::SEUnitScalar* _meanBloodPressureChange;
		biogears::SEScalar* _neuromuscularBlockLevel;
		biogears::SEUnitScalar* _pulsePressureChange;
		biogears::SEUnitScalar* _respirationRateChange;
		biogears::SEScalar* _sedationLevel;
		biogears::SEUnitScalar* _tidalVolumeChange;
		biogears::SEScalar* _tubularPermeabilityChange;
		biogears::SEScalar* _centralNervousResponse;

		biogears::SEUnitScalar* _insulinSynthesisRate;
		biogears::SEUnitScalar* _glucagonSynthesisRate;

		biogears::SEScalar* _achievedExerciseLevel;
		biogears::SEUnitScalar* _chlorideLostToSweat;
		biogears::SEUnitScalar* _coreTemperature;
		biogears::SEUnitScalar* _creatinineProductionRate;
		biogears::SEUnitScalar* _exerciseMeanArterialPressureDelta;
		biogears::SEScalar* _fatigueLevel;
		biogears::SEUnitScalar* _lactateProductionRate;
		biogears::SEUnitScalar* _potassiumLostToSweat;
		biogears::SEUnitScalar* _skinTemperature;
		biogears::SEUnitScalar* _sodiumLostToSweat;
		biogears::SEUnitScalar* _sweatRate;
		biogears::SEScalar* _totalMetabolicRate;
		biogears::SEScalar* _totalWorkRateLevel;

		biogears::SEUnitScalar* _chymeAbsorptionRate;
		biogears::SEUnitScalar* _stomachContents_calcium;
		biogears::SEUnitScalar* _stomachContents_carbohydrates;
		biogears::SEUnitScalar* _stomachContents_carbohydrateDigationRate;
		biogears::SEUnitScalar* _stomachContents_fat;
		biogears::SEUnitScalar* _stomachContents_fatDigtationRate;
		biogears::SEUnitScalar* _stomachContents_protien;
		biogears::SEUnitScalar* _stomachContents_protienDigtationRate;
		biogears::SEUnitScalar* _stomachContents_sodium;
		biogears::SEUnitScalar* _stomachContents_water;

		biogears::SEUnitScalar* _hepaticGluconeogenesisRate;
		biogears::SEUnitScalar* _ketoneproductionRate;

		biogears::SEScalar* _baroreceptorHeartRateScale;
		biogears::SEScalar* _baroreceptorHeartElastanceScale;
		biogears::SEScalar* _baroreceptorResistanceScale;
		biogears::SEScalar* _baroreceptorComplianceScale;
		biogears::SEScalar* _chemoreceptorHeartRateScale;
		biogears::SEScalar* _chemoreceptorHeartElastanceScale;
		biogears::SEScalar* _painVisualAnalogueScale;

		//TODO: Implement Pupillary Response  ReactivityModifier  ShapeModifier  SizeModifier;
		biogears::SEUnitScalar* _leftEyePupillaryResponse;
		biogears::SEUnitScalar* _rightEyePupillaryResponse;

		//Renal
		biogears::SEUnitScalar* _glomerularFiltrationRate;
		biogears::SEScalar* _filtrationFraction;
		biogears::SEUnitScalar* _leftAfferentArterioleResistance;
		biogears::SEUnitScalar* _leftBowmansCapsulesHydrostaticPressure;
		biogears::SEUnitScalar* _leftBowmansCapsulesOsmoticPressure;
		biogears::SEUnitScalar* _leftEfferentArterioleResistance;
		biogears::SEUnitScalar* _leftGlomerularCapillariesHydrostaticPressure;
		biogears::SEUnitScalar* _leftGlomerularCapillariesOsmoticPressure;
		biogears::SEUnitScalar* _leftGlomerularFiltrationCoefficient;
		biogears::SEUnitScalar* _leftGlomerularFiltrationRate;
		biogears::SEUnitScalar* _leftGlomerularFiltrationSurfaceArea;
		biogears::SEUnitScalar* _leftGlomerularFluidPermeability;
		biogears::SEScalar* _leftFiltrationFraction;
		biogears::SEUnitScalar* _leftNetFiltrationPressure;
		biogears::SEUnitScalar* _leftNetReabsorptionPressure;
		biogears::SEUnitScalar* _leftPeritubularCapillariesHydrostaticPressure;
		biogears::SEUnitScalar* _leftPeritubularCapillariesOsmoticPressure;
		biogears::SEUnitScalar* _leftReabsorptionFiltrationCoefficient;
		biogears::SEUnitScalar* _leftReabsorptionRate;
		biogears::SEUnitScalar* _leftTubularReabsorptionFiltrationSurfaceArea;
		biogears::SEUnitScalar* _leftTubularReabsorptionFluidPermeability;
		biogears::SEUnitScalar* _leftTubularHydrostaticPressure;
		biogears::SEUnitScalar* _leftTubularOsmoticPressure;
		biogears::SEUnitScalar* _renalBloodFlow;
		biogears::SEUnitScalar* _renalPlasmaFlow;
		biogears::SEUnitScalar* _renalVascularResistance;
		biogears::SEUnitScalar* _rightAfferentArterioleResistance;
		biogears::SEUnitScalar* _rightBowmansCapsulesHydrostaticPressure;
		biogears::SEUnitScalar* _rightBowmansCapsulesOsmoticPressure;
		biogears::SEUnitScalar* _rightEfferentArterioleResistance;
		biogears::SEUnitScalar* _rightGlomerularCapillariesHydrostaticPressure;
		biogears::SEUnitScalar* _rightGlomerularCapillariesOsmoticPressure;
		biogears::SEUnitScalar* _rightGlomerularFiltrationCoefficient;
		biogears::SEUnitScalar* _rightGlomerularFiltrationRate;
		biogears::SEUnitScalar* _rightGlomerularFiltrationSurfaceArea;
		biogears::SEUnitScalar* _rightGlomerularFluidPermeability;
		biogears::SEScalar* _rightFiltrationFraction;
		biogears::SEUnitScalar* _rightNetFiltrationPressure;
		biogears::SEUnitScalar* _rightNetReabsorptionPressure;
		biogears::SEUnitScalar* _rightPeritubularCapillariesHydrostaticPressure;
		biogears::SEUnitScalar* _rightPeritubularCapillariesOsmoticPressure;
		biogears::SEUnitScalar* _rightReabsorptionFiltrationCoefficient;
		biogears::SEUnitScalar* _rightReabsorptionRate;
		biogears::SEUnitScalar* _rightTubularReabsorptionFiltrationSurfaceArea;
		biogears::SEUnitScalar* _rightTubularReabsorptionFluidPermeability;
		biogears::SEUnitScalar* _rightTubularHydrostaticPressure;
		biogears::SEUnitScalar* _rightTubularOsmoticPressure;
		biogears::SEUnitScalar* _urinationRate;
		biogears::SEUnitScalar* _urineOsmolality;
		biogears::SEUnitScalar* _urineOsmolarity;
		biogears::SEUnitScalar* _urineProductionRate;
		biogears::SEUnitScalar* _meanUrineOutput;
		biogears::SEScalar* _urineSpecificGravity;
		biogears::SEUnitScalar* _urineVolume;
		biogears::SEUnitScalar* _urineUreaNitrogenConcentration;
		//Respiratory
		biogears::SEUnitScalar* _alveolarArterialGradient;
		biogears::SEUnitScalar* _carricoIndex;
		biogears::SEScalar* _endTidalCarbonDioxideFraction;
		biogears::SEUnitScalar* _endTidalCarbonDioxidePressure;
		biogears::SEUnitScalar* _expiratoryFlow;
		biogears::SEScalar* _inspiratoryExpiratoryRatio;
		biogears::SEUnitScalar* _inspiratoryFlow;
		biogears::SEUnitScalar* _pulmonaryCompliance;
		biogears::SEUnitScalar* _pulmonaryResistance;
		biogears::SEUnitScalar* _respirationDriverPressure;
		biogears::SEUnitScalar* _respirationMusclePressure;
		biogears::SEUnitScalar* _respirationRate;
		biogears::SEScalar* _specificVentilation;
		biogears::SEUnitScalar* _targetPulmonaryVentilation;
		biogears::SEUnitScalar* _tidalVolume;
		biogears::SEUnitScalar* _totalAlveolarVentilation;
		biogears::SEUnitScalar* _totalDeadSpaceVentilation;
		biogears::SEUnitScalar* _totalLungVolume;
		biogears::SEUnitScalar* _totalPulmonaryVentilation;
		biogears::SEUnitScalar* _transpulmonaryPressure;

		//Tissue
		biogears::SEUnitScalar* _carbonDioxideProductionRate;
		biogears::SEScalar* _dehydrationFraction;
		biogears::SEUnitScalar* _extracellularFluidVolume;
		biogears::SEUnitScalar* _extravascularFluidVolume;
		biogears::SEScalar* _intracellularFluidPH;
		biogears::SEUnitScalar* _intracellularFluidVolume;
		biogears::SEUnitScalar* _totalBodyFluidVolume;
		biogears::SEUnitScalar* _oxygenConsumptionRate;
		biogears::SEScalar* _respiratoryExchangeRatio;
		biogears::SEUnitScalar* _liverInsulinSetPoint;
		biogears::SEUnitScalar* _liverGlucagonSetPoint;
		biogears::SEUnitScalar* _muscleInsulinSetPoint;
		biogears::SEUnitScalar* _muscleGlucagonSetPoint;
		biogears::SEUnitScalar* _fatInsulinSetPoint;
		biogears::SEUnitScalar* _fatGlucagonSetPoint;
		biogears::SEUnitScalar* _liverGlycogen;
		biogears::SEUnitScalar* _muscleGlycogen;
		biogears::SEUnitScalar* _storedProtein;
		biogears::SEUnitScalar* _storedFat;

		void setup_cache();
		void update_cache();
		void update_metrics();
		void update_conditions();
		void update_state();


};