#pragma once

#include "VH_PatientSubsystem.h"

#if  defined(WITH_BIOGEARS_BINDING) // TODO: Remove when biogears works on android
// BioGears
#include "VH_BioGearsPreHeaderBlock.inl"
#include "biogears/engine/Controller/BioGearsEngine.h"
#include "biogears/schema/biogears/BioGears.hxx"
#include "VH_BioGearsPostHeaderBlock.inl"
#endif

// Generated
#include "VH_PatientEvents.generated.h"

/*
 * Active state of patient events
 * State is true if its currently active
 *
 */
UCLASS(Blueprintable)
class VH_BIOGEARS_API UVH_PatientEvents : public UVH_PatientSubsystem
{
	GENERATED_BODY()


	// ---------------------------------
	// --- Constructors
	// ---------------------------------

public:
	UVH_PatientEvents(const FObjectInitializer& objectInitializer);

	~UVH_PatientEvents();


	// ---------------------------------
	// --- Variables
	// ---------------------------------

protected:
	UPROPERTY()
	bool bAcuteLungInjury;

	UPROPERTY()
	bool bAcuteRespiratoryDistress;

	UPROPERTY()
	bool bAntidiuresis;

	UPROPERTY()
	bool bAsystole;

	UPROPERTY()
	bool bBradycardia;

	UPROPERTY()
	bool bBradypnea;

	UPROPERTY()
	bool bBrainOxygenDeficit;

	UPROPERTY()
	bool bCardiacArrest;

	UPROPERTY()
	bool bCardiogenicShock;

	UPROPERTY()
	bool bCriticalBrainOxygenDeficit;

	UPROPERTY()
	bool bDehydration;

	UPROPERTY()
	bool bDiuresis;

	UPROPERTY()
	bool bFasciculation;

	UPROPERTY()
	bool bFatigue;

	UPROPERTY()
	bool bFunctionalIncontinence;

	UPROPERTY()
	bool bHemolyticTransfusionReaction;

	UPROPERTY()
	bool bHypercapnia;

	UPROPERTY()
	bool bHyperglycemia;

	UPROPERTY()
	bool bMildHyperkalemia;

	UPROPERTY()
	bool bSevereHyperkalemia;

	UPROPERTY()
	bool bMildHypernatremia;

	UPROPERTY()
	bool bSevereHypernatremia;

	UPROPERTY()
	bool bHyperthermia;

	UPROPERTY()
	bool bHypoglycemia;

	UPROPERTY()
	bool bHypoglycemicShock;

	UPROPERTY()
	bool bHypoglycemicComa;

	UPROPERTY()
	bool bHypothermia;

	UPROPERTY()
	bool bMildHypokalemia;

	UPROPERTY()
	bool bSevereHypokalemia;

	UPROPERTY()
	bool bMildHyponatremia;

	UPROPERTY()
	bool bSevereHyponatremia;

	UPROPERTY()
	bool bHypoxia;

	UPROPERTY()
	bool bHypovolemicShock;

	UPROPERTY()
	bool bIntracranialHypertension;

	UPROPERTY()
	bool bIntracranialHypotension;

	UPROPERTY()
	bool bIrreversibleState;

	UPROPERTY()
	bool bKetoacidosis;

	UPROPERTY()
	bool bLacticAcidosis;

	UPROPERTY()
	bool bLiverGlycogenDepleted;

	UPROPERTY()
	bool bMaximumPulmonaryVentilationRate;

	UPROPERTY()
	bool bMetabolicAcidosis;

	UPROPERTY()
	bool bMetabolicAlkalosis;

	UPROPERTY()
	bool bMuscleCatabolism;

	UPROPERTY()
	bool bMuscleGlycogenDepleted;

	UPROPERTY()
	bool bMyocardiumOxygenDeficit;

	UPROPERTY()
	bool bNatriuresis;

	UPROPERTY()
	bool bNutritionDepleted;

	UPROPERTY()
	bool bPulselessRhythm;

	UPROPERTY()
	bool bRenalHypoperfusion;

	UPROPERTY()
	bool bRespiratoryAcidosis;

	UPROPERTY()
	bool bRespiratoryAlkalosis;

	UPROPERTY()
	bool bSevereAcuteRespiratoryDistress;

	UPROPERTY()
	bool bStartOfCardiacCycle;

	UPROPERTY()
	bool bStartOfExhale;

	UPROPERTY()
	bool bStartOfInhale;

	UPROPERTY()
	bool bSevereSepsis;

	UPROPERTY()
	bool bTachycardia;

	UPROPERTY()
	bool bTachypnea;

private:
	FCriticalSection CriticalSection;


	// ---------------------------------
	// --- API
	// ---------------------------------

public:
	virtual void InitializeEvents();

#if  defined(WITH_BIOGEARS_BINDING) // TODO: Remove when biogears works on android
	virtual void UpdateValues(const std::map<CDM::enumPatientEvent::value, bool> events);
#endif

	UFUNCTION(BlueprintCallable)
	virtual bool HasAcuteLungInjury();

	UFUNCTION(BlueprintCallable)
	virtual bool HasAcuteRespiratoryDistress();

	UFUNCTION(BlueprintCallable)
	virtual bool HasAntidiuresis();

