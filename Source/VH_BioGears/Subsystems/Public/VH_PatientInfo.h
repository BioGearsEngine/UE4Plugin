#pragma once

#include "VH_PatientSubsystem.h"
#include "VH_BioGearsEnums.h"

#if  defined(WITH_BIOGEARS_BINDING) // TODO: Remove when biogears works on android
// BioGears
#include "VH_BioGearsPreHeaderBlock.inl"
#include "biogears/engine/Controller/BioGearsEngine.h"
#include "biogears/schema/biogears/BioGears.hxx"
#include "VH_BioGearsPostHeaderBlock.inl"
#endif

// Generated
#include "VH_PatientInfo.generated.h"

/*
 * Clerical & baseline information about the patient
 *
 */
UCLASS(Blueprintable)
class VH_BIOGEARS_API UVH_PatientInfo : public UVH_PatientSubsystem
{
	GENERATED_BODY()


	// ---------------------------------
	// --- Constructors
	// ---------------------------------

public:
	UVH_PatientInfo(const FObjectInitializer& objectInitializer);

	virtual ~UVH_PatientInfo();


	// ---------------------------------
	// --- Variables
	// ---------------------------------

protected:
	UPROPERTY()
	uint8 Age;

	UPROPERTY()
	float BloodRh;

	UPROPERTY()
	EPatientBloodType BloodType;

	UPROPERTY()
	float BloodVolumeBaseline;

	UPROPERTY()
	float BodyFatFraction;

	UPROPERTY()
	float ExpiratoryReserveVolume;

	UPROPERTY()
	EPatientSex Gender;

	UPROPERTY()
	float HeartRateBaseline;

	UPROPERTY()
	float HeartRateMaximum;

	UPROPERTY()
	float HeartRateMinimum;

	UPROPERTY()
	float Height;

	UPROPERTY()
	float InspiratoryCapacity;

	UPROPERTY()
	float LeanBodyMass;

	UPROPERTY()
	float MuscleMass;

	UPROPERTY()
	FString Name;

	UPROPERTY()
	float PainSusceptibility;

	UPROPERTY()
	float RespirationRateBaseline;

	UPROPERTY()
	EPatientSex Sex;

	UPROPERTY()
	float SystolicArterialPressureBaseline;

	UPROPERTY()
	float TotalLungCapacity;

	UPROPERTY()
	float VitalCapacity;

	UPROPERTY()
	float Weight;

private:
	FCriticalSection CriticalSection;


	// ---------------------------------
	// --- API
	// ---------------------------------

public:
	virtual void InitializeInfo();

#if  defined(WITH_BIOGEARS_BINDING) // TODO: Remove when biogears works on android
	virtual void UpdateValues(const biogears::SEPatient& patient);
#endif

	UFUNCTION(BlueprintCallable)
	uint8 GetAge();

	UFUNCTION(BlueprintCallable)
	float GetBloodRh();

	UFUNCTION(BlueprintCallable)
	EPatientBloodType GetBloodType();

	UFUNCTION(BlueprintCallable)
	float GetBloodVolumeBaseline();

	UFUNCTION(BlueprintCallable)
	float GetBodyFatFraction();

	UFUNCTION(BlueprintCallable)
	float GetExpiratoryReserveVolume();

	UFUNCTION(BlueprintCallable)
	EPatientSex GetGender();

	UFUNCTION(BlueprintCallable)
	float GetHeartRateBaseline();

	UFUNCTION(BlueprintCallable)
	float GetHeartRateMaximum();

	UFUNCTION(BlueprintCallable)
	float GetHeartRateMinimum();

	UFUNCTION(BlueprintCallable)
	float GetHeight();

	UFUNCTION(BlueprintCallable)
	float GetInspiratoryCapacity();

	UFUNCTION(BlueprintCallable)
	float GetLeanBodyMass();

	UFUNCTION(BlueprintCallable)
	float GetMuscleMass();

	UFUNCTION(BlueprintCallable)
	FString GetName();

	UFUNCTION(BlueprintCallable)
	float GetPainSusceptibility();

	UFUNCTION(BlueprintCallable)
	float GetRespirationRateBaseline();

	UFUNCTION(BlueprintCallable)
	EPatientSex GetSex();

	UFUNCTION(BlueprintCallable)
	float GetSystolicArterialPressureBaseline();

	UFUNCTION(BlueprintCallable)
	float GetTotalLungCapacity();

	UFUNCTION(BlueprintCallable)
	float GetVitalCapacity();

	UFUNCTION(BlueprintCallable)
	float GetWeight();
};
