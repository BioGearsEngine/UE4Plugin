#pragma once

#include "VH_PatientSubsystem.h"

#if  defined(WITH_BIOGEARS_BINDING) // TODO: Remove when biogears works on android
// BioGears
#include "VH_BioGearsPreHeaderBlock.inl"
#include "biogears/engine/Controller/BioGearsEngine.h"
#include "biogears/schema/biogears/BioGears.hxx"
#include "VH_BioGearsPostHeaderBlock.inl"
#endif

// VH BioGears Plugin
#include "VH_BioGearsEnums.h"
#include "VH_BioGearsStructs.h"

// Generated
#include "VH_PatientActions.generated.h"


/*
 * Information about state of patient conditions/statuses and performed actions
 *
 */
UCLASS(Blueprintable)
class VH_BIOGEARS_API UVH_PatientActions : public UVH_PatientSubsystem
{
	GENERATED_BODY()


	// ---------------------------------
	// --- Constructors
	// ---------------------------------

public:
	UVH_PatientActions(const FObjectInitializer& objectInitializer);

	virtual ~UVH_PatientActions();


	// ---------------------------------
	// --- Variables
	// ---------------------------------

protected:
	UPROPERTY()
	TArray<FBioGearsCompound> ActiveCompoundInfusions;

	UPROPERTY()
	TArray<FBioGearsSubstance> ActiveSubstanceInfusions;


	UPROPERTY()
	bool bAcuteRespiratoryDistress;
	
	UPROPERTY()
	float AcuteRespiratoryDistressSeverity;


	UPROPERTY()
	bool bAcuteStress;
	
	UPROPERTY()
	float AcuteStressSeverity;


	UPROPERTY()
	bool bAirwayObstruction;
	
	UPROPERTY()
	float AirwayObstructionSeverity;


	UPROPERTY()
	bool bApnea;
	
	UPROPERTY()
	float ApneaSeverity;


	UPROPERTY()
	bool bAsthmaAttack;

	UPROPERTY()
	float AsthmaAttackSeverity;


	UPROPERTY()
	EBrainInjuryType BrainInjury;
	
	UPROPERTY()
	float BrainInjurySeverity;


	UPROPERTY()
	bool bBronchoconstriction;


	UPROPERTY()
	bool bBurnWound;
	
	UPROPERTY()
	float BurnWoundTotalBodySurfaceArea;
	
	UPROPERTY()
	bool bBurnWoundInflammation;


	UPROPERTY()
	bool bCardiacArrest;


	UPROPERTY()
	bool bChestCompression;
	
	UPROPERTY()
	float ChestCompressionForce;
	
	UPROPERTY()
	float ChestCompressionForceScale;

	UPROPERTY()
	float ChestCompressionForcePeriod;


	UPROPERTY()
	bool bChestOcclusiveDressingLeft;

	UPROPERTY()
	bool bChestOcclusiveDressingRight;


	UPROPERTY()
	bool bConsciousRespiration;

	UPROPERTY()
	bool bConsumeNutrients;

	UPROPERTY()
	bool bExercise;

	UPROPERTY()
	TMap<FString, FBioGearsHemorrhage> Hemorrhages;

	UPROPERTY()
	bool bInfection;

	UPROPERTY()
	bool bIntubation;

	UPROPERTY()
	bool bMechanicalVentilation;

	UPROPERTY()
	EPatientChestSide NeedleDecompression;

	UPROPERTY()
	TMap<FString, FBioGearsPainStimulus> PainStimuli;

	UPROPERTY()
	bool bPericardialEffusion;

	UPROPERTY()
	bool bSleepState;

	UPROPERTY()
	EPatientChestSide TensionPneumothorax;

	UPROPERTY()
	TMap<FString, ETourniquetLevel> Tourniquets;

	UPROPERTY()
	bool bUrinate;

private:
	FCriticalSection CriticalSection;


	// ---------------------------------
	// --- API
	// ---------------------------------

public:
	virtual void InitializeActions();

#if  defined(WITH_BIOGEARS_BINDING) // TODO: Remove when biogears works on android
	virtual void UpdateValues(biogears::SEPatientActionCollection& actions);
#endif

	UFUNCTION(BlueprintCallable)
	virtual TArray<FBioGearsCompound> GetActiveCompoundInfusions();

