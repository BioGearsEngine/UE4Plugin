#include "VH_PatientBloodChemistry.h"

// BioGears
#if  defined(WITH_BIOGEARS_BINDING) // TODO: Remove when biogears works on android
#include "VH_BioGearsPreHeaderBlock.inl"
#include "biogears/cdm/properties/SEScalarTypes.h"
#include "VH_BioGearsPostHeaderBlock.inl"
#endif

// VH BioGears Plugin
#include "VH_BioGears.h"


// ---------------------------------
// --- Constructors
// ---------------------------------

UVH_PatientBloodChemistry::UVH_PatientBloodChemistry(const FObjectInitializer& objectInitializer) :
	Super(objectInitializer)
{
	InflammatoryResponseClass = UVH_PatientInflammatoryResponse::StaticClass();
}

UVH_PatientBloodChemistry::~UVH_PatientBloodChemistry()
{
}


// ---------------------------------
// --- API
// ---------------------------------

void UVH_PatientBloodChemistry::InitializeBlood()
{
	InflammatoryResponse = NewObject<UVH_PatientInflammatoryResponse>(InflammatoryResponseClass);

	ArterialBloodPH = 0.0f;
	ArterialBloodPHBaseline = 0.0f;
	ArterialCarbonDioxidePressure = 0.0f;
	ArterialOxygenPressure = 0.0f;
	PulmonaryArterialCarbonDioxidePressure = 0.0f;
	PulmonaryArterialOxygenPressure = 0.0f;

	// --------------- Blood --------------- //

	BloodDensity = 0.0f;
	BloodSpecificHeat = 0.0f;
	BloodUreaNitrogenConcentration = 0.0f;
	Hematocrit = 0.0f;
	HemoglobinContent = 0.0f;
	Phosphate = 0.0f;
	PlasmaVolume = 0.0f;
	PulseOximetry = 0.0f;
	RedBloodCellAcetylcholinesterase = 0.0f;
	RedBloodCellCount = 0.0f;
	ShuntFraction = 0.0f;
	StrongIonDifference = 0.0f;
	TotalBilirubin = 0.0f;
	TotalProteinConcentration = 0.0f;
	VenousBloodPH = 0.0f;
	VolumeFractionNeutralPhospholipidInPlasma = 0.0f;
	VolumeFractionNeutralLipidInPlasma = 0.0f;

	// --------------- Gases --------------- //

	CarbonDioxideSaturation = 0.0f;
	CarbonMonoxideSaturation = 0.0f;
	OxygenSaturation = 0.0f;
	PulmonaryVenousCarbonDioxidePressure = 0.0f;
	PulmonaryVenousOxygenPressure = 0.0f;
	VenousCarbonDioxidePressure = 0.0f;
	VenousOxygenPressure = 0.0f;
}

