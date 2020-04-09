#ifndef __SCLOGDEFINE_H
#define __SCLOGDEFINE_H

#include "SCTypes.h"

typedef enum 
{
	SC_E_LOG_ERROR,
	SC_E_LOG_WARNING,
	SC_E_LOG_INFO,
	SC_E_LOG_DEBUG
} ELogLevel;

#if defined(_WIN32) || defined(_WIN64)
#	define	SCLOG(OBJ, LEVEL, FORMAT, ...) \
		do { \
			OBJ.log(LEVEL, SCTEXT("%s(%d) ") FORMAT, __SCFILE__, __LINE__, __VA_ARGS__); \
		} while (0)
#else
#	define	SCLOG(OBJ, LEVEL, FORMAT, ...) \
		do { \
			OBJ.log(LEVEL, SCTEXT("%s(%d) ") FORMAT, __SCFILE__, __LINE__, ## __VA_ARGS__); \
		} while (0)
#endif // defined(_WIN32) || defined(_WIN64)

#endif // !__SCLOGDEFINE_H

