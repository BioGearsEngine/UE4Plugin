#include "UE4BioGearsEngineDriver.h"
#include "UE4BioGearsEngine.h"
#include "UE4BioGearsLogger.h"

#include <chrono>
#include <atomic>
#include <mutex>
#include <thread>

#include <biogears/container/concurrent_queue.h>
#include <biogears/framework/scmp/scmp_channel.h>
#include <biogears/cdm/scenario/SEAction.h>
#include <biogears/cdm/properties/SEScalarTime.h>
#include <biogears/engine/Controller/BioGearsEngine.h>
#include <biogears/framework/scmp/scmp_channel.tci.h>
#include <biogears/container/concurrent_queue.tci.h>

struct UE4BioGearsEngineDriver::Implementation
{
	using ActionQueue = biogears::ConcurrentQueue<std::unique_ptr<biogears::SEAction>>;
	using Channel = biogears::scmp::Channel<ActionQueue>;
	using Source = biogears::scmp::Source<ActionQueue>;

	Implementation();
	Implementation(FString dir, FString name);


	UE4BioGearsLogger logger;
	UE4BioGearsEngine engine;
	Channel _action_queue;

	std::atomic_bool  engine_running;
	std::atomic_bool  in_action_cycle;
	std::atomic_bool  engine_paused;
	std::atomic_bool  engine_throttled;

	std::thread engineThread;
	std::mutex  engineMutex;

