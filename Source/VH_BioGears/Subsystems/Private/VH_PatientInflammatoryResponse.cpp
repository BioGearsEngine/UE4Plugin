#include "VH_PatientInflammatoryResponse.h"

// VH BioGears Plugin
#include "VH_BioGears.h"


// ---------------------------------
// --- Constructors
// ---------------------------------

UVH_PatientInflammatoryResponse::UVH_PatientInflammatoryResponse(const FObjectInitializer& objectInitializer) :
	Super(objectInitializer)
{
}

UVH_PatientInflammatoryResponse::~UVH_PatientInflammatoryResponse()
{
}


// ---------------------------------
// --- API
// ---------------------------------

void UVH_PatientInflammatoryResponse::InitializeInflammatory()
{
	// --------------- Chemicals --------------- //

	Catecholamines = 0.0f;
	ConstitutiveNOS = 0.0f;
	InducibleNOS = 0.0f;
	InducibleNOSPre = 0.0f;
	Nitrate = 0.0f;
	NitricOxide = 0.0f;

	// --------------- Leukin --------------- //
	
	Interleukin6 = 0.0f;
	Interleukin10 = 0.0f;
	Interleukin12 = 0.0f;

	// --------------- Pathogens --------------- //
	
	BloodPathogen = 0.0f;	
	LocalPathogen = 0.0f;

	// --------------- White Blood Cells --------------- //

	LocalMacrophage = 0.0f;
	MacrophageActive = 0.0f;
	MacrophageResting = 0.0f;
	LocalNeutrophil = 0.0f;
	NeutrophilActive = 0.0f;
	NeutrophilResting = 0.0f;

	// --------------- Other --------------- //
	
	LocalBarrier = 0.0f;
	TissueIntegrity = 0.0f;
	Trauma = 0.0f;
	TumorNecrosisFactor = 0.0f;
}

#if  defined(WITH_BIOGEARS_BINDING) // TODO: Remove when biogears works on android
void UVH_PatientInflammatoryResponse::UpdateValues(const biogears::SEInflammatoryResponse& inflammatory)
{
	FScopeLock lock(&CriticalSection);
	
	BloodPathogen = (inflammatory.HasBloodPathogen()) ? inflammatory.GetBloodPathogen() : 0.0f;
	Catecholamines = (inflammatory.HasCatecholamines()) ? inflammatory.GetCatecholamines() : 0.0f;
	ConstitutiveNOS = (inflammatory.HasConstitutiveNOS()) ? inflammatory.GetConstitutiveNOS() : 0.0f;
	InducibleNOS = (inflammatory.HasInducibleNOS()) ? inflammatory.GetInducibleNOS() : 0.0f;
	InducibleNOSPre = (inflammatory.HasInducibleNOSPre()) ? inflammatory.GetInducibleNOSPre() : 0.0f;
	Interleukin6 = (inflammatory.HasInterleukin6()) ? inflammatory.GetInterleukin6() : 0.0f;
	Interleukin10 = (inflammatory.HasInterleukin10()) ? inflammatory.GetInterleukin10() : 0.0f;
	Interleukin12 = (inflammatory.HasInterleukin12()) ? inflammatory.GetInterleukin12() : 0.0f;
	LocalPathogen = (inflammatory.HasLocalPathogen()) ? inflammatory.GetLocalPathogen() : 0.0f;
	LocalMacrophage = (inflammatory.HasLocalMacrophage()) ? inflammatory.GetLocalMacrophage() : 0.0f;
	LocalNeutrophil = (inflammatory.HasLocalNeutrophil()) ? inflammatory.GetLocalNeutrophil() : 0.0f;
	LocalBarrier = (inflammatory.HasLocalBarrier()) ? inflammatory.GetLocalBarrier() : 0.0f;
	MacrophageResting = (inflammatory.HasMacrophageResting()) ? inflammatory.GetMacrophageResting() : 0.0f;
	MacrophageActive = (inflammatory.HasMacrophageActive()) ? inflammatory.GetMacrophageActive() : 0.0f;
	NeutrophilResting = (inflammatory.HasNeutrophilResting()) ? inflammatory.GetNeutrophilResting() : 0.0f;
	NeutrophilActive = (inflammatory.HasNeutrophilActive()) ? inflammatory.GetNeutrophilActive() : 0.0f;
	Nitrate = (inflammatory.HasNitrate()) ? inflammatory.GetNitrate() : 0.0f;
	NitricOxide = (inflammatory.HasNitricOxide()) ? inflammatory.GetNitricOxide() : 0.0f;
	TissueIntegrity = (inflammatory.HasTissueIntegrity()) ? inflammatory.GetTissueIntegrity() : 0.0f;
	Trauma = (inflammatory.HasTrauma()) ? inflammatory.GetTrauma() : 0.0f;
	TumorNecrosisFactor = (inflammatory.HasTumorNecrosisFactor()) ? inflammatory.GetTumorNecrosisFactor() : 0.0f;
}
#endif

