#pragma once

// Engine
#include "Templates/SubclassOf.h"

#if  defined(WITH_BIOGEARS_BINDING) // TODO: Remove when biogears works on android
// BioGears
#include "VH_BioGearsPreHeaderBlock.inl"
#include "biogears/engine/Controller/BioGearsEngine.h"
#include "biogears/schema/biogears/BioGears.hxx"
#include "VH_BioGearsPostHeaderBlock.inl"
#endif

// VH BioGears Plugin
#include "VH_PatientActions.h"
#include "VH_PatientBloodChemistry.h"
#include "VH_PatientCardiovascularSystem.h"
#include "VH_PatientConditions.h"
#include "VH_PatientDrugSystem.h"
#include "VH_PatientEndocrineSystem.h"
#include "VH_PatientEnergy.h"
#include "VH_PatientEvents.h"
#include "VH_PatientGastrointestinalSystem.h"
#include "VH_PatientHepaticSystem.h"
#include "VH_PatientInfo.h"
#include "VH_PatientMetabolicPanel.h"
#include "VH_PatientNervousSystem.h"
#include "VH_PatientRenalSystem.h"
#include "VH_PatientRespiratorySystem.h"
#include "VH_PatientTissue.h"

// Generated
#include "VH_PatientBody.generated.h"

/*
 * Access point to subsystems & conditions of patient's body
 *
 */
UCLASS(Blueprintable)
class VH_BIOGEARS_API UVH_PatientBody : public UObject
{
	GENERATED_BODY()


	// ---------------------------------
	// --- Constructors
	// ---------------------------------

public:
	UVH_PatientBody(const FObjectInitializer& objectInitializer);

	virtual ~UVH_PatientBody();


	// ---------------------------------
	// --- Variables
	// ---------------------------------

protected:
	UPROPERTY(EditDefaultsOnly)
	TSubclassOf<UVH_PatientActions> ActionsClass;

	UPROPERTY(EditDefaultsOnly)
	TSubclassOf<UVH_PatientBloodChemistry> BloodChemistryClass;

	UPROPERTY(EditDefaultsOnly)
	TSubclassOf<UVH_PatientCardiovascularSystem> CardiovascularSystemClass;

	UPROPERTY(EditDefaultsOnly)
	TSubclassOf<UVH_PatientConditions> ConditionsClass;

	UPROPERTY(EditDefaultsOnly)
	TSubclassOf<UVH_PatientDrugSystem> DrugSystemClass;

	UPROPERTY(EditDefaultsOnly)
	TSubclassOf<UVH_PatientEndocrineSystem> EndocrineSystemClass;

	UPROPERTY(EditDefaultsOnly)
	TSubclassOf<UVH_PatientEnergy> EnergyClass;

	UPROPERTY(EditDefaultsOnly)
	TSubclassOf<UVH_PatientEvents> EventsClass;

	UPROPERTY(EditDefaultsOnly)
	TSubclassOf<UVH_PatientGastrointestinalSystem> GastrointestinalSystemClass;

	UPROPERTY(EditDefaultsOnly)
	TSubclassOf<UVH_PatientHepaticSystem> HepaticSystemClass;

	UPROPERTY(EditDefaultsOnly)
	TSubclassOf<UVH_PatientMetabolicPanel> MetabolicPanelClass;

	UPROPERTY(EditDefaultsOnly)
	TSubclassOf<UVH_PatientNervousSystem> NervousSystemClass;

	UPROPERTY(EditDefaultsOnly)
	TSubclassOf<UVH_PatientInfo> PatientInfoClass;

	UPROPERTY(EditDefaultsOnly)
	TSubclassOf<UVH_PatientRenalSystem> RenalSystemClass;

	UPROPERTY(EditDefaultsOnly)
	TSubclassOf<UVH_PatientRespiratorySystem> RespiratorySystemClass;

	UPROPERTY(EditDefaultsOnly)
	TSubclassOf<UVH_PatientTissue> TissueClass;

	// --------------- Subsystems --------------- //

	UPROPERTY()
	UVH_PatientActions* Actions;

	UPROPERTY()
	UVH_PatientBloodChemistry* BloodChemistry;
	
	UPROPERTY()
	UVH_PatientCardiovascularSystem* CardiovascularSystem;

	UPROPERTY()
	UVH_PatientConditions* Conditions;

	UPROPERTY()
	UVH_PatientDrugSystem* DrugSystem;
	
	UPROPERTY()
	UVH_PatientEndocrineSystem* EndocrineSystem;
	
	UPROPERTY()
	UVH_PatientEnergy* Energy;

	UPROPERTY()
	UVH_PatientEvents* Events;
	
	UPROPERTY()
	UVH_PatientGastrointestinalSystem* GastrointestinalSystem;
	
