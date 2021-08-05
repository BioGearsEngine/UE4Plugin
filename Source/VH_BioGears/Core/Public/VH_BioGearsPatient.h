#pragma once

#include "VH_BioGearsEngine.h"
#include "VH_BioGearsPhysiology.h"

// Generated
#include "VH_BioGearsPatient.generated.h"


/**
 * The entry class for the plugin.
 * Contains all the information necessary to manage a patient.
 * Creates & Manages access to public Engine Data and Patient Physiology
 *
 */
UCLASS(Blueprintable)
class VH_BIOGEARS_API UVH_BioGearsPatient : public UObject
{
	GENERATED_BODY()


	// ---------------------------------
	// --- Constructors
	// ---------------------------------

public:
	UVH_BioGearsPatient(const FObjectInitializer& objectInitializer);

	virtual ~UVH_BioGearsPatient();


	// ---------------------------------
	// --- Variables
	// ---------------------------------

protected:
	UPROPERTY(EditDefaultsOnly)
	TSubclassOf<UVH_BioGearsEngine> EngineClass;

	UPROPERTY(EditDefaultsOnly)
	TSubclassOf<UVH_BioGearsLogger> LoggerClass;

	UPROPERTY(EditDefaultsOnly)
	TSubclassOf<UVH_BioGearsPhysiology> PhysiologyClass;


	/** Threaded Wrapper For BioGears Engine */
	UPROPERTY()
	UVH_BioGearsEngine* Engine;

	/** Forward Logger */
	UPROPERTY()
	UVH_BioGearsLogger* Logger;

	/** Patient Physiology */
	UPROPERTY()
	UVH_BioGearsPhysiology* Physiology;


	// ---------------------------------
	// --- Static Functions
	// ---------------------------------

public:
	/** Creates & Returns a Patient Initalized With the Given Patient File */
	static UVH_BioGearsPatient* CreatePatient(TSubclassOf<UVH_BioGearsPatient> patientClass, const FString& patientFile);
	
	/** Creates & Returns a Patient Initalized With the Given Patient State File */
	static UVH_BioGearsPatient* CreatePatientByState(TSubclassOf<UVH_BioGearsPatient> patientClass, const FString& stateFile);


	// ---------------------------------
	// --- API
	// ---------------------------------

public:
	virtual void InitializePatient();


	UFUNCTION(BlueprintCallable)
	UVH_BioGearsEngine* GetEngine() const { return Engine; }

	UFUNCTION(BlueprintCallable)
	UVH_BioGearsPhysiology* GetPhysiology() const { return Physiology; }

	UFUNCTION(BlueprintCallable)
	UVH_BioGearsLogger* GetForwardLogger() const { return Logger; }
};
