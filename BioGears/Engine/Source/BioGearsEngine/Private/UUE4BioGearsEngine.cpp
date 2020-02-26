#include "UUE4BioGearsEngine.h"


void UUE4BioGearsEngine::setup_cache() {
	auto& bloodChemistry = _bg->GetBloodChemistry();
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

	auto& cardiovascular = _bg->GetCardiovascular();
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

	auto& drugs = _bg->GetDrugs();
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

	auto& endocrine = _bg->GetEndocrine();
	_insulinSynthesisRate = (endocrine.HasInsulinSynthesisRate()) ? &endocrine.GetInsulinSynthesisRate() : nullptr;
	_glucagonSynthesisRate = (endocrine.HasGlucagonSynthesisRate()) ? &endocrine.GetGlucagonSynthesisRate() : nullptr;

	auto& energy = _bg->GetEnergy();
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

	auto& gastrointestinal = _bg->GetGastrointestinal();
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

	auto& hepatic = _bg->GetHepatic();
	_hepaticGluconeogenesisRate = (hepatic.HasHepaticGluconeogenesisRate()) ? &hepatic.GetHepaticGluconeogenesisRate() : nullptr;
	_ketoneproductionRate = (hepatic.HasKetoneProductionRate()) ? &hepatic.GetKetoneProductionRate() : nullptr;

	auto& nervous = _bg->GetNervous();
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
	auto& renal = _bg->GetRenal();
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
	auto& respiratory = _bg->GetRespiratory();
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
	auto& tissue = _bg->GetTissue();
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
void UUE4BioGearsEngine::update_cache() {
	update_metrics();
	update_state();
	update_conditions();
}
void UUE4BioGearsEngine::update_metrics() {
	auto& bloodChemistry = _bg->GetBloodChemistry();
	_metrics.bloodChemistry.arterialBloodPH = (_arterialBloodPH) ? _arterialBloodPH->GetValue() : 0.0;
	_metrics.bloodChemistry.arterialBloodPHBaseline = (_arterialBloodPHBaseline) ? _arterialBloodPHBaseline->GetValue() : 0.0;
	_metrics.bloodChemistry.bloodDensity = (_bloodDensity) ? _bloodDensity->GetValue() : 0.0;
	_metrics.bloodChemistry.bloodSpecificHeat = (_bloodSpecificHeat) ? _bloodSpecificHeat->GetValue() : 0.0;
	_metrics.bloodChemistry.bloodUreaNitrogenConcentration = (_bloodUreaNitrogenConcentration) ? _bloodUreaNitrogenConcentration->GetValue() : 0.0;
	_metrics.bloodChemistry.carbonDioxideSaturation = (_carbonDioxideSaturation) ? _carbonDioxideSaturation->GetValue() : 0.0;
	_metrics.bloodChemistry.carbonMonoxideSaturation = (_carbonMonoxideSaturation) ? _carbonMonoxideSaturation->GetValue() : 0.0;
	_metrics.bloodChemistry.hematocrit = (_hematocrit) ? _hematocrit->GetValue() : 0.0;
	_metrics.bloodChemistry.hemoglobinContent = (_hemoglobinContent) ? _hemoglobinContent->GetValue() : 0.0;
	_metrics.bloodChemistry.oxygenSaturation = (_oxygenSaturation) ? _oxygenSaturation->GetValue() : 0.0;
	_metrics.bloodChemistry.phosphate = (_phosphate) ? _phosphate->GetValue() : 0.0;
	_metrics.bloodChemistry.plasmaVolume = (_plasmaVolume) ? _plasmaVolume->GetValue() : 0.0;
	_metrics.bloodChemistry.pulseOximetry = (_pulseOximetry) ? _pulseOximetry->GetValue() : 0.0;
	_metrics.bloodChemistry.redBloodCellAcetylcholinesterase = (_redBloodCellAcetylcholinesterase) ? _redBloodCellAcetylcholinesterase->GetValue() : 0.0;
	_metrics.bloodChemistry.redBloodCellCount = (_redBloodCellCount) ? _redBloodCellCount->GetValue(biogears::AmountPerVolumeUnit::ct_Per_uL) : 0.0;
	_metrics.bloodChemistry.shuntFraction = (_shuntFraction) ? _shuntFraction->GetValue() : 0.0;
	_metrics.bloodChemistry.strongIonDifference = (_strongIonDifference) ? _strongIonDifference->GetValue() : 0.0;
	_metrics.bloodChemistry.totalBilirubin = (_totalBilirubin) ? _totalBilirubin->GetValue() : 0.0;
	_metrics.bloodChemistry.totalProteinConcentration = (_totalProteinConcentration) ? _totalProteinConcentration->GetValue() : 0.0;
	_metrics.bloodChemistry.venousBloodPH = (_venousBloodPH) ? _venousBloodPH->GetValue() : 0.0;
	_metrics.bloodChemistry.volumeFractionNeutralPhospholipidInPlasma = (_volumeFractionNeutralPhospholipidInPlasma) ? _volumeFractionNeutralPhospholipidInPlasma->GetValue() : 0.0;
	_metrics.bloodChemistry.volumeFractionNeutralLipidInPlasma = (_volumeFractionNeutralLipidInPlasma) ? _volumeFractionNeutralLipidInPlasma->GetValue() : 0.0;
	_metrics.bloodChemistry.arterialCarbonDioxidePressure = (_arterialCarbonDioxidePressure) ? _arterialCarbonDioxidePressure->GetValue() : 0.0;
	_metrics.bloodChemistry.arterialOxygenPressure = (_arterialOxygenPressure) ? _arterialOxygenPressure->GetValue() : 0.0;
	_metrics.bloodChemistry.pulmonaryArterialCarbonDioxidePressure = (_pulmonaryArterialCarbonDioxidePressure) ? _pulmonaryArterialCarbonDioxidePressure->GetValue() : 0.0;
	_metrics.bloodChemistry.pulmonaryArterialOxygenPressure = (_pulmonaryArterialOxygenPressure) ? _pulmonaryArterialOxygenPressure->GetValue() : 0.0;
	_metrics.bloodChemistry.pulmonaryVenousCarbonDioxidePressure = (_pulmonaryVenousCarbonDioxidePressure) ? _pulmonaryVenousCarbonDioxidePressure->GetValue() : 0.0;
	_metrics.bloodChemistry.pulmonaryVenousOxygenPressure = (_pulmonaryVenousOxygenPressure) ? _pulmonaryVenousOxygenPressure->GetValue() : 0.0;
	_metrics.bloodChemistry.venousCarbonDioxidePressure = (_venousCarbonDioxidePressure) ? _venousCarbonDioxidePressure->GetValue() : 0.0;
	_metrics.bloodChemistry.venousOxygenPressure = (_venousOxygenPressure) ? _venousOxygenPressure->GetValue() : 0.0;

	_metrics.hasInflammatoryResponse = bloodChemistry.HasInflammatoryResponse();

	auto& inflamatoryResponse = bloodChemistry.GetInflammatoryResponse();
	_metrics.inflamatroyReponse.LocalPathogen = (_inflammatoryResponseLocalPathogen) ? _inflammatoryResponseLocalPathogen->GetValue() : 0.0;
	_metrics.inflamatroyReponse.LocalMacrophage = (_inflammatoryResponseLocalMacrophage) ? _inflammatoryResponseLocalMacrophage->GetValue() : 0.0;
	_metrics.inflamatroyReponse.LocalNeutrophil = (_inflammatoryResponseLocalNeutrophil) ? _inflammatoryResponseLocalNeutrophil->GetValue() : 0.0;
	_metrics.inflamatroyReponse.LocalBarrier = (_inflammatoryResponseLocalBarrier) ? _inflammatoryResponseLocalBarrier->GetValue() : 0.0;
	_metrics.inflamatroyReponse.BloodPathogen = (_inflammatoryResponseBloodPathogen) ? _inflammatoryResponseBloodPathogen->GetValue() : 0.0;
	_metrics.inflamatroyReponse.Trauma = (_inflammatoryResponseTrauma) ? _inflammatoryResponseTrauma->GetValue() : 0.0;
	_metrics.inflamatroyReponse.MacrophageResting = (_inflammatoryResponseMacrophageResting) ? _inflammatoryResponseMacrophageResting->GetValue() : 0.0;
	_metrics.inflamatroyReponse.MacrophageActive = (_inflammatoryResponseMacrophageActive) ? _inflammatoryResponseMacrophageActive->GetValue() : 0.0;
	_metrics.inflamatroyReponse.NeutrophilResting = (_inflammatoryResponseNeutrophilResting) ? _inflammatoryResponseNeutrophilResting->GetValue() : 0.0;
	_metrics.inflamatroyReponse.NeutrophilActive = (_inflammatoryResponseNeutrophilActive) ? _inflammatoryResponseNeutrophilActive->GetValue() : 0.0;
	_metrics.inflamatroyReponse.InducibleNOSPre = (_inflammatoryResponseInducibleNOSPre) ? _inflammatoryResponseInducibleNOSPre->GetValue() : 0.0;
	_metrics.inflamatroyReponse.InducibleNOS = (_inflammatoryResponseInducibleNOS) ? _inflammatoryResponseInducibleNOS->GetValue() : 0.0;
	_metrics.inflamatroyReponse.ConstitutiveNOS = (_inflammatoryResponseConstitutiveNOS) ? _inflammatoryResponseConstitutiveNOS->GetValue() : 0.0;
	_metrics.inflamatroyReponse.Nitrate = (_inflammatoryResponseNitrate) ? _inflammatoryResponseNitrate->GetValue() : 0.0;
	_metrics.inflamatroyReponse.NitricOxide = (_inflammatoryResponseNitricOxide) ? _inflammatoryResponseNitricOxide->GetValue() : 0.0;
	_metrics.inflamatroyReponse.TumorNecrosisFactor = (_inflammatoryResponseTumorNecrosisFactor) ? _inflammatoryResponseTumorNecrosisFactor->GetValue() : 0.0;
	_metrics.inflamatroyReponse.Interleukin6 = (_inflammatoryResponseInterleukin6) ? _inflammatoryResponseInterleukin6->GetValue() : 0.0;
	_metrics.inflamatroyReponse.Interleukin10 = (_inflammatoryResponseInterleukin10) ? _inflammatoryResponseInterleukin10->GetValue() : 0.0;
	_metrics.inflamatroyReponse.Interleukin12 = (_inflammatoryResponseInterleukin12) ? _inflammatoryResponseInterleukin12->GetValue() : 0.0;
	_metrics.inflamatroyReponse.Catecholamines = (_inflammatoryResponseCatecholamines) ? _inflammatoryResponseCatecholamines->GetValue() : 0.0;
	_metrics.inflamatroyReponse.TissueIntegrity = (_inflammatoryResponseTissueIntegrity) ? _inflammatoryResponseTissueIntegrity->GetValue() : 0.0;

	auto& cardiovascular = _bg->GetCardiovascular();
	_metrics.cardiovascular.arterialPressure = (_arterialPressure) ? _arterialPressure->GetValue() : 0.0;
	_metrics.cardiovascular.bloodVolume = (_bloodVolume) ? _bloodVolume->GetValue() : 0.0;
	_metrics.cardiovascular.cardiacIndex = (_cardiacIndex) ? _cardiacIndex->GetValue() : 0.0;
	_metrics.cardiovascular.cardiacOutput = (_cardiacOutput) ? _cardiacOutput->GetValue() : 0.0;
	_metrics.cardiovascular.centralVenousPressure = (_centralVenousPressure) ? _centralVenousPressure->GetValue() : 0.0;
	_metrics.cardiovascular.cerebralBloodFlow = (_cerebralBloodFlow) ? _cerebralBloodFlow->GetValue() : 0.0;
	_metrics.cardiovascular.cerebralPerfusionPressure = (_cerebralPerfusionPressure) ? _cerebralPerfusionPressure->GetValue() : 0.0;
	_metrics.cardiovascular.diastolicArterialPressure = (_diastolicArterialPressure) ? _diastolicArterialPressure->GetValue() : 0.0;
	_metrics.cardiovascular.heartEjectionFraction = (_heartEjectionFraction) ? _heartEjectionFraction->GetValue() : 0.0;
	_metrics.cardiovascular.heartRate = (_heartRate) ? _heartRate->GetValue() : 0.0;
	_metrics.cardiovascular.heartStrokeVolume = (_heartStrokeVolume) ? _heartStrokeVolume->GetValue() : 0.0;
	_metrics.cardiovascular.intracranialPressure = (_intracranialPressure) ? _intracranialPressure->GetValue() : 0.0;
	_metrics.cardiovascular.meanArterialPressure = (_meanArterialPressure) ? _meanArterialPressure->GetValue() : 0.0;
	_metrics.cardiovascular.meanArterialCarbonDioxidePartialPressure = (_meanArterialCarbonDioxidePartialPressure) ? _meanArterialCarbonDioxidePartialPressure->GetValue() : 0.0;
	_metrics.cardiovascular.meanArterialCarbonDioxidePartialPressureDelta = (_meanArterialCarbonDioxidePartialPressureDelta) ? _meanArterialCarbonDioxidePartialPressureDelta->GetValue() : 0.0;
	_metrics.cardiovascular.meanCentralVenousPressure = (_meanCentralVenousPressure) ? _meanCentralVenousPressure->GetValue() : 0.0;
	_metrics.cardiovascular.meanSkinFlow = (_meanSkinFlow) ? _meanSkinFlow->GetValue() : 0.0;
	_metrics.cardiovascular.pulmonaryArterialPressure = (_pulmonaryArterialPressure) ? _pulmonaryArterialPressure->GetValue() : 0.0;
	_metrics.cardiovascular.pulmonaryCapillariesWedgePressure = (_pulmonaryCapillariesWedgePressure) ? _pulmonaryCapillariesWedgePressure->GetValue() : 0.0;
	_metrics.cardiovascular.pulmonaryDiastolicArterialPressure = (_pulmonaryDiastolicArterialPressure) ? _pulmonaryDiastolicArterialPressure->GetValue() : 0.0;
	_metrics.cardiovascular.pulmonaryMeanArterialPressure = (_pulmonaryMeanArterialPressure) ? _pulmonaryMeanArterialPressure->GetValue() : 0.0;
	_metrics.cardiovascular.pulmonaryMeanCapillaryFlow = (_pulmonaryMeanCapillaryFlow) ? _pulmonaryMeanCapillaryFlow->GetValue() : 0.0;
	_metrics.cardiovascular.pulmonaryMeanShuntFlow = (_pulmonaryMeanShuntFlow) ? _pulmonaryMeanShuntFlow->GetValue() : 0.0;
	_metrics.cardiovascular.pulmonarySystolicArterialPressure = (_pulmonarySystolicArterialPressure) ? _pulmonarySystolicArterialPressure->GetValue() : 0.0;
	_metrics.cardiovascular.pulmonaryVascularResistance = (_pulmonaryVascularResistance) ? _pulmonaryVascularResistance->GetValue() : 0.0;
	_metrics.cardiovascular.pulmonaryVascularResistanceIndex = (_pulmonaryVascularResistanceIndex) ? _pulmonaryVascularResistanceIndex->GetValue() : 0.0;
	_metrics.cardiovascular.pulsePressure = (_pulsePressure) ? _pulsePressure->GetValue() : 0.0;
	_metrics.cardiovascular.systemicVascularResistance = (_systemicVascularResistance) ? _systemicVascularResistance->GetValue() : 0.0;
	_metrics.cardiovascular.systolicArterialPressure = (_systolicArterialPressure) ? _systolicArterialPressure->GetValue() : 0.0;

	auto& drugs = _bg->GetDrugs();
	_metrics.drugs.bronchodilationLevel = (_bronchodilationLevel) ? _bronchodilationLevel->GetValue() : 0.0;
	_metrics.drugs.heartRateChange = (_heartRateChange) ? _heartRateChange->GetValue() : 0.0;
	_metrics.drugs.meanBloodPressureChange = (_meanBloodPressureChange) ? _meanBloodPressureChange->GetValue() : 0.0;
	_metrics.drugs.meanBloodPressureChange = (_meanBloodPressureChange) ? _meanBloodPressureChange->GetValue() : 0.0;
	_metrics.drugs.neuromuscularBlockLevel = (_neuromuscularBlockLevel) ? _neuromuscularBlockLevel->GetValue() : 0.0;
	_metrics.drugs.pulsePressureChange = (_pulsePressureChange) ? _pulsePressureChange->GetValue() : 0.0;
	_metrics.drugs.respirationRateChange = (_respirationRateChange) ? _respirationRateChange->GetValue() : 0.0;
	_metrics.drugs.sedationLevel = (_sedationLevel) ? _sedationLevel->GetValue() : 0.0;
	_metrics.drugs.tidalVolumeChange = (_tidalVolumeChange) ? _tidalVolumeChange->GetValue() : 0.0;
	_metrics.drugs.tubularPermeabilityChange = (_tubularPermeabilityChange) ? _tubularPermeabilityChange->GetValue() : 0.0;
	_metrics.drugs.centralNervousResponse = (_centralNervousResponse) ? _centralNervousResponse->GetValue() : 0.0;

	auto& endocrine = _bg->GetEndocrine();
	_metrics.endocrine.insulinSynthesisRate = (_insulinSynthesisRate) ? _insulinSynthesisRate->GetValue() : 0.0;
	_metrics.endocrine.glucagonSynthesisRate = (_glucagonSynthesisRate) ? _glucagonSynthesisRate->GetValue() : 0.0;

	auto& energy = _bg->GetEnergy();
	_metrics.energy.achievedExerciseLevel = (_achievedExerciseLevel) ? _achievedExerciseLevel->GetValue() : 0.0;
	_metrics.energy.chlorideLostToSweat = (_chlorideLostToSweat) ? _chlorideLostToSweat->GetValue() : 0.0;
	_metrics.energy.coreTemperature = (_coreTemperature) ? _coreTemperature->GetValue() : 0.0;
	_metrics.energy.creatinineProductionRate = (_creatinineProductionRate) ? _creatinineProductionRate->GetValue() : 0.0;
	_metrics.energy.exerciseMeanArterialPressureDelta = (_exerciseMeanArterialPressureDelta) ? _exerciseMeanArterialPressureDelta->GetValue() : 0.0;
	_metrics.energy.fatigueLevel = (_fatigueLevel) ? _fatigueLevel->GetValue() : 0.0;
	_metrics.energy.lactateProductionRate = (_lactateProductionRate) ? _lactateProductionRate->GetValue() : 0.0;
	_metrics.energy.potassiumLostToSweat = (_potassiumLostToSweat) ? _potassiumLostToSweat->GetValue() : 0.0;
	_metrics.energy.skinTemperature = (_skinTemperature) ? _skinTemperature->GetValue() : 0.0;
	_metrics.energy.sodiumLostToSweat = (_sodiumLostToSweat) ? _sodiumLostToSweat->GetValue() : 0.0;
	_metrics.energy.sweatRate = (_sweatRate) ? _sweatRate->GetValue() : 0.0;
	_metrics.energy.totalMetabolicRate = (_totalMetabolicRate) ? _totalMetabolicRate->GetValue() : 0.0;
	_metrics.energy.totalWorkRateLevel = (_totalWorkRateLevel) ? _totalWorkRateLevel->GetValue() : 0.0;

	auto& gastrointestinal = _bg->GetGastrointestinal();
	_metrics.gastrointestinal.chymeAbsorptionRate = (_chymeAbsorptionRate) ? _chymeAbsorptionRate->GetValue() : 0.0;
	_metrics.gastrointestinal.stomachContents_calcium = (_stomachContents_calcium) ? _stomachContents_calcium->GetValue() : 0.0;
	_metrics.gastrointestinal.stomachContents_carbohydrates = (_stomachContents_carbohydrates) ? _stomachContents_carbohydrates->GetValue() : 0.0;
	_metrics.gastrointestinal.stomachContents_carbohydrateDigationRate = (_stomachContents_carbohydrateDigationRate) ? _stomachContents_carbohydrateDigationRate->GetValue() : 0.0;
	_metrics.gastrointestinal.stomachContents_fat = (_stomachContents_fat) ? _stomachContents_fat->GetValue() : 0.0;
	_metrics.gastrointestinal.stomachContents_fatDigtationRate = (_stomachContents_fatDigtationRate) ? _stomachContents_fatDigtationRate->GetValue() : 0.0;
	_metrics.gastrointestinal.stomachContents_protien = (_stomachContents_protien) ? _stomachContents_protien->GetValue() : 0.0;
	_metrics.gastrointestinal.stomachContents_protienDigtationRate = (_stomachContents_protienDigtationRate) ? _stomachContents_protienDigtationRate->GetValue() : 0.0;
	_metrics.gastrointestinal.stomachContents_sodium = (_stomachContents_sodium) ? _stomachContents_sodium->GetValue() : 0.0;
	_metrics.gastrointestinal.stomachContents_water = (_stomachContents_water) ? _stomachContents_water->GetValue() : 0.0;

	auto& hepatic = _bg->GetHepatic();
	_metrics.hepatic.hepaticGluconeogenesisRate = (_hepaticGluconeogenesisRate) ? _hepaticGluconeogenesisRate->GetValue() : 0.0;
	_metrics.hepatic.ketoneproductionRate = (_ketoneproductionRate) ? _ketoneproductionRate->GetValue() : 0.0;

	auto& nervous = _bg->GetNervous();
	_metrics.nervous.baroreceptorHeartRateScale = (_baroreceptorHeartRateScale) ? _baroreceptorHeartRateScale->GetValue() : 0.0;
	_metrics.nervous.baroreceptorHeartElastanceScale = (_baroreceptorHeartElastanceScale) ? _baroreceptorHeartElastanceScale->GetValue() : 0.0;
	_metrics.nervous.baroreceptorResistanceScale = (_baroreceptorResistanceScale) ? _baroreceptorResistanceScale->GetValue() : 0.0;
	_metrics.nervous.baroreceptorComplianceScale = (_baroreceptorComplianceScale) ? _baroreceptorComplianceScale->GetValue() : 0.0;
	_metrics.nervous.chemoreceptorHeartRateScale = (_chemoreceptorHeartRateScale) ? _chemoreceptorHeartRateScale->GetValue() : 0.0;
	_metrics.nervous.chemoreceptorHeartElastanceScale = (_chemoreceptorHeartElastanceScale) ? _chemoreceptorHeartElastanceScale->GetValue() : 0.0;
	_metrics.nervous.painVisualAnalogueScale = (_painVisualAnalogueScale) ? _painVisualAnalogueScale->GetValue() : 0.0;

	//TODO: Implement Pupillary Response  ReactivityModifier  ShapeModifier  SizeModifier;
	_metrics.nervous.leftEyePupillaryResponse = 0.0;
	_metrics.nervous.rightEyePupillaryResponse = 0.0;

	//Renal
	auto& renal = _bg->GetRenal();
	_metrics.renal.glomerularFiltrationRate = (_glomerularFiltrationRate) ? _glomerularFiltrationRate->GetValue() : 0.0;
	_metrics.renal.filtrationFraction = (_filtrationFraction) ? _filtrationFraction->GetValue() : 0.0;
	_metrics.renal.leftAfferentArterioleResistance = (_leftAfferentArterioleResistance) ? _leftAfferentArterioleResistance->GetValue() : 0.0;
	_metrics.renal.leftBowmansCapsulesHydrostaticPressure = (_leftBowmansCapsulesHydrostaticPressure) ? _leftBowmansCapsulesHydrostaticPressure->GetValue() : 0.0;
	_metrics.renal.leftBowmansCapsulesOsmoticPressure = (_leftBowmansCapsulesOsmoticPressure) ? _leftBowmansCapsulesOsmoticPressure->GetValue() : 0.0;
	_metrics.renal.leftEfferentArterioleResistance = (_leftEfferentArterioleResistance) ? _leftEfferentArterioleResistance->GetValue() : 0.0;
	_metrics.renal.leftGlomerularCapillariesHydrostaticPressure = (_leftGlomerularCapillariesHydrostaticPressure) ? _leftGlomerularCapillariesHydrostaticPressure->GetValue() : 0.0;
	_metrics.renal.leftGlomerularCapillariesOsmoticPressure = (_leftGlomerularCapillariesOsmoticPressure) ? _leftGlomerularCapillariesOsmoticPressure->GetValue() : 0.0;
	_metrics.renal.leftGlomerularFiltrationCoefficient = (_leftGlomerularFiltrationCoefficient) ? _leftGlomerularFiltrationCoefficient->GetValue() : 0.0;
	_metrics.renal.leftGlomerularFiltrationRate = (_leftGlomerularFiltrationRate) ? _leftGlomerularFiltrationRate->GetValue() : 0.0;
	_metrics.renal.leftGlomerularFiltrationSurfaceArea = (_leftGlomerularFiltrationSurfaceArea) ? _leftGlomerularFiltrationSurfaceArea->GetValue() : 0.0;
	_metrics.renal.leftGlomerularFluidPermeability = (_leftGlomerularFluidPermeability) ? _leftGlomerularFluidPermeability->GetValue() : 0.0;
	_metrics.renal.leftFiltrationFraction = (_leftFiltrationFraction) ? _leftFiltrationFraction->GetValue() : 0.0;
	_metrics.renal.leftNetFiltrationPressure = (_leftNetFiltrationPressure) ? _leftNetFiltrationPressure->GetValue() : 0.0;
	_metrics.renal.leftNetReabsorptionPressure = (_leftNetReabsorptionPressure) ? _leftNetReabsorptionPressure->GetValue() : 0.0;
	_metrics.renal.leftPeritubularCapillariesHydrostaticPressure = (_leftPeritubularCapillariesHydrostaticPressure) ? _leftPeritubularCapillariesHydrostaticPressure->GetValue() : 0.0;
	_metrics.renal.leftPeritubularCapillariesOsmoticPressure = (_leftPeritubularCapillariesOsmoticPressure) ? _leftPeritubularCapillariesOsmoticPressure->GetValue() : 0.0;
	_metrics.renal.leftReabsorptionFiltrationCoefficient = (_leftReabsorptionFiltrationCoefficient) ? _leftReabsorptionFiltrationCoefficient->GetValue() : 0.0;
	_metrics.renal.leftReabsorptionRate = (_leftReabsorptionRate) ? _leftReabsorptionRate->GetValue() : 0.0;
	_metrics.renal.leftTubularReabsorptionFiltrationSurfaceArea = (_leftTubularReabsorptionFiltrationSurfaceArea) ? _leftTubularReabsorptionFiltrationSurfaceArea->GetValue() : 0.0;
	_metrics.renal.leftTubularReabsorptionFluidPermeability = (_leftTubularReabsorptionFluidPermeability) ? _leftTubularReabsorptionFluidPermeability->GetValue() : 0.0;
	_metrics.renal.leftTubularHydrostaticPressure = (_leftTubularHydrostaticPressure) ? _leftTubularHydrostaticPressure->GetValue() : 0.0;
	_metrics.renal.leftTubularOsmoticPressure = (_leftTubularOsmoticPressure) ? _leftTubularOsmoticPressure->GetValue() : 0.0;
	_metrics.renal.renalBloodFlow = (_renalBloodFlow) ? _renalBloodFlow->GetValue() : 0.0;
	_metrics.renal.renalPlasmaFlow = (_renalPlasmaFlow) ? _renalPlasmaFlow->GetValue() : 0.0;
	_metrics.renal.renalVascularResistance = (_renalVascularResistance) ? _renalVascularResistance->GetValue() : 0.0;
	_metrics.renal.rightAfferentArterioleResistance = (_rightAfferentArterioleResistance) ? _rightAfferentArterioleResistance->GetValue() : 0.0;
	_metrics.renal.rightBowmansCapsulesHydrostaticPressure = (_rightBowmansCapsulesHydrostaticPressure) ? _rightBowmansCapsulesHydrostaticPressure->GetValue() : 0.0;
	_metrics.renal.rightBowmansCapsulesOsmoticPressure = (_rightBowmansCapsulesOsmoticPressure) ? _rightBowmansCapsulesOsmoticPressure->GetValue() : 0.0;
	_metrics.renal.rightEfferentArterioleResistance = (_rightEfferentArterioleResistance) ? _rightEfferentArterioleResistance->GetValue() : 0.0;
	_metrics.renal.rightGlomerularCapillariesHydrostaticPressure = (_rightGlomerularCapillariesHydrostaticPressure) ? _rightGlomerularCapillariesHydrostaticPressure->GetValue() : 0.0;
	_metrics.renal.rightGlomerularCapillariesOsmoticPressure = (_rightGlomerularCapillariesOsmoticPressure) ? _rightGlomerularCapillariesOsmoticPressure->GetValue() : 0.0;
	_metrics.renal.rightGlomerularFiltrationCoefficient = (_rightGlomerularFiltrationCoefficient) ? _rightGlomerularFiltrationCoefficient->GetValue() : 0.0;
	_metrics.renal.rightGlomerularFiltrationRate = (_rightGlomerularFiltrationRate) ? _rightGlomerularFiltrationRate->GetValue() : 0.0;
	_metrics.renal.rightGlomerularFiltrationSurfaceArea = (_rightGlomerularFiltrationSurfaceArea) ? _rightGlomerularFiltrationSurfaceArea->GetValue() : 0.0;
	_metrics.renal.rightGlomerularFluidPermeability = (_rightGlomerularFluidPermeability) ? _rightGlomerularFluidPermeability->GetValue() : 0.0;
	_metrics.renal.rightFiltrationFraction = (_rightFiltrationFraction) ? _rightFiltrationFraction->GetValue() : 0.0;
	_metrics.renal.rightNetFiltrationPressure = (_rightNetFiltrationPressure) ? _rightNetFiltrationPressure->GetValue() : 0.0;
	_metrics.renal.rightNetReabsorptionPressure = (_rightNetReabsorptionPressure) ? _rightNetReabsorptionPressure->GetValue() : 0.0;
	_metrics.renal.rightPeritubularCapillariesHydrostaticPressure = (_rightPeritubularCapillariesHydrostaticPressure) ? _rightPeritubularCapillariesHydrostaticPressure->GetValue() : 0.0;
	_metrics.renal.rightPeritubularCapillariesOsmoticPressure = (_rightPeritubularCapillariesOsmoticPressure) ? _rightPeritubularCapillariesOsmoticPressure->GetValue() : 0.0;
	_metrics.renal.rightReabsorptionFiltrationCoefficient = (_rightReabsorptionFiltrationCoefficient) ? _rightReabsorptionFiltrationCoefficient->GetValue() : 0.0;
	_metrics.renal.rightReabsorptionRate = (_rightReabsorptionRate) ? _rightReabsorptionRate->GetValue() : 0.0;
	_metrics.renal.rightTubularReabsorptionFiltrationSurfaceArea = (_rightTubularReabsorptionFiltrationSurfaceArea) ? _rightTubularReabsorptionFiltrationSurfaceArea->GetValue() : 0.0;
	_metrics.renal.rightTubularReabsorptionFluidPermeability = (_rightTubularReabsorptionFluidPermeability) ? _rightTubularReabsorptionFluidPermeability->GetValue() : 0.0;
	_metrics.renal.rightTubularHydrostaticPressure = (_rightTubularHydrostaticPressure) ? _rightTubularHydrostaticPressure->GetValue() : 0.0;
	_metrics.renal.rightTubularOsmoticPressure = (_rightTubularOsmoticPressure) ? _rightTubularOsmoticPressure->GetValue() : 0.0;
	_metrics.renal.urinationRate = (_urinationRate) ? _urinationRate->GetValue() : 0.0;
	_metrics.renal.urineOsmolality = (_urineOsmolality) ? _urineOsmolality->GetValue() : 0.0;
	_metrics.renal.urineOsmolarity = (_urineOsmolarity) ? _urineOsmolarity->GetValue() : 0.0;
	_metrics.renal.urineProductionRate = (_urineProductionRate) ? _urineProductionRate->GetValue() : 0.0;
	_metrics.renal.meanUrineOutput = (_meanUrineOutput) ? _meanUrineOutput->GetValue() : 0.0;
	_metrics.renal.urineSpecificGravity = (_urineSpecificGravity) ? _urineSpecificGravity->GetValue() : 0.0;
	_metrics.renal.urineVolume = (_urineVolume) ? _urineVolume->GetValue() : 0.0;
	_metrics.renal.urineUreaNitrogenConcentration = (_urineUreaNitrogenConcentration) ? _urineUreaNitrogenConcentration->GetValue() : 0.0;

	//Respiratory
	auto& respiratory = _bg->GetRespiratory();
	_metrics.respiratory.alveolarArterialGradient = (_alveolarArterialGradient) ? _alveolarArterialGradient->GetValue() : 0.0;
	_metrics.respiratory.carricoIndex = (_carricoIndex) ? _carricoIndex->GetValue() : 0.0;
	_metrics.respiratory.endTidalCarbonDioxideFraction = (_endTidalCarbonDioxideFraction) ? _endTidalCarbonDioxideFraction->GetValue() : 0.0;
	_metrics.respiratory.endTidalCarbonDioxidePressure = (_endTidalCarbonDioxidePressure) ? _endTidalCarbonDioxidePressure->GetValue() : 0.0;
	_metrics.respiratory.expiratoryFlow = (_expiratoryFlow) ? _expiratoryFlow->GetValue() : 0.0;
	_metrics.respiratory.inspiratoryExpiratoryRatio = (_inspiratoryExpiratoryRatio) ? _inspiratoryExpiratoryRatio->GetValue() : 0.0;
	_metrics.respiratory.inspiratoryFlow = (_inspiratoryFlow) ? _inspiratoryFlow->GetValue() : 0.0;
	_metrics.respiratory.pulmonaryCompliance = (_pulmonaryCompliance) ? _pulmonaryCompliance->GetValue() : 0.0;
	_metrics.respiratory.pulmonaryResistance = (_pulmonaryResistance) ? _pulmonaryResistance->GetValue() : 0.0;
	_metrics.respiratory.respirationDriverPressure = (_respirationDriverPressure) ? _respirationDriverPressure->GetValue() : 0.0;
	_metrics.respiratory.respirationMusclePressure = (_respirationMusclePressure) ? _respirationMusclePressure->GetValue() : 0.0;
	_metrics.respiratory.respirationRate = (_respirationRate) ? _respirationRate->GetValue() : 0.0;
	_metrics.respiratory.specificVentilation = (_specificVentilation) ? _specificVentilation->GetValue() : 0.0;
	_metrics.respiratory.targetPulmonaryVentilation = (_targetPulmonaryVentilation) ? _targetPulmonaryVentilation->GetValue() : 0.0;
	_metrics.respiratory.tidalVolume = (_tidalVolume) ? _tidalVolume->GetValue() : 0.0;
	_metrics.respiratory.totalAlveolarVentilation = (_totalAlveolarVentilation) ? _totalAlveolarVentilation->GetValue() : 0.0;
	_metrics.respiratory.totalDeadSpaceVentilation = (_totalDeadSpaceVentilation) ? _totalDeadSpaceVentilation->GetValue() : 0.0;
	_metrics.respiratory.totalLungVolume = (_totalLungVolume) ? _totalLungVolume->GetValue() : 0.0;
	_metrics.respiratory.totalPulmonaryVentilation = (_totalPulmonaryVentilation) ? _totalPulmonaryVentilation->GetValue() : 0.0;
	_metrics.respiratory.transpulmonaryPressure = (_transpulmonaryPressure) ? _transpulmonaryPressure->GetValue() : 0.0;

	//Tissue
	auto& tissue = _bg->GetTissue();
	_metrics.tissue.carbonDioxideProductionRate = (_carbonDioxideProductionRate) ? _carbonDioxideProductionRate->GetValue() : 0.0;
	_metrics.tissue.dehydrationFraction = (_dehydrationFraction) ? _dehydrationFraction->GetValue() : 0.0;
	_metrics.tissue.extracellularFluidVolume = (_extracellularFluidVolume) ? _extracellularFluidVolume->GetValue() : 0.0;
	_metrics.tissue.extravascularFluidVolume = (_extravascularFluidVolume) ? _extravascularFluidVolume->GetValue() : 0.0;
	_metrics.tissue.intracellularFluidPH = (_intracellularFluidPH) ? _intracellularFluidPH->GetValue() : 0.0;
	_metrics.tissue.intracellularFluidVolume = (_intracellularFluidVolume) ? _intracellularFluidVolume->GetValue() : 0.0;
	_metrics.tissue.totalBodyFluidVolume = (_totalBodyFluidVolume) ? _totalBodyFluidVolume->GetValue() : 0.0;
	_metrics.tissue.oxygenConsumptionRate = (_oxygenConsumptionRate) ? _oxygenConsumptionRate->GetValue() : 0.0;
	_metrics.tissue.respiratoryExchangeRatio = (_respiratoryExchangeRatio) ? _respiratoryExchangeRatio->GetValue() : 0.0;
	_metrics.tissue.liverInsulinSetPoint = (_liverInsulinSetPoint) ? _liverInsulinSetPoint->GetValue() : 0.0;
	_metrics.tissue.liverGlucagonSetPoint = (_liverGlucagonSetPoint) ? _liverGlucagonSetPoint->GetValue() : 0.0;
	_metrics.tissue.muscleInsulinSetPoint = (_muscleInsulinSetPoint) ? _muscleInsulinSetPoint->GetValue() : 0.0;
	_metrics.tissue.muscleGlucagonSetPoint = (_muscleGlucagonSetPoint) ? _muscleGlucagonSetPoint->GetValue() : 0.0;
	_metrics.tissue.fatInsulinSetPoint = (_fatInsulinSetPoint) ? _fatInsulinSetPoint->GetValue() : 0.0;
	_metrics.tissue.fatGlucagonSetPoint = (_fatGlucagonSetPoint) ? _fatGlucagonSetPoint->GetValue() : 0.0;
	_metrics.tissue.liverGlycogen = (_liverGlycogen) ? _liverGlycogen->GetValue() : 0.0;
	_metrics.tissue.muscleGlycogen = (_muscleGlycogen) ? _muscleGlycogen->GetValue() : 0.0;
	_metrics.tissue.storedProtein = (_storedProtein) ? _storedProtein->GetValue() : 0.0;
	_metrics.tissue.storedFat = (_storedFat) ? _storedFat->GetValue() : 0.0;
}
void UUE4BioGearsEngine::update_conditions() {

	_conditions.diabieties = _bg->GetConditions().HasDiabetesType1() | _bg->GetConditions().HasDiabetesType2();

}
void UUE4BioGearsEngine::update_state() {

	const auto& patient = _bg->GetPatient();
	_state.living = true; //TODO:Implement IsAlive
	_state.tacycardia = false; //TODO: Implement Tacycardia HR > 100

	_state.age_yr = (patient.HasAge()) ? patient.GetAge(biogears::TimeUnit::yr) : 0.0;
	_state.height_cm = (patient.HasHeight()) ? patient.GetHeight(biogears::LengthUnit::cm) : 0.0;
	_state.gender = (!patient.HasGender()) ? EBioGearsGender::NONE
		: (patient.GetGender() == CDM::enumSex::Male) ? EBioGearsGender::MALE
		: EBioGearsGender::OTHER;
	_state.weight_kg = (patient.HasWeight()) ? patient.GetWeight(biogears::MassUnit::kg) : 0.0f;
	if (patient.HasWeight() && patient.HasWeight()) {
		auto BSA = std::sqrt(patient.GetHeight(biogears::LengthUnit::cm) * patient.GetWeight(biogears::MassUnit::kg) / 3600.0);
		_state.body_surface_area_m_sq = BSA;
		auto BMI = patient.GetWeight(biogears::MassUnit::kg) / std::pow(patient.GetHeight(biogears::LengthUnit::m), 2);
		_state.body_mass_index_kg_per_m_sq = BMI;
	}
	else {
		_state.body_surface_area_m_sq = 0.0;
		_state.body_mass_index_kg_per_m_sq = 0.0;
	}
	_state.body_fat_pct = (patient.HasBodyFatFraction()) ? patient.GetBodyFatFraction() : 0.0;
	//TODO: Lets take intensity and make a series of animated GIFs inspired off vault-boy
	_state.exercise_state = (_bg->GetActions().GetPatientActions().HasExercise()) ? EBioGearsExerciseState::STANDING : EBioGearsExerciseState::RUNNING;


}
//-------------------------------------------------------------------------------
UUE4BioGearsEngine::UUE4BioGearsEngine()
{

}
void UUE4BioGearsEngine::initialize_here(FString name)
{
	initialize_with_path(FPaths::GetPath("./"), name);
}
void UUE4BioGearsEngine::initialize_with_path(FString dataRoot, FString name)
{
	_logger = NewObject<UBioGearsLogger>(this, UBioGearsLogger::StaticClass());
	_logger->initialize(dataRoot + FString(TEXT("/")), name + FString(TEXT(".log")));

	_bg = MakeUnique<biogears::BioGearsEngine>(_logger->get(), TCHAR_TO_ANSI(*(dataRoot + "/")));
	_name = TCHAR_TO_ANSI(*name);
	_log_name = TCHAR_TO_ANSI(*(name + TEXT(".log")));
	_log_root = TCHAR_TO_ANSI(*(dataRoot + "/"));
	_data_root = TCHAR_TO_ANSI(*(dataRoot + "/"));
}
void UUE4BioGearsEngine::initialize_with_logger(FString dataRoot, UBioGearsLogger* logPtr)
{
	_logger = logPtr;
	_bg = MakeUnique<biogears::BioGearsEngine>(_logger->get(), TCHAR_TO_ANSI(*(dataRoot + "/")));
	_name = "UE4PhysiologyEngine";
	_log_name = "";
	_log_root = TCHAR_TO_ANSI(*(dataRoot + "/"));
	_data_root = TCHAR_TO_ANSI(*(dataRoot + "/"));
}

//-------------------------------------------------------------------------------
UUE4BioGearsEngine::~UUE4BioGearsEngine()
{
	_bg = nullptr;
	_logger = nullptr;
}

//-------------------------------------------------------------------------------
float UUE4BioGearsEngine::getSimulationTime() const
{
	return static_cast<float>(_bg->GetSimulationTime(biogears::TimeUnit::s));
}
//-------------------------------------------------------------------------------
FBioGearsMetrics    UUE4BioGearsEngine::getMetrics() const
{
	return _metrics;
}
//-------------------------------------------------------------------------------
FBioGearsConditions UUE4BioGearsEngine::getConditions() const
{
	return _conditions;
}
//-------------------------------------------------------------------------------
FBioGearsState      UUE4BioGearsEngine::getState() const
{
	return _state;
}
//-------------------------------------------------------------------------------
bool UUE4BioGearsEngine::load_patient(FString patientFile)
{
	//TODO:: Validate InitializeEngine can be called multiple times
	//TODO:: Might Need TO create a new BG here and retain WD
	std::lock_guard<std::mutex> guard{ _mutex };
	_bg = MakeUnique<biogears::BioGearsEngine>(_logger->get(), _data_root);
	_logger->setup_ue4_fowarding();
	_ready = _bg->InitializeEngine(TCHAR_TO_ANSI(*patientFile));
	if (_ready) {
		setup_cache();
		update_cache();
	}
	return _ready;
}
//-------------------------------------------------------------------------------
bool UUE4BioGearsEngine::load_patient_state(FString stateFile)
{
	std::lock_guard<std::mutex> guard{ _mutex };
	_bg = MakeUnique<biogears::BioGearsEngine>(_logger->get(), _data_root);
	_logger->setup_ue4_fowarding();
	_ready = _bg->LoadState(TCHAR_TO_ANSI(*stateFile));
	if (_ready) {
		setup_cache();
		update_cache();
	}
	return _ready;
}
//-------------------------------------------------------------------------------
void UUE4BioGearsEngine::advance_time(float seconds)
{
	 _mutex.lock();
	_bg->AdvanceModelTime(seconds, biogears::TimeUnit::s);
	update_cache();
	_mutex.unlock();
}
//-------------------------------------------------------------------------------
bool UUE4BioGearsEngine::isReady() const
{
	return _ready;
}
//-------------------------------------------------------------------------------
#include <biogears/cdm/patient/actions/SEUrinate.h>
bool UUE4BioGearsEngine::action_urinate()
{
	auto relief = biogears::SEUrinate();
	if (relief.IsValid()) {
		std::lock_guard<std::mutex> guard{ _mutex };
		_bg->ProcessAction(relief);
		return true;
	}
	else {
		return false;
	}
}
//-------------------------------------------------------------------------------
#include <biogears/cdm/patient/assessments/SEUrinalysis.h>
bool UUE4BioGearsEngine::get_urine_analysis()
{
	using namespace biogears;
	FBioGearsUrineAnalysis analysis;
	std::lock_guard<std::mutex> guard{ _mutex };
	SEUrinalysis urineAnalysis{ _bg->GetLogger() };

	bool assessmentSuccess = false;
	if (_bg->GetPatientAssessment(urineAnalysis))
	{
		switch (urineAnalysis.GetColorResult()) {
		default:
		case CDM::enumUrineColor::PaleYellow:
			analysis.color = EBioGearsUrineColor::PaleYellow;
			break;
		case CDM::enumUrineColor::Yellow:
			analysis.color = EBioGearsUrineColor::Yellow;
			break;
		case CDM::enumUrineColor::DarkYellow:
			analysis.color = EBioGearsUrineColor::DarkYellow;
			break;
		case CDM::enumUrineColor::Pink:
			analysis.color = EBioGearsUrineColor::Pink;
			break;
		}
		switch (urineAnalysis.GetAppearanceResult()) {
		default:

		case CDM::enumClarityIndicator::Clear:
			analysis.appearance = EBioGearsClarityIndicator::Clear;
			break;
		case CDM::enumClarityIndicator::SlightlyCloudy:
			analysis.appearance = EBioGearsClarityIndicator::SlightlyCloudy;
			break;
		case CDM::enumClarityIndicator::Cloudy:
			analysis.appearance = EBioGearsClarityIndicator::Cloudy;
			break;
		case CDM::enumClarityIndicator::Turbid:
			analysis.appearance = EBioGearsClarityIndicator::Turbid;
			break;
		}

		switch (urineAnalysis.GetGlucoseResult()) {
		default:

		case CDM::enumPresenceIndicator::Negative:
			analysis.glucose = EBioGearsPresenceIndicator::Negitive;
			break;
		case CDM::enumPresenceIndicator::Positive:
			analysis.glucose = EBioGearsPresenceIndicator::Positive;
			break;
		}

		switch (urineAnalysis.GetKetoneResult()) {
		default:

		case CDM::enumPresenceIndicator::Negative:
			analysis.ketone = EBioGearsPresenceIndicator::Negitive;
			break;
		case CDM::enumPresenceIndicator::Positive:
			analysis.ketone = EBioGearsPresenceIndicator::Positive;
			break;
		}

		switch (urineAnalysis.GetBloodResult()) {
		default:

		case CDM::enumPresenceIndicator::Negative:
			analysis.blood = EBioGearsPresenceIndicator::Negitive;
			break;
		case CDM::enumPresenceIndicator::Positive:
			analysis.blood = EBioGearsPresenceIndicator::Positive;
			break;
		}

		switch (urineAnalysis.GetProteinResult()) {
		default:

		case CDM::enumPresenceIndicator::value::Negative:
			analysis.protien = EBioGearsPresenceIndicator::Negitive;
			break;
		case CDM::enumPresenceIndicator::value::Positive:
			analysis.protien = EBioGearsPresenceIndicator::Positive;
			break;
		}

		switch (urineAnalysis.GetNitriteResult()) {
		default:

		case CDM::enumPresenceIndicator::Negative:
			analysis.nitrite = EBioGearsPresenceIndicator::Negitive;
			break;
		case CDM::enumPresenceIndicator::Positive:
			analysis.nitrite = EBioGearsPresenceIndicator::Positive;
			break;
		}

		switch (urineAnalysis.GetLeukocyteEsteraseResult()) {
		default:

		case CDM::enumPresenceIndicator::Negative:
			analysis.leukocyteEsterase = EBioGearsPresenceIndicator::Negitive;
			break;
		case CDM::enumPresenceIndicator::Positive:
			analysis.leukocyteEsterase = EBioGearsPresenceIndicator::Positive;
			break;
		}


		analysis.bilirubin = urineAnalysis.GetBilirubinResult().GetValue();
		analysis.specificgravity = urineAnalysis.GetSpecificGravityResult().GetValue();
		analysis.ph = urineAnalysis.GetPHResult().GetValue();
		analysis.urobilinogen = urineAnalysis.GetUrobilinogenResult().GetValue();
		assessmentSuccess = true;
		on_urine_analysis_completed.Broadcast(analysis);
	}
	else {
		_logger->Error(TEXT("Unable to finish urine_analysis"), TEXT("UE4BiogearsEngine"));

	}
	return assessmentSuccess;
}
//-------------------------------------------------------------------------------
#include <biogears/cdm/patient/assessments/SEComprehensiveMetabolicPanel.h>
bool UUE4BioGearsEngine::get_comprehensive_metabolic_panel() {
	using namespace biogears;
	FBioGearsMetabolicPanel analysis;
	std::lock_guard<std::mutex> guard{ _mutex };
	SEComprehensiveMetabolicPanel metabolic_panel{ _bg->GetLogger() };

	bool assessmentSuccess = false;
	if (_bg->GetPatientAssessment(metabolic_panel))
	{
		analysis.albumin = metabolic_panel.GetAlbumin().GetValue();
		analysis.ALP = metabolic_panel.GetALP().GetValue();
		analysis.ALT = metabolic_panel.GetALT().GetValue();
		analysis.AST = metabolic_panel.GetAST().GetValue();
		analysis.BUN = metabolic_panel.GetBUN().GetValue();
		analysis.calcium = metabolic_panel.GetCalcium().GetValue();
		analysis.chlordide = metabolic_panel.GetChloride().GetValue();
		analysis.co2 = metabolic_panel.GetCO2().GetValue();
		analysis.creatine = metabolic_panel.GetCreatinine().GetValue();
		analysis.glucose = metabolic_panel.GetGlucose().GetValue();
		analysis.potassium = metabolic_panel.GetPotassium().GetValue();
		analysis.sodium = metabolic_panel.GetSodium().GetValue();
		analysis.bilirubin = metabolic_panel.GetTotalBilirubin().GetValue();
		analysis.protien = metabolic_panel.GetTotalProtein().GetValue();
		assessmentSuccess = true;
		on_metabolic_panel_completed.Broadcast(analysis);
	}
	else {
		_logger->Error(TEXT("Unable to finish metabolic_panel"), TEXT("UE4BiogearsEngine"));

	}
	return assessmentSuccess;
}
//-------------------------------------------------------------------------------
#include <biogears/cdm/patient/assessments/SECompleteBloodCount.h>
bool UUE4BioGearsEngine::get_complete_blood_count() {
	using namespace biogears;
	FBioGearsBloodCount analysis;
	std::lock_guard<std::mutex> guard{ _mutex };
	SECompleteBloodCount bloodcount{ _bg->GetLogger() };

	bool assessmentSuccess = false;
	if (_bg->GetPatientAssessment(bloodcount))
	{
		analysis.hematocrit = bloodcount.GetHematocrit().GetValue();
		analysis.hemoglobin = bloodcount.GetHemoglobin().GetValue();
		analysis.platelet_count = bloodcount.GetPlateletCount().GetValue();
		analysis.mean_corpusular_hemoglobin = bloodcount.GetMeanCorpuscularHemoglobin().GetValue();
		analysis.mean_corpuscular_hemoglobin_concentration = bloodcount.GetMeanCorpuscularHemoglobinConcentration().GetValue();
		analysis.mean_corpuscular_volume = bloodcount.GetMeanCorpuscularVolume().GetValue();
		analysis.red_blood_cell_count = bloodcount.GetRedBloodCellCount().GetValue();
		analysis.white_blood_cell_count = bloodcount.GetWhiteBloodCellCount().GetValue();
		assessmentSuccess = true;
		on_blood_count_completed.Broadcast(analysis);
	}
	else {
		_logger->Error(TEXT("Unable to finish complete_blood_count"), TEXT("UE4BiogearsEngine"));

	}
	return assessmentSuccess;
}
//-------------------------------------------------------------------------------
#include <biogears/cdm/patient/assessments/SEPulmonaryFunctionTest.h>
#include <biogears/cdm/properties/SEFunctionVolumeVsTime.h>
bool UUE4BioGearsEngine::get_pulmonary_function_test() {
	using namespace biogears;
	FBioGearsPulmonaryTest analysis;
	std::lock_guard<std::mutex> guard{ _mutex };
	SEPulmonaryFunctionTest pulmonary_function{ _bg->GetLogger() };
	_bg->GetPatientAssessment(pulmonary_function);

	bool assessmentSuccess = false;
	if (_bg->GetPatientAssessment(pulmonary_function))
	{
		analysis.number_of_plot_points = pulmonary_function.GetNumberOfPlotPoints();
		analysis.expiratory_reserve_volume = pulmonary_function.GetExpiratoryReserveVolume().GetValue();
		analysis.forced_vital_capacity = pulmonary_function.GetForcedVitalCapacity().GetValue();
		analysis.forced_expiratory_volume = pulmonary_function.GetForcedExpiratoryFlow().GetValue();
		analysis.functional_residual_capacity = pulmonary_function.GetFunctionalResidualCapacity().GetValue();
		analysis.inspiratory_capacity = pulmonary_function.GetInspiratoryCapacity().GetValue();
		analysis.inspiratory_reserve_volume = pulmonary_function.GetInspiratoryReserveVolume().GetValue();
		analysis.maximum_volunatary_ventilation = pulmonary_function.GetMaximumVoluntaryVentilation().GetValue();
		analysis.peek_expitatory_flow = pulmonary_function.GetPeakExpiratoryFlow().GetValue();
		analysis.residual_volume = pulmonary_function.GetResidualVolume().GetValue();
		analysis.slow_vital_capacity = pulmonary_function.GetSlowVitalCapacity().GetValue();
		analysis.total_lung_capacity = pulmonary_function.GetTotalLungCapacity().GetValue();
		analysis.vital_capacity = pulmonary_function.GetVitalCapacity().GetValue();
		//TODO: Support Lung Volume Plot
		//		analysis.lung_volume_plot = pulmonary_function.GetLungVolumePlot().Get();
		on_pulmonary_test_completed.Broadcast(analysis);
		assessmentSuccess = true;
	}
	else {
		_logger->Error(TEXT("Unable to finish pulminary_function_test"), TEXT("UE4BiogearsEngine"));

	}
	return assessmentSuccess;
}
//-------------------------------------------------------------------------------
#include <biogears/cdm/system/environment/actions/SEEnvironmentChange.h>
bool UUE4BioGearsEngine::action_env_change(FBioGearsEnvironmentalConditions conditions)
{
	//TODO: Refactor - Introduce an environment struct
	return false;
}
//-------------------------------------------------------------------------------
#include <biogears/cdm/patient/actions/SETourniquet.h>
bool UUE4BioGearsEngine::action_apply_tourniquet(EBioGearsExtremity limb, EBioGearsTourniquet application)
{
	using namespace biogears;
	auto tourniquet = SETourniquet();

	switch (limb)
	{
	case EBioGearsExtremity::LeftArm:
		tourniquet.SetCompartment("LeftArm");
		break;
	case EBioGearsExtremity::RightArm:
		tourniquet.SetCompartment("RightArm");
		break;
	case EBioGearsExtremity::LeftLeg:
		tourniquet.SetCompartment("LeftLeg");
		break;
	case EBioGearsExtremity::RightLeg:
		tourniquet.SetCompartment("RightLeg");
		break;
	}

	switch (application)
	{
	case EBioGearsTourniquet::Applied:
		tourniquet.SetTourniquetLevel(CDM::enumTourniquetApplicationLevel::Applied);
		break;
	case EBioGearsTourniquet::Misapplied:
		tourniquet.SetTourniquetLevel(CDM::enumTourniquetApplicationLevel::Misapplied);
		break;
	case EBioGearsTourniquet::None:
		tourniquet.SetTourniquetLevel(CDM::enumTourniquetApplicationLevel::None);
		break;
	}

	if (tourniquet.IsValid()) {
		_bg->ProcessAction(tourniquet);
		return true;
	}
	else {
		return false;
	}
}
//-------------------------------------------------------------------------------
#include <biogears/cdm/patient/actions/SEHemorrhage.h>
bool UUE4BioGearsEngine::action_apply_hemorrhage(EBioGearsExtremity limb, float flowrate_ml_Per_min)
{

	//TODO: Thread Guard
	auto hemorrhage = biogears::SEHemorrhage();
	using namespace biogears;
	switch (limb) {
	default:
	case EBioGearsExtremity::LeftArm:
		hemorrhage.SetCompartment("LeftArm");
		break;
	case EBioGearsExtremity::RightArm:
		hemorrhage.SetCompartment("RightArm");
		break;
	case EBioGearsExtremity::LeftLeg:
		hemorrhage.SetCompartment("LeftLeg");
		break;
	case EBioGearsExtremity::RightLeg:
		hemorrhage.SetCompartment("RightLeg");
		break;
	}
	hemorrhage.GetInitialRate().SetValue(flowrate_ml_Per_min, biogears::VolumePerTimeUnit::mL_Per_min);
	if (hemorrhage.IsValid()) {
		std::lock_guard<std::mutex> guard{ _mutex };
		_bg->ProcessAction(hemorrhage);
		return true;
	}
	else {
		return false;
	}
}
//-------------------------------------------------------------------------------
#include <biogears/cdm/patient/actions/SETensionPneumothorax.h>
bool UUE4BioGearsEngine::action_tension_pneumothorax(EBioGearsSide side, EBioGearsPneumothorax type, float severity_0_to_1)
{
	using namespace biogears;
	auto pneumothorax = SETensionPneumothorax();
	switch (side) {
	case EBioGearsSide::Left:
		pneumothorax.SetSide(CDM::enumSide::Left);
		break;
	case EBioGearsSide::Right:
		pneumothorax.SetSide(CDM::enumSide::Right);
		break;
	}
	switch (type) {
	case EBioGearsPneumothorax::Open:
		pneumothorax.SetType(CDM::enumPneumothoraxType::Open);
		break;
	case EBioGearsPneumothorax::Closed:
		pneumothorax.SetType(CDM::enumPneumothoraxType::Closed);
		break;

	}

	pneumothorax.GetSeverity().SetValue(severity_0_to_1);
	if (pneumothorax.IsValid()) {
		std::lock_guard<std::mutex> guard{ _mutex };
		_bg->ProcessAction(pneumothorax);
		return true;
	}
	else {
		return false;
	}
}
//-------------------------------------------------------------------------------
#include <biogears/cdm/patient/actions/SENeedleDecompression.h>
bool UUE4BioGearsEngine::action_needle_decompression(EBioGearsSide side, bool active)
{
	using namespace biogears;
	auto needleD = SENeedleDecompression();
	switch (side) {
	case EBioGearsSide::Left:
		needleD.SetSide(CDM::enumSide::Left);
		break;
	case EBioGearsSide::Right:
		needleD.SetSide(CDM::enumSide::Right);
		break;
	}

	needleD.SetActive(active);
	if (needleD.IsValid()) {
		std::lock_guard<std::mutex> guard{ _mutex };
		_bg->ProcessAction(needleD);
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
bool UUE4BioGearsEngine::action_o2_mask(float o2_fraction, float o2_volume1, float o2_volume2)
{
	using namespace biogears;
	std::lock_guard<std::mutex> guard{ _mutex };
	auto AMConfig = SEAnesthesiaMachineConfiguration(_bg->GetSubstanceManager());
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

		_bg->ProcessAction(AMConfig);
		return true;
	}
	else {
		return false;
	}
	return false;
}
//-------------------------------------------------------------------------------
#include <biogears/cdm/patient/actions/SEInfection.h>
bool UUE4BioGearsEngine::action_infection(EBioGearsInfectionSeverity severity, FString location, float mic_mg_Per_l)
{
	using namespace biogears;
	auto sepsis = biogears::SEInfection();

	switch (severity)
	{
	default:
	case EBioGearsInfectionSeverity::Eliminated:
		sepsis.SetSeverity(CDM::enumInfectionSeverity::Eliminated);
		break;
	case EBioGearsInfectionSeverity::Mild:
		sepsis.SetSeverity(CDM::enumInfectionSeverity::Mild);
		break;
	case EBioGearsInfectionSeverity::Moderate:
		sepsis.SetSeverity(CDM::enumInfectionSeverity::Moderate);
		break;
	case EBioGearsInfectionSeverity::Severe:
		sepsis.SetSeverity(CDM::enumInfectionSeverity::Severe);
		break;
	}


	sepsis.SetLocation(TCHAR_TO_ANSI(*location));
	sepsis.GetMinimumInhibitoryConcentration().SetValue(mic_mg_Per_l, biogears::MassPerVolumeUnit::mg_Per_L);
	if (sepsis.IsValid()) {
		std::lock_guard<std::mutex> guard{ _mutex };
		_bg->ProcessAction(sepsis);
		return true;
	}
	else {
		return false;
	}
}
//-------------------------------------------------------------------------------
#include <biogears/cdm/patient/actions/SESubstanceInfusion.h>
#include <biogears/cdm/substance/SESubstanceCompound.h>
bool UUE4BioGearsEngine::action_bloodtransfusion(EBioGearsBloodType type, float blood_volume_ml, float flowrate_ml_Per_min)
{
	using namespace biogears;
	std::lock_guard<std::mutex> guard{ _mutex };
	SESubstanceCompound* bloodSource = nullptr;

	switch (type)
	{
	case EBioGearsBloodType::O_Negitive:	bloodSource = _bg->GetSubstanceManager().GetCompound("Blood_ONegative"); break;
	case EBioGearsBloodType::O_Positive:	bloodSource = _bg->GetSubstanceManager().GetCompound("Blood_OPositive"); break;
	case EBioGearsBloodType::A_B_Negative:	bloodSource = _bg->GetSubstanceManager().GetCompound("Blood_ABNegative"); break;
	case EBioGearsBloodType::A_B_Positive:	bloodSource = _bg->GetSubstanceManager().GetCompound("Blood_ABPositive"); break;
	case EBioGearsBloodType::A_Negitive:	bloodSource = _bg->GetSubstanceManager().GetCompound("Blood_ANegative"); break;
	case EBioGearsBloodType::A_Positive:	bloodSource = _bg->GetSubstanceManager().GetCompound("Blood_APositive"); break;
	case EBioGearsBloodType::B_Negative:	bloodSource = _bg->GetSubstanceManager().GetCompound("Blood_NNegative"); break;
	case EBioGearsBloodType::B_Positive:	bloodSource = _bg->GetSubstanceManager().GetCompound("Blood_BPositive"); break;
	default:	bloodSource = _bg->GetSubstanceManager().GetCompound("Blood_ONegative"); break;
	}

	auto transfusion = SESubstanceCompoundInfusion(*bloodSource);
	transfusion.GetBagVolume().SetValue(blood_volume_ml, biogears::VolumeUnit::mL); //the total volume in the bag
	transfusion.GetRate().SetValue(flowrate_ml_Per_min, biogears::VolumePerTimeUnit::mL_Per_min); //The rate to admnister the compound in the bag

	if (transfusion.IsValid()) {
		_bg->ProcessAction(transfusion);
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
bool UUE4BioGearsEngine::action_thermal_blanket(float watt, float surface_area_fraction)
{
	using namespace biogears;
	auto thermalApplication = SEThermalApplication();
	auto& blanket = thermalApplication.GetActiveHeating();
	blanket.GetPower().SetValue(watt, PowerUnit::W);
	blanket.GetSurfaceAreaFraction().SetValue(surface_area_fraction);
	if (thermalApplication.IsValid()) {
		std::lock_guard<std::mutex> guard{ _mutex };
		_bg->ProcessAction(thermalApplication);
		return true;
	}
	else {
		return false;
	}
	return false;
}
//-------------------------------------------------------------------------------
#include <biogears/cdm/patient/actions/SEPainStimulus.h>
bool UUE4BioGearsEngine::action_pain_stimulus(EBioGearsCompartment compartment, float severity)
{
	auto pain = biogears::SEPainStimulus();
	switch (compartment)
	{
	case EBioGearsCompartment::LeftArm:	pain.SetLocation("LeftArm"); break;
	case EBioGearsCompartment::RightArm:	pain.SetLocation("RightArm"); break;
	case EBioGearsCompartment::LeftLeg:	pain.SetLocation("LeftLeg"); break;
	case EBioGearsCompartment::RightLeg:	pain.SetLocation("RightLeg"); break;
	}

	pain.GetSeverity().SetValue(severity);
	if (pain.IsValid()) {
		std::lock_guard<std::mutex> guard{ _mutex };
		_bg->ProcessAction(pain);
		return true;
	}
	else {
		return false;
	}
	return false;
}
bool UUE4BioGearsEngine::action_substanceInfusion(EBioGearsIvSubstance substance, float substance_volume_ml, float flowrate_ml_Per_min)
{
	//TODO: Implement Substance Infusion Action
	return false;
}
bool UUE4BioGearsEngine::action_substanceCompoundInfusion(EBioGearsIvCompound compound, float compound_volume_ml, float flowrate_ml_Per_min)
{
	//TODO: Implement SubstanceCompound Infusion Action
	return false;
}
bool UUE4BioGearsEngine::action_oralSubstanceAdministration(EBioGearsOralSubstance type, EBioGearsOralAbsorption, float dosage_mg)
{
	//TODO: Implement Oral Substance  Action
	return false;
}
//-------------------------------------------------------------------------------
bool UUE4BioGearsEngine::new_environment(FString key, FBioGearsEnvironmentalConditions conditions) { return false; }
bool UUE4BioGearsEngine::set_environment(FString key) { return false; }
bool UUE4BioGearsEngine::new_custom_compound(FString key, FBioGearsCompound compound) { return false; }
bool UUE4BioGearsEngine::custom_compound_infusion(FString key, float substance_volume_ml, float flowrate_ml_Per_min) { return false; }

//Destructor Functions
void UUE4BioGearsEngine::BeginDestroy()
{
	Super::BeginDestroy();
}
bool UUE4BioGearsEngine::IsReadyForFinishDestroy()
{
	return true;
}
void UUE4BioGearsEngine::FinishDestroy()
{
	Super::FinishDestroy();
}