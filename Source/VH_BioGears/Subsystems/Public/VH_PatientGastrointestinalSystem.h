#pragma once

#include "VH_PatientSubsystem.h"

#if  defined(WITH_BIOGEARS_BINDING) // TODO: Remove when biogears works on android
// BioGears
#include "VH_BioGearsPreHeaderBlock.inl"
#include <biogears/engine/Controller/BioGearsEngine.h>
#include <biogears/schema/biogears/BioGears.hxx>
#include "VH_BioGearsPostHeaderBlock.inl"
#endif

// Generated
#include "VH_PatientGastrointestinalSystem.generated.h"

/*
 * Information about the contents of the patient's stomach
 * 
 * The organs that handle the intake, digestion, and disposal of food.
 * Food taken orally is digested in the stomach and nutrients are extracted
 * The remaining waste is expelled
 */
UCLASS(Blueprintable)
class VH_BIOGEARS_API UVH_PatientGastrointestinalSystem : public UVH_PatientSubsystem
{
	GENERATED_BODY()


	// ---------------------------------
	// --- Constructors
	// ---------------------------------

public:
	UVH_PatientGastrointestinalSystem(const FObjectInitializer& objectInitializer);

	virtual ~UVH_PatientGastrointestinalSystem();


	// ---------------------------------
	// --- Variables
	// ---------------------------------

protected:
	/***/
	UPROPERTY()
	float ChymeAbsorptionRate;

	/***/
	UPROPERTY()
	float StomachContents_Calcium;

	/***/
	UPROPERTY()
	float StomachContents_Carbohydrates;

	/***/
	UPROPERTY()
	float StomachContents_Fat;

	/***/
	UPROPERTY()
	float StomachContents_Protein;

	/***/
	UPROPERTY()
	float StomachContents_Sodium;

	/***/
	UPROPERTY()
	float StomachContents_Water;

private:
	FCriticalSection CriticalSection;


	// ---------------------------------
	// --- API
	// ---------------------------------

public:
	virtual void InitializeGastrointestinal();

#if  defined(WITH_BIOGEARS_BINDING) // TODO: Remove when biogears works on android
	virtual void UpdateValues(const biogears::SEGastrointestinalSystem* gastrointestinal);
#endif

	UFUNCTION(BlueprintCallable)
	virtual float GetChymeAbsorptionRate();
	
	UFUNCTION(BlueprintCallable)
	virtual float GetStomachContents_Calcium();
	
	UFUNCTION(BlueprintCallable)
	virtual float GetStomachContents_Carbohydrates();
	
	UFUNCTION(BlueprintCallable)
	virtual float GetStomachContents_Fat();
	
	UFUNCTION(BlueprintCallable)
	virtual float GetStomachContents_Protein();
	
	UFUNCTION(BlueprintCallable)
	virtual float GetStomachContents_Sodium();
	
	UFUNCTION(BlueprintCallable)
	virtual float GetStomachContents_Water();
};
