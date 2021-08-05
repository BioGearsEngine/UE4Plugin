#include "VH_AnesthesiaMachine.h"

#if  defined(WITH_BIOGEARS_BINDING) // TODO: Remove when biogears works on android
// BioGears
#include "VH_BioGearsPreHeaderBlock.inl"
#include "biogears/cdm/system/equipment/Anesthesia/SEAnesthesiaMachineOxygenBottle.h"
#include "VH_BioGearsPostHeaderBlock.inl"
#endif

// VH BioGears Plugin
#include "VH_BioGears.h"


// ---------------------------------
// --- Constructors
// ---------------------------------

UVH_AnesthesiaMachine::UVH_AnesthesiaMachine(const FObjectInitializer& objectInitializer) :
	Super(objectInitializer)
{
}

UVH_AnesthesiaMachine::~UVH_AnesthesiaMachine()
{
}


// ---------------------------------
// --- API
// ---------------------------------

void UVH_AnesthesiaMachine::InitializeAnesthesia()
{
	bConnected = false;
	InletFlow = 0.0f;
	InspiratoryExpiratoryRatio = 0.0f;
	OxygenBottleOneVolume = 0.0f;
	OxygenBottleTwoVolume = 0.0f;
	OxygenFraction = 0.0f;
	PrimaryGas = EAnesthesia::None;
	ReliefValvePressure = 0.0f;
	RespiratoryRate = 0.0f;
	VentilatorPressure = 0.0f;
}


#if  defined(WITH_BIOGEARS_BINDING) // TODO: Remove when biogears works on android
void UVH_AnesthesiaMachine::UpdateValues(const biogears::SEAnesthesiaMachine* anesthesia)
{
	FScopeLock lock(&CriticalSection);

	if (anesthesia != nullptr)
	{
		bConnected = (anesthesia->HasConnection()) ? (anesthesia->GetConnection() != CDM::enumAnesthesiaMachineConnection::Off) : false;
		InletFlow = (anesthesia->HasInletFlow()) ? anesthesia->GetInletFlow(biogears::VolumePerTimeUnit::mL_Per_min) : 0.0f;
		InspiratoryExpiratoryRatio = (anesthesia->HasInspiratoryExpiratoryRatio()) ? anesthesia->GetInspiratoryExpiratoryRatio() : 0.0f;
		OxygenBottleOneVolume = (anesthesia->HasOxygenBottleOne() && anesthesia->GetOxygenBottleOne()->HasVolume()) ? anesthesia->GetOxygenBottleOne()->GetVolume(biogears::VolumeUnit::mL) : 0.0f;
		OxygenBottleTwoVolume = (anesthesia->HasOxygenBottleTwo() && anesthesia->GetOxygenBottleTwo()->HasVolume()) ? anesthesia->GetOxygenBottleTwo()->GetVolume(biogears::VolumeUnit::mL) : 0.0f;
		OxygenFraction = (anesthesia->HasOxygenFraction()) ? anesthesia->GetOxygenFraction() : 0.0f;
		ReliefValvePressure = (anesthesia->HasReliefValvePressure()) ? anesthesia->GetReliefValvePressure(biogears::PressureUnit::mmHg) : 0.0f;
		RespiratoryRate = (anesthesia->HasRespiratoryRate()) ? anesthesia->GetRespiratoryRate(biogears::FrequencyUnit::Per_min) : 0.0f;
		VentilatorPressure = (anesthesia->HasVentilatorPressure()) ? anesthesia->GetVentilatorPressure(biogears::PressureUnit::mmHg) : 0.0f;

		if (anesthesia->HasPrimaryGas())
		{
			CDM::enumAnesthesiaMachinePrimaryGas gas = anesthesia->GetPrimaryGas();
			PrimaryGas = (gas == CDM::enumAnesthesiaMachinePrimaryGas::Air) ? EAnesthesia::Air : EAnesthesia::Nitrogen;
		}
		else
		{
			PrimaryGas = EAnesthesia::None;
		}
	}
}
#endif

bool UVH_AnesthesiaMachine::GetConnected()
{
	FScopeLock lock(&CriticalSection);
	return bConnected;
}

float UVH_AnesthesiaMachine::GetInletFlow()
{
	FScopeLock lock(&CriticalSection);
	return InletFlow;
}

float UVH_AnesthesiaMachine::GetInspiratoryExpiratoryRatio()
{
	FScopeLock lock(&CriticalSection);
	return InspiratoryExpiratoryRatio;
}

float UVH_AnesthesiaMachine::GetOxygenBottleOneVolume()
{
	FScopeLock lock(&CriticalSection);
	return OxygenBottleOneVolume;
}

float UVH_AnesthesiaMachine::GetOxygenBottleTwoVolume()
{
	FScopeLock lock(&CriticalSection);
	return OxygenBottleTwoVolume;
}

float UVH_AnesthesiaMachine::GetOxygenFraction()
{
	FScopeLock lock(&CriticalSection);
	return OxygenFraction;
}

EAnesthesia UVH_AnesthesiaMachine::GetPrimaryGas()
{
	FScopeLock lock(&CriticalSection);
	return PrimaryGas;
}

float UVH_AnesthesiaMachine::GetReliefValvePressure()
{
	FScopeLock lock(&CriticalSection);
	return ReliefValvePressure;
}

float UVH_AnesthesiaMachine::GetRespiratoryRate()
{
	FScopeLock lock(&CriticalSection);
	return RespiratoryRate;
}

float UVH_AnesthesiaMachine::GetVentilatorPressure()
{
	FScopeLock lock(&CriticalSection);
	return VentilatorPressure;
}
