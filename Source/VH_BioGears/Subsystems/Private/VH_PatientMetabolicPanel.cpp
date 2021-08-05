#include "VH_PatientMetabolicPanel.h"

// VH BioGears Plugin
#include "VH_BioGears.h"


// ---------------------------------
// --- Constructors
// ---------------------------------

UVH_PatientMetabolicPanel::UVH_PatientMetabolicPanel(const FObjectInitializer& objectInitializer) :
	Super(objectInitializer)
{
}

UVH_PatientMetabolicPanel::~UVH_PatientMetabolicPanel()
{
}


// ---------------------------------
// --- API
// ---------------------------------

void UVH_PatientMetabolicPanel::InitializeMetabolic()
{
	Albumin = 0.0f;
	ALP = 0.0f;
	ALT = 0.0f;
	AST = 0.0f;
	BUN = 0.0f;
	Calcium = 0.0f;
	Chloride = 0.0f;
	Co2 = 0.0f;
	Creatine = 0.0f;
	Glucose = 0.0f;
	Potassium = 0.0f;
	Sodium = 0.0f;
	Bilirubin = 0.0f;
	Protein = 0.0f;
}

void UVH_PatientMetabolicPanel::UpdateValues()
{

}


float UVH_PatientMetabolicPanel::GetAlbumin()
{
	FScopeLock lock(&CriticalSection);
	return Albumin;
}

float UVH_PatientMetabolicPanel::GetALP()
{
	FScopeLock lock(&CriticalSection);
	return ALP;
}

float UVH_PatientMetabolicPanel::GetALT()
{
	FScopeLock lock(&CriticalSection);
	return ALT;
}

float UVH_PatientMetabolicPanel::GetAST()
{
	FScopeLock lock(&CriticalSection);
	return AST;
}

float UVH_PatientMetabolicPanel::GetBilirubin()
{
	FScopeLock lock(&CriticalSection);
	return Bilirubin;
}

float UVH_PatientMetabolicPanel::GetBUN()
{
	FScopeLock lock(&CriticalSection);
	return BUN;
}

float UVH_PatientMetabolicPanel::GetCalcium()
{
	FScopeLock lock(&CriticalSection);
	return Calcium;
}

float UVH_PatientMetabolicPanel::GetChloride()
{
	FScopeLock lock(&CriticalSection);
	return Chloride;
}

float UVH_PatientMetabolicPanel::GetCo2()
{
	FScopeLock lock(&CriticalSection);
	return Co2;
}

float UVH_PatientMetabolicPanel::GetCreatine()
{
	FScopeLock lock(&CriticalSection);
	return Creatine;
}

float UVH_PatientMetabolicPanel::GetGlucose()
{
	FScopeLock lock(&CriticalSection);
	return Glucose;
}

float UVH_PatientMetabolicPanel::GetPotassium()
{
	FScopeLock lock(&CriticalSection);
	return Potassium;
}

float UVH_PatientMetabolicPanel::GetProtein()
{
	FScopeLock lock(&CriticalSection);
	return Protein;
}

float UVH_PatientMetabolicPanel::GetSodium()
{
	FScopeLock lock(&CriticalSection);
	return Sodium;
}
