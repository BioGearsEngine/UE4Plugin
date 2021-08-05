#include "VH_PatientPupillaryResponse.h"

// VH BioGears Plugin
#include "VH_BioGears.h"


// ---------------------------------
// --- Constructors
// ---------------------------------

UVH_PatientPupillaryResponse::UVH_PatientPupillaryResponse(const FObjectInitializer& objectInitializer) :
	Super(objectInitializer)
{
}

UVH_PatientPupillaryResponse::~UVH_PatientPupillaryResponse()
{
}


// ---------------------------------
// --- API
// ---------------------------------

void UVH_PatientPupillaryResponse::InitializePupillaryResponse()
{
	ReactivityModifier = 0.0f;
	ShapeModifier = 0.0f;
	SizeModifier = 0.0f;
}

#if  defined(WITH_BIOGEARS_BINDING) // TODO: Remove when biogears works on android
void UVH_PatientPupillaryResponse::UpdateValues(const biogears::SEPupillaryResponse* response)
{
	FScopeLock lock(&CriticalSection);

	if (response != nullptr)
	{
		ReactivityModifier = (response->HasReactivityModifier()) ? response->GetReactivityModifier() : 0.0f;
		ShapeModifier = (response->HasShapeModifier()) ? response->GetShapeModifier() : 0.0f;
		SizeModifier = (response->HasSizeModifier()) ? response->GetSizeModifier() : 0.0f;
	}
}
#endif

float UVH_PatientPupillaryResponse::GetReactivityModifier()
{
	FScopeLock lock(&CriticalSection);
	return ReactivityModifier;
}

float UVH_PatientPupillaryResponse::GetShapeModifier()
{
	FScopeLock lock(&CriticalSection);
	return ShapeModifier;
}

float UVH_PatientPupillaryResponse::GetSizeModifier()
{
	FScopeLock lock(&CriticalSection);
	return SizeModifier;
}
