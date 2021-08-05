#include "VH_PatientKidney.h"

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

UVH_PatientKidney::UVH_PatientKidney(const FObjectInitializer& objectInitializer) :
	Super(objectInitializer)
{
}

UVH_PatientKidney::~UVH_PatientKidney()
{
}


// ---------------------------------
// --- API
// ---------------------------------

void UVH_PatientKidney::InitializeKidney()
{
	FiltrationFraction = 0.0f;
	ReabsorptionFiltrationCoefficient = 0.0f;
	ReabsorptionRate = 0.0f;
	TubularReabsorptionFiltrationSurfaceArea = 0.0f;
	TubularReabsorptionFluidPermeability = 0.0f;

	// --------------- Arterial --------------- //

	AfferentArterioleResistance = 0.0f;
	EfferentArterioleResistance = 0.0f;

	// --------------- Glomerulus --------------- //

	GlomerularCapillariesHydrostaticPressure = 0.0f;
	GlomerularCapillariesOsmoticPressure = 0.0f;
	GlomerularFiltrationCoefficient = 0.0f;
	GlomerularFiltrationRate = 0.0f;
	GlomerularFiltrationSurfaceArea = 0.0f;
	GlomerularFluidPermeability = 0.0f;

	// --------------- Pressure --------------- //

	BowmansCapsulesHydrostaticPressure = 0.0f;
	BowmansCapsulesOsmoticPressure = 0.0f;
	NetFiltrationPressure = 0.0f;
	NetReabsorptionPressure = 0.0f;
	PeritubularCapillariesHydrostaticPressure = 0.0f;
	PeritubularCapillariesOsmoticPressure = 0.0f;
	TubularHydrostaticPressure = 0.0f;
	TubularOsmoticPressure = 0.0f;
}

