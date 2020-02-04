#include "UE4BioGearsEngine.h"

#include <thread>
#include <memory>

#include <biogears/engine/BioGearsPhysiologyEngine.h>
#include <biogears/engine/controller/BioGears.h>
struct UE4BioGearsEngine::Implementation
{
	std::unique_ptr<biogears::PhysiologyEngine> bg;
};
//-------------------------------------------------------------------------------
UE4BioGearsEngine::UE4BioGearsEngine()
	:_pimpl(MakeUnique<Implementation>())
{

}
//-------------------------------------------------------------------------------
UE4BioGearsEngine::UE4BioGearsEngine(UE4BioGearsEngine&& obj)
	: _pimpl(std::move(obj._pimpl))
{

}
//-------------------------------------------------------------------------------
UE4BioGearsEngine::~UE4BioGearsEngine()
{
	_pimpl = nullptr;
}
//-------------------------------------------------------------------------------
UE4BioGearsEngine& UE4BioGearsEngine::operator=(UE4BioGearsEngine&& rhs)
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
BiogearsMetrics    UE4BioGearsEngine::getMetrics()
{
	return {};
}
//-------------------------------------------------------------------------------
BiogearsConditions UE4BioGearsEngine::getConditions()
{
	return {};
}
//-------------------------------------------------------------------------------
BiogearsState      UE4BioGearsEngine::getState()
{
	return {};
}
//-------------------------------------------------------------------------------
void UE4BioGearsEngine::advance_time(std::chrono::seconds seconds)
{
	_pimpl->bg->AdvanceModelTime(seconds.count(), biogears::TimeUnit::s);
}
//-------------------------------------------------------------------------------
bool UE4BioGearsEngine::process_action(std::unique_ptr<biogears::SEAction> action)
{
	auto result = _pimpl->bg->ProcessAction(*action);
	action.reset();
	return result;
}

bool UE4BioGearsEngine::isReady()
{
	return false;
}
//-------------------------------------------------------------------------------