#if  defined(WITH_BIOGEARS_BINDING) // TODO: Remove when biogears works on android
void UVH_PatientBloodChemistry::UpdateValues(const biogears::SEBloodChemistrySystem* blood)
{
	FScopeLock lock(&CriticalSection);

	if (blood != nullptr)
	{
		ArterialBloodPH = (blood->HasArterialBloodPH()) ? blood->GetArterialBloodPH() : 0.0f;
		ArterialBloodPHBaseline = (blood->HasArterialBloodPHBaseline()) ? blood->GetArterialBloodPHBaseline() : 0.0f;
		ArterialCarbonDioxidePressure = (blood->HasArterialCarbonDioxidePressure()) ? blood->GetArterialCarbonDioxidePressure(biogears::PressureUnit::mmHg) : 0.0f;
		ArterialOxygenPressure = (blood->HasArterialOxygenPressure()) ? blood->GetArterialOxygenPressure(biogears::PressureUnit::mmHg) : 0.0f;
		BloodDensity = (blood->HasBloodDensity()) ? blood->GetBloodDensity(biogears::MassPerVolumeUnit::g_Per_cm3) : 0.0f;
		BloodSpecificHeat = (blood->HasBloodSpecificHeat()) ? blood->GetBloodSpecificHeat(biogears::HeatCapacitancePerMassUnit::kcal_Per_C_kg) : 0.0f;
		BloodUreaNitrogenConcentration = (blood->HasBloodUreaNitrogenConcentration()) ? blood->GetBloodUreaNitrogenConcentration(biogears::MassPerVolumeUnit::g_Per_cm3) : 0.0f;
		CarbonDioxideSaturation = (blood->HasCarbonDioxideSaturation()) ? blood->GetCarbonDioxideSaturation() : 0.0f;
		CarbonMonoxideSaturation = (blood->HasCarbonMonoxideSaturation()) ? blood->GetCarbonMonoxideSaturation() : 0.0f;
		Hematocrit = (blood->HasHematocrit()) ? blood->GetHematocrit() : 0.0f;
		HemoglobinContent = (blood->HasHemoglobinContent()) ? blood->GetHemoglobinContent(biogears::MassUnit::g) : 0.0f;
		OxygenSaturation = (blood->HasOxygenSaturation()) ? blood->GetOxygenSaturation() : 0.0f;
		Phosphate = (blood->HasPhosphate()) ? blood->GetPhosphate(biogears::AmountPerVolumeUnit::ct_Per_L) : 0.0f;
		PlasmaVolume = (blood->HasPlasmaVolume()) ? blood->GetPlasmaVolume(biogears::VolumeUnit::mL) : 0.0f;
		PulmonaryArterialCarbonDioxidePressure = (blood->HasPulmonaryArterialCarbonDioxidePressure()) ? blood->GetPulmonaryArterialCarbonDioxidePressure(biogears::PressureUnit::mmHg) : 0.0f;
		PulmonaryArterialOxygenPressure = (blood->HasPulmonaryArterialOxygenPressure()) ? blood->GetPulmonaryArterialOxygenPressure(biogears::PressureUnit::mmHg) : 0.0f;
		PulmonaryVenousCarbonDioxidePressure = (blood->HasPulmonaryVenousCarbonDioxidePressure()) ? blood->GetPulmonaryVenousCarbonDioxidePressure(biogears::PressureUnit::mmHg) : 0.0f;
		PulmonaryVenousOxygenPressure = (blood->HasPulmonaryVenousOxygenPressure()) ? blood->GetPulmonaryVenousOxygenPressure(biogears::PressureUnit::mmHg) : 0.0f;
		PulseOximetry = (blood->HasPulseOximetry()) ? blood->GetPulseOximetry() : 0.0f;
		RedBloodCellAcetylcholinesterase = (blood->HasRedBloodCellAcetylcholinesterase()) ? blood->GetRedBloodCellAcetylcholinesterase(biogears::AmountPerVolumeUnit::ct_Per_L) : 0.0f;
		RedBloodCellCount = (blood->HasRedBloodCellCount()) ? blood->GetRedBloodCellCount(biogears::AmountPerVolumeUnit::ct_Per_L) : 0.0f;
		ShuntFraction = (blood->HasShuntFraction()) ? blood->GetShuntFraction() : 0.0f;
		StrongIonDifference = (blood->HasStrongIonDifference()) ? blood->GetStrongIonDifference(biogears::AmountPerVolumeUnit::ct_Per_L) : 0.0f;
		TotalBilirubin = (blood->HasTotalBilirubin()) ? blood->GetTotalBilirubin(biogears::MassPerVolumeUnit::g_Per_mL) : 0.0f;
		TotalProteinConcentration = (blood->HasTotalProteinConcentration()) ? blood->GetTotalProteinConcentration(biogears::MassPerVolumeUnit::g_Per_mL) : 0.0f;
		VenousBloodPH = (blood->HasVenousBloodPH()) ? blood->GetVenousBloodPH() : 0.0f;
		VenousCarbonDioxidePressure = (blood->HasVenousCarbonDioxidePressure()) ? blood->GetVenousCarbonDioxidePressure(biogears::PressureUnit::mmHg) : 0.0f;
		VenousOxygenPressure = (blood->HasVenousOxygenPressure()) ? blood->GetVenousOxygenPressure(biogears::PressureUnit::mmHg) : 0.0f;
		VolumeFractionNeutralLipidInPlasma = (blood->HasVolumeFractionNeutralLipidInPlasma()) ? blood->GetVolumeFractionNeutralLipidInPlasma() : 0.0f;
		VolumeFractionNeutralPhospholipidInPlasma = (blood->HasVolumeFractionNeutralPhospholipidInPlasma()) ? blood->GetVolumeFractionNeutralPhospholipidInPlasma() : 0.0f;
	
		if (blood->HasInflammatoryResponse() && InflammatoryResponse != nullptr)
		{
			InflammatoryResponse->UpdateValues(blood->GetInflammatoryResponse());
		}
	}
}
#endif

// --------------- Arterial --------------- //

float UVH_PatientBloodChemistry::GetArterialBloodPH()
{ 
	FScopeLock lock(&CriticalSection);
	return ArterialBloodPH;
}

float UVH_PatientBloodChemistry::GetArterialBloodPHBaseline()
{
	FScopeLock lock(&CriticalSection);
	return ArterialBloodPHBaseline;
}

float UVH_PatientBloodChemistry::GetArterialCarbonDioxidePressure()
{
	FScopeLock lock(&CriticalSection);
	return ArterialCarbonDioxidePressure;
}

