#pragma once

#include <memory>
#include <chrono>

#include <Misc/Paths.h>
#include <UObject/Object.h>
#include <Templates/UniquePtr.h>

#include <biogears/cdm/scenario/SEAction.h>

#include "UBioGearsEnums.h"
#include "UBioGearsStructs.h"
#include "UBioGearsLogger.h"

class BIOGEARSENGINE_API UBioGearsEngine {
public:
	UBioGearsEngine();
	explicit UBioGearsEngine(FString name);
	explicit UBioGearsEngine(FString dataRoot, FString name);
	explicit UBioGearsEngine(FString dataRoot, UBioGearsLogger& logger);
	
	UBioGearsEngine(UBioGearsEngine&) = default;
	UBioGearsEngine(UBioGearsEngine&&) noexcept;
	~UBioGearsEngine();

	UBioGearsEngine& operator=(const UBioGearsEngine&) = delete;
	UBioGearsEngine& operator=(UBioGearsEngine&&) noexcept;

	std::chrono::seconds getSimulationTime();
	FBiogearsMetrics    getMetrics();
	FBiogearsConditions getConditions();
	FBiogearsState      getState();

	bool load_patient(FString patient);
	bool load_patient_state(FString state);
	
	void advance_time(std::chrono::seconds seconds);
	bool process_action(std::unique_ptr<biogears::SEAction>);
	bool isReady();

	bool action_urinate();
	bool action_env_change(FEnvironmentalConditions conditons);
	bool action_apply_tourniquet(EExtremity limb, ETourniquet application);
	bool action_apply_hemorrhage(EExtremity limb, double flowrate_ml_Per_min);
	bool action_tension_pneumothorax(ESide, EPneumothorax, double severity_0_to_1);
	bool action_needle_decompression(ESide side, bool active);
	bool action_o2_mask(double o2_fraction, double o2_volume1, double o2_volume2);
	bool action_infection(EInfectionSeverity severity, FString location, double mic_mg_Per_l);
	bool action_bloodtransfusion(EBloodType type, double blood_volume_ml, double flowrate_ml_Per_min);
	bool action_thermal_blanket(double watt, double surface_area_fraction);
	bool action_pain_stimulus(ECompartment compartment, double severity);
	bool action_substanceInfusion(EIvSubstance substance, double substance_volume_ml, double flowrate_ml_Per_min);
	bool action_substanceCompoundInfusion(EIvCompound compound, double compound_volume_ml, double flowrate_ml_Per_min);
	bool action_oralSubstanceAdministration(EOralSubstance type, EOralAbsorption, double dosage_mg);
	//Query Actions
	bool get_urine_color(EUrineColor& result); //<! Side Effect result contains the color
	//TODO: I want to play with the concept of managing environments for quick change
	//TODO: If this works I would like to do it with patients, substances and such
	bool new_environment(FString key, double lots_of_paramaters);
	bool delete_environment(FString key);
	bool set_environment(FString key);
	
private:
    struct Implementation;
    TUniquePtr<Implementation> _pimpl;
};