#include "UBioGearsEngineDriver.h"
#include "UBioGearsengine.h"
#include "UBioGearsLogger.h"

#include <chrono>
#include <atomic>

#include <thread>

#include <biogears/container/concurrent_queue.h>
#include <biogears/framework/scmp/scmp_channel.h>
#include <biogears/cdm/scenario/SEAction.h>
#include <biogears/cdm/properties/SEScalarTime.h>
#include <biogears/engine/Controller/BioGearsengine.h>
#include <biogears/framework/scmp/scmp_channel.tci.h>
#include <biogears/container/concurrent_queue.tci.h>
#include <biogears/version.h>


void UBioGearsEngineDriver::action_urinate()
{
	_action_source->insert([&]() { return _engine->action_urinate(); });
}
//-------------------------------------------------------------------------------
void UBioGearsEngineDriver::action_env_change(FEnvironmentalConditions conditons)
{
	return;
}
//-------------------------------------------------------------------------------
void UBioGearsEngineDriver::action_apply_tourniquet(EExtremity limb, ETourniquet application)
{
	_action_source->insert([&, limb, application]() { return _engine->action_apply_tourniquet(limb, application); });
}
//-------------------------------------------------------------------------------
void UBioGearsEngineDriver::action_apply_hemorrhage(EExtremity limb, float flowrate_ml_Per_min)
{
	_action_source->insert([&, limb, flowrate_ml_Per_min]() { return _engine->action_apply_hemorrhage(limb, flowrate_ml_Per_min); });
}
//-------------------------------------------------------------------------------
void UBioGearsEngineDriver::action_tension_pneumothorax(ESide side, EPneumothorax type, float severity_0_to_1)
{
	_action_source->insert([&, side, type, severity_0_to_1]() { return _engine->action_tension_pneumothorax(side, type, severity_0_to_1); });
}
//-------------------------------------------------------------------------------
void UBioGearsEngineDriver::action_needle_decompression(ESide side, bool active)
{
	_action_source->insert([&, side, active]() { return _engine->action_needle_decompression(side, active); });
}
//-------------------------------------------------------------------------------
void UBioGearsEngineDriver::action_o2_mask(float o2_fraction, float o2_volume1, float o2_volume2)
{
	_action_source->insert([&, o2_fraction, o2_volume1, o2_volume2]() { return _engine->action_o2_mask(o2_fraction, o2_volume1, o2_volume2); });
}
//-------------------------------------------------------------------------------
void UBioGearsEngineDriver::action_infection(EInfectionSeverity severity, FString location, float mic_mg_Per_l)
{
	_action_source->insert([&, severity, location, mic_mg_Per_l]() { return _engine->action_infection(severity, location, mic_mg_Per_l); });
}
//-------------------------------------------------------------------------------
void UBioGearsEngineDriver::action_bloodtransfusion(EBloodType type, float blood_volume_ml, float flowrate_ml_Per_min)
{
	_action_source->insert([&, type, blood_volume_ml, flowrate_ml_Per_min]() { return _engine->action_bloodtransfusion(type, blood_volume_ml, flowrate_ml_Per_min); });
}
//-------------------------------------------------------------------------------
void UBioGearsEngineDriver::action_substanceInfusion(EIvSubstance substance, float bag_volume_ml, float flowrate_ml_Per_min)
{
	_action_source->insert([&, substance, bag_volume_ml, flowrate_ml_Per_min]() { return _engine->action_substanceInfusion(substance, bag_volume_ml, flowrate_ml_Per_min); });
}
//-------------------------------------------------------------------------------
void UBioGearsEngineDriver::action_substanceCompoundInfusion(EIvCompound compound, float bag_volume_ml, float flowrate_ml_Per_min)
{
	_action_source->insert([&, compound, bag_volume_ml, flowrate_ml_Per_min]() { return _engine->action_substanceCompoundInfusion(compound, bag_volume_ml, flowrate_ml_Per_min); });
}
//-------------------------------------------------------------------------------
void UBioGearsEngineDriver::action_oralSubstanceAdministration(EOralSubstance type, EOralAbsorption route, float dosage_mg)
{
	_action_source->insert([&, type, route, dosage_mg]() { return _engine->action_oralSubstanceAdministration(type, route, dosage_mg); });
}
//-------------------------------------------------------------------------------
void UBioGearsEngineDriver::action_thermal_blanket(float watt, float surface_area_fraction)
{
	_action_source->insert([&, watt, surface_area_fraction]() { return _engine->action_thermal_blanket(watt, surface_area_fraction); });
}
//-------------------------------------------------------------------------------
void UBioGearsEngineDriver::action_pain_stimulus(ECompartment compartment, float severity)
{
	_action_source->insert([&, compartment, severity]() { return _engine->action_pain_stimulus(compartment, severity); });
}
//-------------------------------------------------------------------------------
void UBioGearsEngineDriver::engine_thread_main()
{
	using namespace std::chrono_literals;
	using namespace biogears;

	auto current_time = std::chrono::steady_clock::now();
	std::chrono::time_point<std::chrono::steady_clock> prev;

	_engine_running = true;
	while (_engine_thread_continue) {
		prev = current_time;

		using namespace std::chrono_literals;
		if (_engine && !_engine_paused) {
			while (_action_queue.size()) {
				if ( !_action_queue.consume()())
				{
					UE_LOG(BioGearsLog, Error, TEXT("Unable to process given action."));
				} else
				{
					UE_LOG(BioGearsLog, Display, TEXT("Processed an action"));
				}
			}
			_engine->advance_time(1s);

			onStateUpdated.Broadcast(_engine->getState());
			onMetricsUpdated.Broadcast(_engine->getMetrics());
			onConditionsUpdated.Broadcast(_engine->getConditions());
			
			onTimeAdvance.Broadcast(_engine->getSimulationTime());
		}
		else {
			std::this_thread::sleep_for(16ms);
		}

		current_time = std::chrono::steady_clock::now();
		if (_engine_throttled) {
			while ((current_time - prev) < 1s) {
				std::this_thread::sleep_for(16ms);
				current_time = std::chrono::steady_clock::now();
			}
		}
	}
	_engine_running = false;
}
//-------------------------------------------------------------------------------
inline void UBioGearsEngineDriver::engine_thread_step()
{
	using namespace std::chrono_literals;
	if (_engine && !_engine_paused) {
		while (_action_queue.size()) {
			if (_action_queue.consume()())
			{
				UE_LOG(BioGearsLog, Error, TEXT("Unable to process given action."));
			}
		}
		_engine->advance_time(1s);
	}
	else {
		std::this_thread::sleep_for(16ms);
	}
}
//-------------------------------------------------------------------------------
UBioGearsEngineDriver::UBioGearsEngineDriver(const FObjectInitializer& ObjectInitializer)
	: Super(ObjectInitializer)
	, _action_queue()
	, _action_source(MakeUnique<Source>(_action_queue.as_source()))
	, _engine_thread_continue(false)
	, _engine_running(false)
	, _engine_paused(false)
	, _engine_throttled(true)
{

}
//-------------------------------------------------------------------------------
void UBioGearsEngineDriver::initialize_here(FString name, UObject* parent)
{
	FString biogearsContentPath = FString::Printf(TEXT("BioGears/%d.%d.%d"), ::biogears::biogears_major_version()
		, ::biogears::biogears_minor_version()
		, ::biogears::biogears_patch_version());

	FString biogearsContentDir = FPaths::Combine(FPaths::ProjectDir(), TEXT("Plugins"), TEXT("Content"), biogearsContentPath);
	
	this->_engine = MakeUnique<UBioGearsEngine>(biogearsContentDir, MakeUnique<UBioGearsLogger>(biogearsContentDir, TEXT("/") + name + TEXT(".log")));
	this->_action_source = nullptr;
	this->_action_source = MakeUnique<Source>(_action_queue.as_source());

}
//-------------------------------------------------------------------------------
void UBioGearsEngineDriver::initialize(FString working_dir, FString name, UObject* parent)
{
	this->_engine = MakeUnique<UBioGearsEngine>(working_dir, MakeUnique<UBioGearsLogger>(working_dir, name));
	this->_action_source = nullptr;
	this->_action_source = MakeUnique<Source>(_action_queue.as_source());

}
//-------------------------------------------------------------------------------
UBioGearsEngineDriver::~UBioGearsEngineDriver()
{
	_engine_paused = false;
	_engine_throttled = false;
	_engine_thread_continue = false;
	if (_engineThread.joinable())
	{
		_engineThread.join();
	}
}
bool UBioGearsEngineDriver::load_patient_state(FString stateFile)
{
	return _action_source->insert([&, stateFile]() { return _engine->load_patient_state(stateFile); });
}
//-------------------------------------------------------------------------------
bool UBioGearsEngineDriver::load_patient(FString patientFile)
{
	return _action_source->insert([&, patientFile]() { return _engine->load_patient(patientFile); });
}
//-------------------------------------------------------------------------------
void UBioGearsEngineDriver::start()
{
	using namespace biogears;
	using namespace std::chrono_literals;

	if (!_engineThread.joinable()) {
		_engine_thread_continue = true;
		_engineThread = std::thread{ &UBioGearsEngineDriver::engine_thread_main, this };

		runningToggled.Broadcast(_engine_thread_continue);
		
	}
	else if (!_engine_thread_continue)
	{
		_engineThread.join();
		_engine_thread_continue = true;
		_engineThread = std::thread{ &UBioGearsEngineDriver::engine_thread_main, this };

		runningToggled.Broadcast(_engine_thread_continue);
		
	}
}