	UFUNCTION(BlueprintCallable)
	virtual bool HasAsystole();

	UFUNCTION(BlueprintCallable)
	virtual bool HasBradycardia();

	UFUNCTION(BlueprintCallable)
	virtual bool HasBradypnea();

	UFUNCTION(BlueprintCallable)
	virtual bool HasBrainOxygenDeficit();

	UFUNCTION(BlueprintCallable)
	virtual bool HasCardiacArrest();

	UFUNCTION(BlueprintCallable)
	virtual bool HasCardiogenicShock();

	UFUNCTION(BlueprintCallable)
	virtual bool HasCriticalBrainOxygenDeficit();

	UFUNCTION(BlueprintCallable)
	virtual bool HasDehydration();

	UFUNCTION(BlueprintCallable)
	virtual bool HasDiuresis();

	UFUNCTION(BlueprintCallable)
	virtual bool HasFasciculation();

	UFUNCTION(BlueprintCallable)
	virtual bool HasFatigue();

	UFUNCTION(BlueprintCallable)
	virtual bool HasFunctionalIncontinence();

	UFUNCTION(BlueprintCallable)
	virtual bool HasHemolyticTransfusionReaction();

	UFUNCTION(BlueprintCallable)
	virtual bool HasHypercapnia();

	UFUNCTION(BlueprintCallable)
	virtual bool HasHyperglycemia();

	UFUNCTION(BlueprintCallable)
	virtual bool HasMildHyperkalemia();

	UFUNCTION(BlueprintCallable)
	virtual bool HasSevereHyperkalemia();

	UFUNCTION(BlueprintCallable)
	virtual bool HasMildHypernatremia();

	UFUNCTION(BlueprintCallable)
	virtual bool HasSevereHypernatremia();

	UFUNCTION(BlueprintCallable)
	virtual bool HasHyperthermia();

	UFUNCTION(BlueprintCallable)
	virtual bool HasHypoglycemia();

	UFUNCTION(BlueprintCallable)
	virtual bool HasHypoglycemicShock();

	UFUNCTION(BlueprintCallable)
	virtual bool HasHypoglycemicComa();

	UFUNCTION(BlueprintCallable)
	virtual bool HasHypothermia();

	UFUNCTION(BlueprintCallable)
	virtual bool HasMildHypokalemia();

	UFUNCTION(BlueprintCallable)
	virtual bool HasSevereHypokalemia();

	UFUNCTION(BlueprintCallable)
	virtual bool HasMildHyponatremia();

	UFUNCTION(BlueprintCallable)
	virtual bool HasSevereHyponatremia();

	UFUNCTION(BlueprintCallable)
	virtual bool HasHypoxia();

	UFUNCTION(BlueprintCallable)
	virtual bool HasHypovolemicShock();

	UFUNCTION(BlueprintCallable)
	virtual bool HasIntracranialHypertension();

	UFUNCTION(BlueprintCallable)
	virtual bool HasIntracranialHypotension();

	UFUNCTION(BlueprintCallable)
	virtual bool HasIrreversibleState();

	UFUNCTION(BlueprintCallable)
	virtual bool HasKetoacidosis();

	UFUNCTION(BlueprintCallable)
	virtual bool HasLacticAcidosis();

	UFUNCTION(BlueprintCallable)
	virtual bool HasLiverGlycogenDepleted();

	UFUNCTION(BlueprintCallable)
	virtual bool HasMaximumPulmonaryVentilationRate();

	UFUNCTION(BlueprintCallable)
	virtual bool HasMetabolicAcidosis();

	UFUNCTION(BlueprintCallable)
	virtual bool HasMetabolicAlkalosis();

	UFUNCTION(BlueprintCallable)
	virtual bool HasMuscleCatabolism();

	UFUNCTION(BlueprintCallable)
	virtual bool HasMuscleGlycogenDepleted();

	UFUNCTION(BlueprintCallable)
	virtual bool HasMyocardiumOxygenDeficit();

	UFUNCTION(BlueprintCallable)
	virtual bool HasNatriuresis();

	UFUNCTION(BlueprintCallable)
	virtual bool HasNutritionDepleted();

	UFUNCTION(BlueprintCallable)
	virtual bool HasPulselessRhythm();

	UFUNCTION(BlueprintCallable)
	virtual bool HasRenalHypoperfusion();

	UFUNCTION(BlueprintCallable)
	virtual bool HasRespiratoryAcidosis();

	UFUNCTION(BlueprintCallable)
	virtual bool HasRespiratoryAlkalosis();

	UFUNCTION(BlueprintCallable)
	virtual bool HasSevereAcuteRespiratoryDistress();

	UFUNCTION(BlueprintCallable)
	virtual bool HasStartOfCardiacCycle();

	UFUNCTION(BlueprintCallable)
	virtual bool HasStartOfExhale();

	UFUNCTION(BlueprintCallable)
	virtual bool HasStartOfInhale();

	UFUNCTION(BlueprintCallable)
	virtual bool HasSevereSepsis();

	UFUNCTION(BlueprintCallable)
	virtual bool HasTachycardia();

	UFUNCTION(BlueprintCallable)
	virtual bool HasTachypnea();
};
