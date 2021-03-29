
#include "CoreMinimal.h"

#pragma warning(push)
#pragma warning(disable : 4263)  // member function does not override any base class virtual member function
#pragma warning(disable : 4264)  // no override available for virtual member function from base {function}; function is hidden
#pragma warning(disable : 4265)  // class has virtual functions, but destructor is not virtual
#pragma warning(disable : 4458)  // func/param declaration hides class member

#if PLATFORM_ANDROID
#pragma warning(push)
#pragma warning(default : 4668)  // #if not_defined treated as #if 0
#endif                           // PLATFORM_ANDROID

#if PLATFORM_WINDOWS
#if _MSC_VER >= 1200
#pragma warning(push)
#pragma warning(default : 4668)  // #if not_defined treated as #if 0
#endif                           // _MSC_VER >= 1200

// need to wrap these around the includes to avoid errors for DWORD etc.
#include "AllowWindowsPlatformTypes.h"
#endif  // PLATFORM_WINDOWS