#if  defined(WITH_BIOGEARS_BINDING) // TODO: Remove when biogears works on android
void UVH_PatientKidney::UpdateValues(const biogears::SERenalSystem* renal, bool bLeft)
{
	FScopeLock lock(&CriticalSection);

	if (renal != nullptr)
	{
		if (bLeft)
		{

			AfferentArterioleResistance = (renal->HasLeftAfferentArterioleResistance()) ? renal->GetLeftAfferentArterioleResistance(biogears::FlowResistanceUnit::mmHg_min_Per_mL) : 0.0f;
			BowmansCapsulesHydrostaticPressure = (renal->HasLeftBowmansCapsulesHydrostaticPressure()) ? renal->GetLeftBowmansCapsulesHydrostaticPressure(biogears::PressureUnit::mmHg) : 0.0f;
			BowmansCapsulesOsmoticPressure = (renal->HasLeftBowmansCapsulesOsmoticPressure()) ? renal->GetLeftBowmansCapsulesOsmoticPressure(biogears::PressureUnit::mmHg) : 0.0f;
			EfferentArterioleResistance = (renal->HasLeftEfferentArterioleResistance()) ? renal->GetLeftEfferentArterioleResistance(biogears::FlowResistanceUnit::mmHg_min_Per_mL) : 0.0f;
			GlomerularCapillariesHydrostaticPressure = (renal->HasLeftGlomerularCapillariesHydrostaticPressure()) ? renal->GetLeftGlomerularCapillariesHydrostaticPressure(biogears::PressureUnit::mmHg) : 0.0f;
			GlomerularCapillariesOsmoticPressure = (renal->HasLeftGlomerularCapillariesOsmoticPressure()) ? renal->GetLeftGlomerularCapillariesOsmoticPressure(biogears::PressureUnit::mmHg) : 0.0f;
			GlomerularFiltrationCoefficient = (renal->HasLeftGlomerularFiltrationCoefficient()) ? renal->GetLeftGlomerularFiltrationCoefficient(biogears::VolumePerTimePressureUnit::mL_Per_min_mmHg) : 0.0f;
			GlomerularFiltrationRate = (renal->HasLeftGlomerularFiltrationRate()) ? renal->GetLeftGlomerularFiltrationRate(biogears::VolumePerTimeUnit::mL_Per_min) : 0.0f;
			GlomerularFiltrationSurfaceArea = (renal->HasLeftGlomerularFiltrationSurfaceArea()) ? renal->GetLeftGlomerularFiltrationSurfaceArea(biogears::AreaUnit::cm2) : 0.0f;
			GlomerularFluidPermeability = (renal->HasLeftGlomerularFluidPermeability()) ? renal->GetLeftGlomerularFluidPermeability(biogears::VolumePerTimePressureAreaUnit::mL_Per_min_mmHg_m2) : 0.0f;
			FiltrationFraction = (renal->HasLeftFiltrationFraction()) ? renal->GetLeftFiltrationFraction() : 0.0f;
			NetFiltrationPressure = (renal->HasLeftNetFiltrationPressure()) ? renal->GetLeftNetFiltrationPressure(biogears::PressureUnit::mmHg) : 0.0f;
			NetReabsorptionPressure = (renal->HasLeftNetReabsorptionPressure()) ? renal->GetLeftNetReabsorptionPressure(biogears::PressureUnit::mmHg) : 0.0f;
			PeritubularCapillariesHydrostaticPressure = (renal->HasLeftPeritubularCapillariesHydrostaticPressure()) ? renal->GetLeftPeritubularCapillariesHydrostaticPressure(biogears::PressureUnit::mmHg) : 0.0f;
			PeritubularCapillariesOsmoticPressure = (renal->HasLeftPeritubularCapillariesOsmoticPressure()) ? renal->GetLeftPeritubularCapillariesOsmoticPressure(biogears::PressureUnit::mmHg) : 0.0f;
			ReabsorptionFiltrationCoefficient = (renal->HasLeftReabsorptionFiltrationCoefficient()) ? renal->GetLeftReabsorptionFiltrationCoefficient(biogears::VolumePerTimePressureUnit::mL_Per_min_mmHg) : 0.0f;
			ReabsorptionRate = (renal->HasLeftReabsorptionRate()) ? renal->GetLeftReabsorptionRate(biogears::VolumePerTimeUnit::mL_Per_min) : 0.0f;
			TubularReabsorptionFiltrationSurfaceArea = (renal->HasLeftTubularReabsorptionFiltrationSurfaceArea()) ? renal->GetLeftTubularReabsorptionFiltrationSurfaceArea(biogears::AreaUnit::cm2) : 0.0f;
			TubularReabsorptionFluidPermeability = (renal->HasLeftTubularReabsorptionFluidPermeability()) ? renal->GetLeftTubularReabsorptionFluidPermeability(biogears::VolumePerTimePressureAreaUnit::mL_Per_min_mmHg_m2) : 0.0f;
			TubularHydrostaticPressure = (renal->HasLeftTubularHydrostaticPressure()) ? renal->GetLeftTubularHydrostaticPressure(biogears::PressureUnit::mmHg) : 0.0f;
			TubularOsmoticPressure = (renal->HasLeftTubularOsmoticPressure()) ? renal->GetLeftTubularOsmoticPressure(biogears::PressureUnit::mmHg) : 0.0f;
		}
		else
		{
			AfferentArterioleResistance = (renal->HasRightAfferentArterioleResistance()) ? renal->GetRightAfferentArterioleResistance(biogears::FlowResistanceUnit::mmHg_min_Per_mL) : 0.0f;
			BowmansCapsulesHydrostaticPressure = (renal->HasRightBowmansCapsulesHydrostaticPressure()) ? renal->GetRightBowmansCapsulesHydrostaticPressure(biogears::PressureUnit::mmHg) : 0.0f;
			BowmansCapsulesOsmoticPressure = (renal->HasRightBowmansCapsulesOsmoticPressure()) ? renal->GetRightBowmansCapsulesOsmoticPressure(biogears::PressureUnit::mmHg) : 0.0f;
			EfferentArterioleResistance = (renal->HasRightEfferentArterioleResistance()) ? renal->GetRightEfferentArterioleResistance(biogears::FlowResistanceUnit::mmHg_min_Per_mL) : 0.0f;
			GlomerularCapillariesHydrostaticPressure = (renal->HasRightGlomerularCapillariesHydrostaticPressure()) ? renal->GetRightGlomerularCapillariesHydrostaticPressure(biogears::PressureUnit::mmHg) : 0.0f;
			GlomerularCapillariesOsmoticPressure = (renal->HasRightGlomerularCapillariesOsmoticPressure()) ? renal->GetRightGlomerularCapillariesOsmoticPressure(biogears::PressureUnit::mmHg) : 0.0f;
			GlomerularFiltrationCoefficient = (renal->HasRightGlomerularFiltrationCoefficient()) ? renal->GetRightGlomerularFiltrationCoefficient(biogears::VolumePerTimePressureUnit::mL_Per_min_mmHg) : 0.0f;
			GlomerularFiltrationRate = (renal->HasRightGlomerularFiltrationRate()) ? renal->GetRightGlomerularFiltrationRate(biogears::VolumePerTimeUnit::mL_Per_min) : 0.0f;
			GlomerularFiltrationSurfaceArea = (renal->HasRightGlomerularFiltrationSurfaceArea()) ? renal->GetRightGlomerularFiltrationSurfaceArea(biogears::AreaUnit::cm2) : 0.0f;
			GlomerularFluidPermeability = (renal->HasRightGlomerularFluidPermeability()) ? renal->GetRightGlomerularFluidPermeability(biogears::VolumePerTimePressureAreaUnit::mL_Per_min_mmHg_m2) : 0.0f;
			FiltrationFraction = (renal->HasRightFiltrationFraction()) ? renal->GetRightFiltrationFraction() : 0.0f;
			NetFiltrationPressure = (renal->HasRightNetFiltrationPressure()) ? renal->GetRightNetFiltrationPressure(biogears::PressureUnit::mmHg) : 0.0f;
			NetReabsorptionPressure = (renal->HasRightNetReabsorptionPressure()) ? renal->GetRightNetReabsorptionPressure(biogears::PressureUnit::mmHg) : 0.0f;
			PeritubularCapillariesHydrostaticPressure = (renal->HasRightPeritubularCapillariesHydrostaticPressure()) ? renal->GetRightPeritubularCapillariesHydrostaticPressure(biogears::PressureUnit::mmHg) : 0.0f;
			PeritubularCapillariesOsmoticPressure = (renal->HasRightPeritubularCapillariesOsmoticPressure()) ? renal->GetRightPeritubularCapillariesOsmoticPressure(biogears::PressureUnit::mmHg) : 0.0f;
			ReabsorptionFiltrationCoefficient = (renal->HasRightReabsorptionFiltrationCoefficient()) ? renal->GetRightReabsorptionFiltrationCoefficient(biogears::VolumePerTimePressureUnit::mL_Per_min_mmHg) : 0.0f;
			ReabsorptionRate = (renal->HasRightReabsorptionRate()) ? renal->GetRightReabsorptionRate(biogears::VolumePerTimeUnit::mL_Per_min) : 0.0f;
			TubularReabsorptionFiltrationSurfaceArea = (renal->HasRightTubularReabsorptionFiltrationSurfaceArea()) ? renal->GetRightTubularReabsorptionFiltrationSurfaceArea(biogears::AreaUnit::cm2) : 0.0f;
			TubularReabsorptionFluidPermeability = (renal->HasRightTubularReabsorptionFluidPermeability()) ? renal->GetRightTubularReabsorptionFluidPermeability(biogears::VolumePerTimePressureAreaUnit::mL_Per_min_mmHg_m2) : 0.0f;
			TubularHydrostaticPressure = (renal->HasRightTubularHydrostaticPressure()) ? renal->GetRightTubularHydrostaticPressure(biogears::PressureUnit::mmHg) : 0.0f;
			TubularOsmoticPressure = (renal->HasRightTubularOsmoticPressure()) ? renal->GetRightTubularOsmoticPressure(biogears::PressureUnit::mmHg) : 0.0f;
		}
	}
}
#endif

