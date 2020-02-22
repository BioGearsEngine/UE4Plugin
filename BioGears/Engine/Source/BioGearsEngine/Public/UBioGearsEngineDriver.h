#pragma once

#include <UObject/Object.h>
#include <UObject/Class.h>
#include <Templates/UniquePtr.h>

#include <chrono>
#include <memory>
#include <atomic>

#include "UBioGearsStructs.h"
#include "UBioGearsEnums.h"
#include "UUE4BioGearsEngine.h"
#include <biogears/container/concurrent_queue.h>
#include <biogears/framework/scmp/scmp_channel.tci.h>
#include <biogears/container/concurrent_queue.tci.h>

#include "UBioGearsEngineDriver.generated.h"

DECLARE_DYNAMIC_MULTICAST_DELEGATE_OneParam(FOnTimeAdvance, float, time_in_simulation_s);
DECLARE_DYNAMIC_MULTICAST_DELEGATE_OneParam(FOnStateUpdated, FBiogearsState, patient_state);
DECLARE_DYNAMIC_MULTICAST_DELEGATE_OneParam(FOnMetricsUpdated, FBiogearsMetrics, patient_metrics);
DECLARE_DYNAMIC_MULTICAST_DELEGATE_OneParam(FOnConditionsUpdated, FBiogearsConditions, patient_conditions);
DECLARE_DYNAMIC_MULTICAST_DELEGATE_OneParam(FRunningToggled, bool, running);
DECLARE_DYNAMIC_MULTICAST_DELEGATE_OneParam(FPausedToggled, bool, paused);
DECLARE_DYNAMIC_MULTICAST_DELEGATE_OneParam(FThrottledToggled, bool, throttled);



UCLASS(BlueprintType, Config = "BioGears", meta = (DisplayName = "BioGearsThread"))
class  UBioGearsEngineDriver : public UObject {

	GENERATED_BODY()

public:
	UBioGearsEngineDriver(const FObjectInitializer& ObjectInitializer);
	~UBioGearsEngineDriver() override;

	UFUNCTION(BlueprintCallable, Category = "Physiology|Create", meta = (DisplayName = "BioGears::initialize_here"))
		void initialize_here(FString name, UObject* parent);
	UFUNCTION(BlueprintCallable, Category = "Physiology|Create", meta = (DisplayName = "BioGears::initialize"))
		void initialize(FString working_dir, FString name, UObject* parent);


	UFUNCTION(BlueprintCallable, Category = "Physiology|FileIO", meta = (DisplayName = "BioGears::LoadPatientState"))
		bool load_patient_state(FString stateName);
	UFUNCTION(BlueprintCallable, Category = "Physiology|FileIO", meta = (DisplayName = "BioGears::LoadPatient"))
		bool load_patient(FString pateintName);

	UFUNCTION(BlueprintCallable, Category = "Physiology|Control", meta = (DisplayName = "BioGears::Start"))
		void start();   //<! Start Simulation Thread
	UFUNCTION(BlueprintCallable, Category = "Physiology|Control", meta = (DisplayName = "BioGears::Stop"))
		void stop();    //<! Stop Simulation Thread (Shutdown)
	UFUNCTION(BlueprintCallable, Category = "Physiology|Control", meta = (DisplayName = "BioGears::Join"))
		void join();    //<! Block until thread is joined then return.
	UFUNCTION(BlueprintCallable, Category = "Physiology|Control", meta = (DisplayName = "BioGears::PauseToggle"))
		void pause_resume(bool doPause);   //<! If Running then stop advacing simulation time until unpaused

	UFUNCTION(BlueprintCallable, Category = "Physiology|Control", meta = (DisplayName = "BioGears::setRate"))
		void set_throttle(int rate);    //<! Block until thread is joined then return.

	UFUNCTION(BlueprintCallable, Category = "Physiology|Status", meta = (DisplayName = "BioGears::Isready"))
		bool isReady();
	UFUNCTION(BlueprintCallable, Category = "Physiology|Status", meta = (DisplayName = "BioGears::IsRunning"))
		bool running();
	UFUNCTION(BlueprintCallable, Category = "Physiology|Status", meta = (DisplayName = "BioGears::IsPaused"))
		bool paused();
	UFUNCTION(BlueprintCallable, Category = "Physiology|Status", meta = (DisplayName = "BioGears::IsThrottled"))
		bool throttled();


