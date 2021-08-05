#pragma once

#include "VH_PatientBody.h"
#include "VH_EnvironmentConditions.h"
#include "VH_AnesthesiaMachine.h"

// Generated
#include "VH_BioGearsPhysiology.generated.h"

/*
 * Manages access to individual components of patient's physiology (Anesthesia Machine, Environment, & Body)
 * 
 */
UCLASS(Blueprintable)
class VH_BIOGEARS_API UVH_BioGearsPhysiology : public UObject
{
	GENERATED_BODY()


	// ---------------------------------
	// --- Constructors
	// ---------------------------------

public:
	UVH_BioGearsPhysiology(const FObjectInitializer& objectInitializer);

	virtual ~UVH_BioGearsPhysiology();


	// ---------------------------------
	// --- Variables
	// ---------------------------------

protected:
	UPROPERTY(BlueprintReadOnly)
	UVH_AnesthesiaMachine* Anesthesia;

	UPROPERTY(BlueprintReadOnly)
	UVH_EnvironmentConditions* Environment;

	UPROPERTY(BlueprintReadOnly)
	UVH_PatientBody* PatientBody;


	// ---------------------------------
	// --- API
	// ---------------------------------

public:				    
	void InitializePhysiology();

#if  defined(WITH_BIOGEARS_BINDING) // TODO: Remove when biogears works on android
	void UpdateValues(biogears::BioGearsEngine* engine);
#endif

	UVH_AnesthesiaMachine* GetAnesthesiaMachine() const { return Anesthesia; }
	UVH_EnvironmentConditions* GetEnvironmentConditions() const { return Environment; }
	UVH_PatientBody* GetPatientBody() const { return PatientBody; }
};