// --------------- Absorption --------------- //

float UVH_PatientKidney::GetFiltrationFraction()
{
	FScopeLock lock(&CriticalSection);
	return FiltrationFraction;
}

float UVH_PatientKidney::GetReabsorptionFiltrationCoefficient()
{
	FScopeLock lock(&CriticalSection);
	return ReabsorptionFiltrationCoefficient;
}

float UVH_PatientKidney::GetReabsorptionRate()
{
	FScopeLock lock(&CriticalSection);
	return ReabsorptionRate;
}
 
float UVH_PatientKidney::GetTubularReabsorptionFiltrationSurfaceArea()
{
	FScopeLock lock(&CriticalSection);
	return TubularReabsorptionFiltrationSurfaceArea;
}

float UVH_PatientKidney::GetTubularReabsorptionFluidPermeability()
{
	FScopeLock lock(&CriticalSection);
	return TubularReabsorptionFluidPermeability;
}

// --------------- Arterial --------------- //

float UVH_PatientKidney::GetAfferentArterioleResistance()
{
	FScopeLock lock(&CriticalSection);
	return AfferentArterioleResistance;
}

float UVH_PatientKidney::GetEfferentArterioleResistance()
{
	FScopeLock lock(&CriticalSection);
	return EfferentArterioleResistance;
}

