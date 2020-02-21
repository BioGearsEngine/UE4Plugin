#include "UBioGearsEngine.h"
#include "UBioGearsEnums.h"
#include "UBioGearsStructs.h"

#include <thread>
#include <memory>
#include <mutex>
#include <atomic>

#include <biogears/engine/BioGearsPhysiologyEngine.h>
#include <biogears/engine/controller/BioGears.h>
#include <biogears/engine/controller/BioGearsEngine.h>
#include <biogears/cdm/properties/SEScalarTypes.h>
struct UBioGearsEngine::Implementation
{
	TUniquePtr <UBioGearsLogger> logger;     //<! Only Used if logger not passed to system
	TUniquePtr<biogears::BioGearsEngine> bg;

	std::mutex mutex;
	std::string name;
	std::string log_name;
	std::string log_root;
	std::string data_root;

	FBiogearsMetrics metrics;
	FBiogearsConditions conditions;
	FBiogearsState state;

	std::atomic_bool ready{ false };

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

	explicit Implementation();
	explicit Implementation(const std::string& dataRoot, const std::string& n);
	explicit Implementation(const std::string& dataRoot, TUniquePtr<UBioGearsLogger>  logger);

	void setup_cache();
	void update_cache();
	void update_metrics();
	void update_conditions();
	void update_state();
};
UBioGearsEngine::Implementation::Implementation()
	: Implementation(TCHAR_TO_ANSI(*FPaths::GetPath("./")), "UBioGearsEngine")
{ }
UBioGearsEngine::Implementation::Implementation(const std::string& dataRoot, const std::string& n)
	: logger(MakeUnique<UBioGearsLogger>(ANSI_TO_TCHAR(dataRoot.c_str()) + FString(TEXT("/")), ANSI_TO_TCHAR(n.c_str()) + FString(TEXT(".log"))))
	, bg(MakeUnique<biogears::BioGearsEngine>(logger.Get(), dataRoot + "/"))
	, name(n)
	, log_name(n + ".log")
	, log_root(dataRoot + "/")
	, data_root(dataRoot + "/")
{ }
UBioGearsEngine::Implementation::Implementation(const std::string& dataRoot, TUniquePtr<UBioGearsLogger>  logPtr)
	: logger(std::move(logPtr))
	, bg(MakeUnique<biogears::BioGearsEngine>(logger.Get(), dataRoot + "/"))
	, name("UE4PhysiologyEngine")
	, log_name("")
	, log_root(dataRoot + "/")
	, data_root(dataRoot + "/")
{ }

