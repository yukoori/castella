#ifndef	__SCASTELLA_CONFIG_H
#define __SCASTELLA_CONFIG_H

#if	defined(_WIN32) || defined(_WIN64)
#	include "config-windows.h"
#elif	defined(_HPUX_)
#	include "config-hpux.h"
#else
#	include "config-linux.h"
#endif

#endif	// !__SCASTELLA_CONFIG_H
