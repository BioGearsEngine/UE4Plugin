#include "VH_PatientInfo.h"

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

UVH_PatientInfo::UVH_PatientInfo(const FObjectInitializer& objectInitializer) :
	Super(objectInitializer)
{
}

UVH_PatientInfo::~UVH_PatientInfo()
{
}


// ---------------------------------
// --- API
// ---------------------------------

void UVH_PatientInfo::InitializeInfo()
{
	Name = FString("");
	Age = 0;
	Height = 0.0f;
	Weight =  0.0f;
	BloodRh = 0.0f;
	BloodVolumeBaseline = 0.0f;
	BodyFatFraction = 0.0f;
	ExpiratoryReserveVolume = 0.0f;
	HeartRateBaseline = 0.0f;
	HeartRateMaximum = 0.0f;
	HeartRateMinimum = 0.0f;
	InspiratoryCapacity = 0.0f;
	LeanBodyMass = 0.0f;
	MuscleMass = 0.0f;
	PainSusceptibility = 0.0f;
	RespirationRateBaseline = 0.0f;
	SystolicArterialPressureBaseline = 0.0f;
	TotalLungCapacity = 0.0f;
	VitalCapacity = 0.0f;
}

#if  defined(WITH_BIOGEARS_BINDING) // TODO: Remove when biogears works on android
void UVH_PatientInfo::UpdateValues(const biogears::SEPatient& patient)
{
	FScopeLock lock(&CriticalSection);

	Name = patient.HasName() ? ANSI_TO_TCHAR(patient.GetName().c_str()) : FString();
	Age = patient.HasAge() ? patient.GetAge(biogears::TimeUnit::yr) : 0;
	Height = patient.HasHeight() ? patient.GetHeight(biogears::LengthUnit::cm) : 0.0f;
	Weight = patient.HasWeight() ? patient.GetWeight(biogears::MassUnit::lb) : 0.0f;
	BloodRh = (patient.HasBloodRh()) ? patient.GetBloodRh() : 0.0f;
	BloodVolumeBaseline = (patient.HasBloodVolumeBaseline()) ? patient.GetBloodVolumeBaseline(biogears::VolumeUnit::mL) : 0.0f;
	BodyFatFraction = (patient.HasBodyFatFraction()) ? patient.GetBodyFatFraction() : 0.0f;
	ExpiratoryReserveVolume = (patient.HasExpiratoryReserveVolume()) ? patient.GetExpiratoryReserveVolume(biogears::VolumeUnit::mL) : 0.0f;
	HeartRateBaseline = (patient.HasHeartRateBaseline()) ? patient.GetHeartRateBaseline(biogears::FrequencyUnit::Per_min) : 0.0f;
	HeartRateMaximum = (patient.HasHeartRateMaximum()) ? patient.GetHeartRateMaximum(biogears::FrequencyUnit::Per_min) : 0.0f;
	HeartRateMinimum = (patient.HasHeartRateMinimum()) ? patient.GetHeartRateMinimum(biogears::FrequencyUnit::Per_min) : 0.0f;
	InspiratoryCapacity = (patient.HasInspiratoryCapacity()) ? patient.GetInspiratoryCapacity(biogears::VolumeUnit::mL) : 0.0f;
	LeanBodyMass = (patient.HasLeanBodyMass()) ? patient.GetLeanBodyMass(biogears::MassUnit::g) : 0.0f;
	MuscleMass = (patient.HasMuscleMass()) ? patient.GetMuscleMass(biogears::MassUnit::g) : 0.0f;
	PainSusceptibility = (patient.HasPainSusceptibility()) ? patient.GetPainSusceptibility() : 0.0f;
	RespirationRateBaseline = (patient.HasRespirationRateBaseline()) ? patient.GetRespirationRateBaseline(biogears::FrequencyUnit::Per_min) : 0.0f;
	SystolicArterialPressureBaseline = (patient.HasSystolicArterialPressureBaseline()) ? patient.GetSystolicArterialPressureBaseline(biogears::PressureUnit::mmHg) : 0.0f;
	TotalLungCapacity = (patient.HasTotalLungCapacity()) ? patient.GetTotalLungCapacity(biogears::VolumeUnit::mL) : 0.0f;
	VitalCapacity = (patient.HasVitalCapacity()) ? patient.GetVitalCapacity(biogears::VolumeUnit::mL) : 0.0f;

	if (patient.HasGender())
	{
		CDM::enumSex gender = patient.GetGender();
		Gender = (gender == CDM::enumSex::Male) ? EPatientSex::Male : EPatientSex::Female;
	}
	else
	{
		Gender = EPatientSex::None;
	}

	if (patient.HasSex())
	{
		CDM::enumSex sex = patient.GetGender();
		Sex = (sex == CDM::enumSex::Male) ? EPatientSex::Male : EPatientSex::Female;
	}
	else
	{
		Sex = EPatientSex::None;
	}

	if (patient.HasBloodType())
	{
		CDM::enumBloodType::value type = patient.GetBloodType();
		switch (type)
		{
		case CDM::enumBloodType::A:
			BloodType = EPatientBloodType::A;
			break;
		case CDM::enumBloodType::AB:
			BloodType = EPatientBloodType::AB;
			break;
		case CDM::enumBloodType::B:
			BloodType = EPatientBloodType::B;
			break;
		case CDM::enumBloodType::O:
			BloodType = EPatientBloodType::O;
			break;
		}
	}
	else
	{
		BloodType = EPatientBloodType::O;
	}
}
#endif

