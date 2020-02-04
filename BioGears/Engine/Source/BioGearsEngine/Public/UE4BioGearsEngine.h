#pragma once

#include <memory>
#include <chrono>

#include <UObject/Object.h>
#include <Templates/UniquePtr.h>

#include <biogears/cdm/scenario/SEAction.h>

struct BiogearsMetrics
{
	
};

struct BiogearsState
{
	bool living;
};

struct BiogearsConditions
{
	
};

class UE4BioGearsEngine: public UObject {
public:
	UE4BioGearsEngine();
	UE4BioGearsEngine(UE4BioGearsEngine&) = default;
	UE4BioGearsEngine(UE4BioGearsEngine&&);
	~UE4BioGearsEngine();

	UE4BioGearsEngine& operator=(const UE4BioGearsEngine&) = delete;
	UE4BioGearsEngine& operator=(UE4BioGearsEngine&&);

	std::chrono::seconds getSimulationTime();
	BiogearsMetrics    getMetrics();
	BiogearsConditions getConditions();
	BiogearsState      getState();

	void advance_time(std::chrono::seconds seconds);
	bool process_action(std::unique_ptr<biogears::SEAction>);
	bool isReady();

private:
    struct Implementation;
    TUniquePtr<Implementation> _pimpl;
};