// --------------- Chemicals --------------- //

float UVH_PatientInflammatoryResponse::GetCatecholamines()
{
	FScopeLock lock(&CriticalSection);
	return Catecholamines;
}

float UVH_PatientInflammatoryResponse::GetConstitutiveNOS()
{
	FScopeLock lock(&CriticalSection);
	return ConstitutiveNOS;
}

float UVH_PatientInflammatoryResponse::GetInducibleNOS()
{
	FScopeLock lock(&CriticalSection);
	return InducibleNOS;
}

float UVH_PatientInflammatoryResponse::GetInducibleNOSPre()
{
	FScopeLock lock(&CriticalSection);
	return InducibleNOSPre;
}

float UVH_PatientInflammatoryResponse::GetNitrate()
{
	FScopeLock lock(&CriticalSection);
	return Nitrate;
}

float UVH_PatientInflammatoryResponse::GetNitricOxide()
{
	FScopeLock lock(&CriticalSection);
	return NitricOxide;
}

// --------------- Leukin --------------- //

float UVH_PatientInflammatoryResponse::GetInterleukin6()
{
	FScopeLock lock(&CriticalSection);
	return Interleukin6;
}

float UVH_PatientInflammatoryResponse::GetInterleukin10()
{
	FScopeLock lock(&CriticalSection);
	return Interleukin10;
}

float UVH_PatientInflammatoryResponse::GetInterleukin12()
{
	FScopeLock lock(&CriticalSection);
	return Interleukin12;
}

// --------------- Pathogen --------------- //

float UVH_PatientInflammatoryResponse::GetBloodPathogen()
{
	FScopeLock lock(&CriticalSection);
	return BloodPathogen;
}

float UVH_PatientInflammatoryResponse::GetLocalPathogen()
{
	FScopeLock lock(&CriticalSection);
	return LocalPathogen;
}

// --------------- White Blood Cells --------------- //

float UVH_PatientInflammatoryResponse::GetLocalMacrophage()
{
	FScopeLock lock(&CriticalSection);
	return LocalMacrophage;
}

float UVH_PatientInflammatoryResponse::GetMacrophageActive()
{
	FScopeLock lock(&CriticalSection);
	return MacrophageActive;
}

float UVH_PatientInflammatoryResponse::GetMacrophageResting()
{
	FScopeLock lock(&CriticalSection);
	return MacrophageResting;
}

float UVH_PatientInflammatoryResponse::GetLocalNeutrophil()
{
	FScopeLock lock(&CriticalSection);
	return LocalNeutrophil;
}

float UVH_PatientInflammatoryResponse::GetNeutrophilActive()
{
	FScopeLock lock(&CriticalSection);
	return NeutrophilActive;
}

float UVH_PatientInflammatoryResponse::GetNeutrophilResting()
{
	FScopeLock lock(&CriticalSection);
	return NeutrophilResting;
}

// --------------- Other --------------- //

float UVH_PatientInflammatoryResponse::GetLocalBarrier()
{
	FScopeLock lock(&CriticalSection);
	return LocalBarrier;
}

float UVH_PatientInflammatoryResponse::GetTissueIntegrity()
{
	FScopeLock lock(&CriticalSection);
	return TissueIntegrity;
}

float UVH_PatientInflammatoryResponse::GetTrauma()
{
	FScopeLock lock(&CriticalSection);
	return Trauma;
}

float UVH_PatientInflammatoryResponse::GetTumorNecrosisFactor()
{
	FScopeLock lock(&CriticalSection);
	return TumorNecrosisFactor;
}