void UBioGearsEngine::Implementation::setup_cache() {
	auto& bloodChemistry = bg->GetBloodChemistry();
	_arterialBloodPH = (bloodChemistry.HasArterialBloodPH()) ? &bloodChemistry.GetArterialBloodPH() : nullptr;
	_arterialBloodPHBaseline = (bloodChemistry.HasArterialBloodPHBaseline()) ? &bloodChemistry.GetArterialBloodPHBaseline() : nullptr;
	_bloodDensity = (bloodChemistry.HasBloodDensity()) ? &bloodChemistry.GetBloodDensity() : nullptr;
	_bloodSpecificHeat = (bloodChemistry.HasBloodSpecificHeat()) ? &bloodChemistry.GetBloodSpecificHeat() : nullptr;
	_bloodUreaNitrogenConcentration = (bloodChemistry.HasBloodUreaNitrogenConcentration()) ? &bloodChemistry.GetBloodUreaNitrogenConcentration() : nullptr;
	_carbonDioxideSaturation = (bloodChemistry.HasCarbonDioxideSaturation()) ? &bloodChemistry.GetCarbonDioxideSaturation() : nullptr;
	_carbonMonoxideSaturation = (bloodChemistry.HasCarbonMonoxideSaturation()) ? &bloodChemistry.GetCarbonMonoxideSaturation() : nullptr;
	_hematocrit = (bloodChemistry.HasHematocrit()) ? &bloodChemistry.GetHematocrit() : nullptr;
	_hemoglobinContent = (bloodChemistry.HasHemoglobinContent()) ? &bloodChemistry.GetHemoglobinContent() : nullptr;
	_oxygenSaturation = (bloodChemistry.HasOxygenSaturation()) ? &bloodChemistry.GetOxygenSaturation() : nullptr;
	_phosphate = (bloodChemistry.HasPhosphate()) ? &bloodChemistry.GetPhosphate() : nullptr;
	_plasmaVolume = (bloodChemistry.HasPlasmaVolume()) ? &bloodChemistry.GetPlasmaVolume() : nullptr;
	_pulseOximetry = (bloodChemistry.HasPulseOximetry()) ? &bloodChemistry.GetPulseOximetry() : nullptr;
	_redBloodCellAcetylcholinesterase = (bloodChemistry.HasRedBloodCellAcetylcholinesterase()) ? &bloodChemistry.GetRedBloodCellAcetylcholinesterase() : nullptr;
	_redBloodCellCount = (bloodChemistry.HasRedBloodCellCount()) ? &bloodChemistry.GetRedBloodCellCount() : nullptr;
	_shuntFraction = (bloodChemistry.HasShuntFraction()) ? &bloodChemistry.GetShuntFraction() : nullptr;
	_strongIonDifference = (bloodChemistry.HasStrongIonDifference()) ? &bloodChemistry.GetStrongIonDifference() : nullptr;
	_totalBilirubin = (bloodChemistry.HasTotalBilirubin()) ? &bloodChemistry.GetTotalBilirubin() : nullptr;
	_totalProteinConcentration = (bloodChemistry.HasTotalProteinConcentration()) ? &bloodChemistry.GetTotalProteinConcentration() : nullptr;
	_venousBloodPH = (bloodChemistry.HasVenousBloodPH()) ? &bloodChemistry.GetVenousBloodPH() : nullptr;
	_volumeFractionNeutralPhospholipidInPlasma = (bloodChemistry.HasVolumeFractionNeutralPhospholipidInPlasma()) ? &bloodChemistry.GetVolumeFractionNeutralPhospholipidInPlasma() : nullptr;
	_volumeFractionNeutralLipidInPlasma = (bloodChemistry.HasVolumeFractionNeutralLipidInPlasma()) ? &bloodChemistry.GetVolumeFractionNeutralLipidInPlasma() : nullptr;
	_arterialCarbonDioxidePressure = (bloodChemistry.HasArterialCarbonDioxidePressure()) ? &bloodChemistry.GetArterialCarbonDioxidePressure() : nullptr;
	_arterialOxygenPressure = (bloodChemistry.HasArterialOxygenPressure()) ? &bloodChemistry.GetArterialOxygenPressure() : nullptr;
	_pulmonaryArterialCarbonDioxidePressure = (bloodChemistry.HasPulmonaryArterialCarbonDioxidePressure()) ? &bloodChemistry.GetPulmonaryArterialCarbonDioxidePressure() : nullptr;
	_pulmonaryArterialOxygenPressure = (bloodChemistry.HasPulmonaryArterialOxygenPressure()) ? &bloodChemistry.GetPulmonaryArterialOxygenPressure() : nullptr;
	_pulmonaryVenousCarbonDioxidePressure = (bloodChemistry.HasPulmonaryVenousCarbonDioxidePressure()) ? &bloodChemistry.GetPulmonaryVenousCarbonDioxidePressure() : nullptr;
	_pulmonaryVenousOxygenPressure = (bloodChemistry.HasPulmonaryVenousOxygenPressure()) ? &bloodChemistry.GetPulmonaryVenousOxygenPressure() : nullptr;
	_venousCarbonDioxidePressure = (bloodChemistry.HasVenousCarbonDioxidePressure()) ? &bloodChemistry.GetVenousCarbonDioxidePressure() : nullptr;
	_venousOxygenPressure = (bloodChemistry.HasVenousOxygenPressure()) ? &bloodChemistry.GetVenousOxygenPressure() : nullptr;
	_inflammatoryResponse = bloodChemistry.HasInflammatoryResponse();

	auto& inflamatoryResponse = bloodChemistry.GetInflammatoryResponse();
	_inflammatoryResponseLocalPathogen = (inflamatoryResponse.HasLocalPathogen()) ? &inflamatoryResponse.GetLocalPathogen() : nullptr;
	_inflammatoryResponseLocalMacrophage = (inflamatoryResponse.HasLocalMacrophage()) ? &inflamatoryResponse.GetLocalMacrophage() : nullptr;
	_inflammatoryResponseLocalNeutrophil = (inflamatoryResponse.HasLocalNeutrophil()) ? &inflamatoryResponse.GetLocalNeutrophil() : nullptr;
	_inflammatoryResponseLocalBarrier = (inflamatoryResponse.HasLocalBarrier()) ? &inflamatoryResponse.GetLocalBarrier() : nullptr;
	_inflammatoryResponseBloodPathogen = (inflamatoryResponse.HasBloodPathogen()) ? &inflamatoryResponse.GetBloodPathogen() : nullptr;
	_inflammatoryResponseTrauma = (inflamatoryResponse.HasTrauma()) ? &inflamatoryResponse.GetTrauma() : nullptr;
	_inflammatoryResponseMacrophageResting = (inflamatoryResponse.HasMacrophageResting()) ? &inflamatoryResponse.GetMacrophageResting() : nullptr;
	_inflammatoryResponseMacrophageActive = (inflamatoryResponse.HasMacrophageActive()) ? &inflamatoryResponse.GetMacrophageActive() : nullptr;
	_inflammatoryResponseNeutrophilResting = (inflamatoryResponse.HasNeutrophilResting()) ? &inflamatoryResponse.GetNeutrophilResting() : nullptr;
	_inflammatoryResponseNeutrophilActive = (inflamatoryResponse.HasNeutrophilActive()) ? &inflamatoryResponse.GetNeutrophilActive() : nullptr;
	_inflammatoryResponseInducibleNOSPre = (inflamatoryResponse.HasInducibleNOSPre()) ? &inflamatoryResponse.GetInducibleNOSPre() : nullptr;
	_inflammatoryResponseInducibleNOS = (inflamatoryResponse.HasInducibleNOS()) ? &inflamatoryResponse.GetInducibleNOS() : nullptr;
	_inflammatoryResponseConstitutiveNOS = (inflamatoryResponse.HasConstitutiveNOS()) ? &inflamatoryResponse.GetConstitutiveNOS() : nullptr;
	_inflammatoryResponseNitrate = (inflamatoryResponse.HasNitrate()) ? &inflamatoryResponse.GetNitrate() : nullptr;
	_inflammatoryResponseNitricOxide = (inflamatoryResponse.HasNitricOxide()) ? &inflamatoryResponse.GetNitricOxide() : nullptr;
	_inflammatoryResponseTumorNecrosisFactor = (inflamatoryResponse.HasTumorNecrosisFactor()) ? &inflamatoryResponse.GetTumorNecrosisFactor() : nullptr;
	_inflammatoryResponseInterleukin6 = (inflamatoryResponse.HasInterleukin6()) ? &inflamatoryResponse.GetInterleukin6() : nullptr;
	_inflammatoryResponseInterleukin10 = (inflamatoryResponse.HasInterleukin10()) ? &inflamatoryResponse.GetInterleukin10() : nullptr;
	_inflammatoryResponseInterleukin12 = (inflamatoryResponse.HasInterleukin12()) ? &inflamatoryResponse.GetInterleukin12() : nullptr;
	_inflammatoryResponseCatecholamines = (inflamatoryResponse.HasCatecholamines()) ? &inflamatoryResponse.GetCatecholamines() : nullptr;
	_inflammatoryResponseTissueIntegrity = (inflamatoryResponse.HasTissueIntegrity()) ? &inflamatoryResponse.GetTissueIntegrity() : nullptr;

	auto& cardiovascular = bg->GetCardiovascular();
	_arterialPressure = (cardiovascular.HasArterialPressure()) ? &cardiovascular.GetArterialPressure() : nullptr;
	_bloodVolume = (cardiovascular.HasBloodVolume()) ? &cardiovascular.GetBloodVolume() : nullptr;
	_cardiacIndex = (cardiovascular.HasCardiacIndex()) ? &cardiovascular.GetCardiacIndex() : nullptr;
	_cardiacOutput = (cardiovascular.HasCardiacOutput()) ? &cardiovascular.GetCardiacOutput() : nullptr;
	_centralVenousPressure = (cardiovascular.HasCentralVenousPressure()) ? &cardiovascular.GetCentralVenousPressure() : nullptr;
	_cerebralBloodFlow = (cardiovascular.HasCerebralBloodFlow()) ? &cardiovascular.GetCerebralBloodFlow() : nullptr;
	_cerebralPerfusionPressure = (cardiovascular.HasCerebralPerfusionPressure()) ? &cardiovascular.GetCerebralPerfusionPressure() : nullptr;
	_diastolicArterialPressure = (cardiovascular.HasDiastolicArterialPressure()) ? &cardiovascular.GetDiastolicArterialPressure() : nullptr;
	_heartEjectionFraction = (cardiovascular.HasHeartEjectionFraction()) ? &cardiovascular.GetHeartEjectionFraction() : nullptr;
	_heartRate = (cardiovascular.HasHeartRate()) ? &cardiovascular.GetHeartRate() : nullptr;
	_heartStrokeVolume = (cardiovascular.HasHeartStrokeVolume()) ? &cardiovascular.GetHeartStrokeVolume() : nullptr;
	_intracranialPressure = (cardiovascular.HasIntracranialPressure()) ? &cardiovascular.GetIntracranialPressure() : nullptr;
	_meanArterialPressure = (cardiovascular.HasMeanArterialPressure()) ? &cardiovascular.GetMeanArterialPressure() : nullptr;
	_meanArterialCarbonDioxidePartialPressure = (cardiovascular.HasMeanArterialCarbonDioxidePartialPressure()) ? &cardiovascular.GetMeanArterialCarbonDioxidePartialPressure() : nullptr;
	_meanArterialCarbonDioxidePartialPressureDelta = (cardiovascular.HasMeanArterialCarbonDioxidePartialPressureDelta()) ? &cardiovascular.GetMeanArterialCarbonDioxidePartialPressureDelta() : nullptr;
	_meanCentralVenousPressure = (cardiovascular.HasMeanCentralVenousPressure()) ? &cardiovascular.GetMeanCentralVenousPressure() : nullptr;
	_meanSkinFlow = (cardiovascular.HasMeanSkinFlow()) ? &cardiovascular.GetMeanSkinFlow() : nullptr;
	_pulmonaryArterialPressure = (cardiovascular.HasPulmonaryArterialPressure()) ? &cardiovascular.GetPulmonaryArterialPressure() : nullptr;
	_pulmonaryCapillariesWedgePressure = (cardiovascular.HasPulmonaryCapillariesWedgePressure()) ? &cardiovascular.GetPulmonaryCapillariesWedgePressure() : nullptr;
	_pulmonaryDiastolicArterialPressure = (cardiovascular.HasPulmonaryDiastolicArterialPressure()) ? &cardiovascular.GetPulmonaryDiastolicArterialPressure() : nullptr;
	_pulmonaryMeanArterialPressure = (cardiovascular.HasPulmonaryMeanArterialPressure()) ? &cardiovascular.GetPulmonaryMeanArterialPressure() : nullptr;
	_pulmonaryMeanCapillaryFlow = (cardiovascular.HasPulmonaryMeanArterialPressure()) ? &cardiovascular.GetPulmonaryMeanArterialPressure() : nullptr;
	_pulmonaryMeanShuntFlow = (cardiovascular.HasPulmonaryMeanShuntFlow()) ? &cardiovascular.GetPulmonaryMeanShuntFlow() : nullptr;
	_pulmonarySystolicArterialPressure = (cardiovascular.HasPulmonarySystolicArterialPressure()) ? &cardiovascular.GetPulmonarySystolicArterialPressure() : nullptr;
	_pulmonaryVascularResistance = (cardiovascular.HasPulmonaryVascularResistance()) ? &cardiovascular.GetPulmonaryVascularResistance() : nullptr;
	_pulmonaryVascularResistanceIndex = (cardiovascular.HasPulmonaryVascularResistanceIndex()) ? &cardiovascular.GetPulmonaryVascularResistanceIndex() : nullptr;
	_pulsePressure = (cardiovascular.HasPulsePressure()) ? &cardiovascular.GetPulsePressure() : nullptr;
	_systemicVascularResistance = (cardiovascular.HasSystemicVascularResistance()) ? &cardiovascular.GetSystemicVascularResistance() : nullptr;
	_systolicArterialPressure = (cardiovascular.HasSystolicArterialPressure()) ? &cardiovascular.GetSystolicArterialPressure() : nullptr;

	auto& drugs = bg->GetDrugs();
	_bronchodilationLevel = (drugs.HasBronchodilationLevel()) ? &drugs.GetBronchodilationLevel() : nullptr;
	_heartRateChange = (drugs.HasHeartRateChange()) ? &drugs.GetHeartRateChange() : nullptr;
	_meanBloodPressureChange = (drugs.HasMeanBloodPressureChange()) ? &drugs.GetMeanBloodPressureChange() : nullptr;
	_neuromuscularBlockLevel = (drugs.HasNeuromuscularBlockLevel()) ? &drugs.GetNeuromuscularBlockLevel() : nullptr;
	_pulsePressureChange = (drugs.HasPulsePressureChange()) ? &drugs.GetPulsePressureChange() : nullptr;
	_respirationRateChange = (drugs.HasRespirationRateChange()) ? &drugs.GetRespirationRateChange() : nullptr;
	_sedationLevel = (drugs.HasSedationLevel()) ? &drugs.GetSedationLevel() : nullptr;
	_tidalVolumeChange = (drugs.HasTidalVolumeChange()) ? &drugs.GetTidalVolumeChange() : nullptr;
	_tubularPermeabilityChange = (drugs.HasTubularPermeabilityChange()) ? &drugs.GetTubularPermeabilityChange() : nullptr;
	_centralNervousResponse = (drugs.HasCentralNervousResponse()) ? &drugs.GetCentralNervousResponse() : nullptr;

	auto& endocrine = bg->GetEndocrine();
	_insulinSynthesisRate = (endocrine.HasInsulinSynthesisRate()) ? &endocrine.GetInsulinSynthesisRate() : nullptr;
	_glucagonSynthesisRate = (endocrine.HasGlucagonSynthesisRate()) ? &endocrine.GetGlucagonSynthesisRate() : nullptr;

	auto& energy = bg->GetEnergy();
	_achievedExerciseLevel = (energy.HasAchievedExerciseLevel()) ? &energy.GetAchievedExerciseLevel() : nullptr;
	_chlorideLostToSweat = (energy.HasChlorideLostToSweat()) ? &energy.GetChlorideLostToSweat() : nullptr;
	_coreTemperature = (energy.HasCoreTemperature()) ? &energy.GetCoreTemperature() : nullptr;
	_creatinineProductionRate = (energy.HasCreatinineProductionRate()) ? &energy.GetCreatinineProductionRate() : nullptr;
	_exerciseMeanArterialPressureDelta = (energy.HasExerciseMeanArterialPressureDelta()) ? &energy.GetExerciseMeanArterialPressureDelta() : nullptr;
	_fatigueLevel = (energy.HasFatigueLevel()) ? &energy.GetFatigueLevel() : nullptr;
	_lactateProductionRate = (energy.HasLactateProductionRate()) ? &energy.GetLactateProductionRate() : nullptr;
	_potassiumLostToSweat = (energy.HasPotassiumLostToSweat()) ? &energy.GetPotassiumLostToSweat() : nullptr;
	_skinTemperature = (energy.HasSkinTemperature()) ? &energy.GetSkinTemperature() : nullptr;
	_sodiumLostToSweat = (energy.HasSodiumLostToSweat()) ? &energy.GetSodiumLostToSweat() : nullptr;
	_sweatRate = (energy.HasSweatRate()) ? &energy.GetSweatRate() : nullptr;
	_totalMetabolicRate = (energy.HasTotalMetabolicRate()) ? &energy.GetTotalWorkRateLevel() : nullptr;
	_totalWorkRateLevel = (energy.HasTotalWorkRateLevel()) ? &energy.GetTotalWorkRateLevel() : nullptr;

	auto& gastrointestinal = bg->GetGastrointestinal();
	_chymeAbsorptionRate = (gastrointestinal.HasChymeAbsorptionRate()) ? &gastrointestinal.GetChymeAbsorptionRate() : nullptr;
	_stomachContents_calcium = (gastrointestinal.HasStomachContents() && gastrointestinal.GetStomachContents().HasCalcium()) ? &gastrointestinal.GetStomachContents().GetCalcium() : nullptr;
	_stomachContents_carbohydrates = (gastrointestinal.HasStomachContents() && gastrointestinal.GetStomachContents().HasCarbohydrate()) ? &gastrointestinal.GetStomachContents().GetCarbohydrate() : nullptr;
	_stomachContents_carbohydrateDigationRate = (gastrointestinal.HasStomachContents() && gastrointestinal.GetStomachContents().HasCarbohydrateDigestionRate()) ? &gastrointestinal.GetStomachContents().GetCarbohydrateDigestionRate() : nullptr;
	_stomachContents_fat = (gastrointestinal.HasStomachContents() && gastrointestinal.GetStomachContents().HasFat()) ? &gastrointestinal.GetStomachContents().GetFat() : nullptr;
	_stomachContents_fatDigtationRate = (gastrointestinal.HasStomachContents() && gastrointestinal.GetStomachContents().HasFatDigestionRate()) ? &gastrointestinal.GetStomachContents().GetFatDigestionRate() : nullptr;
	_stomachContents_protien = (gastrointestinal.HasStomachContents() && gastrointestinal.GetStomachContents().HasProtein()) ? &gastrointestinal.GetStomachContents().GetProtein() : nullptr;
	_stomachContents_protienDigtationRate = (gastrointestinal.HasStomachContents() && gastrointestinal.GetStomachContents().HasProteinDigestionRate()) ? &gastrointestinal.GetStomachContents().GetProteinDigestionRate() : nullptr;
	_stomachContents_sodium = (gastrointestinal.HasStomachContents() && gastrointestinal.GetStomachContents().HasSodium()) ? &gastrointestinal.GetStomachContents().GetSodium() : nullptr;
	_stomachContents_water = (gastrointestinal.HasStomachContents() && gastrointestinal.GetStomachContents().HasWater()) ? &gastrointestinal.GetStomachContents().GetWater() : nullptr;

	auto& hepatic = bg->GetHepatic();
	_hepaticGluconeogenesisRate = (hepatic.HasHepaticGluconeogenesisRate()) ? &hepatic.GetHepaticGluconeogenesisRate() : nullptr;
	_ketoneproductionRate = (hepatic.HasKetoneProductionRate()) ? &hepatic.GetKetoneProductionRate() : nullptr;

	auto& nervous = bg->GetNervous();
	_baroreceptorHeartRateScale = (nervous.HasBaroreceptorHeartRateScale()) ? &nervous.GetBaroreceptorHeartRateScale() : nullptr;
	_baroreceptorHeartElastanceScale = (nervous.HasBaroreceptorHeartElastanceScale()) ? &nervous.GetBaroreceptorHeartElastanceScale() : nullptr;
	_baroreceptorResistanceScale = (nervous.HasBaroreceptorResistanceScale()) ? &nervous.GetBaroreceptorResistanceScale() : nullptr;
	_baroreceptorComplianceScale = (nervous.HasBaroreceptorComplianceScale()) ? &nervous.GetBaroreceptorComplianceScale() : nullptr;
	_chemoreceptorHeartRateScale = (nervous.HasChemoreceptorHeartRateScale()) ? &nervous.GetChemoreceptorHeartRateScale() : nullptr;
	_chemoreceptorHeartElastanceScale = (nervous.HasChemoreceptorHeartElastanceScale()) ? &nervous.GetChemoreceptorHeartElastanceScale() : nullptr;
	_painVisualAnalogueScale = (nervous.HasPainVisualAnalogueScale()) ? &nervous.GetPainVisualAnalogueScale() : nullptr;

	//TODO: Implement Pupillary Response  ReactivityModifier  ShapeModifier  SizeModifier;
	_leftEyePupillaryResponse = nullptr;
	_rightEyePupillaryResponse = nullptr;

	//Renal
	auto& renal = bg->GetRenal();
	_glomerularFiltrationRate = (renal.HasGlomerularFiltrationRate()) ? &renal.GetGlomerularFiltrationRate() : nullptr;
	_filtrationFraction = (renal.HasFiltrationFraction()) ? &renal.GetFiltrationFraction() : nullptr;
	_leftAfferentArterioleResistance = (renal.HasLeftAfferentArterioleResistance()) ? &renal.GetLeftAfferentArterioleResistance() : nullptr;
	_leftBowmansCapsulesHydrostaticPressure = (renal.HasLeftBowmansCapsulesHydrostaticPressure()) ? &renal.GetLeftBowmansCapsulesHydrostaticPressure() : nullptr;
	_leftBowmansCapsulesOsmoticPressure = (renal.HasLeftBowmansCapsulesOsmoticPressure()) ? &renal.GetLeftBowmansCapsulesOsmoticPressure() : nullptr;
	_leftEfferentArterioleResistance = (renal.HasLeftEfferentArterioleResistance()) ? &renal.GetLeftEfferentArterioleResistance() : nullptr;
	_leftGlomerularCapillariesHydrostaticPressure = (renal.HasLeftGlomerularCapillariesHydrostaticPressure()) ? &renal.GetLeftGlomerularCapillariesHydrostaticPressure() : nullptr;
	_leftGlomerularCapillariesOsmoticPressure = (renal.HasLeftGlomerularCapillariesOsmoticPressure()) ? &renal.GetLeftGlomerularCapillariesOsmoticPressure() : nullptr;
	_leftGlomerularFiltrationCoefficient = (renal.HasLeftGlomerularFiltrationCoefficient()) ? &renal.GetLeftGlomerularFiltrationCoefficient() : nullptr;
	_leftGlomerularFiltrationRate = (renal.HasLeftGlomerularFiltrationRate()) ? &renal.GetLeftGlomerularFiltrationRate() : nullptr;
	_leftGlomerularFiltrationSurfaceArea = (renal.HasLeftGlomerularFiltrationSurfaceArea()) ? &renal.GetLeftGlomerularFiltrationSurfaceArea() : nullptr;
	_leftGlomerularFluidPermeability = (renal.HasLeftGlomerularFluidPermeability()) ? &renal.GetLeftGlomerularFluidPermeability() : nullptr;
	_leftFiltrationFraction = (renal.HasLeftFiltrationFraction()) ? &renal.GetLeftFiltrationFraction() : nullptr;
	_leftNetFiltrationPressure = (renal.HasLeftNetFiltrationPressure()) ? &renal.GetLeftNetFiltrationPressure() : nullptr;
	_leftNetReabsorptionPressure = (renal.HasLeftNetReabsorptionPressure()) ? &renal.GetLeftNetReabsorptionPressure() : nullptr;
	_leftPeritubularCapillariesHydrostaticPressure = (renal.HasLeftPeritubularCapillariesHydrostaticPressure()) ? &renal.GetLeftPeritubularCapillariesHydrostaticPressure() : nullptr;
	_leftPeritubularCapillariesOsmoticPressure = (renal.HasLeftPeritubularCapillariesOsmoticPressure()) ? &renal.GetLeftPeritubularCapillariesOsmoticPressure() : nullptr;
	_leftReabsorptionFiltrationCoefficient = (renal.HasLeftReabsorptionFiltrationCoefficient()) ? &renal.GetLeftReabsorptionFiltrationCoefficient() : nullptr;
	_leftReabsorptionRate = (renal.HasLeftReabsorptionRate()) ? &renal.GetLeftReabsorptionRate() : nullptr;
	_leftTubularReabsorptionFiltrationSurfaceArea = (renal.HasLeftTubularReabsorptionFiltrationSurfaceArea()) ? &renal.GetLeftTubularReabsorptionFiltrationSurfaceArea() : nullptr;
	_leftTubularReabsorptionFluidPermeability = (renal.HasLeftTubularReabsorptionFluidPermeability()) ? &renal.GetLeftTubularReabsorptionFluidPermeability() : nullptr;
	_leftTubularHydrostaticPressure = (renal.HasLeftTubularHydrostaticPressure()) ? &renal.GetLeftTubularHydrostaticPressure() : nullptr;
	_leftTubularOsmoticPressure = (renal.HasLeftTubularOsmoticPressure()) ? &renal.GetLeftTubularOsmoticPressure() : nullptr;
	_renalBloodFlow = (renal.HasRenalBloodFlow()) ? &renal.GetRenalBloodFlow() : nullptr;
	_renalPlasmaFlow = (renal.HasRenalPlasmaFlow()) ? &renal.GetRenalPlasmaFlow() : nullptr;
	_renalVascularResistance = (renal.HasRenalVascularResistance()) ? &renal.GetRenalVascularResistance() : nullptr;
	_rightAfferentArterioleResistance = (renal.HasRightAfferentArterioleResistance()) ? &renal.GetRightAfferentArterioleResistance() : nullptr;
	_rightBowmansCapsulesHydrostaticPressure = (renal.HasRightBowmansCapsulesHydrostaticPressure()) ? &renal.GetRightBowmansCapsulesHydrostaticPressure() : nullptr;
	_rightBowmansCapsulesOsmoticPressure = (renal.HasRightBowmansCapsulesOsmoticPressure()) ? &renal.GetRightBowmansCapsulesOsmoticPressure() : nullptr;
	_rightEfferentArterioleResistance = (renal.HasRightEfferentArterioleResistance()) ? &renal.GetRightEfferentArterioleResistance() : nullptr;
	_rightGlomerularCapillariesHydrostaticPressure = (renal.HasRightGlomerularCapillariesHydrostaticPressure()) ? &renal.GetRightGlomerularCapillariesHydrostaticPressure() : nullptr;
	_rightGlomerularCapillariesOsmoticPressure = (renal.HasRightGlomerularCapillariesOsmoticPressure()) ? &renal.GetRightGlomerularCapillariesOsmoticPressure() : nullptr;
	_rightGlomerularFiltrationCoefficient = (renal.HasRightGlomerularFiltrationCoefficient()) ? &renal.GetRightGlomerularFiltrationCoefficient() : nullptr;
	_rightGlomerularFiltrationRate = (renal.HasRightGlomerularFiltrationRate()) ? &renal.GetRightGlomerularFiltrationRate() : nullptr;
	_rightGlomerularFiltrationSurfaceArea = (renal.HasRightGlomerularFiltrationSurfaceArea()) ? &renal.GetRightGlomerularFiltrationSurfaceArea() : nullptr;
	_rightGlomerularFluidPermeability = (renal.HasRightGlomerularFluidPermeability()) ? &renal.GetRightGlomerularFluidPermeability() : nullptr;
	_rightFiltrationFraction = (renal.HasRightFiltrationFraction()) ? &renal.GetRightFiltrationFraction() : nullptr;
	_rightNetFiltrationPressure = (renal.HasRightNetFiltrationPressure()) ? &renal.GetRightNetFiltrationPressure() : nullptr;
	_rightNetReabsorptionPressure = (renal.HasRightNetReabsorptionPressure()) ? &renal.GetRightNetReabsorptionPressure() : nullptr;
	_rightPeritubularCapillariesHydrostaticPressure = (renal.HasRightPeritubularCapillariesHydrostaticPressure()) ? &renal.GetRightPeritubularCapillariesHydrostaticPressure() : nullptr;
	_rightPeritubularCapillariesOsmoticPressure = (renal.HasRightPeritubularCapillariesOsmoticPressure()) ? &renal.GetRightPeritubularCapillariesOsmoticPressure() : nullptr;
	_rightReabsorptionFiltrationCoefficient = (renal.HasRightReabsorptionFiltrationCoefficient()) ? &renal.GetRightReabsorptionFiltrationCoefficient() : nullptr;
	_rightReabsorptionRate = (renal.HasRightReabsorptionRate()) ? &renal.GetRightReabsorptionRate() : nullptr;
	_rightTubularReabsorptionFiltrationSurfaceArea = (renal.HasRightTubularReabsorptionFiltrationSurfaceArea()) ? &renal.GetRightTubularReabsorptionFiltrationSurfaceArea() : nullptr;
	_rightTubularReabsorptionFluidPermeability = (renal.HasRightTubularReabsorptionFluidPermeability()) ? &renal.GetRightTubularReabsorptionFluidPermeability() : nullptr;
	_rightTubularHydrostaticPressure = (renal.HasRightTubularHydrostaticPressure()) ? &renal.GetRightTubularHydrostaticPressure() : nullptr;
	_rightTubularOsmoticPressure = (renal.HasRightTubularOsmoticPressure()) ? &renal.GetRightTubularOsmoticPressure() : nullptr;
	_urinationRate = (renal.HasUrinationRate()) ? &renal.GetUrinationRate() : nullptr;
	_urineOsmolality = (renal.HasUrineOsmolality()) ? &renal.GetUrineOsmolality() : nullptr;
	_urineOsmolarity = (renal.HasUrineOsmolarity()) ? &renal.GetUrineOsmolarity() : nullptr;
	_urineProductionRate = (renal.HasUrineProductionRate()) ? &renal.GetUrineProductionRate() : nullptr;
	_meanUrineOutput = (renal.HasMeanUrineOutput()) ? &renal.GetMeanUrineOutput() : nullptr;
	_urineSpecificGravity = (renal.HasUrineSpecificGravity()) ? &renal.GetUrineSpecificGravity() : nullptr;
	_urineVolume = (renal.HasUrineVolume()) ? &renal.GetUrineVolume() : nullptr;
	_urineUreaNitrogenConcentration = (renal.HasUrineUreaNitrogenConcentration()) ? &renal.GetUrineUreaNitrogenConcentration() : nullptr;

	//Respiratory
	auto& respiratory = bg->GetRespiratory();
	_alveolarArterialGradient = (respiratory.HasAlveolarArterialGradient()) ? &respiratory.GetAlveolarArterialGradient() : nullptr;
	_carricoIndex = (respiratory.HasCarricoIndex()) ? &respiratory.GetCarricoIndex() : nullptr;
	_endTidalCarbonDioxideFraction = (respiratory.HasEndTidalCarbonDioxideFraction()) ? &respiratory.GetEndTidalCarbonDioxideFraction() : nullptr;
	_endTidalCarbonDioxidePressure = (respiratory.HasEndTidalCarbonDioxidePressure()) ? &respiratory.GetEndTidalCarbonDioxidePressure() : nullptr;
	_expiratoryFlow = (respiratory.HasExpiratoryFlow()) ? &respiratory.GetExpiratoryFlow() : nullptr;
	_inspiratoryExpiratoryRatio = (respiratory.HasInspiratoryExpiratoryRatio()) ? &respiratory.GetInspiratoryExpiratoryRatio() : nullptr;
	_inspiratoryFlow = (respiratory.HasInspiratoryFlow()) ? &respiratory.GetInspiratoryFlow() : nullptr;
	_pulmonaryCompliance = (respiratory.HasPulmonaryCompliance()) ? &respiratory.GetPulmonaryCompliance() : nullptr;
	_pulmonaryResistance = (respiratory.HasPulmonaryResistance()) ? &respiratory.GetPulmonaryResistance() : nullptr;
	_respirationDriverPressure = (respiratory.HasRespirationDriverPressure()) ? &respiratory.GetRespirationDriverPressure() : nullptr;
	_respirationMusclePressure = (respiratory.HasRespirationMusclePressure()) ? &respiratory.GetRespirationMusclePressure() : nullptr;
	_respirationRate = (respiratory.HasRespirationRate()) ? &respiratory.GetRespirationRate() : nullptr;
	_specificVentilation = (respiratory.HasSpecificVentilation()) ? &respiratory.GetSpecificVentilation() : nullptr;
	_targetPulmonaryVentilation = (respiratory.HasTargetPulmonaryVentilation()) ? &respiratory.GetTargetPulmonaryVentilation() : nullptr;
	_tidalVolume = (respiratory.HasTidalVolume()) ? &respiratory.GetTidalVolume() : nullptr;
	_totalAlveolarVentilation = (respiratory.HasTotalAlveolarVentilation()) ? &respiratory.GetTotalAlveolarVentilation() : nullptr;
	_totalDeadSpaceVentilation = (respiratory.HasTotalDeadSpaceVentilation()) ? &respiratory.GetTotalDeadSpaceVentilation() : nullptr;
	_totalLungVolume = (respiratory.HasTotalLungVolume()) ? &respiratory.GetTotalLungVolume() : nullptr;
	_totalPulmonaryVentilation = (respiratory.HasTotalPulmonaryVentilation()) ? &respiratory.GetTotalPulmonaryVentilation() : nullptr;
	_transpulmonaryPressure = (respiratory.HasTranspulmonaryPressure()) ? &respiratory.GetTranspulmonaryPressure() : nullptr;

	//Tissue
	auto& tissue = bg->GetTissue();
	_carbonDioxideProductionRate = (tissue.HasCarbonDioxideProductionRate()) ? &tissue.GetCarbonDioxideProductionRate() : nullptr;
	_dehydrationFraction = (tissue.HasDehydrationFraction()) ? &tissue.GetDehydrationFraction() : nullptr;
	_extracellularFluidVolume = (tissue.HasExtracellularFluidVolume()) ? &tissue.GetExtracellularFluidVolume() : nullptr;
	_extravascularFluidVolume = (tissue.HasExtravascularFluidVolume()) ? &tissue.GetExtravascularFluidVolume() : nullptr;
	_intracellularFluidPH = (tissue.HasIntracellularFluidPH()) ? &tissue.GetIntracellularFluidPH() : nullptr;
	_intracellularFluidVolume = (tissue.HasIntracellularFluidVolume()) ? &tissue.GetIntracellularFluidVolume() : nullptr;
	_totalBodyFluidVolume = (tissue.HasTotalBodyFluidVolume()) ? &tissue.GetTotalBodyFluidVolume() : nullptr;
	_oxygenConsumptionRate = (tissue.HasOxygenConsumptionRate()) ? &tissue.GetOxygenConsumptionRate() : nullptr;
	_respiratoryExchangeRatio = (tissue.HasRespiratoryExchangeRatio()) ? &tissue.GetRespiratoryExchangeRatio() : nullptr;
	_liverInsulinSetPoint = (tissue.HasLiverInsulinSetPoint()) ? &tissue.GetLiverInsulinSetPoint() : nullptr;
	_liverGlucagonSetPoint = (tissue.HasLiverGlucagonSetPoint()) ? &tissue.GetLiverGlucagonSetPoint() : nullptr;
	_muscleInsulinSetPoint = (tissue.HasMuscleInsulinSetPoint()) ? &tissue.GetMuscleInsulinSetPoint() : nullptr;
	_muscleGlucagonSetPoint = (tissue.HasMuscleGlucagonSetPoint()) ? &tissue.GetMuscleGlucagonSetPoint() : nullptr;
	_fatInsulinSetPoint = (tissue.HasFatInsulinSetPoint()) ? &tissue.GetFatInsulinSetPoint() : nullptr;
	_fatGlucagonSetPoint = (tissue.HasFatGlucagonSetPoint()) ? &tissue.GetFatGlucagonSetPoint() : nullptr;
	_liverGlycogen = (tissue.HasLiverGlycogen()) ? &tissue.GetLiverGlycogen() : nullptr;
	_muscleGlycogen = (tissue.HasMuscleGlycogen()) ? &tissue.GetMuscleGlycogen() : nullptr;
	_storedProtein = (tissue.HasStoredProtein()) ? &tissue.GetStoredProtein() : nullptr;
	_storedFat = (tissue.HasStoredFat()) ? &tissue.GetStoredFat() : nullptr;
}
void UBioGearsEngine::Implementation::update_cache() {
	update_metrics();
	update_state();
	update_conditions();
}
void UBioGearsEngine::Implementation::update_metrics() {
	auto& bloodChemistry = bg->GetBloodChemistry();
	metrics.bloodChemistry.arterialBloodPH = (_arterialBloodPH) ? _arterialBloodPH->GetValue() : 0.0;
	metrics.bloodChemistry.arterialBloodPHBaseline = (_arterialBloodPHBaseline) ? _arterialBloodPHBaseline->GetValue() : 0.0;
	metrics.bloodChemistry.bloodDensity = (_bloodDensity) ? _bloodDensity->GetValue() : 0.0;
	metrics.bloodChemistry.bloodSpecificHeat = (_bloodSpecificHeat) ? _bloodSpecificHeat->GetValue() : 0.0;
	metrics.bloodChemistry.bloodUreaNitrogenConcentration = (_bloodUreaNitrogenConcentration) ? _bloodUreaNitrogenConcentration->GetValue() : 0.0;
	metrics.bloodChemistry.carbonDioxideSaturation = (_carbonDioxideSaturation) ? _carbonDioxideSaturation->GetValue() : 0.0;
	metrics.bloodChemistry.carbonMonoxideSaturation = (_carbonMonoxideSaturation) ? _carbonMonoxideSaturation->GetValue() : 0.0;
	metrics.bloodChemistry.hematocrit = (_hematocrit) ? _hematocrit->GetValue() : 0.0;
	metrics.bloodChemistry.hemoglobinContent = (_hemoglobinContent) ? _hemoglobinContent->GetValue() : 0.0;
	metrics.bloodChemistry.oxygenSaturation = (_oxygenSaturation) ? _oxygenSaturation->GetValue() : 0.0;
	metrics.bloodChemistry.phosphate = (_phosphate) ? _phosphate->GetValue() : 0.0;
	metrics.bloodChemistry.plasmaVolume = (_plasmaVolume) ? _plasmaVolume->GetValue() : 0.0;
	metrics.bloodChemistry.pulseOximetry = (_pulseOximetry) ? _pulseOximetry->GetValue() : 0.0;
	metrics.bloodChemistry.redBloodCellAcetylcholinesterase = (_redBloodCellAcetylcholinesterase) ? _redBloodCellAcetylcholinesterase->GetValue() : 0.0;
	metrics.bloodChemistry.redBloodCellCount = (_redBloodCellCount) ? _redBloodCellCount->GetValue(biogears::AmountPerVolumeUnit::ct_Per_uL) : 0.0;
	metrics.bloodChemistry.shuntFraction = (_shuntFraction) ? _shuntFraction->GetValue() : 0.0;
	metrics.bloodChemistry.strongIonDifference = (_strongIonDifference) ? _strongIonDifference->GetValue() : 0.0;
	metrics.bloodChemistry.totalBilirubin = (_totalBilirubin) ? _totalBilirubin->GetValue() : 0.0;
	metrics.bloodChemistry.totalProteinConcentration = (_totalProteinConcentration) ? _totalProteinConcentration->GetValue() : 0.0;
	metrics.bloodChemistry.venousBloodPH = (_venousBloodPH) ? _venousBloodPH->GetValue() : 0.0;
	metrics.bloodChemistry.volumeFractionNeutralPhospholipidInPlasma = (_volumeFractionNeutralPhospholipidInPlasma) ? _volumeFractionNeutralPhospholipidInPlasma->GetValue() : 0.0;
	metrics.bloodChemistry.volumeFractionNeutralLipidInPlasma = (_volumeFractionNeutralLipidInPlasma) ? _volumeFractionNeutralLipidInPlasma->GetValue() : 0.0;
	metrics.bloodChemistry.arterialCarbonDioxidePressure = (_arterialCarbonDioxidePressure) ? _arterialCarbonDioxidePressure->GetValue() : 0.0;
	metrics.bloodChemistry.arterialOxygenPressure = (_arterialOxygenPressure) ? _arterialOxygenPressure->GetValue() : 0.0;
	metrics.bloodChemistry.pulmonaryArterialCarbonDioxidePressure = (_pulmonaryArterialCarbonDioxidePressure) ? _pulmonaryArterialCarbonDioxidePressure->GetValue() : 0.0;
	metrics.bloodChemistry.pulmonaryArterialOxygenPressure = (_pulmonaryArterialOxygenPressure) ? _pulmonaryArterialOxygenPressure->GetValue() : 0.0;
	metrics.bloodChemistry.pulmonaryVenousCarbonDioxidePressure = (_pulmonaryVenousCarbonDioxidePressure) ? _pulmonaryVenousCarbonDioxidePressure->GetValue() : 0.0;
	metrics.bloodChemistry.pulmonaryVenousOxygenPressure = (_pulmonaryVenousOxygenPressure) ? _pulmonaryVenousOxygenPressure->GetValue() : 0.0;
	metrics.bloodChemistry.venousCarbonDioxidePressure = (_venousCarbonDioxidePressure) ? _venousCarbonDioxidePressure->GetValue() : 0.0;
	metrics.bloodChemistry.venousOxygenPressure = (_venousOxygenPressure) ? _venousOxygenPressure->GetValue() : 0.0;
	
	metrics.hasInflammatoryResponse = bloodChemistry.HasInflammatoryResponse();

	auto& inflamatoryResponse = bloodChemistry.GetInflammatoryResponse();
	metrics.inflamatroyReponse.LocalPathogen = (_inflammatoryResponseLocalPathogen) ? _inflammatoryResponseLocalPathogen->GetValue() : 0.0;
	metrics.inflamatroyReponse.LocalMacrophage = (_inflammatoryResponseLocalMacrophage) ? _inflammatoryResponseLocalMacrophage->GetValue() : 0.0;
	metrics.inflamatroyReponse.LocalNeutrophil = (_inflammatoryResponseLocalNeutrophil) ? _inflammatoryResponseLocalNeutrophil->GetValue() : 0.0;
	metrics.inflamatroyReponse.LocalBarrier = (_inflammatoryResponseLocalBarrier) ? _inflammatoryResponseLocalBarrier->GetValue() : 0.0;
	metrics.inflamatroyReponse.BloodPathogen = (_inflammatoryResponseBloodPathogen) ? _inflammatoryResponseBloodPathogen->GetValue() : 0.0;
	metrics.inflamatroyReponse.Trauma = (_inflammatoryResponseTrauma) ? _inflammatoryResponseTrauma->GetValue() : 0.0;
	metrics.inflamatroyReponse.MacrophageResting = (_inflammatoryResponseMacrophageResting) ? _inflammatoryResponseMacrophageResting->GetValue() : 0.0;
	metrics.inflamatroyReponse.MacrophageActive = (_inflammatoryResponseMacrophageActive) ? _inflammatoryResponseMacrophageActive->GetValue() : 0.0;
	metrics.inflamatroyReponse.NeutrophilResting = (_inflammatoryResponseNeutrophilResting) ? _inflammatoryResponseNeutrophilResting->GetValue() : 0.0;
	metrics.inflamatroyReponse.NeutrophilActive = (_inflammatoryResponseNeutrophilActive) ? _inflammatoryResponseNeutrophilActive->GetValue() : 0.0;
	metrics.inflamatroyReponse.InducibleNOSPre = (_inflammatoryResponseInducibleNOSPre) ? _inflammatoryResponseInducibleNOSPre->GetValue() : 0.0;
	metrics.inflamatroyReponse.InducibleNOS = (_inflammatoryResponseInducibleNOS) ? _inflammatoryResponseInducibleNOS->GetValue() : 0.0;
	metrics.inflamatroyReponse.ConstitutiveNOS = (_inflammatoryResponseConstitutiveNOS) ? _inflammatoryResponseConstitutiveNOS->GetValue() : 0.0;
	metrics.inflamatroyReponse.Nitrate = (_inflammatoryResponseNitrate) ? _inflammatoryResponseNitrate->GetValue() : 0.0;
	metrics.inflamatroyReponse.NitricOxide = (_inflammatoryResponseNitricOxide) ? _inflammatoryResponseNitricOxide->GetValue() : 0.0;
	metrics.inflamatroyReponse.TumorNecrosisFactor = (_inflammatoryResponseTumorNecrosisFactor) ? _inflammatoryResponseTumorNecrosisFactor->GetValue() : 0.0;
	metrics.inflamatroyReponse.Interleukin6 = (_inflammatoryResponseInterleukin6) ? _inflammatoryResponseInterleukin6->GetValue() : 0.0;
	metrics.inflamatroyReponse.Interleukin10 = (_inflammatoryResponseInterleukin10) ? _inflammatoryResponseInterleukin10->GetValue() : 0.0;
	metrics.inflamatroyReponse.Interleukin12 = (_inflammatoryResponseInterleukin12) ? _inflammatoryResponseInterleukin12->GetValue() : 0.0;
	metrics.inflamatroyReponse.Catecholamines = (_inflammatoryResponseCatecholamines) ? _inflammatoryResponseCatecholamines->GetValue() : 0.0;
	metrics.inflamatroyReponse.TissueIntegrity = (_inflammatoryResponseTissueIntegrity) ? _inflammatoryResponseTissueIntegrity->GetValue() : 0.0;

	auto& cardiovascular = bg->GetCardiovascular();
	metrics.cardiovascular.arterialPressure = (_arterialPressure) ? _arterialPressure->GetValue() : 0.0;
	metrics.cardiovascular.bloodVolume = (_bloodVolume) ? _bloodVolume->GetValue() : 0.0;
	metrics.cardiovascular.cardiacIndex = (_cardiacIndex) ? _cardiacIndex->GetValue() : 0.0;
	metrics.cardiovascular.cardiacOutput = (_cardiacOutput) ? _cardiacOutput->GetValue() : 0.0;
	metrics.cardiovascular.centralVenousPressure = (_centralVenousPressure) ? _centralVenousPressure->GetValue() : 0.0;
	metrics.cardiovascular.cerebralBloodFlow = (_cerebralBloodFlow) ? _cerebralBloodFlow->GetValue() : 0.0;
	metrics.cardiovascular.cerebralPerfusionPressure = (_cerebralPerfusionPressure) ? _cerebralPerfusionPressure->GetValue() : 0.0;
	metrics.cardiovascular.diastolicArterialPressure = (_diastolicArterialPressure) ? _diastolicArterialPressure->GetValue() : 0.0;
	metrics.cardiovascular.heartEjectionFraction = (_heartEjectionFraction) ? _heartEjectionFraction->GetValue() : 0.0;
	metrics.cardiovascular.heartRate = (_heartRate) ? _heartRate->GetValue() : 0.0;
	metrics.cardiovascular.heartStrokeVolume = (_heartStrokeVolume) ? _heartStrokeVolume->GetValue() : 0.0;
	metrics.cardiovascular.intracranialPressure = (_intracranialPressure) ? _intracranialPressure->GetValue() : 0.0;
	metrics.cardiovascular.meanArterialPressure = (_meanArterialPressure) ? _meanArterialPressure->GetValue() : 0.0;
	metrics.cardiovascular.meanArterialCarbonDioxidePartialPressure = (_meanArterialCarbonDioxidePartialPressure) ? _meanArterialCarbonDioxidePartialPressure->GetValue() : 0.0;
	metrics.cardiovascular.meanArterialCarbonDioxidePartialPressureDelta = (_meanArterialCarbonDioxidePartialPressureDelta) ? _meanArterialCarbonDioxidePartialPressureDelta->GetValue() : 0.0;
	metrics.cardiovascular.meanCentralVenousPressure = (_meanCentralVenousPressure) ? _meanCentralVenousPressure->GetValue() : 0.0;
	metrics.cardiovascular.meanSkinFlow = (_meanSkinFlow) ? _meanSkinFlow->GetValue() : 0.0;
	metrics.cardiovascular.pulmonaryArterialPressure = (_pulmonaryArterialPressure) ? _pulmonaryArterialPressure->GetValue() : 0.0;
	metrics.cardiovascular.pulmonaryCapillariesWedgePressure = (_pulmonaryCapillariesWedgePressure) ? _pulmonaryCapillariesWedgePressure->GetValue() : 0.0;
	metrics.cardiovascular.pulmonaryDiastolicArterialPressure = (_pulmonaryDiastolicArterialPressure) ? _pulmonaryDiastolicArterialPressure->GetValue() : 0.0;
	metrics.cardiovascular.pulmonaryMeanArterialPressure = (_pulmonaryMeanArterialPressure) ? _pulmonaryMeanArterialPressure->GetValue() : 0.0;
	metrics.cardiovascular.pulmonaryMeanCapillaryFlow = (_pulmonaryMeanCapillaryFlow) ? _pulmonaryMeanCapillaryFlow->GetValue() : 0.0;
	metrics.cardiovascular.pulmonaryMeanShuntFlow = (_pulmonaryMeanShuntFlow) ? _pulmonaryMeanShuntFlow->GetValue() : 0.0;
	metrics.cardiovascular.pulmonarySystolicArterialPressure = (_pulmonarySystolicArterialPressure) ? _pulmonarySystolicArterialPressure->GetValue() : 0.0;
	metrics.cardiovascular.pulmonaryVascularResistance = (_pulmonaryVascularResistance) ? _pulmonaryVascularResistance->GetValue() : 0.0;
	metrics.cardiovascular.pulmonaryVascularResistanceIndex = (_pulmonaryVascularResistanceIndex) ? _pulmonaryVascularResistanceIndex->GetValue() : 0.0;
	metrics.cardiovascular.pulsePressure = (_pulsePressure) ? _pulsePressure->GetValue() : 0.0;
	metrics.cardiovascular.systemicVascularResistance = (_systemicVascularResistance) ? _systemicVascularResistance->GetValue() : 0.0;
	metrics.cardiovascular.systolicArterialPressure = (_systolicArterialPressure) ? _systolicArterialPressure->GetValue() : 0.0;

	auto& drugs = bg->GetDrugs();
	metrics.drugs.bronchodilationLevel = (_bronchodilationLevel) ? _bronchodilationLevel->GetValue() : 0.0;
	metrics.drugs.heartRateChange = (_heartRateChange) ? _heartRateChange->GetValue() : 0.0;
	metrics.drugs.meanBloodPressureChange = (_meanBloodPressureChange) ? _meanBloodPressureChange->GetValue() : 0.0;
	metrics.drugs.meanBloodPressureChange = (_meanBloodPressureChange) ? _meanBloodPressureChange->GetValue() : 0.0;
	metrics.drugs.neuromuscularBlockLevel = (_neuromuscularBlockLevel) ? _neuromuscularBlockLevel->GetValue() : 0.0;
	metrics.drugs.pulsePressureChange = (_pulsePressureChange) ? _pulsePressureChange->GetValue() : 0.0;
	metrics.drugs.respirationRateChange = (_respirationRateChange) ? _respirationRateChange->GetValue() : 0.0;
	metrics.drugs.sedationLevel = (_sedationLevel) ? _sedationLevel->GetValue() : 0.0;
	metrics.drugs.tidalVolumeChange = (_tidalVolumeChange) ? _tidalVolumeChange->GetValue() : 0.0;
	metrics.drugs.tubularPermeabilityChange = (_tubularPermeabilityChange) ? _tubularPermeabilityChange->GetValue() : 0.0;
	metrics.drugs.centralNervousResponse = (_centralNervousResponse) ? _centralNervousResponse->GetValue() : 0.0;

	auto& endocrine = bg->GetEndocrine();
	metrics.endocrine.insulinSynthesisRate = (_insulinSynthesisRate) ? _insulinSynthesisRate->GetValue() : 0.0;
	metrics.endocrine.glucagonSynthesisRate = (_glucagonSynthesisRate) ? _glucagonSynthesisRate->GetValue() : 0.0;

	auto& energy = bg->GetEnergy();
	metrics.energy.achievedExerciseLevel = (_achievedExerciseLevel) ? _achievedExerciseLevel->GetValue() : 0.0;
	metrics.energy.chlorideLostToSweat = (_chlorideLostToSweat) ? _chlorideLostToSweat->GetValue() : 0.0;
	metrics.energy.coreTemperature = (_coreTemperature) ? _coreTemperature->GetValue() : 0.0;
	metrics.energy.creatinineProductionRate = (_creatinineProductionRate) ? _creatinineProductionRate->GetValue() : 0.0;
	metrics.energy.exerciseMeanArterialPressureDelta = (_exerciseMeanArterialPressureDelta) ? _exerciseMeanArterialPressureDelta->GetValue() : 0.0;
	metrics.energy.fatigueLevel = (_fatigueLevel) ? _fatigueLevel->GetValue() : 0.0;
	metrics.energy.lactateProductionRate = (_lactateProductionRate) ? _lactateProductionRate->GetValue() : 0.0;
	metrics.energy.potassiumLostToSweat = (_potassiumLostToSweat) ? _potassiumLostToSweat->GetValue() : 0.0;
	metrics.energy.skinTemperature = (_skinTemperature) ? _skinTemperature->GetValue() : 0.0;
	metrics.energy.sodiumLostToSweat = (_sodiumLostToSweat) ? _sodiumLostToSweat->GetValue() : 0.0;
	metrics.energy.sweatRate = (_sweatRate) ? _sweatRate->GetValue() : 0.0;
	metrics.energy.totalMetabolicRate = (_totalMetabolicRate) ? _totalMetabolicRate->GetValue() : 0.0;
	metrics.energy.totalWorkRateLevel = (_totalWorkRateLevel) ? _totalWorkRateLevel->GetValue() : 0.0;

	auto& gastrointestinal = bg->GetGastrointestinal();
	metrics.gastrointestinal.chymeAbsorptionRate = (_chymeAbsorptionRate) ? _chymeAbsorptionRate->GetValue() : 0.0;
	metrics.gastrointestinal.stomachContents_calcium = (_stomachContents_calcium) ? _stomachContents_calcium->GetValue() : 0.0;
	metrics.gastrointestinal.stomachContents_carbohydrates = (_stomachContents_carbohydrates) ? _stomachContents_carbohydrates->GetValue() : 0.0;
	metrics.gastrointestinal.stomachContents_carbohydrateDigationRate = (_stomachContents_carbohydrateDigationRate) ? _stomachContents_carbohydrateDigationRate->GetValue() : 0.0;
	metrics.gastrointestinal.stomachContents_fat = (_stomachContents_fat) ? _stomachContents_fat->GetValue() : 0.0;
	metrics.gastrointestinal.stomachContents_fatDigtationRate = (_stomachContents_fatDigtationRate) ? _stomachContents_fatDigtationRate->GetValue() : 0.0;
	metrics.gastrointestinal.stomachContents_protien = (_stomachContents_protien) ? _stomachContents_protien->GetValue() : 0.0;
	metrics.gastrointestinal.stomachContents_protienDigtationRate = (_stomachContents_protienDigtationRate) ? _stomachContents_protienDigtationRate->GetValue() : 0.0;
	metrics.gastrointestinal.stomachContents_sodium = (_stomachContents_sodium) ? _stomachContents_sodium->GetValue() : 0.0;
	metrics.gastrointestinal.stomachContents_water = (_stomachContents_water) ? _stomachContents_water->GetValue() : 0.0;

	auto& hepatic = bg->GetHepatic();
	metrics.hepatic.hepaticGluconeogenesisRate = (_hepaticGluconeogenesisRate) ? _hepaticGluconeogenesisRate->GetValue() : 0.0;
	metrics.hepatic.ketoneproductionRate = (_ketoneproductionRate) ? _ketoneproductionRate->GetValue() : 0.0;

	auto& nervous = bg->GetNervous();
	metrics.nervous.baroreceptorHeartRateScale = (_baroreceptorHeartRateScale) ? _baroreceptorHeartRateScale->GetValue() : 0.0;
	metrics.nervous.baroreceptorHeartElastanceScale = (_baroreceptorHeartElastanceScale) ? _baroreceptorHeartElastanceScale->GetValue() : 0.0;
	metrics.nervous.baroreceptorResistanceScale = (_baroreceptorResistanceScale) ? _baroreceptorResistanceScale->GetValue() : 0.0;
	metrics.nervous.baroreceptorComplianceScale = (_baroreceptorComplianceScale) ? _baroreceptorComplianceScale->GetValue() : 0.0;
	metrics.nervous.chemoreceptorHeartRateScale = (_chemoreceptorHeartRateScale) ? _chemoreceptorHeartRateScale->GetValue() : 0.0;
	metrics.nervous.chemoreceptorHeartElastanceScale = (_chemoreceptorHeartElastanceScale) ? _chemoreceptorHeartElastanceScale->GetValue() : 0.0;
	metrics.nervous.painVisualAnalogueScale = (_painVisualAnalogueScale) ? _painVisualAnalogueScale->GetValue() : 0.0;

	//TODO: Implement Pupillary Response  ReactivityModifier  ShapeModifier  SizeModifier;
	metrics.nervous.leftEyePupillaryResponse = 0.0;
	metrics.nervous.rightEyePupillaryResponse = 0.0;

	//Renal
	auto& renal = bg->GetRenal();
	metrics.renal.glomerularFiltrationRate = (_glomerularFiltrationRate) ? _glomerularFiltrationRate->GetValue() : 0.0;
	metrics.renal.filtrationFraction = (_filtrationFraction) ? _filtrationFraction->GetValue() : 0.0;
	metrics.renal.leftAfferentArterioleResistance = (_leftAfferentArterioleResistance) ? _leftAfferentArterioleResistance->GetValue() : 0.0;
	metrics.renal.leftBowmansCapsulesHydrostaticPressure = (_leftBowmansCapsulesHydrostaticPressure) ? _leftBowmansCapsulesHydrostaticPressure->GetValue() : 0.0;
	metrics.renal.leftBowmansCapsulesOsmoticPressure = (_leftBowmansCapsulesOsmoticPressure) ? _leftBowmansCapsulesOsmoticPressure->GetValue() : 0.0;
	metrics.renal.leftEfferentArterioleResistance = (_leftEfferentArterioleResistance) ? _leftEfferentArterioleResistance->GetValue() : 0.0;
	metrics.renal.leftGlomerularCapillariesHydrostaticPressure = (_leftGlomerularCapillariesHydrostaticPressure) ? _leftGlomerularCapillariesHydrostaticPressure->GetValue() : 0.0;
	metrics.renal.leftGlomerularCapillariesOsmoticPressure = (_leftGlomerularCapillariesOsmoticPressure) ? _leftGlomerularCapillariesOsmoticPressure->GetValue() : 0.0;
	metrics.renal.leftGlomerularFiltrationCoefficient = (_leftGlomerularFiltrationCoefficient) ? _leftGlomerularFiltrationCoefficient->GetValue() : 0.0;
	metrics.renal.leftGlomerularFiltrationRate = (_leftGlomerularFiltrationRate) ? _leftGlomerularFiltrationRate->GetValue() : 0.0;
	metrics.renal.leftGlomerularFiltrationSurfaceArea = (_leftGlomerularFiltrationSurfaceArea) ? _leftGlomerularFiltrationSurfaceArea->GetValue() : 0.0;
	metrics.renal.leftGlomerularFluidPermeability = (_leftGlomerularFluidPermeability) ? _leftGlomerularFluidPermeability->GetValue() : 0.0;
	metrics.renal.leftFiltrationFraction = (_leftFiltrationFraction) ? _leftFiltrationFraction->GetValue() : 0.0;
	metrics.renal.leftNetFiltrationPressure = (_leftNetFiltrationPressure) ? _leftNetFiltrationPressure->GetValue() : 0.0;
	metrics.renal.leftNetReabsorptionPressure = (_leftNetReabsorptionPressure) ? _leftNetReabsorptionPressure->GetValue() : 0.0;
	metrics.renal.leftPeritubularCapillariesHydrostaticPressure = (_leftPeritubularCapillariesHydrostaticPressure) ? _leftPeritubularCapillariesHydrostaticPressure->GetValue() : 0.0;
	metrics.renal.leftPeritubularCapillariesOsmoticPressure = (_leftPeritubularCapillariesOsmoticPressure) ? _leftPeritubularCapillariesOsmoticPressure->GetValue() : 0.0;
	metrics.renal.leftReabsorptionFiltrationCoefficient = (_leftReabsorptionFiltrationCoefficient) ? _leftReabsorptionFiltrationCoefficient->GetValue() : 0.0;
	metrics.renal.leftReabsorptionRate = (_leftReabsorptionRate) ? _leftReabsorptionRate->GetValue() : 0.0;
	metrics.renal.leftTubularReabsorptionFiltrationSurfaceArea = (_leftTubularReabsorptionFiltrationSurfaceArea) ? _leftTubularReabsorptionFiltrationSurfaceArea->GetValue() : 0.0;
	metrics.renal.leftTubularReabsorptionFluidPermeability = (_leftTubularReabsorptionFluidPermeability) ? _leftTubularReabsorptionFluidPermeability->GetValue() : 0.0;
	metrics.renal.leftTubularHydrostaticPressure = (_leftTubularHydrostaticPressure) ? _leftTubularHydrostaticPressure->GetValue() : 0.0;
	metrics.renal.leftTubularOsmoticPressure = (_leftTubularOsmoticPressure) ? _leftTubularOsmoticPressure->GetValue() : 0.0;
	metrics.renal.renalBloodFlow = (_renalBloodFlow) ? _renalBloodFlow->GetValue() : 0.0;
	metrics.renal.renalPlasmaFlow = (_renalPlasmaFlow) ? _renalPlasmaFlow->GetValue() : 0.0;
	metrics.renal.renalVascularResistance = (_renalVascularResistance) ? _renalVascularResistance->GetValue() : 0.0;
	metrics.renal.rightAfferentArterioleResistance = (_rightAfferentArterioleResistance) ? _rightAfferentArterioleResistance->GetValue() : 0.0;
	metrics.renal.rightBowmansCapsulesHydrostaticPressure = (_rightBowmansCapsulesHydrostaticPressure) ? _rightBowmansCapsulesHydrostaticPressure->GetValue() : 0.0;
	metrics.renal.rightBowmansCapsulesOsmoticPressure = (_rightBowmansCapsulesOsmoticPressure) ? _rightBowmansCapsulesOsmoticPressure->GetValue() : 0.0;
	metrics.renal.rightEfferentArterioleResistance = (_rightEfferentArterioleResistance) ? _rightEfferentArterioleResistance->GetValue() : 0.0;
	metrics.renal.rightGlomerularCapillariesHydrostaticPressure = (_rightGlomerularCapillariesHydrostaticPressure) ? _rightGlomerularCapillariesHydrostaticPressure->GetValue() : 0.0;
	metrics.renal.rightGlomerularCapillariesOsmoticPressure = (_rightGlomerularCapillariesOsmoticPressure) ? _rightGlomerularCapillariesOsmoticPressure->GetValue() : 0.0;
	metrics.renal.rightGlomerularFiltrationCoefficient = (_rightGlomerularFiltrationCoefficient) ? _rightGlomerularFiltrationCoefficient->GetValue() : 0.0;
	metrics.renal.rightGlomerularFiltrationRate = (_rightGlomerularFiltrationRate) ? _rightGlomerularFiltrationRate->GetValue() : 0.0;
	metrics.renal.rightGlomerularFiltrationSurfaceArea = (_rightGlomerularFiltrationSurfaceArea) ? _rightGlomerularFiltrationSurfaceArea->GetValue() : 0.0;
	metrics.renal.rightGlomerularFluidPermeability = (_rightGlomerularFluidPermeability) ? _rightGlomerularFluidPermeability->GetValue() : 0.0;
	metrics.renal.rightFiltrationFraction = (_rightFiltrationFraction) ? _rightFiltrationFraction->GetValue() : 0.0;
	metrics.renal.rightNetFiltrationPressure = (_rightNetFiltrationPressure) ? _rightNetFiltrationPressure->GetValue() : 0.0;
	metrics.renal.rightNetReabsorptionPressure = (_rightNetReabsorptionPressure) ? _rightNetReabsorptionPressure->GetValue() : 0.0;
	metrics.renal.rightPeritubularCapillariesHydrostaticPressure = (_rightPeritubularCapillariesHydrostaticPressure) ? _rightPeritubularCapillariesHydrostaticPressure->GetValue() : 0.0;
	metrics.renal.rightPeritubularCapillariesOsmoticPressure = (_rightPeritubularCapillariesOsmoticPressure) ? _rightPeritubularCapillariesOsmoticPressure->GetValue() : 0.0;
	metrics.renal.rightReabsorptionFiltrationCoefficient = (_rightReabsorptionFiltrationCoefficient) ? _rightReabsorptionFiltrationCoefficient->GetValue() : 0.0;
	metrics.renal.rightReabsorptionRate = (_rightReabsorptionRate) ? _rightReabsorptionRate->GetValue() : 0.0;
	metrics.renal.rightTubularReabsorptionFiltrationSurfaceArea = (_rightTubularReabsorptionFiltrationSurfaceArea) ? _rightTubularReabsorptionFiltrationSurfaceArea->GetValue() : 0.0;
	metrics.renal.rightTubularReabsorptionFluidPermeability = (_rightTubularReabsorptionFluidPermeability) ? _rightTubularReabsorptionFluidPermeability->GetValue() : 0.0;
	metrics.renal.rightTubularHydrostaticPressure = (_rightTubularHydrostaticPressure) ? _rightTubularHydrostaticPressure->GetValue() : 0.0;
	metrics.renal.rightTubularOsmoticPressure = (_rightTubularOsmoticPressure) ? _rightTubularOsmoticPressure->GetValue() : 0.0;
	metrics.renal.urinationRate = (_urinationRate) ? _urinationRate->GetValue() : 0.0;
	metrics.renal.urineOsmolality = (_urineOsmolality) ? _urineOsmolality->GetValue() : 0.0;
	metrics.renal.urineOsmolarity = (_urineOsmolarity) ? _urineOsmolarity->GetValue() : 0.0;
	metrics.renal.urineProductionRate = (_urineProductionRate) ? _urineProductionRate->GetValue() : 0.0;
	metrics.renal.meanUrineOutput = (_meanUrineOutput) ? _meanUrineOutput->GetValue() : 0.0;
	metrics.renal.urineSpecificGravity = (_urineSpecificGravity) ? _urineSpecificGravity->GetValue() : 0.0;
	metrics.renal.urineVolume = (_urineVolume) ? _urineVolume->GetValue() : 0.0;
	metrics.renal.urineUreaNitrogenConcentration = (_urineUreaNitrogenConcentration) ? _urineUreaNitrogenConcentration->GetValue() : 0.0;

	//Respiratory
	auto& respiratory = bg->GetRespiratory();
	metrics.respiratory.alveolarArterialGradient = (_alveolarArterialGradient) ? _alveolarArterialGradient->GetValue() : 0.0;
	metrics.respiratory.carricoIndex = (_carricoIndex) ? _carricoIndex->GetValue() : 0.0;
	metrics.respiratory.endTidalCarbonDioxideFraction = (_endTidalCarbonDioxideFraction) ? _endTidalCarbonDioxideFraction->GetValue() : 0.0;
	metrics.respiratory.endTidalCarbonDioxidePressure = (_endTidalCarbonDioxidePressure) ? _endTidalCarbonDioxidePressure->GetValue() : 0.0;
	metrics.respiratory.expiratoryFlow = (_expiratoryFlow) ? _expiratoryFlow->GetValue() : 0.0;
	metrics.respiratory.inspiratoryExpiratoryRatio = (_inspiratoryExpiratoryRatio) ? _inspiratoryExpiratoryRatio->GetValue() : 0.0;
	metrics.respiratory.inspiratoryFlow = (_inspiratoryFlow) ? _inspiratoryFlow->GetValue() : 0.0;
	metrics.respiratory.pulmonaryCompliance = (_pulmonaryCompliance) ? _pulmonaryCompliance->GetValue() : 0.0;
	metrics.respiratory.pulmonaryResistance = (_pulmonaryResistance) ? _pulmonaryResistance->GetValue() : 0.0;
	metrics.respiratory.respirationDriverPressure = (_respirationDriverPressure) ? _respirationDriverPressure->GetValue() : 0.0;
	metrics.respiratory.respirationMusclePressure = (_respirationMusclePressure) ? _respirationMusclePressure->GetValue() : 0.0;
	metrics.respiratory.respirationRate = (_respirationRate) ? _respirationRate->GetValue() : 0.0;
	metrics.respiratory.specificVentilation = (_specificVentilation) ? _specificVentilation->GetValue() : 0.0;
	metrics.respiratory.targetPulmonaryVentilation = (_targetPulmonaryVentilation) ? _targetPulmonaryVentilation->GetValue() : 0.0;
	metrics.respiratory.tidalVolume = (_tidalVolume) ? _tidalVolume->GetValue() : 0.0;
	metrics.respiratory.totalAlveolarVentilation = (_totalAlveolarVentilation) ? _totalAlveolarVentilation->GetValue() : 0.0;
	metrics.respiratory.totalDeadSpaceVentilation = (_totalDeadSpaceVentilation) ? _totalDeadSpaceVentilation->GetValue() : 0.0;
	metrics.respiratory.totalLungVolume = (_totalLungVolume) ? _totalLungVolume->GetValue() : 0.0;
	metrics.respiratory.totalPulmonaryVentilation = (_totalPulmonaryVentilation) ? _totalPulmonaryVentilation->GetValue() : 0.0;
	metrics.respiratory.transpulmonaryPressure = (_transpulmonaryPressure) ? _transpulmonaryPressure->GetValue() : 0.0;

	//Tissue
	auto& tissue = bg->GetTissue();
	metrics.tissue.carbonDioxideProductionRate = (_carbonDioxideProductionRate) ? _carbonDioxideProductionRate->GetValue() : 0.0;
	metrics.tissue.dehydrationFraction = (_dehydrationFraction) ? _dehydrationFraction->GetValue() : 0.0;
	metrics.tissue.extracellularFluidVolume = (_extracellularFluidVolume) ? _extracellularFluidVolume->GetValue() : 0.0;
	metrics.tissue.extravascularFluidVolume = (_extravascularFluidVolume) ? _extravascularFluidVolume->GetValue() : 0.0;
	metrics.tissue.intracellularFluidPH = (_intracellularFluidPH) ? _intracellularFluidPH->GetValue() : 0.0;
	metrics.tissue.intracellularFluidVolume = (_intracellularFluidVolume) ? _intracellularFluidVolume->GetValue() : 0.0;
	metrics.tissue.totalBodyFluidVolume = (_totalBodyFluidVolume) ? _totalBodyFluidVolume->GetValue() : 0.0;
	metrics.tissue.oxygenConsumptionRate = (_oxygenConsumptionRate) ? _oxygenConsumptionRate->GetValue() : 0.0;
	metrics.tissue.respiratoryExchangeRatio = (_respiratoryExchangeRatio) ? _respiratoryExchangeRatio->GetValue() : 0.0;
	metrics.tissue.liverInsulinSetPoint = (_liverInsulinSetPoint) ? _liverInsulinSetPoint->GetValue() : 0.0;
	metrics.tissue.liverGlucagonSetPoint = (_liverGlucagonSetPoint) ? _liverGlucagonSetPoint->GetValue() : 0.0;
	metrics.tissue.muscleInsulinSetPoint = (_muscleInsulinSetPoint) ? _muscleInsulinSetPoint->GetValue() : 0.0;
	metrics.tissue.muscleGlucagonSetPoint = (_muscleGlucagonSetPoint) ? _muscleGlucagonSetPoint->GetValue() : 0.0;
	metrics.tissue.fatInsulinSetPoint = (_fatInsulinSetPoint) ? _fatInsulinSetPoint->GetValue() : 0.0;
	metrics.tissue.fatGlucagonSetPoint = (_fatGlucagonSetPoint) ? _fatGlucagonSetPoint->GetValue() : 0.0;
	metrics.tissue.liverGlycogen = (_liverGlycogen) ? _liverGlycogen->GetValue() : 0.0;
	metrics.tissue.muscleGlycogen = (_muscleGlycogen) ? _muscleGlycogen->GetValue() : 0.0;
	metrics.tissue.storedProtein = (_storedProtein) ? _storedProtein->GetValue() : 0.0;
	metrics.tissue.storedFat = (_storedFat) ? _storedFat->GetValue() : 0.0;
}
void UBioGearsEngine::Implementation::update_conditions() {

	conditions.diabieties = bg->GetConditions().HasDiabetesType1() | bg->GetConditions().HasDiabetesType2();

}
void UBioGearsEngine::Implementation::update_state() {

	const auto& patient = bg->GetPatient();
	state.living = true; //TODO:Implement IsAlive
	state.tacycardia = false; //TODO: Implement Tacycardia HR > 100

	state.age_yr = (patient.HasAge()) ? patient.GetAge(biogears::TimeUnit::yr) : 0.0;
	state.height_cm = (patient.HasHeight()) ? patient.GetHeight(biogears::LengthUnit::cm) : 0.0;
	state.gender = (!patient.HasGender()) ? EGender::NONE
		: (patient.GetGender() == CDM::enumSex::Male) ? EGender::MALE
		: EGender::OTHER;
	state.weight_kg = (patient.HasWeight()) ? patient.GetWeight(biogears::MassUnit::kg) :  0.0f;
	if (patient.HasWeight() && patient.HasWeight()) {
		auto BSA = std::sqrt(patient.GetHeight(biogears::LengthUnit::cm) * patient.GetWeight(biogears::MassUnit::kg) / 3600.0);
		state.body_surface_area_m_sq = BSA;
		auto BMI = patient.GetWeight(biogears::MassUnit::kg) / std::pow(patient.GetHeight(biogears::LengthUnit::m), 2);
		state.body_mass_index_kg_per_m_sq = BMI;
	}
	else {
		state.body_surface_area_m_sq = 0.0;
		state.body_mass_index_kg_per_m_sq = 0.0;
	}
	state.body_fat_pct = (patient.HasBodyFatFraction()) ? patient.GetBodyFatFraction()	: 0.0;
	//TODO: Lets take intensity and make a series of animated GIFs inspired off vault-boy
	state.exercise_state = (bg->GetActions().GetPatientActions().HasExercise()) ? EExerciseState::STANDING : EExerciseState::RUNNING;


}
//-------------------------------------------------------------------------------
UBioGearsEngine::UBioGearsEngine()
	: _pimpl(MakeUnique<Implementation>())
{

}
UBioGearsEngine::UBioGearsEngine(FString name)
	: _pimpl(MakeUnique<Implementation>(TCHAR_TO_ANSI(*FPaths::GetPath("./")), TCHAR_TO_ANSI(*name)))
{
}
UBioGearsEngine::UBioGearsEngine(FString dataRoot, FString name)
	: _pimpl(MakeUnique<Implementation>(TCHAR_TO_ANSI(*dataRoot), TCHAR_TO_ANSI(*name)))
{
}
UBioGearsEngine::UBioGearsEngine(FString dataRoot, TUniquePtr<UBioGearsLogger> logger)
	: _pimpl(MakeUnique<Implementation>(TCHAR_TO_ANSI(*dataRoot), std::move(logger)))
{
}
//-------------------------------------------------------------------------------
UBioGearsEngine::UBioGearsEngine(UBioGearsEngine&& obj) noexcept
	: _pimpl(std::move(obj._pimpl))
{
	obj._pimpl = TUniquePtr<Implementation>();
}
//-------------------------------------------------------------------------------
UBioGearsEngine::~UBioGearsEngine()
{
	_pimpl = nullptr;
}
//-------------------------------------------------------------------------------
UBioGearsEngine& UBioGearsEngine::operator=(UBioGearsEngine&& rhs) noexcept
{
	this->_pimpl = std::move(rhs._pimpl);
	rhs._pimpl = TUniquePtr<Implementation>();
	return *this;
}

