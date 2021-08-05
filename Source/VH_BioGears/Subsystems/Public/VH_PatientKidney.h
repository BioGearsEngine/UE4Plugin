#pragma once

#if  defined(WITH_BIOGEARS_BINDING) // TODO: Remove when biogears works on android
// BioGears
#include "VH_BioGearsPreHeaderBlock.inl"
#include "biogears/engine/Controller/BioGearsEngine.h"
#include "biogears/schema/biogears/BioGears.hxx"
#include "VH_BioGearsPostHeaderBlock.inl"
#endif

// Generated
#include "VH_PatientKidney.generated.h"

/*
 * Information about a patient's kidney
 * 
 * The kidneys are two bean-shaped organs located just below the rib cage, one on each side of your spine.
 * Kidneys remove wastes, extra fluid, and acid that is produced by the cells of your body.
 * Helps maintain a healthy balance of water, salts, and minerals in your blood.
 */
UCLASS(Blueprintable)
class VH_BIOGEARS_API UVH_PatientKidney : public UObject
{
	GENERATED_BODY()


	// ---------------------------------
	// --- Constructors
	// ---------------------------------

public:
	UVH_PatientKidney(const FObjectInitializer& objectInitializer);

	virtual ~UVH_PatientKidney();


	// ---------------------------------
	// --- Variables
	// ---------------------------------

protected:
	// --------------- Absorption --------------- //

	UPROPERTY()
	float FiltrationFraction;

	UPROPERTY()
	float ReabsorptionFiltrationCoefficient;

	UPROPERTY()
	float ReabsorptionRate;

	UPROPERTY()
	float TubularReabsorptionFiltrationSurfaceArea;

	UPROPERTY()
	float TubularReabsorptionFluidPermeability;

	// --------------- Arterial --------------- //

	UPROPERTY()
	float AfferentArterioleResistance;

	UPROPERTY()
	float EfferentArterioleResistance;

	// --------------- Glomerulus --------------- //

	UPROPERTY()
	float GlomerularCapillariesHydrostaticPressure;

	UPROPERTY()
	float GlomerularCapillariesOsmoticPressure;

	UPROPERTY()
	float GlomerularFiltrationCoefficient;

	UPROPERTY()
	float GlomerularFiltrationRate;

	UPROPERTY()
	float GlomerularFiltrationSurfaceArea;

	UPROPERTY()
	float GlomerularFluidPermeability;

	// --------------- Pressure --------------- //

	UPROPERTY()
	float BowmansCapsulesHydrostaticPressure;

	UPROPERTY()
	float BowmansCapsulesOsmoticPressure;

	UPROPERTY()
	float NetFiltrationPressure;

	UPROPERTY()
	float NetReabsorptionPressure;

	UPROPERTY()
	float PeritubularCapillariesHydrostaticPressure;

	UPROPERTY()
	float PeritubularCapillariesOsmoticPressure;

	UPROPERTY()
	float TubularHydrostaticPressure;

	UPROPERTY()
	float TubularOsmoticPressure;

private:
	FCriticalSection CriticalSection;


	// ---------------------------------
	// --- API
	// ---------------------------------

public:
	virtual void InitializeKidney();

#if  defined(WITH_BIOGEARS_BINDING) // TODO: Remove when biogears works on android
	virtual void UpdateValues(const biogears::SERenalSystem* renal, bool bLeft);
#endif

	// --------------- Absorption --------------- //
	
	UFUNCTION(BlueprintCallable)
	virtual float GetFiltrationFraction();

	UFUNCTION(BlueprintCallable)
	virtual float GetReabsorptionFiltrationCoefficient();

	UFUNCTION(BlueprintCallable)
	virtual float GetReabsorptionRate();

	UFUNCTION(BlueprintCallable)
	virtual float GetTubularReabsorptionFiltrationSurfaceArea();

	UFUNCTION(BlueprintCallable)
	virtual float GetTubularReabsorptionFluidPermeability();

	// --------------- Arterial --------------- //

	UFUNCTION(BlueprintCallable)
	virtual float GetAfferentArterioleResistance();

	UFUNCTION(BlueprintCallable)
	virtual float GetEfferentArterioleResistance();

	// --------------- Glomerulus --------------- //

	UFUNCTION(BlueprintCallable)
	virtual float GetGlomerularFiltrationCoefficient();

	UFUNCTION(BlueprintCallable)
	virtual float GetGlomerularFiltrationRate();

	UFUNCTION(BlueprintCallable)
	virtual float GetGlomerularFiltrationSurfaceArea();

	UFUNCTION(BlueprintCallable)
	virtual float GetGlomerularFluidPermeability();

	// --------------- Pressure --------------- //
	
	UFUNCTION(BlueprintCallable)
	virtual float GetBowmansCapsulesHydrostaticPressure();
	
	UFUNCTION(BlueprintCallable)
	virtual float GetBowmansCapsulesOsmoticPressure();

	UFUNCTION(BlueprintCallable)
	virtual float GetGlomerularCapillariesHydrostaticPressure();
	
	UFUNCTION(BlueprintCallable)
	virtual float GetGlomerularCapillariesOsmoticPressure();

	UFUNCTION(BlueprintCallable)
	virtual float GetNetFiltrationPressure();
	
	UFUNCTION(BlueprintCallable)
	virtual float GetNetReabsorptionPressure();

	UFUNCTION(BlueprintCallable)
	virtual float GetPeritubularCapillariesHydrostaticPressure();
	
	UFUNCTION(BlueprintCallable)
	virtual float GetPeritubularCapillariesOsmoticPressure();

	UFUNCTION(BlueprintCallable)
	virtual float GetTubularHydrostaticPressure();

	UFUNCTION(BlueprintCallable)
	virtual float GetTubularOsmoticPressure();
};
