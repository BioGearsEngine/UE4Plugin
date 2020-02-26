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
DECLARE_DYNAMIC_MULTICAST_DELEGATE_OneParam(FOnStateUpdated, FBioGearsState, patient_state);
DECLARE_DYNAMIC_MULTICAST_DELEGATE_OneParam(FOnMetricsUpdated, FBioGearsMetrics, patient_metrics);
DECLARE_DYNAMIC_MULTICAST_DELEGATE_OneParam(FOnConditionsUpdated, FBioGearsConditions, patient_conditions);
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
		void action_env_change(FBioGearsEnvironmentalConditions conditons);
	UFUNCTION(BlueprintCallable, Category = "Physiology|Action", meta = (DisplayName = "BioGears::Action::Tourniquet"))
		void action_apply_tourniquet(EBioGearsExtremity limb, EBioGearsTourniquet application);
	UFUNCTION(BlueprintCallable, Category = "Physiology|Action", meta = (DisplayName = "BioGears::Action::Hemorrhage"))
		void action_apply_hemorrhage(EBioGearsExtremity limb, float flowrate_ml_Per_min);
	UFUNCTION(BlueprintCallable, Category = "Physiology|Action", meta = (DisplayName = "BioGears::Action::TensionPneumothorax"))
		void action_tension_pneumothorax(EBioGearsSide side, EBioGearsPneumothorax type, float severity_0_to_1);
	UFUNCTION(BlueprintCallable, Category = "Physiology|Action", meta = (DisplayName = "BioGears::Action::NeedleD"))
		void action_needle_decompression(EBioGearsSide side, bool active);
	UFUNCTION(BlueprintCallable, Category = "Physiology|Action", meta = (DisplayName = "BioGears::Action::O2Mask"))
		void action_o2_mask(float o2_fraction, float o2_volume1, float o2_volume2);
	UFUNCTION(BlueprintCallable, Category = "Physiology|Action", meta = (DisplayName = "BioGears::Action::Infection"))
		void action_infection(EBioGearsInfectionSeverity severity, FString location, float mic_mg_Per_l);
	UFUNCTION(BlueprintCallable, Category = "Physiology|Action", meta = (DisplayName = "BioGears::Action::BloodTransfusion"))
		void action_bloodtransfusion(EBioGearsBloodType type, float blood_volume_ml, float flowrate_ml_Per_min);
	UFUNCTION(BlueprintCallable, Category = "Physiology|Action", meta = (DisplayName = "BioGears::Action::SubstanceInfusion"))
		void action_substanceInfusion(EBioGearsIvSubstance substance, float substance_volume_ml, float flowrate_ml_Per_min);
	UFUNCTION(BlueprintCallable, Category = "Physiology|Action", meta = (DisplayName = "BioGears::Action::SubstanceCompoundInfusion"))
		void action_substanceCompoundInfusion(EBioGearsIvCompound compound, float compound_volume_ml, float flowrate_ml_Per_min);
	UFUNCTION(BlueprintCallable, Category = "Physiology|Action", meta = (DisplayName = "BioGears::Action::oralSubstanceAdministration"))
		void action_oralSubstanceAdministration(EBioGearsOralSubstance type, EBioGearsOralAbsorption route, float dosage_mg);
	UFUNCTION(BlueprintCallable, Category = "Physiology|Action", meta = (DisplayName = "BioGears::Action::ThermalBlanket"))
		void action_thermal_blanket(float watt, float surface_area_fraction);
	UFUNCTION(BlueprintCallable, Category = "Physiology|Action", meta = (DisplayName = "BioGears::Action::PainStimulus"))
		void action_pain_stimulus(EBioGearsCompartment compartment, float severity);

	//TODO: I want to play with the concept of managing environments for quick change
    //TODO: If this works I would like to do it with patients, substances and such
	UFUNCTION(BlueprintCallable, Category = "Physiology|Panel", meta = (DisplayName = "BioGears::Creation::CreateEnvironment"))
		bool new_environment(FString key, FBioGearsEnvironmentalConditions conditions);
	UFUNCTION(BlueprintCallable, Category = "Physiology|Panel", meta = (DisplayName = "BioGears::Action::SetEnvironment"))
		bool set_environment(FString key);

	//TODO: Add Custom Substances to the engine while running (You should never change an existing compound and we will make sure of that)
	UFUNCTION(BlueprintCallable, Category = "Physiology|Panel", meta = (DisplayName = "BioGears::Creation::CreateCustomCompound"))
		bool new_custom_compound(FString key, FBioGearsCompound compound);
	UFUNCTION(BlueprintCallable, Category = "Physiology|Panel", meta = (DisplayName = "BioGears::Action::CustomCompoundInfusion"))
		bool custom_compound_infusion(FString key, float substance_volume_ml, float flowrate_ml_Per_min);

	UFUNCTION(BlueprintCallable, Category = "Physiology|Panel", meta = (DisplayName = "BioGears::Panel::UrineAnalyis"))
		void get_urine_analysis();
	UFUNCTION(BlueprintCallable, Category = "Physiology|Panel", meta = (DisplayName = "BioGears::Panel::ComprehensiveMetabolicPanel"))
		void get_comprehensive_metabolic_panel();
	UFUNCTION(BlueprintCallable, Category = "Physiology|Panel", meta = (DisplayName = "BioGears::Panel::CompleteBloodCount"))
		void get_complete_blood_count();
	UFUNCTION(BlueprintCallable, Category = "Physiology|Panel", meta = (DisplayName = "BioGears::Panel::PulmonaryFunctionTest"))
		void get_pulmonary_function_test();


//Data Request Functions
	float getSimulationTime();

	UPROPERTY(BlueprintReadOnly, Category = "Data")
		FBioGearsState patient_state;
	UPROPERTY(BlueprintReadOnly, Category = "Data")
		FBioGearsMetrics patient_metrics;
	UPROPERTY(BlueprintReadOnly, Category = "Data")
		FBioGearsConditions patient_conditions;

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

	UPROPERTY(BlueprintAssignable, Category = "Events")
		FOnUrineAnalysisComplete on_urine_analysis_completed;
	UPROPERTY(BlueprintAssignable, Category = "Events")
		FOnMetabolicPanelComplete on_metabolic_panel_completed;
	UPROPERTY(BlueprintAssignable, Category = "Events")
		FOnBloodCountComplete on_blood_count_completed;
	UPROPERTY(BlueprintAssignable, Category = "Events")
		FOnPulmonaryTextComplete on_pulmonary_test_completed;

	UFUNCTION()
	void broadcast_urine_analysis_completed(FBioGearsUrineAnalysis analysis);
	UFUNCTION()
	void broadcast_metabolic_panel_completed(FBioGearsMetabolicPanel analysis);
	UFUNCTION()
	void broadcast_blood_count_completed(FBioGearsBloodCount analysis);
	UFUNCTION()
	void broadcast_pulmonary_test_completed(FBioGearsPulmonaryTest analysis);
	
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

	UPROPERTY()
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
