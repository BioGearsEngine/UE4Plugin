#pragma once

// Engine
#include "Templates/SubclassOf.h"

// VH BioGears Plugin
#include "VH_PatientKidney.h" 
#include "VH_PatientSubsystem.h"
#include "VH_PatientUrinarySystem.h"

// Generated
#include "VH_PatientRenalSystem.generated.h"

/*
 * Information about the patient's Renal System & access to associated organs
 *
 * The organs include the kidneys, renal pelvis, ureters, bladder and urethra.
 * Helps filter, eliminate, and transport liquid waste (Urea) and keeps chemicals, such as potassium, sodium, and water in balance.
 */
UCLASS(Blueprintable)
class VH_BIOGEARS_API UVH_PatientRenalSystem : public UVH_PatientSubsystem
{
	GENERATED_BODY()


	// ---------------------------------
	// --- Constructors
	// ---------------------------------

public:
	UVH_PatientRenalSystem(const FObjectInitializer& objectInitializer);

	virtual ~UVH_PatientRenalSystem();


	// ---------------------------------
	// --- Variables
	// ---------------------------------

protected:
	UPROPERTY(EditDefaultsOnly)
	TSubclassOf<UVH_PatientKidney> KidneyClass;
	TSubclassOf<UVH_PatientUrinarySystem> UrinarySystemClass;

	/***/
	UPROPERTY()
	float FiltrationFraction;

	/***/
	UPROPERTY()
	float GlomerularFiltrationRate;

	/***/
	UPROPERTY()
	UVH_PatientKidney* LeftKidney;

	/***/
	UPROPERTY()
	float RenalBloodFlow;

	/***/
	UPROPERTY()
	float RenalPlasmaFlow;

	/***/
	UPROPERTY()
	float RenalVascularResistance;
	
	/***/
	UPROPERTY()
	UVH_PatientUrinarySystem* UrinarySystem;
	
	/***/
	UPROPERTY()
	UVH_PatientKidney* RightKidney;

private:
	FCriticalSection CriticalSection;


	// ---------------------------------
	// --- API
	// ---------------------------------

public:
	virtual void InitializeRenal();

#if  defined(WITH_BIOGEARS_BINDING) // TODO: Remove when biogears works on android
	virtual void UpdateValues(const biogears::SERenalSystem* renal);
#endif

	UFUNCTION(BlueprintCallable)
	virtual float GetFiltrationFraction();

	UFUNCTION(BlueprintCallable)
	virtual float GetGlomerularFiltrationRate();

	UFUNCTION(BlueprintCallable)
	UVH_PatientKidney* GetLeftKidney() const { return LeftKidney; }

	UFUNCTION(BlueprintCallable)
	virtual float GetRenalBloodFlow();
	
	UFUNCTION(BlueprintCallable)
	virtual float GetRenalPlasmaFlow();
	
	UFUNCTION(BlueprintCallable)
	virtual float GetRenalVascularResistance();

	UFUNCTION(BlueprintCallable)
	UVH_PatientKidney* GetRightKidney() const { return RightKidney;}
	
	UFUNCTION(BlueprintCallable)
	UVH_PatientUrinarySystem* GetUrinarySystem() const { return UrinarySystem; }
};
