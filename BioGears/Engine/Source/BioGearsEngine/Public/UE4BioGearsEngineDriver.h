#pragma once

#include <chrono>
#include <memory>

#include <UObject/Object.h>
#include <Templates/UniquePtr.h>

#include "UE4BioGearsEngine.h"
#include <biogears/container/concurrent_queue.h>

class UE4BioGearsEngineDriver {
public:
	UE4BioGearsEngineDriver();
	UE4BioGearsEngineDriver(FString name);
	UE4BioGearsEngineDriver(FString working_dir, FString name);
	
	UE4BioGearsEngineDriver(UE4BioGearsEngineDriver&) = default;
	UE4BioGearsEngineDriver(UE4BioGearsEngineDriver&&);
   ~UE4BioGearsEngineDriver();

   UE4BioGearsEngineDriver& operator=(const UE4BioGearsEngineDriver&) = delete;
   UE4BioGearsEngineDriver& operator=(UE4BioGearsEngineDriver&&);

   bool load_patient_state(FString);
   bool load_patient(FString);

   void start();   //<! Start Simulation Thread
   void pause_resume(bool);   //<! Sleep Thread
   void stop();    //<! Stop Simulation Thread (Shutdown)
   void join();    //<! Block until thread is joined then return.

   bool isReady();

   void throttle(bool state);

   std::chrono::seconds getSimulationTime();

	biogears::BiogearsMetrics    getMetrics();
	biogears::BiogearsConditions getConditions();
	biogears::BiogearsState      getState();

private:
    struct Implementation;
    TUniquePtr<Implementation> _pimpl;
};
