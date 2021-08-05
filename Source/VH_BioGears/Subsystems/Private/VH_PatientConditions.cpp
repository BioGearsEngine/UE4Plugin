#include "VH_PatientConditions.h"

// VH BioGears Plugin
#include "VH_BioGears.h"


// ---------------------------------
// --- Constructors
// ---------------------------------

UVH_PatientConditions::UVH_PatientConditions(const FObjectInitializer& objectInitializer) :
	Super(objectInitializer)
{
}

UVH_PatientConditions::~UVH_PatientConditions()
{
}


// ---------------------------------
// --- API
// ---------------------------------

void UVH_PatientConditions::InitializeConditions()
{
	ChronicAnemia =  false;
	ChronicObstructivePulmonaryDisease =  false;
	ChronicPericardialEffusion =  false;
	ChronicRenalStenosis =  false;
	ChronicVentricularSystolicDysfunction =  false;
	DiabetesType1 =  false;
	DiabetesType2 =  false;
	ImpairedAlveolarExchange =  false;
	LobarPneumonia =  false;
}

#if  defined(WITH_BIOGEARS_BINDING) // TODO: Remove when biogears works on android
void UVH_PatientConditions::UpdateValues(const biogears::SEConditionManager& conditions)
{
	FScopeLock lock(&CriticalSection);

	ChronicAnemia = conditions.HasChronicAnemia();
	ChronicObstructivePulmonaryDisease = conditions.HasChronicObstructivePulmonaryDisease();
	ChronicPericardialEffusion = conditions.HasChronicPericardialEffusion();
	ChronicRenalStenosis = conditions.HasChronicRenalStenosis();
	ChronicVentricularSystolicDysfunction = conditions.HasChronicVentricularSystolicDysfunction();
	DiabetesType1 = conditions.HasDiabetesType1();
	DiabetesType2 = conditions.HasDiabetesType2();
	ImpairedAlveolarExchange = conditions.HasImpairedAlveolarExchange();
	LobarPneumonia = conditions.HasLobarPneumonia();
}
#endif

bool UVH_PatientConditions::HasChronicAnemia()
{
	return ChronicAnemia;
}

bool UVH_PatientConditions::HasChronicObstructivePulmonaryDisease()
{
	return ChronicObstructivePulmonaryDisease;
}

bool UVH_PatientConditions::HasChronicPericardialEffusion()
{
	return ChronicPericardialEffusion;
}

bool UVH_PatientConditions::HasChronicRenalStenosis()
{
	return ChronicRenalStenosis;
}

bool UVH_PatientConditions::HasChronicVentricularSystolicDysfunction()
{
	return ChronicVentricularSystolicDysfunction;
}

bool UVH_PatientConditions::HasDiabetesType1()
{
	return DiabetesType1;
}

bool UVH_PatientConditions::HasDiabetesType2()
{
	return DiabetesType2;
}

bool UVH_PatientConditions::HasImpairedAlveolarExchange()
{
	return ImpairedAlveolarExchange;
}

bool UVH_PatientConditions::HasLobarPneumonia()
{
	return LobarPneumonia;
}