	void engine_thread_main();
	void engine_thread_step();
};
//-------------------------------------------------------------------------------
UE4BioGearsEngineDriver::Implementation::Implementation()
	: Implementation("./", "UE4EngineName")
{

}
//-------------------------------------------------------------------------------
UE4BioGearsEngineDriver::Implementation::Implementation(FString dir, FString name)
	: logger(dir,name)
    , engine(dir, logger)
	, engine_running(false)
	, in_action_cycle(false)
	, engine_paused(false)
	, engine_throttled(true)
{

}
//-------------------------------------------------------------------------------
void UE4BioGearsEngineDriver::Implementation::engine_thread_main()
{
	using namespace std::chrono_literals;
	using namespace biogears;

	auto current_time = std::chrono::steady_clock::now();
	std::chrono::time_point<std::chrono::steady_clock> prev;

	engine_running = true;
	while (engine_running) {
		prev = current_time;
		current_time = std::chrono::steady_clock::now();
		engine.advance_time(60s);
		if (engine_throttled) {
			while ((current_time - prev) < 60s) {
				std::this_thread::sleep_for(16ms);
				current_time = std::chrono::steady_clock::now();
			}
		}
	}
}
//-------------------------------------------------------------------------------
inline void UE4BioGearsEngineDriver::Implementation::engine_thread_step()
{
	using namespace std::chrono_literals;
	if (!engine_paused) {
		if (_action_queue.size()) {
			if (!engine.process_action(std::move(_action_queue.consume())))
			{
				//TODO: Handle Action Error
			}
		}
		engine.advance_time(60s);
	}
	else {
		std::this_thread::sleep_for(16ms);
	}
}
//-------------------------------------------------------------------------------
UE4BioGearsEngineDriver::UE4BioGearsEngineDriver()
	:UE4BioGearsEngineDriver(TEXT("./"), TEXT("UE4BioGearsEngine"))
{

}
UE4BioGearsEngineDriver::UE4BioGearsEngineDriver(FString name)
	: _pimpl(MakeUnique<Implementation>(TEXT("./"), name))
{

}
//-------------------------------------------------------------------------------
UE4BioGearsEngineDriver::UE4BioGearsEngineDriver(FString working_dir, FString name)
	: _pimpl(MakeUnique<Implementation>(working_dir, name))
{

}
//-------------------------------------------------------------------------------
UE4BioGearsEngineDriver::UE4BioGearsEngineDriver(UE4BioGearsEngineDriver&& obj)
	: _pimpl(std::move(obj._pimpl))
{

}
//-------------------------------------------------------------------------------
UE4BioGearsEngineDriver::~UE4BioGearsEngineDriver()
{
	_pimpl = nullptr;
}
//-------------------------------------------------------------------------------
UE4BioGearsEngineDriver& UE4BioGearsEngineDriver::operator=(UE4BioGearsEngineDriver&& rhs)
{
	this->_pimpl = std::move(rhs._pimpl);
	rhs._pimpl = TUniquePtr<Implementation>();
	return *this;
}
bool UE4BioGearsEngineDriver::load_patient_state(FString stateFile)
{
	return _pimpl->engine.load_patient_state(stateFile);
}
bool UE4BioGearsEngineDriver::load_patient(FString patientFile)
{
	return _pimpl->engine.load_patient(patientFile);
}
//-------------------------------------------------------------------------------
void UE4BioGearsEngineDriver::start()
{
	_pimpl->engine_running = true;

	using namespace biogears;
	using namespace std::chrono_literals;

	if (!_pimpl->engineThread.joinable()) {
		_pimpl->engine_running.store(true);
		_pimpl->engineThread = std::thread{ [&]() {
			auto start_time = std::chrono::steady_clock::now();
			_pimpl->in_action_cycle.store(true);
			UE_LOG(BioGearsLog, Display, TEXT("BioGears Thread Starting"));
			_pimpl->engine.action_apply_hemorrhage(eExtremity::LeftLeg, 5.);
			_pimpl->engine.action_apply_tourniquet(eExtremity::LeftLeg, eTourniquet::Applied);
			_pimpl->engine.advance_time(60s);
			auto duration = std::chrono::steady_clock::now() - start_time;
			UE_LOG(BioGearsLog, Display, TEXT("BioGears Thread has run for %lld"), std::chrono::duration_cast<std::chrono::seconds>(duration).count());
			_pimpl->engine.action_apply_hemorrhage(eExtremity::LeftLeg, 5.);
			_pimpl->engine.action_apply_tourniquet(eExtremity::LeftLeg, eTourniquet::Misapplied);
			_pimpl->engine.advance_time(60s);
			duration = std::chrono::steady_clock::now() - start_time;
			UE_LOG(LogTemp, Display, TEXT("BioGears Thread has run for %lld"), std::chrono::duration_cast<std::chrono::seconds>(duration).count());
			_pimpl->engine.action_apply_tourniquet(eExtremity::LeftLeg, eTourniquet::Applied);
			_pimpl->engine.advance_time(60s); start_time = std::chrono::steady_clock::now();			_pimpl->engine.action_apply_tourniquet(eExtremity::LeftLeg, eTourniquet::None);
			_pimpl->engine.advance_time(60s);
			duration = std::chrono::steady_clock::now() - start_time;
			UE_LOG(BioGearsLog, Display, TEXT("BioGears Thread has run for %lld"), std::chrono::duration_cast<std::chrono::seconds>(duration).count());
			_pimpl->engine.action_tension_pneumothorax(eSide::Left, ePneumothorax::Open, 0.5);
			_pimpl->engine.advance_time(60s);
			duration = std::chrono::steady_clock::now() - start_time;
			UE_LOG(BioGearsLog, Display, TEXT("BioGears Thread has run for %lld"), std::chrono::duration_cast<std::chrono::seconds>(duration).count());
			_pimpl->engine.action_needle_decompression(eSide::Left, true);
			_pimpl->engine.advance_time(60s);
			duration = std::chrono::steady_clock::now() - start_time;
			UE_LOG(BioGearsLog, Display, TEXT("BioGears Thread has run for %lld"), std::chrono::duration_cast<std::chrono::seconds>(duration).count());
			_pimpl->engine.action_o2_mask(.5, 3., 0.);
			_pimpl->engine.advance_time(60s);
			duration = std::chrono::steady_clock::now() - start_time;
			UE_LOG(BioGearsLog, Display, TEXT("BioGears Thread has run for %lld"), std::chrono::duration_cast<std::chrono::seconds>(duration).count());
			_pimpl->engine.action_infection(eInfectionSeverity::Mild, "Liver", 0.2);
			_pimpl->engine.advance_time(60s);
			duration = std::chrono::steady_clock::now() - start_time;
			UE_LOG(BioGearsLog, Display, TEXT("BioGears Thread has run for %lld"), std::chrono::duration_cast<std::chrono::seconds>(duration).count());
			_pimpl->engine.action_bloodtransfuction(eBloodType::O_Negitive, 500, 10);
			_pimpl->engine.advance_time(60s);
			duration = std::chrono::steady_clock::now() - start_time;
			UE_LOG(BioGearsLog, Display, TEXT("BioGears Thread has run for %lld"), std::chrono::duration_cast<std::chrono::seconds>(duration).count());
			_pimpl->engine.action_thermal_blanket(500, 0.5);
			_pimpl->engine.advance_time(60s);
			duration = std::chrono::steady_clock::now() - start_time;
			UE_LOG(BioGearsLog, Display, TEXT("BioGears Thread has run for %lld"), std::chrono::duration_cast<std::chrono::seconds>(duration).count());
			_pimpl->engine.action_pain_stimulus(eCompartment::LeftArm, 0.3);
			_pimpl->engine.advance_time(60s);
			duration = std::chrono::steady_clock::now() - start_time;
			UE_LOG(BioGearsLog, Display, TEXT("BioGears Thread has run for %lld"), std::chrono::duration_cast<std::chrono::seconds>(duration).count());
			biogears::eUrineColor eColor;
			_pimpl->engine.get_urine_color(eColor);
			FString urineColor;
			switch (eColor)
			{
			  case eUrineColor::PaleYellow:	urineColor = TEXT("PaleYellow");  break;
			  case eUrineColor::DarkYellow: urineColor = TEXT("DarkYellow");  break;
			  case eUrineColor::Pink:		urineColor = TEXT("Pink");    break;
			  case eUrineColor::Yellow:	    urineColor = TEXT("Yellow");  break;
			}
			UE_LOG(BioGearsLog, Display, TEXT("BioGears Patient has %s UrineColor"), *urineColor);
			_pimpl->engine.advance_time(60s);
			duration = std::chrono::steady_clock::now() - start_time;
			UE_LOG(BioGearsLog, Display, TEXT("BioGears Thread has run for %lld"), std::chrono::duration_cast<std::chrono::seconds>(duration).count());
			_pimpl->engine.action_urinate();
			_pimpl->engine.advance_time(60s);
			duration = std::chrono::steady_clock::now() - start_time;
			UE_LOG(BioGearsLog, Display, TEXT("BioGears Thread has run for %lld"), std::chrono::duration_cast<std::chrono::seconds>(duration).count());
			_pimpl->in_action_cycle.store(false);
		} };
	}
}

