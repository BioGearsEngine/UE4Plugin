#pragma once

#include "VH_PatientSubsystem.h"

#if  defined(WITH_BIOGEARS_BINDING) // TODO: Remove when biogears works on android
// BioGears
#include "VH_BioGearsPreHeaderBlock.inl"
#include "biogears/cdm/system/physiology/SEEnergySystem.h"
#include "biogears/engine/Controller/BioGearsEngine.h"
#include "biogears/schema/biogears/BioGears.hxx"
#include "VH_BioGearsPostHeaderBlock.inl"
#endif

// Generated
#include "VH_PatientEnergy.generated.h"

/*
 * Information about the patient's Energy levels, sweat, and fatigue
 *
 */
UCLASS(Blueprintable)
class VH_BIOGEARS_API UVH_PatientEnergy : public UVH_PatientSubsystem
{
	GENERATED_BODY()


	// ---------------------------------
	// --- Constructors
	// ---------------------------------

public:
	UVH_PatientEnergy(const FObjectInitializer& objectInitializer);

	virtual ~UVH_PatientEnergy();


	// ---------------------------------
	// --- Variables
	// ---------------------------------

protected:
	// --------------- Level --------------- //

	/** */
	UPROPERTY()
	float AchievedExerciseLevel;

	/** */
	UPROPERTY()
	float FatigueLevel;

	/** */
	UPROPERTY()
	float TotalWorkRateLevel;

	// --------------- Other --------------- //

	/** */
	UPROPERTY()
	float ExerciseMeanArterialPressureDelta;

	// --------------- Production Rate --------------- //

	/** */
	UPROPERTY()
	float CreatinineProductionRate;

	/** */
	UPROPERTY()
	float TotalMetabolicRate;

	/** */
	UPROPERTY()
	float LactateProductionRate;

	// --------------- Sweat --------------- //

	/** */
	UPROPERTY()
	float SweatRate;

	/** */
	UPROPERTY()
	float ChlorideLostToSweat;

	/** */
	UPROPERTY()
	float PotassiumLostToSweat;

	/** */
	UPROPERTY()
	float SodiumLostToSweat;

	// --------------- Temperature --------------- //

	/** */
	UPROPERTY()
	float CoreTemperature;

	/**  */
	UPROPERTY()
	float SkinTemperature;

private:
	FCriticalSection CriticalSection;


	// ---------------------------------
	// --- API
	// ---------------------------------

public:
	virtual void InitializeEnergy();

#if  defined(WITH_BIOGEARS_BINDING) // TODO: Remove when biogears works on android
	virtual void UpdateValues(const biogears::SEEnergySystem* energy);
#endif

	// --------------- Level --------------- //

	UFUNCTION(BlueprintCallable)
	virtual float GetAchievedExerciseLevel();
		
	UFUNCTION(BlueprintCallable)
	virtual float GetFatigueLevel();
	
	UFUNCTION(BlueprintCallable)
	virtual float GetTotalWorkRateLevel();
	
	// --------------- Production Rate --------------- //

	UFUNCTION(BlueprintCallable)
	virtual float GetCreatinineProductionRate();
	
	UFUNCTION(BlueprintCallable)
	virtual float GetLactateProductionRate();
	
	UFUNCTION(BlueprintCallable)
	virtual float GetTotalMetabolicRate();
	
	// --------------- Sweat --------------- //

	UFUNCTION(BlueprintCallable)
	virtual float GetSweatRate();
	
	UFUNCTION(BlueprintCallable)
	virtual float GetChlorideLostToSweat();
	
	UFUNCTION(BlueprintCallable)
	virtual float GetPotassiumLostToSweat();
	
	UFUNCTION(BlueprintCallable)
	virtual float GetSodiumLostToSweat();
	
	// --------------- Temperature --------------- //

	UFUNCTION(BlueprintCallable)
	virtual float GetCoreTemperature();
	
	UFUNCTION(BlueprintCallable)
	virtual float GetSkinTemperature();
	
	// --------------- Other --------------- //

	UFUNCTION(BlueprintCallable)
	virtual float GetExerciseMeanArterialPressureDelta();
};
