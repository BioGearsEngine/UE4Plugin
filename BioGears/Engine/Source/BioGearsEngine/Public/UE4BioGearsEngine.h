#pragma once

#include <memory>
#include <chrono>

#include <Misc/Paths.h>
#include <UObject/Object.h>
#include <Templates/UniquePtr.h>

#include <biogears/cdm/scenario/SEAction.h>

#include "UE4BioGearsEnums.h"
#include "UE4BioGearsStructs.h"

class UE4BioGearsEngine {
public:
	UE4BioGearsEngine();
	explicit UE4BioGearsEngine(FString name);
	explicit UE4BioGearsEngine(FString dataRoot, FString name);
	
	UE4BioGearsEngine(UE4BioGearsEngine&) = default;
	UE4BioGearsEngine(UE4BioGearsEngine&&) noexcept;
	~UE4BioGearsEngine();

	UE4BioGearsEngine& operator=(const UE4BioGearsEngine&) = delete;
	UE4BioGearsEngine& operator=(UE4BioGearsEngine&&) noexcept;

	std::chrono::seconds getSimulationTime();
	biogears::BiogearsMetrics    getMetrics();
	biogears::BiogearsConditions getConditions();
	biogears::BiogearsState      getState();

	bool load_patient(FString patient);
	bool load_patient_state(FString state);
	
	void advance_time(std::chrono::seconds seconds);
	bool process_action(std::unique_ptr<biogears::SEAction>);
	bool isReady();

	bool action_urinate();
	bool action_env_change(biogears::sEnvironmentalConditions conditons);
	bool action_apply_tourniquet(biogears::eExtremity limb, biogears::eTourniquet application);
	bool action_apply_hemorrhage(biogears::eExtremity limb, double flowrate_ml_Per_min);
	bool action_tension_pneumothorax(biogears::eSide, biogears::ePneumothorax, double severity_0_to_1);
	bool action_needle_decompression(biogears::eSide side, bool active);
	bool action_o2_mask(double o2_fraction, double o2_volume1, double o2_volume2);
	bool action_infection(biogears::eInfectionSeverity severity, FString location, double mic_mg_Per_l);
	bool action_bloodtransfuction(biogears::eBloodType type, double blood_volume_ml, double flowrate_ml_Per_min);
	bool action_thermal_blanket(double watt, double surface_area_fraction);
	bool action_pain_stimulus(biogears::eCompartment compartment, double severity);

	//Query Actions
	bool get_urine_color(biogears::eUrineColor& result); //<! Side Effect result contains the color
	//TODO: I want to play with the concept of managing environments for quick change
	//TODO: If this works I would like to do it with patients, substances and such
	bool new_environment(FString key, double lots_of_paramaters);
	bool delete_environment(FString key);
	bool set_environment(FString key);
	
private:
    struct Implementation;
    TUniquePtr<Implementation> _pimpl;
};