	UPROPERTY()
	UVH_PatientHepaticSystem* HepaticSystem;

	UPROPERTY()
	UVH_PatientMetabolicPanel* MetabolicPanel;
	
	UPROPERTY()
	UVH_PatientNervousSystem* NervousSystem;

	UPROPERTY()
	UVH_PatientInfo* PatientInfo;
	
	UPROPERTY()
	UVH_PatientRenalSystem* RenalSystem;
	
	UPROPERTY()
	UVH_PatientRespiratorySystem* RespiratorySystem;
	
	UPROPERTY()
	UVH_PatientTissue* Tissue;

private:
	FCriticalSection CriticalSection;


	// ---------------------------------
	// --- API
	// ---------------------------------

public:
	virtual void InitializePatientBody();

#if  defined(WITH_BIOGEARS_BINDING) // TODO: Remove when biogears works on android
	virtual void UpdateValues(biogears::BioGearsEngine* engine);
#endif

	// --------------- Subsystems --------------- //

	UFUNCTION(BlueprintCallable)
	UVH_PatientActions* GetActions() const { return Actions; }

	UFUNCTION(BlueprintCallable)
	UVH_PatientBloodChemistry* GetBloodChemistry() const { return BloodChemistry; }

	UFUNCTION(BlueprintCallable)
	UVH_PatientCardiovascularSystem* GetCardiovascularSystem() const { return CardiovascularSystem; }

	UFUNCTION(BlueprintCallable)
	UVH_PatientConditions* GetPatientConditions() const { return Conditions; }

	UFUNCTION(BlueprintCallable)
	UVH_PatientDrugSystem* GetDrugSystem() const { return DrugSystem; }

	UFUNCTION(BlueprintCallable)
	UVH_PatientEndocrineSystem* GetEndocrineSystem() const { return EndocrineSystem; }

	UFUNCTION(BlueprintCallable)
	UVH_PatientEnergy* GetEnergy() const { return Energy; }

	UFUNCTION(BlueprintCallable)
	UVH_PatientEvents* GetEvents() const { return Events; }

	UFUNCTION(BlueprintCallable)
	UVH_PatientGastrointestinalSystem* GetGastrointestinalSystem() const { return GastrointestinalSystem; }

	UFUNCTION(BlueprintCallable)
	UVH_PatientHepaticSystem* GetHepaticSystem() const { return HepaticSystem; }

	UFUNCTION(BlueprintCallable)
	UVH_PatientMetabolicPanel* GetMetabolicPanel() const { return MetabolicPanel; }

	UFUNCTION(BlueprintCallable)
	UVH_PatientNervousSystem* GetNervousSystem() const { return NervousSystem; }

	UFUNCTION(BlueprintCallable)
	UVH_PatientInfo* GetPatientInfo() const { return PatientInfo; }

	UFUNCTION(BlueprintCallable)
	UVH_PatientRenalSystem* GetRenalSystem() const { return RenalSystem; }

	UFUNCTION(BlueprintCallable)
	UVH_PatientRespiratorySystem* GetRespiratorySystem() const { return RespiratorySystem; }

	UFUNCTION(BlueprintCallable)
	UVH_PatientTissue* GetTissue() const { return Tissue; }


	// ---------------------------------
	// --- Implementation
	// ---------------------------------

private:
#if  defined(WITH_BIOGEARS_BINDING) // TODO: Remove when biogears works on android
	void UpdateActions(biogears::SEPatientActionCollection& actions);
	void UpdateBloodChemistry(const biogears::SEBloodChemistrySystem* blood);
	void UpdateCardiovascularSystem(const biogears::SECardiovascularSystem* cardiovascular);
	void UpdateConditions(const biogears::SEConditionManager& conditions);
	void UpdateDrugSystem(const biogears::SEDrugSystem* drugs);
	void UpdateEndocrineSystem(const biogears::SEEndocrineSystem* endocrine);
	void UpdateEnergy(const biogears::SEEnergySystem* energy);
	void UpdateEvents(const std::map<CDM::enumPatientEvent::value, bool> events);
	void UpdateGastrointestinalSystem(const biogears::SEGastrointestinalSystem* gastrointestinal);
	void UpdateHepaticSystem(const biogears::SEHepaticSystem* hepatic);
	void UpdateInfo(const biogears::SEPatient& patient);
	void UpdateMetabolicPanel();
	void UpdateNervousSystem(const biogears::SENervousSystem* nervous);
	void UpdateRenalSystem(const biogears::SERenalSystem* renal);
	void UpdateRespiratorySystem(const biogears::SERespiratorySystem* respiratory);
	void UpdateTissue(const biogears::SETissueSystem* tissue);
#endif
};