uint8 UVH_PatientInfo::GetAge()
{
	FScopeLock lock(&CriticalSection);
	return Age;
}

float UVH_PatientInfo::GetBloodRh()
{
	FScopeLock lock(&CriticalSection);
	return BloodRh;
}

EPatientBloodType UVH_PatientInfo::GetBloodType()
{
	FScopeLock lock(&CriticalSection);
	return BloodType;
}

float UVH_PatientInfo::GetBloodVolumeBaseline()
{
	FScopeLock lock(&CriticalSection);
	return BloodVolumeBaseline;
}

float UVH_PatientInfo::GetBodyFatFraction()
{
	FScopeLock lock(&CriticalSection);
	return BodyFatFraction;
}

float UVH_PatientInfo::GetExpiratoryReserveVolume()
{
	FScopeLock lock(&CriticalSection);
	return ExpiratoryReserveVolume;
}

EPatientSex UVH_PatientInfo::GetGender()
{
	FScopeLock lock(&CriticalSection);
	return Gender;
}

float UVH_PatientInfo::GetHeartRateBaseline()
{
	FScopeLock lock(&CriticalSection);
	return HeartRateBaseline;
}

float UVH_PatientInfo::GetHeartRateMaximum()
{
	FScopeLock lock(&CriticalSection);
	return HeartRateMaximum;
}

float UVH_PatientInfo::GetHeartRateMinimum()
{
	FScopeLock lock(&CriticalSection);
	return HeartRateMinimum;
}

float UVH_PatientInfo::GetHeight()
{
	FScopeLock lock(&CriticalSection);
	return Height;
}

float UVH_PatientInfo::GetInspiratoryCapacity()
{
	FScopeLock lock(&CriticalSection);
	return InspiratoryCapacity;
}

float UVH_PatientInfo::GetLeanBodyMass()
{
	FScopeLock lock(&CriticalSection);
	return LeanBodyMass;
}

float UVH_PatientInfo::GetMuscleMass()
{
	FScopeLock lock(&CriticalSection);
	return MuscleMass;
}

FString UVH_PatientInfo::GetName()
{
	FScopeLock lock(&CriticalSection);
	return Name;
}

float UVH_PatientInfo::GetPainSusceptibility()
{
	FScopeLock lock(&CriticalSection);
	return PainSusceptibility;
}

float UVH_PatientInfo::GetRespirationRateBaseline()
{
	FScopeLock lock(&CriticalSection);
	return RespirationRateBaseline;
}

EPatientSex UVH_PatientInfo::GetSex()
{
	FScopeLock lock(&CriticalSection);
	return Sex;
}

float UVH_PatientInfo::GetSystolicArterialPressureBaseline()
{
	FScopeLock lock(&CriticalSection);
	return SystolicArterialPressureBaseline;
}

float UVH_PatientInfo::GetTotalLungCapacity()
{
	FScopeLock lock(&CriticalSection);
	return TotalLungCapacity;
}

float UVH_PatientInfo::GetVitalCapacity()
{
	FScopeLock lock(&CriticalSection);
	return VitalCapacity;
}

float UVH_PatientInfo::GetWeight()
{
	FScopeLock lock(&CriticalSection);
	return Weight;
}
