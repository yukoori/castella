#ifndef	__SCASTELLA_CONFIG_WINDOWS_H
#define __SCASTELLA_CONFIG_WINDOWS_H

#if !defined(_WIN32) && !defined(_WIN64)
#	include <limits.h>
#	if (LONG_MAX > INT_MAX)
#		define _WIN64
#	else
#		define _WIN32
#	endif	// (LONG_MAX > INT_MAX)
#endif // !defined(_WIN32) && !defined(_WIN64)

#endif	// !__SCASTELLA_CONFIG_WINDOWS_H