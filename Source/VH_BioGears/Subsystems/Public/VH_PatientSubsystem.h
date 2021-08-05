#pragma once

// Engine
#include "UObject/Object.h"

// Generated
#include "VH_PatientSubsystem.generated.h"

/*
 * Generic base class for a patient's body subsystem
 *
 */
UCLASS(Blueprintable)
class VH_BIOGEARS_API UVH_PatientSubsystem : public UObject
{
	GENERATED_BODY()


	// ---------------------------------
	// --- Constructors
	// ---------------------------------

public:
	UVH_PatientSubsystem(const FObjectInitializer& objectInitializer);

	virtual ~UVH_PatientSubsystem();


	// ---------------------------------
	// --- Variables
	// ---------------------------------


	// ---------------------------------
	// --- API
	// ---------------------------------

public:

};