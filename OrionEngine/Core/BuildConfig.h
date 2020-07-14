#pragma once

#ifdef _DEBUG
#   define OE_DEBUG
#else
#   define OE_RELEASE
#endif

#ifdef WIN32
#   define OE_PLATFORM_WINDOWS
#endif