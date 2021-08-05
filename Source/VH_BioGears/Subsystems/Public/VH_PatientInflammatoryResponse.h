#pragma once

#include "VH_PatientSubsystem.h"

#if  defined(WITH_BIOGEARS_BINDING) // TODO: Remove when biogears works on android
// BioGears
#include "VH_BioGearsPreHeaderBlock.inl"
#include <biogears/engine/Controller/BioGearsEngine.h>
#include <biogears/schema/biogears/BioGears.hxx>
#include "VH_BioGearsPostHeaderBlock.inl"
#endif

// Generated
#include "VH_PatientInflammatoryResponse.generated.h"

/*
 * Information about the response when patient's tissues are injured 
 * Tissue chemical, blood, & structural contents
 */
UCLASS(Blueprintable)
class VH_BIOGEARS_API UVH_PatientInflammatoryResponse : public UVH_PatientSubsystem
{
	GENERATED_BODY()


	// ---------------------------------
	// --- Constructors
	// ---------------------------------

public:
	UVH_PatientInflammatoryResponse(const FObjectInitializer& objectInitializer);

	virtual ~UVH_PatientInflammatoryResponse();


	// ---------------------------------
	// --- Variables
	// ---------------------------------

protected:
	// --------------- Chemicals --------------- //
	
	/***/
	UPROPERTY()
	float Catecholamines;

	/***/
	UPROPERTY()
	float ConstitutiveNOS;

	/***/
	UPROPERTY()
	float InducibleNOS;

	/***/
	UPROPERTY()
	float InducibleNOSPre;

	/***/
	UPROPERTY()
	float Nitrate;

	/***/
	UPROPERTY()
	float NitricOxide;

	// --------------- Leukin --------------- //

	/***/
	UPROPERTY()
	float Interleukin6;

	/***/
	UPROPERTY()
	float Interleukin10;

	/***/
	UPROPERTY()
	float Interleukin12;

	// --------------- Pathogens --------------- //

	/***/
	UPROPERTY()
	float BloodPathogen;

	/***/
	UPROPERTY()
	float LocalPathogen;

	// --------------- White Blood Cells --------------- //

	/***/
	UPROPERTY()
	float LocalMacrophage;

	/***/
	UPROPERTY()
	float MacrophageActive;

	/***/
	UPROPERTY()
	float MacrophageResting;

	/***/
	UPROPERTY()
	float LocalNeutrophil;

	/***/
	UPROPERTY()
	float NeutrophilActive;

	/***/
	UPROPERTY()
	float NeutrophilResting;

	// --------------- Other --------------- //

	/***/
	UPROPERTY()
	float LocalBarrier;

	/***/
	UPROPERTY()
	float TissueIntegrity;

	/***/
	UPROPERTY()
	float Trauma;

	/***/
	UPROPERTY()
	float TumorNecrosisFactor;

private:
	FCriticalSection CriticalSection;


	// ---------------------------------
	// --- API
	// ---------------------------------

public:
	virtual void InitializeInflammatory();

#if  defined(WITH_BIOGEARS_BINDING) // TODO: Remove when biogears works on android
	virtual void UpdateValues(const biogears::SEInflammatoryResponse& inflammatory);
#endif

	// --------------- Chemicals --------------- //

	UFUNCTION(BlueprintCallable)
	virtual float GetCatecholamines();

	UFUNCTION(BlueprintCallable)
	virtual float GetConstitutiveNOS();
	
	UFUNCTION(BlueprintCallable)
	virtual float GetInducibleNOS();
	
	UFUNCTION(BlueprintCallable)
	virtual float GetInducibleNOSPre();
	
	UFUNCTION(BlueprintCallable)
	virtual float GetNitrate();
	
	UFUNCTION(BlueprintCallable)
	virtual float GetNitricOxide();
	
	// --------------- Leukin --------------- //

	UFUNCTION(BlueprintCallable)
	virtual float GetInterleukin6();
	
	UFUNCTION(BlueprintCallable)
	virtual float GetInterleukin10();
	
	UFUNCTION(BlueprintCallable)
	virtual float GetInterleukin12();
	
	// --------------- Pathogen --------------- //
	
	UFUNCTION(BlueprintCallable)
	virtual float GetBloodPathogen();
	
	UFUNCTION(BlueprintCallable)
	virtual float GetLocalPathogen();
	
	// --------------- White Blood Cells --------------- //

	UFUNCTION(BlueprintCallable)
	virtual float GetLocalMacrophage();
	
	UFUNCTION(BlueprintCallable)
	virtual float GetMacrophageActive();
	
	UFUNCTION(BlueprintCallable)
	virtual float GetMacrophageResting();
	
	UFUNCTION(BlueprintCallable)
	virtual float GetLocalNeutrophil();
	
	UFUNCTION(BlueprintCallable)
	virtual float GetNeutrophilActive();
	
	UFUNCTION(BlueprintCallable)
	virtual float GetNeutrophilResting();
	
	// --------------- Other --------------- //

	UFUNCTION(BlueprintCallable)
	virtual float GetLocalBarrier();
	
	UFUNCTION(BlueprintCallable)
	virtual float GetTissueIntegrity();
	
	UFUNCTION(BlueprintCallable)
	virtual float GetTrauma();
	
	UFUNCTION(BlueprintCallable)
	virtual float GetTumorNecrosisFactor();
};
