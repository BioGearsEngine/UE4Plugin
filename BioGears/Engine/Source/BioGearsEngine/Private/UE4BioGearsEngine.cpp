#include "UE4BioGearsEngine.h"

#include <thread>
#include <memory>
#include <mutex>
#include <atomic>

#include <biogears/engine/BioGearsPhysiologyEngine.h>
#include <biogears/engine/controller/BioGears.h>
#include <biogears/engine/controller/BioGearsEngine.h>
struct UE4BioGearsEngine::Implementation
{
	std::unique_ptr<biogears::BioGearsEngine> bg;
	std::mutex mutex;
	std::string name;

	std::atomic_bool ready{ false };

	Implementation();
	Implementation(std::string dataRoot, std::string n);
};
UE4BioGearsEngine::Implementation::Implementation()
	: Implementation(TCHAR_TO_ANSI(*FPaths::GetPath("./")), "UE4BioGearsEngine")
{ }
UE4BioGearsEngine::Implementation::Implementation(std::string dataRoot, std::string n)
	: bg(std::make_unique<biogears::BioGearsEngine>(n + ".log", dataRoot + "/"))
	, name(n)
{ }
//-------------------------------------------------------------------------------
UE4BioGearsEngine::UE4BioGearsEngine()
	: _pimpl(MakeUnique<Implementation>())
{

}
UE4BioGearsEngine::UE4BioGearsEngine(FString name)
	: _pimpl(MakeUnique<Implementation>(TCHAR_TO_ANSI(*FPaths::GetPath("./")), TCHAR_TO_ANSI(*name)))
{
}
UE4BioGearsEngine::UE4BioGearsEngine(FString dataRoot, FString name)
	: _pimpl(MakeUnique<Implementation>(TCHAR_TO_ANSI(*dataRoot), TCHAR_TO_ANSI(*name)))
{
}
//-------------------------------------------------------------------------------
UE4BioGearsEngine::UE4BioGearsEngine(UE4BioGearsEngine&& obj) noexcept
	: _pimpl(std::move(obj._pimpl))
{
	obj._pimpl = TUniquePtr<Implementation>();
}
//-------------------------------------------------------------------------------
UE4BioGearsEngine::~UE4BioGearsEngine()
{
	_pimpl = nullptr;
}
//-------------------------------------------------------------------------------
UE4BioGearsEngine& UE4BioGearsEngine::operator=(UE4BioGearsEngine&& rhs) noexcept
{
	this->_pimpl = std::move(rhs._pimpl);
	rhs._pimpl = TUniquePtr<Implementation>();
	return *this;
}