void UE4BioGearsEngineDriver::pause_resume(bool state)
{
	_pimpl->engine_paused = state;
}
//-------------------------------------------------------------------------------
void UE4BioGearsEngineDriver::stop()
{
	_pimpl->engine_running = false;
	_pimpl->engine_throttled = false;
	_pimpl->engine_paused = true;
}
//-------------------------------------------------------------------------------
void UE4BioGearsEngineDriver::join()
{
	if (_pimpl->engineThread.joinable())
	{
		_pimpl->engineThread.join();
	}
}
//-------------------------------------------------------------------------------
bool UE4BioGearsEngineDriver::isReady()
{
	return _pimpl->engine.isReady();
}
//-------------------------------------------------------------------------------
void UE4BioGearsEngineDriver::throttle(bool state)
{
	_pimpl->engine_throttled = state;
}
//-------------------------------------------------------------------------------
std::chrono::seconds UE4BioGearsEngineDriver::getSimulationTime()
{
	return _pimpl->engine.getSimulationTime();
}
//-------------------------------------------------------------------------------
biogears::BiogearsMetrics    UE4BioGearsEngineDriver::getMetrics()
{
	return _pimpl->engine.getMetrics();
}
//-------------------------------------------------------------------------------
biogears::BiogearsConditions UE4BioGearsEngineDriver::getConditions()
{
	return _pimpl->engine.getConditions();
}
//-------------------------------------------------------------------------------
biogears::BiogearsState      UE4BioGearsEngineDriver::getState()
{
	return _pimpl->engine.getState();
}