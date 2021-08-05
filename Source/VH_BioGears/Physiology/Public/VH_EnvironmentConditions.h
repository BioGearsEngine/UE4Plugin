#pragma once

#if  defined(WITH_BIOGEARS_BINDING) // TODO: Remove when biogears works on android
// BioGears
#include "VH_BioGearsPreHeaderBlock.inl"
#include "biogears/cdm/system/environment/SEEnvironment.h"
#include "biogears/engine/Controller/BioGearsEngine.h"
#include "biogears/schema/biogears/BioGears.hxx"
#include "VH_BioGearsPostHeaderBlock.inl"
#endif

// Generated
#include "VH_EnvironmentConditions.generated.h"

/*
 * Conditions of the physical environment of the patient
 * Contains information about the surrounding air & temperature
 *
 */
UCLASS(Blueprintable)
class VH_BIOGEARS_API UVH_EnvironmentConditions : public UObject
{
	GENERATED_BODY()


	// ---------------------------------
	// --- Constructors
	// ---------------------------------

public:
	UVH_EnvironmentConditions(const FObjectInitializer& objectInitializer);

	virtual ~UVH_EnvironmentConditions();


	// ---------------------------------
	// --- Variables
	// ---------------------------------

protected:
	UPROPERTY()
	FString Name;

	/** Measured in kg/m^3 */
	UPROPERTY()
	float AirDensity;

	/* Measured in m/s */
	UPROPERTY()
	float AirVelocity;

	/* Measured in C */
	UPROPERTY()
	float AmbientTemperature;

	/* Measured in C */
	UPROPERTY()
	float AppliedTemperature;

	/** Measured in mmHg */
	UPROPERTY()
	float AtmosphericPressure;

	/** Measured in CLO*/
	UPROPERTY()
	float ClothingResistance;

	/** Measued in ? */
	UPROPERTY()
	float Emissivity;

	/** Measured in C */
	UPROPERTY()
	float MeanRadiantTemperature;

	/** Measured in PCT*/
	UPROPERTY()
	float RelativeHumidity;

	/** Measured in C*/
	UPROPERTY()
	float RespirationAmbientTemperature;

private:
	FCriticalSection CriticalSection;


	// ---------------------------------
	// --- API
	// ---------------------------------

public:
	void InitializeEnvironment();

#if  defined(WITH_BIOGEARS_BINDING) // TODO: Remove when biogears works on android
	void UpdateValues(const biogears::SEEnvironment* environment, const biogears::SEEnvironmentActionCollection& actions);
#endif

	UFUNCTION(BlueprintCallable)
	FString GetName();
	
	/** Measured in kg/m^3 */
	UFUNCTION(BlueprintCallable)
	float GetAirDensity();
	
	/* Measured in m/s */
	UFUNCTION(BlueprintCallable)
	float GetAirVelocity();
	
	/* Measured in C */
	UFUNCTION(BlueprintCallable)
	float GetAmbientTemperature();
	
	/* Measured in C */
	UFUNCTION(BlueprintCallable)
	float GetAppliedTemperature();
	
	/** Measured in mmHg */
	UFUNCTION(BlueprintCallable)
	float GetAtmosphericPressure();
	
	/** Measured in CLO*/
	UFUNCTION(BlueprintCallable)
	float GetClothingResistance();
	
	/** */
	UFUNCTION(BlueprintCallable)
	float GetEmissivity();
	
	/* Measured in C */
	UFUNCTION(BlueprintCallable)
	float GetMeanRadiantTemperature();
	
	/** Measured in PCT*/
	UFUNCTION(BlueprintCallable)
	float GetRelativeHumidity();
	
	/* Measured in C */
	UFUNCTION(BlueprintCallable)
	float GetRespirationAmbientTemperature();
};
