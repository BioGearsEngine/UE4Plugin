#pragma once

// Engine
#include "UObject/Object.h"

#if  defined(WITH_BIOGEARS_BINDING) // TODO: Remove when biogears works on android
// BioGears
#include "VH_BioGearsPreHeaderBlock.inl"
#include "biogears/engine/Controller/BioGearsEngine.h"
#include "biogears/schema/biogears/BioGears.hxx"
#include "VH_BioGearsPostHeaderBlock.inl"
#endif

// Generated
#include "VH_PatientPupillaryResponse.generated.h"

/*
 * Information about the patient's pupillary response to stimuli
 *
 * Physiological response to a variety of different stimuli that varies the size of the pupil
 */
UCLASS(Blueprintable)
class VH_BIOGEARS_API UVH_PatientPupillaryResponse : public UObject
{
	GENERATED_BODY()


	// ---------------------------------
	// --- Constructors
	// ---------------------------------

public:
	UVH_PatientPupillaryResponse(const FObjectInitializer& objectInitializer);

	virtual ~UVH_PatientPupillaryResponse();


	// ---------------------------------
	// --- Variables
	// ---------------------------------

protected:
	UPROPERTY()
	float ReactivityModifier;
	
	UPROPERTY()
	float ShapeModifier;
	
	UPROPERTY()
	float SizeModifier;

private:
	FCriticalSection CriticalSection;


	// ---------------------------------
	// --- API
	// ---------------------------------

public:
	virtual void InitializePupillaryResponse();

#if  defined(WITH_BIOGEARS_BINDING) // TODO: Remove when biogears works on android
	virtual void UpdateValues(const biogears::SEPupillaryResponse* response);
#endif

	UFUNCTION(BlueprintCallable)
	virtual float GetReactivityModifier();
	
	UFUNCTION(BlueprintCallable)
	virtual float GetShapeModifier();
	
	UFUNCTION(BlueprintCallable)
	virtual float GetSizeModifier();

};
