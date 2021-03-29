
#if PLATFORM_ANDROID
#pragma warning(pop)
#endif  // PLATFORM_ANDROID

#if PLATFORM_WINDOWS
#include "HideWindowsPlatformTypes.h"

#if _MSC_VER >= 1200
#pragma warning(pop)
#endif  // _MSC_VER >= 1200

#endif  // PLATFORM_WINDOWS

#pragma warning(pop)
