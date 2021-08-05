#pragma once

#if  defined(WITH_BIOGEARS_BINDING) // TODO: Remove when biogears works on android
// BioGears
#include "VH_BioGearsPreHeaderBlock.inl"
#include <biogears/cdm/system/equipment/Anesthesia/SEAnesthesiaMachine.h>
#include <biogears/engine/Controller/BioGearsEngine.h>
#include <biogears/schema/biogears/BioGears.hxx>
#include "VH_BioGearsPostHeaderBlock.inl"
#endif

// VH BioGears Plugin
#include "VH_BioGearsEnums.h"

// Generated
#include "VH_AnesthesiaMachine.generated.h"

/*
 * Simulated Two-bottle oxygen tank anesthesia machine connected to patient
 * Provides access to state of the oxygen bottles
 *
 */
UCLASS(Blueprintable)
class VH_BIOGEARS_API UVH_AnesthesiaMachine : public UObject
{
	GENERATED_BODY()


	// ---------------------------------
	// --- Constructors
	// ---------------------------------

public:
	UVH_AnesthesiaMachine(const FObjectInitializer& objectInitializer);

	virtual ~UVH_AnesthesiaMachine();


	// ---------------------------------
	// --- Variables
	// ---------------------------------

protected:
	UPROPERTY()
	bool bConnected;

	UPROPERTY()
	float InletFlow;

	UPROPERTY()
	float InspiratoryExpiratoryRatio;

	UPROPERTY()
	float OxygenBottleOneVolume;

	UPROPERTY()
	float OxygenBottleTwoVolume;

	UPROPERTY()
	float OxygenFraction;

	UPROPERTY()
	EAnesthesia PrimaryGas;

	UPROPERTY()
	float ReliefValvePressure;

	UPROPERTY()
	float RespiratoryRate;

	UPROPERTY()
	float VentilatorPressure;

private:
	FCriticalSection CriticalSection;


	// ---------------------------------
	// --- API
	// ---------------------------------

public:
	void InitializeAnesthesia();

#if  defined(WITH_BIOGEARS_BINDING) // TODO: Remove when biogears works on android
	void UpdateValues(const biogears::SEAnesthesiaMachine* anesthesia);
#endif

	UFUNCTION(BlueprintCallable)
	bool GetConnected();
	
	UFUNCTION(BlueprintCallable)
	float GetInletFlow();
	
	UFUNCTION(BlueprintCallable)
	float GetInspiratoryExpiratoryRatio();
	
	UFUNCTION(BlueprintCallable)
	float GetOxygenBottleOneVolume();
	
	UFUNCTION(BlueprintCallable)
	float GetOxygenBottleTwoVolume();
	
	UFUNCTION(BlueprintCallable)
	float GetOxygenFraction();
	
	UFUNCTION(BlueprintCallable)
	EAnesthesia GetPrimaryGas();
	
	UFUNCTION(BlueprintCallable)
	float GetReliefValvePressure();
	
	UFUNCTION(BlueprintCallable)
	float GetRespiratoryRate();
	
	UFUNCTION(BlueprintCallable)
	float GetVentilatorPressure();
};
