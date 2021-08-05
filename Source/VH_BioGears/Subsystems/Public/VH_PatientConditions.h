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
#include "VH_PatientConditions.generated.h"

/*
 * Information about the medical conditions of the patient
 * These conditons are determined by the patient's initial file and do not change at runtime
 */
UCLASS(Blueprintable)
class VH_BIOGEARS_API UVH_PatientConditions : public UVH_PatientSubsystem
{
	GENERATED_BODY()


	// ---------------------------------
	// --- Constructors
	// ---------------------------------

public:
	UVH_PatientConditions(const FObjectInitializer& objectInitializer);

	virtual ~UVH_PatientConditions();


	// ---------------------------------
	// --- Variables
	// ---------------------------------

protected:
	UPROPERTY()
	bool ChronicAnemia;
	
	UPROPERTY()
	bool ChronicObstructivePulmonaryDisease;
	
	UPROPERTY()
	bool ChronicPericardialEffusion;
	
	UPROPERTY()
	bool ChronicRenalStenosis;
	
	UPROPERTY()
	bool ChronicVentricularSystolicDysfunction;
	
	UPROPERTY()
	bool DiabetesType1;
	
	UPROPERTY()
	bool DiabetesType2;
	
	UPROPERTY()
	bool ImpairedAlveolarExchange;
	
	UPROPERTY()
	bool LobarPneumonia;

private:
	FCriticalSection CriticalSection;


	// ---------------------------------
	// --- API
	// ---------------------------------

public:
	virtual void InitializeConditions();

#if  defined(WITH_BIOGEARS_BINDING) // TODO: Remove when biogears works on android
	virtual void UpdateValues(const biogears::SEConditionManager& conditions);
#endif

	UFUNCTION(BlueprintCallable)
	virtual bool HasChronicAnemia();

	UFUNCTION(BlueprintCallable)
	virtual bool HasChronicObstructivePulmonaryDisease();

	UFUNCTION(BlueprintCallable)
	virtual bool HasChronicPericardialEffusion();

	UFUNCTION(BlueprintCallable)
	virtual bool HasChronicRenalStenosis();

	UFUNCTION(BlueprintCallable)
	virtual bool HasChronicVentricularSystolicDysfunction();

	UFUNCTION(BlueprintCallable)
	virtual bool HasDiabetesType1();

	UFUNCTION(BlueprintCallable)
	virtual bool HasDiabetesType2();

	UFUNCTION(BlueprintCallable)
	virtual bool HasImpairedAlveolarExchange();

	UFUNCTION(BlueprintCallable)
	virtual bool HasLobarPneumonia();
};
