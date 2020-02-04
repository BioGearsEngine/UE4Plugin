#include "UE4BioGearsEngineDriver.h"
#include "UE4BioGearsEngine.h"

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
	
	TUniquePtr<UE4BioGearsEngine> engine;
	Channel _action_queue;
	
	std::atomic_bool  engine_running;
	std::atomic_bool  engine_paused;
	std::atomic_bool  engine_throttled;
	
	std::thread engineThread;
	std::mutex  engineMutex;

	void engine_thread_main();
	void engine_thread_step();
};
//-------------------------------------------------------------------------------
void UE4BioGearsEngineDriver::Implementation::engine_thread_main()
{
	using namespace std::chrono_literals;

	auto current_time = std::chrono::steady_clock::now();
	std::chrono::time_point<std::chrono::steady_clock> prev;
	while (engine_running) {
		prev = current_time;
		engine_thread_step();
		current_time = std::chrono::steady_clock::now();
		if (engine_throttled) {
			while ((current_time - prev) < 1s) {
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
			if( !engine->process_action( std::move(_action_queue.consume())))
			{
				//TODO: Handle Action Error
			}
		}
		engine->advance_time(1s);
	}
	else {
		std::this_thread::sleep_for(16ms);
	}
}
//-------------------------------------------------------------------------------
UE4BioGearsEngineDriver::UE4BioGearsEngineDriver()
	:_pimpl(MakeUnique<Implementation>())
{
	
}
//-------------------------------------------------------------------------------
UE4BioGearsEngineDriver::UE4BioGearsEngineDriver(UE4BioGearsEngineDriver&& obj)
	:_pimpl(std::move(obj._pimpl))
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
//-------------------------------------------------------------------------------
void UE4BioGearsEngineDriver::start()
{
	_pimpl->engine_running = true;
}

void UE4BioGearsEngineDriver::pause_resume(bool state)
{
	_pimpl->engine_paused = state;
}
//-------------------------------------------------------------------------------
void UE4BioGearsEngineDriver::stop()
{

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
	return _pimpl->engine->isReady();
}
//-------------------------------------------------------------------------------
void UE4BioGearsEngineDriver::throttle(bool state)
{
	_pimpl->engine_throttled = state;
}
//-------------------------------------------------------------------------------
std::chrono::seconds UE4BioGearsEngineDriver::getSimulationTime()
{
	return _pimpl->engine->getSimulationTime();
}
//-------------------------------------------------------------------------------
BiogearsMetrics    UE4BioGearsEngineDriver::getMetrics()
{
	return _pimpl->engine->getMetrics();
}
//-------------------------------------------------------------------------------
BiogearsConditions UE4BioGearsEngineDriver::getConditions()
{
	return _pimpl->engine->getConditions();
}
//-------------------------------------------------------------------------------
BiogearsState      UE4BioGearsEngineDriver::getState()
{
	return _pimpl->engine->getState();
}