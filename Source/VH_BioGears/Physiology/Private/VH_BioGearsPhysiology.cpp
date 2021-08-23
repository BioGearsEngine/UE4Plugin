#include "VH_BioGearsPhysiology.h"

// VH BioGears Plugin
#include "VH_BioGears.h"


// ---------------------------------
// --- Constructors
// ---------------------------------

UVH_BioGearsPhysiology::UVH_BioGearsPhysiology(const FObjectInitializer& objectInitializer) :
	Super(objectInitializer)
{
}

UVH_BioGearsPhysiology::~UVH_BioGearsPhysiology()
{
}


// ---------------------------------
// --- API
// ---------------------------------

void UVH_BioGearsPhysiology::InitializePhysiology()
{
	Anesthesia = NewObject<UVH_AnesthesiaMachine>();
	Anesthesia->InitializeAnesthesia();

	Environment = NewObject<UVH_EnvironmentConditions>();
	Environment->InitializeEnvironment();

	PatientBody = NewObject<UVH_PatientBody>();
	PatientBody->InitializePatientBody();
}

#if  defined(WITH_BIOGEARS_BINDING) // TODO: Remove when biogears works on android
void UVH_BioGearsPhysiology::UpdateValues(biogears::BioGearsEngine* engine)
{
	if (engine != nullptr)
	{
		if (Environment != nullptr)
		{
			Environment->UpdateValues(engine->GetEnvironment(), engine->GetActions().GetEnvironmentActions());
		}

		if (PatientBody != nullptr)
		{
			PatientBody->UpdateValues(engine);
		}

		if (Anesthesia != nullptr)
		{
			Anesthesia->UpdateValues(engine->GetAnesthesiaMachine());
		}
	}
}
#endif