//-------------------------------------------------------------------------------
float UBioGearsEngine::getSimulationTime() const
{
	return static_cast<float>(_pimpl->bg->GetSimulationTime(biogears::TimeUnit::s));
}
//-------------------------------------------------------------------------------
FBiogearsMetrics    UBioGearsEngine::getMetrics() const
{
	return _pimpl->metrics;
}
//-------------------------------------------------------------------------------
FBiogearsConditions UBioGearsEngine::getConditions() const
{
	return _pimpl->conditions;
}
//-------------------------------------------------------------------------------
FBiogearsState      UBioGearsEngine::getState() const
{
	return _pimpl->state;
}
//-------------------------------------------------------------------------------
bool UBioGearsEngine::load_patient(FString patientFile)
{
	//TODO:: Validate InitializeEngine can be called multiple times
	//TODO:: Might Need TO create a new BG here and retain WD
	std::lock_guard<std::mutex> guard{ _pimpl->mutex };
	_pimpl->bg = MakeUnique<biogears::BioGearsEngine>(_pimpl->logger.Get(), _pimpl->data_root);
	_pimpl->logger->init();
	_pimpl->ready = _pimpl->bg->InitializeEngine(TCHAR_TO_ANSI(*patientFile));
	if (_pimpl->ready) {
		_pimpl->setup_cache();
		_pimpl->update_cache();
	}
	return _pimpl->ready;
}
//-------------------------------------------------------------------------------
bool UBioGearsEngine::load_patient_state(FString stateFile)
{
	std::lock_guard<std::mutex> guard{ _pimpl->mutex };
	_pimpl->bg = MakeUnique<biogears::BioGearsEngine>(_pimpl->logger.Get(), _pimpl->data_root);
	_pimpl->logger->init();
	_pimpl->ready = _pimpl->bg->LoadState(TCHAR_TO_ANSI(*stateFile));
	if (_pimpl->ready) {
		_pimpl->setup_cache();
		_pimpl->update_cache();
	}
	return _pimpl->ready;
}
//-------------------------------------------------------------------------------
void UBioGearsEngine::advance_time(std::chrono::seconds seconds)
{
	std::lock_guard<std::mutex> guard{ _pimpl->mutex };
	_pimpl->bg->AdvanceModelTime(seconds.count(), biogears::TimeUnit::s);
	_pimpl->update_cache();
}
//-------------------------------------------------------------------------------
bool UBioGearsEngine::process_action(std::unique_ptr<biogears::SEAction> action)
{
	std::lock_guard<std::mutex> guard{ _pimpl->mutex };
	auto result = _pimpl->bg->ProcessAction(*action);
	action.reset();
	return result;
}
//-------------------------------------------------------------------------------
bool UBioGearsEngine::isReady() const
{
	return _pimpl->ready;
}
//-------------------------------------------------------------------------------
#include <biogears/cdm/patient/actions/SEUrinate.h>
bool UBioGearsEngine::action_urinate()
{
	auto relief = biogears::SEUrinate();
	if (relief.IsValid()) {
		std::lock_guard<std::mutex> guard{ _pimpl->mutex };
		_pimpl->bg->ProcessAction(relief);
		return true;
	}
	else {
		return false;
	}
}
//-------------------------------------------------------------------------------
#include <biogears/cdm/patient/assessments/SEUrinalysis.h>
bool UBioGearsEngine::get_urine_color(EUrineColor& eColor)
{
	using namespace biogears;
	std::lock_guard<std::mutex> guard{ _pimpl->mutex };
	SEUrinalysis urineAnalysis{ _pimpl->bg->GetLogger() };
	const biogears::Renal* constRenalSystem = dynamic_cast<const biogears::Renal*>(_pimpl->bg->GetRenalSystem());
	biogears::Renal* renalSystem = const_cast<biogears::Renal*>(constRenalSystem);


	renalSystem->CalculateUrinalysis(urineAnalysis);
	if (urineAnalysis.HasColorResult())
	{
		switch (urineAnalysis.GetColorResult())
		{
		case CDM::enumUrineColor::DarkYellow:
			eColor = EUrineColor::DarkYellow;
		case CDM::enumUrineColor::PaleYellow:
			eColor = EUrineColor::PaleYellow;
		case CDM::enumUrineColor::Pink:
			eColor = EUrineColor::Pink;
		case CDM::enumUrineColor::Yellow:
			eColor = EUrineColor::Yellow;
		}
		return true;
	}
	else
	{
		return false;
	}


}
//-------------------------------------------------------------------------------
#include <biogears/cdm/system/environment/actions/SEEnvironmentChange.h>
bool UBioGearsEngine::action_env_change(FEnvironmentalConditions conditions)
{
	//TODO: Refactor - Introduce an environment struct
	return false;
}
//-------------------------------------------------------------------------------
#include <biogears/cdm/patient/actions/SETourniquet.h>
bool UBioGearsEngine::action_apply_tourniquet(EExtremity limb, ETourniquet application)
{
	using namespace biogears;
	auto tourniquet = SETourniquet();

	switch (limb)
	{
	case EExtremity::LeftArm:
		tourniquet.SetCompartment("LeftArm");
		break;
	case EExtremity::RightArm:
		tourniquet.SetCompartment("RightArm");
		break;
	case EExtremity::LeftLeg:
		tourniquet.SetCompartment("LeftLeg");
		break;
	case EExtremity::RightLeg:
		tourniquet.SetCompartment("RightLeg");
		break;
	}

	switch (application)
	{
	case ETourniquet::Applied:
		tourniquet.SetTourniquetLevel(CDM::enumTourniquetApplicationLevel::Applied);
		break;
	case ETourniquet::Misapplied:
		tourniquet.SetTourniquetLevel(CDM::enumTourniquetApplicationLevel::Misapplied);
		break;
	case ETourniquet::None:
		tourniquet.SetTourniquetLevel(CDM::enumTourniquetApplicationLevel::None);
		break;
	}

	if (tourniquet.IsValid()) {
		_pimpl->bg->ProcessAction(tourniquet);
		return true;
	}
	else {
		return false;
	}
}
//-------------------------------------------------------------------------------
#include <biogears/cdm/patient/actions/SEHemorrhage.h>
bool UBioGearsEngine::action_apply_hemorrhage(EExtremity limb, double flowrate_ml_Per_min)
{

	//TODO: Thread Guard
	auto hemorrhage = biogears::SEHemorrhage();
	using namespace biogears;
	switch (limb) {
	default:
	case EExtremity::LeftArm:
		hemorrhage.SetCompartment("LeftArm");
		break;
	case EExtremity::RightArm:
		hemorrhage.SetCompartment("RightArm");
		break;
	case EExtremity::LeftLeg:
		hemorrhage.SetCompartment("LeftLeg");
		break;
	case EExtremity::RightLeg:
		hemorrhage.SetCompartment("RightLeg");
		break;
	}
	hemorrhage.GetInitialRate().SetValue(flowrate_ml_Per_min, biogears::VolumePerTimeUnit::mL_Per_min);
	if (hemorrhage.IsValid()) {
		std::lock_guard<std::mutex> guard{ _pimpl->mutex };
		_pimpl->bg->ProcessAction(hemorrhage);
		return true;
	}
	else {
		return false;
	}
}
//-------------------------------------------------------------------------------
#include <biogears/cdm/patient/actions/SETensionPneumothorax.h>
bool UBioGearsEngine::action_tension_pneumothorax(ESide side, EPneumothorax type, double severity_0_to_1)
{
	using namespace biogears;
	auto pneumothorax = SETensionPneumothorax();
	switch (side) {
	case ESide::Left:
		pneumothorax.SetSide(CDM::enumSide::Left);
		break;
	case ESide::Right:
		pneumothorax.SetSide(CDM::enumSide::Right);
		break;
	}
	switch (type) {
	case EPneumothorax::Open:
		pneumothorax.SetType(CDM::enumPneumothoraxType::Open);
		break;
	case EPneumothorax::Closed:
		pneumothorax.SetType(CDM::enumPneumothoraxType::Closed);
		break;

	}

	pneumothorax.GetSeverity().SetValue(severity_0_to_1);
	if (pneumothorax.IsValid()) {
		std::lock_guard<std::mutex> guard{ _pimpl->mutex };
		_pimpl->bg->ProcessAction(pneumothorax);
		return true;
	}
	else {
		return false;
	}
}
//-------------------------------------------------------------------------------
#include <biogears/cdm/patient/actions/SENeedleDecompression.h>
bool UBioGearsEngine::action_needle_decompression(ESide side, bool active)
{
	using namespace biogears;
	auto needleD = SENeedleDecompression();
	switch (side) {
	case ESide::Left:
		needleD.SetSide(CDM::enumSide::Left);
		break;
	case ESide::Right:
		needleD.SetSide(CDM::enumSide::Right);
		break;
	}

	needleD.SetActive(active);
	if (needleD.IsValid()) {
		std::lock_guard<std::mutex> guard{ _pimpl->mutex };
		_pimpl->bg->ProcessAction(needleD);
		return true;
	}
	else {
		return false;
	}
}
//-------------------------------------------------------------------------------
#include <biogears/cdm/system/equipment/Anesthesia/SEAnesthesiaMachine.h>
#include <biogears/cdm/system/equipment/Anesthesia/SEAnesthesiaMachineOxygenBottle.h>
#include <biogears/cdm/system/equipment/Anesthesia/actions/SEAnesthesiaMachineConfiguration.h>
bool UBioGearsEngine::action_o2_mask(double o2_fraction, double o2_volume1, double o2_volume2)
{
	using namespace biogears;
	std::lock_guard<std::mutex> guard{ _pimpl->mutex };
	auto AMConfig = SEAnesthesiaMachineConfiguration(_pimpl->bg->GetSubstanceManager());
	auto& config = AMConfig.GetConfiguration();
	config.GetOxygenFraction().SetValue(o2_fraction);
	config.GetOxygenBottleOne().GetVolume().SetValue(o2_volume1, VolumeUnit::L);
	config.GetOxygenBottleTwo().GetVolume().SetValue(o2_volume2, VolumeUnit::L);

	//Any of these values could auso be adjusted, but I don't think its required
	//for this example
	config.SetConnection(CDM::enumAnesthesiaMachineConnection::Mask);
	config.GetInletFlow().SetValue(2.0, VolumePerTimeUnit::L_Per_min);
	config.GetInspiratoryExpiratoryRatio().SetValue(.5);
	config.SetOxygenSource(CDM::enumAnesthesiaMachineOxygenSource::Wall);
	config.GetPositiveEndExpiredPressure().SetValue(0.0, PressureUnit::cmH2O);
	config.SetPrimaryGas(CDM::enumAnesthesiaMachinePrimaryGas::Nitrogen);
	config.GetReliefValvePressure().SetValue(20.0, PressureUnit::cmH2O);
	config.GetRespiratoryRate().SetValue(12, FrequencyUnit::Per_min);
	config.GetVentilatorPressure().SetValue(0.0, PressureUnit::cmH2O);

	if (AMConfig.IsValid()) {

		_pimpl->bg->ProcessAction(AMConfig);
		return true;
	}
	else {
		return false;
	}
	return false;
}
//-------------------------------------------------------------------------------
#include <biogears/cdm/patient/actions/SEInfection.h>
bool UBioGearsEngine::action_infection(EInfectionSeverity severity, FString location, double mic_mg_Per_l)
{
	using namespace biogears;
	auto sepsis = biogears::SEInfection();

	switch (severity)
	{
	default:
	case EInfectionSeverity::Eliminated:
		sepsis.SetSeverity(CDM::enumInfectionSeverity::Eliminated);
		break;
	case EInfectionSeverity::Mild:
		sepsis.SetSeverity(CDM::enumInfectionSeverity::Mild);
		break;
	case EInfectionSeverity::Moderate:
		sepsis.SetSeverity(CDM::enumInfectionSeverity::Moderate);
		break;
	case EInfectionSeverity::Severe:
		sepsis.SetSeverity(CDM::enumInfectionSeverity::Severe);
		break;
	}


	sepsis.SetLocation(TCHAR_TO_ANSI(*location));
	sepsis.GetMinimumInhibitoryConcentration().SetValue(mic_mg_Per_l, biogears::MassPerVolumeUnit::mg_Per_L);
	if (sepsis.IsValid()) {
		std::lock_guard<std::mutex> guard{ _pimpl->mutex };
		_pimpl->bg->ProcessAction(sepsis);
		return true;
	}
	else {
		return false;
	}
}
//-------------------------------------------------------------------------------
#include <biogears/cdm/patient/actions/SESubstanceInfusion.h>
#include <biogears/cdm/substance/SESubstanceCompound.h>
bool UBioGearsEngine::action_bloodtransfusion(EBloodType type, double blood_volume_ml, double flowrate_ml_Per_min)
{
	using namespace biogears;
	std::lock_guard<std::mutex> guard{ _pimpl->mutex };
	SESubstanceCompound* bloodSource = nullptr;

	switch (type)
	{
	case EBloodType::O_Negitive:	bloodSource = _pimpl->bg->GetSubstanceManager().GetCompound("Blood_ONegative"); break;
	case EBloodType::O_Positive:	bloodSource = _pimpl->bg->GetSubstanceManager().GetCompound("Blood_OPositive"); break;
	case EBloodType::A_B_Negative:	bloodSource = _pimpl->bg->GetSubstanceManager().GetCompound("Blood_ABNegative"); break;
	case EBloodType::A_B_Positive:	bloodSource = _pimpl->bg->GetSubstanceManager().GetCompound("Blood_ABPositive"); break;
	case EBloodType::A_Negitive:	bloodSource = _pimpl->bg->GetSubstanceManager().GetCompound("Blood_ANegative"); break;
	case EBloodType::A_Positive:	bloodSource = _pimpl->bg->GetSubstanceManager().GetCompound("Blood_APositive"); break;
	case EBloodType::B_Negative:	bloodSource = _pimpl->bg->GetSubstanceManager().GetCompound("Blood_NNegative"); break;
	case EBloodType::B_Positive:	bloodSource = _pimpl->bg->GetSubstanceManager().GetCompound("Blood_BPositive"); break;
	default:	bloodSource = _pimpl->bg->GetSubstanceManager().GetCompound("Blood_ONegative"); break;
	}

	auto transfusion = SESubstanceCompoundInfusion(*bloodSource);
	transfusion.GetBagVolume().SetValue(blood_volume_ml, biogears::VolumeUnit::mL); //the total volume in the bag
	transfusion.GetRate().SetValue(flowrate_ml_Per_min, biogears::VolumePerTimeUnit::mL_Per_min); //The rate to admnister the compound in the bag

	if (transfusion.IsValid()) {
		_pimpl->bg->ProcessAction(transfusion);
		return true;
	}
	else {
		return false;
	}
	return false;
}
//-------------------------------------------------------------------------------
#include <biogears/cdm/system/environment/actions/SEThermalApplication.h>
#include <biogears/cdm/system/environment/SEActiveHeating.h>
#include <biogears/cdm/system/environment/SEActiveCooling.h>
bool UBioGearsEngine::action_thermal_blanket(double watt, double surface_area_fraction)
{
	using namespace biogears;
	auto thermalApplication = SEThermalApplication();
	auto& blanket = thermalApplication.GetActiveHeating();
	blanket.GetPower().SetValue(watt, PowerUnit::W);
	blanket.GetSurfaceAreaFraction().SetValue(surface_area_fraction);
	if (thermalApplication.IsValid()) {
		std::lock_guard<std::mutex> guard{ _pimpl->mutex };
		_pimpl->bg->ProcessAction(thermalApplication);
		return true;
	}
	else {
		return false;
	}
	return false;
}
//-------------------------------------------------------------------------------
#include <biogears/cdm/patient/actions/SEPainStimulus.h>
bool UBioGearsEngine::action_pain_stimulus(ECompartment compartment, double severity)
{
	auto pain = biogears::SEPainStimulus();
	switch (compartment)
	{
	case ECompartment::LeftArm:	pain.SetLocation("LeftArm"); break;
	case ECompartment::RightArm:	pain.SetLocation("RightArm"); break;
	case ECompartment::LeftLeg:	pain.SetLocation("LeftLeg"); break;
	case ECompartment::RightLeg:	pain.SetLocation("RightLeg"); break;
	}

	pain.GetSeverity().SetValue(severity);
	if (pain.IsValid()) {
		std::lock_guard<std::mutex> guard{ _pimpl->mutex };
		_pimpl->bg->ProcessAction(pain);
		return true;
	}
	else {
		return false;
	}
	return false;
}
bool UBioGearsEngine::action_substanceInfusion(EIvSubstance substance, double substance_volume_ml, double flowrate_ml_Per_min)
{
	//TODO: Implement Substance Infusion Action
	return false;
}
bool UBioGearsEngine::action_substanceCompoundInfusion(EIvCompound compound, double compound_volume_ml, double flowrate_ml_Per_min)
{
	//TODO: Implement SubstanceCompound Infusion Action
	return false;
}
bool UBioGearsEngine::action_oralSubstanceAdministration(EOralSubstance type, EOralAbsorption, double dosage_mg)
{
	//TODO: Implement Oral Substance  Action
	return false;
}
//-------------------------------------------------------------------------------