	UFUNCTION(BlueprintCallable)
	virtual TArray<FBioGearsSubstance> GetActiveSubstanceInfusions();


	UFUNCTION(BlueprintCallable)
	virtual bool HasAcuteRespiratoryDistress();
	
	UFUNCTION(BlueprintCallable)
	virtual float GetAcuteRespiratoryDistressSeverity();

	
	UFUNCTION(BlueprintCallable)
	virtual bool HasAcuteStress();
	
	UFUNCTION(BlueprintCallable)
	virtual float GetAcuteStressSeverity();


	UFUNCTION(BlueprintCallable)
	virtual bool HasAirwayObstruction();
	
	UFUNCTION(BlueprintCallable)
	virtual float GetAirwayObstructionSeverity();


	UFUNCTION(BlueprintCallable)
	virtual bool HasApnea();
	
	UFUNCTION(BlueprintCallable)
	virtual float GetApneaSeverity();


	UFUNCTION(BlueprintCallable)
	virtual bool HasAsthmaAttack();

	UFUNCTION(BlueprintCallable)
	virtual float GetAsthmaAttackSeverity();


	UFUNCTION(BlueprintCallable)
	virtual EBrainInjuryType GetBrainInjury();
	
	UFUNCTION(BlueprintCallable)
	virtual float GetBrainInjurySeverity();


	UFUNCTION(BlueprintCallable)
	virtual bool HasBronchoconstriction();


	UFUNCTION(BlueprintCallable)
	virtual bool HasBurnWound();
	
	UFUNCTION(BlueprintCallable)
	virtual float GetBurnWoundTotalBodySurfaceArea();
	
	UFUNCTION(BlueprintCallable)
	virtual bool HasBurnWoundInflammation();


	UFUNCTION(BlueprintCallable)
	virtual bool HasCardiacArrest();


	UFUNCTION(BlueprintCallable)
	virtual bool HasChestCompression();
	
	UFUNCTION(BlueprintCallable)
	virtual float GetChestCompressionForce();
	
	UFUNCTION(BlueprintCallable)
	virtual float GetChestCompressionForceScale();

	UFUNCTION(BlueprintCallable)
	virtual float GetChestCompressionForcePeriod();


	UFUNCTION(BlueprintCallable)
	virtual bool HasChestOcclusiveDressingLeft();
	
	UFUNCTION(BlueprintCallable)
	virtual bool HasChestOcclusiveDressingRight();


	UFUNCTION(BlueprintCallable)
	virtual bool HasConsciousRespiration();

	UFUNCTION(BlueprintCallable)
	virtual bool HasConsumeNutrients();

	UFUNCTION(BlueprintCallable)
	virtual bool HasExercise();

	UFUNCTION(BlueprintCallable)
	virtual const TMap<FString, FBioGearsHemorrhage> GetHemorrhages();

	UFUNCTION(BlueprintCallable)
	virtual bool HasInfection();

	UFUNCTION(BlueprintCallable)
	virtual bool HasIntubation();

	UFUNCTION(BlueprintCallable)
	virtual bool HasMechanicalVentilation();

	UFUNCTION(BlueprintCallable)
	virtual EPatientChestSide HasNeedleDecompression();

	UFUNCTION(BlueprintCallable)
	virtual const TMap<FString, FBioGearsPainStimulus> GetPainStimuli();
	
	UFUNCTION(BlueprintCallable)
	virtual bool HasPericardialEffusion();

	UFUNCTION(BlueprintCallable)
	virtual bool HasSleepState();

	UFUNCTION(BlueprintCallable)
	virtual EPatientChestSide GetTensionPneumothorax();

	UFUNCTION(BlueprintCallable)
	virtual const TMap<FString, ETourniquetLevel> GetTourniquets();

	UFUNCTION(BlueprintCallable)
	virtual bool HasToUrinate();


	// ---------------------------------
	// --- Implementation
	// ---------------------------------

private:
#if  defined(WITH_BIOGEARS_BINDING) // TODO: Remove when biogears works on android
	void UpdateCompoundInfusions(const biogears::MapWrapper<const biogears::SESubstanceCompound*, biogears::SESubstanceCompoundInfusion*>);
	void UpdateSubstanceInfusions(const biogears::MapWrapper<const biogears::SESubstance*, biogears::SESubstanceInfusion*>);
#endif
};
