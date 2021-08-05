#pragma once

#include "VH_PatientSubsystem.h"

// Generated
#include "VH_PatientMetabolicPanel.generated.h"

/*
 * Information about the contents of the patien't blood
 *
 * Results of a blood test identifying the contents of the patient's blood
 * A common lab test consisting of seven or eight biochemical tests
 * Measures functionality of Kidneys
 */
UCLASS(Blueprintable)
class VH_BIOGEARS_API UVH_PatientMetabolicPanel : public UVH_PatientSubsystem
{
	GENERATED_BODY()


	// ---------------------------------
	// --- Constructors
	// ---------------------------------

public:
	UVH_PatientMetabolicPanel(const FObjectInitializer& objectInitializer);

	virtual ~UVH_PatientMetabolicPanel();


	// ---------------------------------
	// --- Variables
	// ---------------------------------

protected:
	/***/
	UPROPERTY()
	float Albumin;

	/***/
	UPROPERTY()
	float ALP;

	/***/
	UPROPERTY()
	float ALT;

	/***/
	UPROPERTY()
	float AST;

	/***/
	UPROPERTY()
	float BUN;

	/***/
	UPROPERTY()
	float Calcium;

	/***/
	UPROPERTY()
	float Chloride;

	/***/
	UPROPERTY()
	float Co2;

	/***/
	UPROPERTY()
	float Creatine;

	/***/
	UPROPERTY()
	float Glucose;

	/***/
	UPROPERTY()
	float Potassium;

	/***/
	UPROPERTY()
	float Sodium;

	/***/
	UPROPERTY()
	float Bilirubin;

	/***/
	UPROPERTY()
	float Protein;

private:
	FCriticalSection CriticalSection;


	// ---------------------------------
	// --- API
	// ---------------------------------

public:
	virtual void InitializeMetabolic();

	virtual void UpdateValues();


	UFUNCTION(BlueprintCallable)
	virtual float GetAlbumin();
	
	UFUNCTION(BlueprintCallable)
	virtual float GetALP();
	
	UFUNCTION(BlueprintCallable)
	virtual float GetALT();
	
	UFUNCTION(BlueprintCallable)
	virtual float GetAST();
	
	UFUNCTION(BlueprintCallable)
	virtual float GetBilirubin();

	UFUNCTION(BlueprintCallable)
	virtual float GetBUN();
	
	UFUNCTION(BlueprintCallable)
	virtual float GetCalcium();
	
	UFUNCTION(BlueprintCallable)
	virtual float GetChloride();
	
	UFUNCTION(BlueprintCallable)
	virtual float GetCo2();
	
	UFUNCTION(BlueprintCallable)
	virtual float GetCreatine();
	
	UFUNCTION(BlueprintCallable)
	virtual float GetGlucose();
	
	UFUNCTION(BlueprintCallable)
	virtual float GetPotassium();
	
	UFUNCTION(BlueprintCallable)
	virtual float GetProtein();

	UFUNCTION(BlueprintCallable)
	virtual float GetSodium();
};