// --------------- Glomerulus --------------- //

float UVH_PatientKidney::GetGlomerularFiltrationCoefficient()
{
	FScopeLock lock(&CriticalSection);
	return GlomerularFiltrationCoefficient;
}

float UVH_PatientKidney::GetGlomerularFiltrationRate()
{
	FScopeLock lock(&CriticalSection);
	return GlomerularFiltrationRate;
}

float UVH_PatientKidney::GetGlomerularFiltrationSurfaceArea()
{
	FScopeLock lock(&CriticalSection);
	return GlomerularFiltrationSurfaceArea;
}

float UVH_PatientKidney::GetGlomerularFluidPermeability()
{
	FScopeLock lock(&CriticalSection);
	return GlomerularFluidPermeability;
}

// --------------- Pressure --------------- //

float UVH_PatientKidney::GetBowmansCapsulesHydrostaticPressure()
{
	FScopeLock lock(&CriticalSection);
	return BowmansCapsulesHydrostaticPressure;
}

float UVH_PatientKidney::GetBowmansCapsulesOsmoticPressure()
{
	FScopeLock lock(&CriticalSection);
	return BowmansCapsulesOsmoticPressure;
}

float UVH_PatientKidney::GetGlomerularCapillariesHydrostaticPressure()
{
	FScopeLock lock(&CriticalSection);
	return GlomerularCapillariesHydrostaticPressure;
}

float UVH_PatientKidney::GetGlomerularCapillariesOsmoticPressure()
{
	FScopeLock lock(&CriticalSection);
	return GlomerularCapillariesOsmoticPressure;
}

float UVH_PatientKidney::GetNetFiltrationPressure()
{
	FScopeLock lock(&CriticalSection);
	return NetFiltrationPressure;
}

float UVH_PatientKidney::GetNetReabsorptionPressure()
{
	FScopeLock lock(&CriticalSection);
	return NetReabsorptionPressure;
}

float UVH_PatientKidney::GetPeritubularCapillariesHydrostaticPressure()
{
	FScopeLock lock(&CriticalSection);
	return PeritubularCapillariesHydrostaticPressure;
}

float UVH_PatientKidney::GetPeritubularCapillariesOsmoticPressure()
{
	FScopeLock lock(&CriticalSection);
	return PeritubularCapillariesOsmoticPressure;
}

float UVH_PatientKidney::GetTubularHydrostaticPressure()
{
	FScopeLock lock(&CriticalSection);
	return TubularHydrostaticPressure;
}

float UVH_PatientKidney::GetTubularOsmoticPressure()
{
	FScopeLock lock(&CriticalSection);
	return TubularOsmoticPressure;
}