	UFUNCTION(BlueprintCallable, Category = "Physiology|Action", meta = (DisplayName = "BioGears::Action::Urinate"))
		void action_urinate();
	UFUNCTION(BlueprintCallable, Category = "Physiology|Action", meta = (DisplayName = "BioGears::Action::EnvChange"))
		void action_env_change(FEnvironmentalConditions conditons);
	UFUNCTION(BlueprintCallable, Category = "Physiology|Action", meta = (DisplayName = "BioGears::Action::Tourniquet"))
		void action_apply_tourniquet(EExtremity limb, ETourniquet application);
	UFUNCTION(BlueprintCallable, Category = "Physiology|Action", meta = (DisplayName = "BioGears::Action::Hemorrhage"))
		void action_apply_hemorrhage(EExtremity limb, float flowrate_ml_Per_min);
	UFUNCTION(BlueprintCallable, Category = "Physiology|Action", meta = (DisplayName = "BioGears::Action::TensionPneumothorax"))
		void action_tension_pneumothorax(ESide side, EPneumothorax type, float severity_0_to_1);
	UFUNCTION(BlueprintCallable, Category = "Physiology|Action", meta = (DisplayName = "BioGears::Action::NeedleD"))
		void action_needle_decompression(ESide side, bool active);
	UFUNCTION(BlueprintCallable, Category = "Physiology|Action", meta = (DisplayName = "BioGears::Action::O2Mask"))
		void action_o2_mask(float o2_fraction, float o2_volume1, float o2_volume2);
	UFUNCTION(BlueprintCallable, Category = "Physiology|Action", meta = (DisplayName = "BioGears::Action::Infection"))
		void action_infection(EInfectionSeverity severity, FString location, float mic_mg_Per_l);
	UFUNCTION(BlueprintCallable, Category = "Physiology|Action", meta = (DisplayName = "BioGears::Action::BloodTransfusion"))
		void action_bloodtransfusion(EBloodType type, float blood_volume_ml, float flowrate_ml_Per_min);
	UFUNCTION(BlueprintCallable, Category = "Physiology|Action", meta = (DisplayName = "BioGears::Action::SubstanceInfusion"))
		void action_substanceInfusion(EIvSubstance substance, float substance_volume_ml, float flowrate_ml_Per_min);
	UFUNCTION(BlueprintCallable, Category = "Physiology|Action", meta = (DisplayName = "BioGears::Action::SubstanceCompoundInfusion"))
		void action_substanceCompoundInfusion(EIvCompound compound, float compound_volume_ml, float flowrate_ml_Per_min);
	UFUNCTION(BlueprintCallable, Category = "Physiology|Action", meta = (DisplayName = "BioGears::Action::oralSubstanceAdministration"))
		void action_oralSubstanceAdministration(EOralSubstance type, EOralAbsorption route, float dosage_mg);
	UFUNCTION(BlueprintCallable, Category = "Physiology|Action", meta = (DisplayName = "BioGears::Action::ThermalBlanket"))
		void action_thermal_blanket(float watt, float surface_area_fraction);
	UFUNCTION(BlueprintCallable, Category = "Physiology|Action", meta = (DisplayName = "BioGears::Action::PainStimulus"))
		void action_pain_stimulus(ECompartment compartment, float severity);

	//UFUNCTION(BlueprintCallable, Category = "Physiology|Registery", meta = (DisplayName = "BioGears::ActionUrinate"))
	//	bool create_environment();
	//UFUNCTION(BlueprintCallable, Category = "Physiology|Registry", meta = (DisplayName = "BioGears::ActionUrinate"))
	//	bool destroy_environment();


//Data Request Functions
	float getSimulationTime();

	UPROPERTY(BlueprintReadOnly, Category = "Data")
		FBiogearsState patient_state;
	UPROPERTY(BlueprintReadOnly, Category = "Data")
		FBiogearsMetrics patient_metrics;
	UPROPERTY(BlueprintReadOnly, Category = "Data")
		FBiogearsConditions patient_conditions;

	UPROPERTY(BlueprintAssignable, Category = "Events")
		FOnTimeAdvance			 onTimeAdvance;
	UPROPERTY(BlueprintAssignable, Category = "Events")
		FOnStateUpdated			 onStateUpdated;
	UPROPERTY(BlueprintAssignable, Category = "Events")
		FOnMetricsUpdated		 onMetricsUpdated;
	UPROPERTY(BlueprintAssignable, Category = "Events")
		FOnConditionsUpdated	 onConditionsUpdated;
	UPROPERTY(BlueprintAssignable, Category = "Events")
		FRunningToggled			 runningToggled;
	UPROPERTY(BlueprintAssignable, Category = "Events")
		FPausedToggled			 pausedToggled;
	UPROPERTY(BlueprintAssignable, Category = "Events")
		FThrottledToggled		 throttledToggled;

	//Destructor Functions
	void BeginDestroy() override;
	bool IsReadyForFinishDestroy() override;
	void FinishDestroy() override;

private:
	//UBioGearsEngineDriver::UBioGearsEngineDriver(FString name, UClass* parent);
	//UBioGearsEngineDriver::UBioGearsEngineDriver(FString working_dir, FString name, UClass* parent);

	using ActionQueue = biogears::ConcurrentQueue<std::function<bool(void)>>;
	using Channel = biogears::scmp::Channel<ActionQueue>;
	using Source = biogears::scmp::Source<ActionQueue>;

	UUE4BioGearsEngine* _engine;

	Channel     _action_queue;
	TUniquePtr<Source>      _action_source;

	std::atomic_bool  _engine_thread_continue;
	std::atomic_bool  _engine_running;
	std::atomic_bool  _engine_paused;
	std::atomic_bool  _engine_throttled;

	std::thread _engineThread;

	void engine_thread_main();
	void engine_thread_step();


};