//-------------------------------------------------------------------------------
std::chrono::seconds UE4BioGearsEngine::getSimulationTime()
{
	return std::chrono::seconds{ static_cast<int>(_pimpl->bg->GetSimulationTime(biogears::TimeUnit::s)) };
}
//-------------------------------------------------------------------------------
biogears::BiogearsMetrics    UE4BioGearsEngine::getMetrics()
{
	return {};
}
//-------------------------------------------------------------------------------
biogears::BiogearsConditions UE4BioGearsEngine::getConditions()
{
	return {};
}
//-------------------------------------------------------------------------------
biogears::BiogearsState      UE4BioGearsEngine::getState()
{
	return {};
}
//-------------------------------------------------------------------------------
bool UE4BioGearsEngine::load_patient(FString patientFile)
{
	//TODO:: Validate InitializeEngine can be called multiple times
	//TODO:: Might Need TO create a new BG here and retain WD
	std::lock_guard<std::mutex> guard{ _pimpl->mutex };
	return _pimpl->ready = _pimpl->bg->InitializeEngine(TCHAR_TO_ANSI(*patientFile));
}
//-------------------------------------------------------------------------------
bool UE4BioGearsEngine::load_patient_state(FString stateFile)
{
	std::lock_guard<std::mutex> guard{ _pimpl->mutex };
	return _pimpl->ready = _pimpl->bg->LoadState(TCHAR_TO_ANSI(*stateFile));
}
//-------------------------------------------------------------------------------
void UE4BioGearsEngine::advance_time(std::chrono::seconds seconds)
{
	std::lock_guard<std::mutex> guard{ _pimpl->mutex };
	_pimpl->bg->AdvanceModelTime(seconds.count(), biogears::TimeUnit::s);
}
//-------------------------------------------------------------------------------
bool UE4BioGearsEngine::process_action(std::unique_ptr<biogears::SEAction> action)
{
	std::lock_guard<std::mutex> guard{ _pimpl->mutex };
	auto result = _pimpl->bg->ProcessAction(*action);
	action.reset();
	return result;
}
//-------------------------------------------------------------------------------
bool UE4BioGearsEngine::isReady()
{
	return _pimpl->ready;
}
//-------------------------------------------------------------------------------
#include <biogears/cdm/patient/actions/SEUrinate.h>
bool UE4BioGearsEngine::action_urinate()
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
bool UE4BioGearsEngine::get_urine_color(biogears::eUrineColor& eColor)
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
			eColor = biogears::eUrineColor::DarkYellow;
		case CDM::enumUrineColor::PaleYellow:
			eColor = biogears::eUrineColor::PaleYellow;
		case CDM::enumUrineColor::Pink:
			eColor = biogears::eUrineColor::Pink;
		case CDM::enumUrineColor::Yellow:
			eColor = biogears::eUrineColor::Yellow;
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
bool UE4BioGearsEngine::action_env_change(biogears::sEnvironmentalConditions conditions)
{
	//TODO: Refactor - Introduce an environment struct
	return false;
}
//-------------------------------------------------------------------------------
#include <biogears/cdm/patient/actions/SETourniquet.h>
bool UE4BioGearsEngine::action_apply_tourniquet(biogears::eExtremity limb, biogears::eTourniquet application)
{
	using namespace biogears;
	auto tourniquet = SETourniquet();

	switch (limb)
	{
	case eExtremity::LeftArm:
		tourniquet.SetCompartment("LeftArm");
		break;
	case eExtremity::RightArm:
		tourniquet.SetCompartment("RightArm");
		break;
	case eExtremity::LeftLeg:
		tourniquet.SetCompartment("LeftLeg");
		break;
	case eExtremity::RightLeg:
		tourniquet.SetCompartment("RightLeg");
		break;
	}

	switch (application)
	{
	case eTourniquet::Applied:
		tourniquet.SetTourniquetLevel(CDM::enumTourniquetApplicationLevel::Applied);
		break;
	case eTourniquet::Misapplied:
		tourniquet.SetTourniquetLevel(CDM::enumTourniquetApplicationLevel::Misapplied);
		break;
	case eTourniquet::None:
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
bool UE4BioGearsEngine::action_apply_hemorrhage(biogears::eExtremity limb, double flowrate_ml_Per_min)
{

	//TODO: Thread Guard
	auto hemorrhage = biogears::SEHemorrhage();
	using namespace biogears;
	switch (limb) {
	case eExtremity::LeftArm:
		hemorrhage.SetCompartment("LeftArm");
		break;
	case eExtremity::RightArm:
		hemorrhage.SetCompartment("RightArm");
		break;
	case eExtremity::LeftLeg:
		hemorrhage.SetCompartment("LeftLeg");
		break;
	case eExtremity::RightLeg:
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
bool UE4BioGearsEngine::action_tension_pneumothorax(biogears::eSide side, biogears::ePneumothorax type, double severity_0_to_1)
{
	using namespace biogears;
	auto pneumothorax = SETensionPneumothorax();
	switch (side) {
	case eSide::Left:
		pneumothorax.SetSide(CDM::enumSide::Left);
		break;
	case eSide::Right:
		pneumothorax.SetSide(CDM::enumSide::Right);
		break;
	}
	switch (type) {
	case ePneumothorax::Open:
		pneumothorax.SetType(CDM::enumPneumothoraxType::Open);
		break;
	case ePneumothorax::Closed:
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
bool UE4BioGearsEngine::action_needle_decompression(biogears::eSide side, bool active)
{
	using namespace biogears;
	auto needleD = SENeedleDecompression();
	switch (side) {
	case eSide::Left:
		needleD.SetSide(CDM::enumSide::Left);
		break;
	case eSide::Right:
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
bool UE4BioGearsEngine::action_o2_mask(double o2_fraction, double o2_volume1, double o2_volume2)
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
bool UE4BioGearsEngine::action_infection(biogears::eInfectionSeverity severity, FString location, double mic_mg_Per_l)
{
	using namespace biogears;
	auto sepsis = biogears::SEInfection();

	switch (severity)
	{
	case eInfectionSeverity::Eliminated:
		sepsis.SetSeverity(CDM::enumInfectionSeverity::Eliminated);
		break;
	case eInfectionSeverity::Mild:
		sepsis.SetSeverity(CDM::enumInfectionSeverity::Mild);
		break;
	case eInfectionSeverity::Moderate:
		sepsis.SetSeverity(CDM::enumInfectionSeverity::Moderate);
		break;
	case eInfectionSeverity::Severe:
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
bool UE4BioGearsEngine::action_bloodtransfuction(biogears::eBloodType type, double blood_volume_ml, double flowrate_ml_Per_min)
{
	using namespace biogears;
	std::lock_guard<std::mutex> guard{ _pimpl->mutex };
	SESubstanceCompound* bloodSource = nullptr;

	switch (type)
	{
	case eBloodType::O_Negitive:	bloodSource = _pimpl->bg->GetSubstanceManager().GetCompound("Blood_ONegative"); break;
	case eBloodType::O_Positive:	bloodSource = _pimpl->bg->GetSubstanceManager().GetCompound("Blood_OPositive"); break;
	case eBloodType::A_B_Negative:	bloodSource = _pimpl->bg->GetSubstanceManager().GetCompound("Blood_ABNegative"); break;
	case eBloodType::A_B_Positive:	bloodSource = _pimpl->bg->GetSubstanceManager().GetCompound("Blood_ABPositive"); break;
	case eBloodType::A_Negitive:	bloodSource = _pimpl->bg->GetSubstanceManager().GetCompound("Blood_ANegative"); break;
	case eBloodType::A_Positive:	bloodSource = _pimpl->bg->GetSubstanceManager().GetCompound("Blood_APositive"); break;
	case eBloodType::B_Negative:	bloodSource = _pimpl->bg->GetSubstanceManager().GetCompound("Blood_NNegative"); break;
	case eBloodType::B_Positive:	bloodSource = _pimpl->bg->GetSubstanceManager().GetCompound("Blood_BPositive"); break;
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
bool UE4BioGearsEngine::action_thermal_blanket(double watt, double surface_area_fraction)
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
bool UE4BioGearsEngine::action_pain_stimulus(biogears::eCompartment compartment, double severity)
{
	auto pain = biogears::SEPainStimulus();
	switch (compartment)
	{
	case biogears::eCompartment::LeftArm:	pain.SetLocation("LeftArm"); break;
	case biogears::eCompartment::RightArm:	pain.SetLocation("RightArm"); break;
	case biogears::eCompartment::LeftLeg:	pain.SetLocation("LeftLeg"); break;
	case biogears::eCompartment::RightLeg:	pain.SetLocation("RightLeg"); break;
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
//-------------------------------------------------------------------------------