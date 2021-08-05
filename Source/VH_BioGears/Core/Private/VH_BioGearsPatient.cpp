#include "VH_BioGearsPatient.h"

// VH BioGears Plugin
#include "VH_BioGears.h"


// ---------------------------------
// --- Constructors
// ---------------------------------

UVH_BioGearsPatient::UVH_BioGearsPatient(const FObjectInitializer& objectInitializer) :
	Super(objectInitializer),
	Engine(nullptr),
	Logger(nullptr),
	Physiology(nullptr)
{
	EngineClass = UVH_BioGearsEngine::StaticClass();
	LoggerClass = UVH_BioGearsLogger::StaticClass();
	PhysiologyClass = UVH_BioGearsPhysiology::StaticClass();
}

UVH_BioGearsPatient::~UVH_BioGearsPatient()
{
} 


// ---------------------------------
// --- Static Functions
// ---------------------------------

UVH_BioGearsPatient* UVH_BioGearsPatient::CreatePatient(TSubclassOf<UVH_BioGearsPatient> patientClass, const FString& patientFile)
{
	UVH_BioGearsPatient* patient = NewObject<UVH_BioGearsPatient>(patientClass);
	patient->InitializePatient();
	patient->Engine->LoadPatient(patientFile);

	return patient;
}

UVH_BioGearsPatient* UVH_BioGearsPatient::CreatePatientByState(TSubclassOf<UVH_BioGearsPatient> patientClass, const FString& stateFile)
{
	UVH_BioGearsPatient* patient = NewObject<UVH_BioGearsPatient>(patientClass);
	patient->InitializePatient();
	patient->Engine->LoadPatientState(stateFile);	
	return patient;
}


// ---------------------------------
// --- API
// ---------------------------------

void UVH_BioGearsPatient::InitializePatient()
{
	Logger = NewObject<UVH_BioGearsLogger>(LoggerClass);
	Logger->Initialize();

	Physiology = NewObject<UVH_BioGearsPhysiology>(PhysiologyClass);
	Physiology->InitializePhysiology();

	Engine = NewObject<UVH_BioGearsEngine>(EngineClass);
	Engine->InitializeEngine(Logger, Physiology);
}