void UBioGearsEngineDriver::pause_resume(bool state)
{
	_engine_paused = state;

	pausedToggled.Broadcast(_engine_paused);
	
}
//-------------------------------------------------------------------------------
void UBioGearsEngineDriver::stop()
{
	_engine_paused = true;
	_engine_throttled = false;
	_engine_thread_continue = false;
	
	pausedToggled.Broadcast(_engine_paused);
	runningToggled.Broadcast(_engine_thread_continue);
	throttledToggled.Broadcast(_engine_throttled);
}
//-------------------------------------------------------------------------------
void UBioGearsEngineDriver::join()
{
	if (_engineThread.joinable())
	{
		_engineThread.join();
	}
}
//-------------------------------------------------------------------------------
void UBioGearsEngineDriver::set_throttle(int rate)
{
	if (rate <= 1)	{
		_engine_throttled = true;
	}	else if (rate > 1)	{
		_engine_throttled = false;
	}
	throttledToggled.Broadcast(_engine_throttled);
	
	return;
}
//-------------------------------------------------------------------------------
bool UBioGearsEngineDriver::isReady()
{
	return _engine->isReady();
}
//-------------------------------------------------------------------------------
bool UBioGearsEngineDriver::running()
{
	return _engine_thread_continue && _engine_thread_continue;
}
//-------------------------------------------------------------------------------
bool UBioGearsEngineDriver::paused()
{
	return _engine_paused;
}
//-------------------------------------------------------------------------------
bool UBioGearsEngineDriver::throttled()
{
	return _engine_throttled;
}
//-------------------------------------------------------------------------------
float UBioGearsEngineDriver::getSimulationTime()
{
	return _engine->getSimulationTime();
}

//-------------------------------------------------------------------------------
void UBioGearsEngineDriver::BeginDestroy()
{
	_engine_paused = false;
	_engine_throttled = false;
	_engine_thread_continue = false;

	Super::BeginDestroy();
}
//-------------------------------------------------------------------------------
bool UBioGearsEngineDriver::IsReadyForFinishDestroy() {
	return !(_engine_thread_continue || _engine_thread_continue);

}
//-------------------------------------------------------------------------------
void UBioGearsEngineDriver::FinishDestroy()
{
	if (_engineThread.joinable())
	{
		_engineThread.join();
	}
	Super::FinishDestroy();
}
//-------------------------------------------------------------------------------