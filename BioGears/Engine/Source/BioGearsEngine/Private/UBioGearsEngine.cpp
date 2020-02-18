#include "UBioGearsEngine.h"

#include <thread>
#include <memory>
#include <mutex>
#include <atomic>

#include <biogears/engine/BioGearsPhysiologyEngine.h>
#include <biogears/engine/controller/BioGears.h>
#include <biogears/engine/controller/BioGearsEngine.h>
struct UBioGearsEngine::Implementation
{
	TUniquePtr <UBioGearsLogger> logger;     //<! Only Used if logger not passed to system
	TUniquePtr<biogears::BioGearsEngine> bg;

	std::mutex mutex;
	std::string name;
	std::string log_name;
	std::string log_root;
	std::string data_root;

	std::atomic_bool ready{ false };

	explicit Implementation();
	explicit Implementation(const std::string& dataRoot, const std::string& n);
	explicit Implementation(const std::string& dataRoot, TUniquePtr<UBioGearsLogger>  logger);
};
UBioGearsEngine::Implementation::Implementation()
	: Implementation(TCHAR_TO_ANSI(*FPaths::GetPath("./")), "UBioGearsEngine")
{ }
UBioGearsEngine::Implementation::Implementation(const std::string& dataRoot, const std::string& n)
	: logger(MakeUnique<UBioGearsLogger>(ANSI_TO_TCHAR(dataRoot.c_str()) + FString(TEXT("/")), ANSI_TO_TCHAR(n.c_str()) + FString(TEXT(".log")) ))
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
std::chrono::seconds UBioGearsEngine::getSimulationTime()
{
	return std::chrono::seconds{ static_cast<int>(_pimpl->bg->GetSimulationTime(biogears::TimeUnit::s)) };
}
//-------------------------------------------------------------------------------
FBiogearsMetrics    UBioGearsEngine::getMetrics()
{
	return {};
}
//-------------------------------------------------------------------------------
FBiogearsConditions UBioGearsEngine::getConditions()
{
	return {};
}
//-------------------------------------------------------------------------------
FBiogearsState      UBioGearsEngine::getState()
{
	return {};
}
//-------------------------------------------------------------------------------
bool UBioGearsEngine::load_patient(FString patientFile)
{
	//TODO:: Validate InitializeEngine can be called multiple times
	//TODO:: Might Need TO create a new BG here and retain WD
	std::lock_guard<std::mutex> guard{ _pimpl->mutex };
	_pimpl->bg = MakeUnique<biogears::BioGearsEngine>(_pimpl->logger.Get(), _pimpl->data_root);
	_pimpl->logger->init();
	return _pimpl->ready = _pimpl->bg->InitializeEngine(TCHAR_TO_ANSI(*patientFile));
}
//-------------------------------------------------------------------------------
bool UBioGearsEngine::load_patient_state(FString stateFile)
{
	std::lock_guard<std::mutex> guard{ _pimpl->mutex };
	_pimpl->bg = MakeUnique<biogears::BioGearsEngine>(_pimpl->logger.Get(), _pimpl->data_root);
	_pimpl->logger->init();
	return _pimpl->ready = _pimpl->bg->LoadState(TCHAR_TO_ANSI(*stateFile));
}
//-------------------------------------------------------------------------------
void UBioGearsEngine::advance_time(std::chrono::seconds seconds)
{
	std::lock_guard<std::mutex> guard{ _pimpl->mutex };
	_pimpl->bg->AdvanceModelTime(seconds.count(), biogears::TimeUnit::s);
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
bool UBioGearsEngine::isReady()
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