float UVH_PatientBloodChemistry::GetArterialOxygenPressure()
{
	FScopeLock lock(&CriticalSection);
	return ArterialOxygenPressure;
}

float UVH_PatientBloodChemistry::GetPulmonaryArterialCarbonDioxidePressure()
{
	FScopeLock lock(&CriticalSection);
	return PulmonaryArterialCarbonDioxidePressure;
}

float UVH_PatientBloodChemistry::GetPulmonaryArterialOxygenPressure()
{
	FScopeLock lock(&CriticalSection);
	return PulmonaryArterialOxygenPressure;
}

// --------------- Blood --------------- //

float UVH_PatientBloodChemistry::GetBloodDensity()
{
	FScopeLock lock(&CriticalSection);
	return BloodDensity;
}

float UVH_PatientBloodChemistry::GetBloodSpecificHeat()
{
	FScopeLock lock(&CriticalSection);
	return BloodSpecificHeat;
}

float UVH_PatientBloodChemistry::GetBloodUreaNitrogenConcentration()
{
	FScopeLock lock(&CriticalSection);
	return BloodUreaNitrogenConcentration;
}

float UVH_PatientBloodChemistry::GetHematocrit()
{
	FScopeLock lock(&CriticalSection);
	return Hematocrit;
}

float UVH_PatientBloodChemistry::GetHemoglobinContent()
{
	FScopeLock lock(&CriticalSection);
	return HemoglobinContent;
}

float UVH_PatientBloodChemistry::GetPhosphate()
{
	FScopeLock lock(&CriticalSection);
	return Phosphate;
}

float UVH_PatientBloodChemistry::GetPlasmaVolume()
{
	FScopeLock lock(&CriticalSection);
	return PlasmaVolume;
}

float UVH_PatientBloodChemistry::GetPulseOximetry()
{
	FScopeLock lock(&CriticalSection);
	return PulseOximetry;
}

float UVH_PatientBloodChemistry::GetRedBloodCellAcetylcholinesterase()
{
	FScopeLock lock(&CriticalSection);
	return RedBloodCellAcetylcholinesterase;
}

float UVH_PatientBloodChemistry::GetRedBloodCellCount()
{
	FScopeLock lock(&CriticalSection);
	return RedBloodCellCount;
}

float UVH_PatientBloodChemistry::GetShuntFraction()
{
	FScopeLock lock(&CriticalSection);
	return ShuntFraction;
}

float UVH_PatientBloodChemistry::GetStrongIonDifference()
{
	FScopeLock lock(&CriticalSection);
	return StrongIonDifference;
}

float UVH_PatientBloodChemistry::GetTotalBilirubin()
{
	FScopeLock lock(&CriticalSection);
	return TotalBilirubin;
}

float UVH_PatientBloodChemistry::GetTotalProteinConcentration()
{
	FScopeLock lock(&CriticalSection);
	return TotalProteinConcentration;
}

float UVH_PatientBloodChemistry::GetVenousBloodPH()
{
	FScopeLock lock(&CriticalSection);
	return VenousBloodPH;
}

float UVH_PatientBloodChemistry::GetVolumeFractionNeutralPhospholipidInPlasma()
{
	FScopeLock lock(&CriticalSection);
	return VolumeFractionNeutralPhospholipidInPlasma;
}

float UVH_PatientBloodChemistry::GetVolumeFractionNeutralLipidInPlasma()
{
	FScopeLock lock(&CriticalSection);
	return VolumeFractionNeutralLipidInPlasma;
}

// --------------- Gases --------------- //

float UVH_PatientBloodChemistry::GetCarbonDioxideSaturation()
{
	FScopeLock lock(&CriticalSection);
	return CarbonDioxideSaturation;
}

float UVH_PatientBloodChemistry::GetCarbonMonoxideSaturation()
{
	FScopeLock lock(&CriticalSection);
	return CarbonMonoxideSaturation;
}

float UVH_PatientBloodChemistry::GetOxygenSaturation()
{
	FScopeLock lock(&CriticalSection);
	return OxygenSaturation;
}

float UVH_PatientBloodChemistry::GetPulmonaryVenousCarbonDioxidePressure()
{
	FScopeLock lock(&CriticalSection);
	return PulmonaryVenousCarbonDioxidePressure;
}

float UVH_PatientBloodChemistry::GetPulmonaryVenousOxygenPressure()
{
	FScopeLock lock(&CriticalSection);
	return PulmonaryVenousOxygenPressure;
}

float UVH_PatientBloodChemistry::GetVenousCarbonDioxidePressure()
{
	FScopeLock lock(&CriticalSection);
	return VenousCarbonDioxidePressure;
}

float UVH_PatientBloodChemistry::GetVenousOxygenPressure()
{
	FScopeLock lock(&CriticalSection);
	return VenousOxygenPressure;
}
