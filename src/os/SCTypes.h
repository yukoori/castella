#ifndef __SCTYPES_H
#define	__SCTYPES_H

#include "config.h"

#include <string>
#include <errno.h>
#include <sys/types.h>
#include <sys/stat.h>

#if !defined(_WIN32) && !defined(_WIN64)
#	include <string.h>
#	include <dirent.h>
#	include <unistd.h>
#	include <sys/io.h>
#else
#	include <windows.h>
#	include <direct.h>
#	include <io.h>
#	include <strsafe.h>
#endif // !defined(_WIN32) && !defined(_WIN64)

#ifdef UNICODE
#	include	<tchar.h>
#	define	SCChar						wchar_t
#	define	SCString					std::wstring
#	define	SCOFStream					std::wofstream
#	define	SCSPRINTF(b, s, f, ...)		wsprintf(b, f, __VA_ARGS__)
#	define	SCPRINTF					wprintf
#	define	SCTEXT(x)					L ## x
#	define	WIDEN(x)					SCTEXT(x)
#	define	__SCFILE__					WIDEN(__FILE__)
#	define	SCFPRINTF(p, f, ...)		fwprintf(p, f, __VA_ARGS__)
#	define	STRLEN						wcslen
#if defined(_WIN32) || defined(_WIN64)
#	define	SCVSPRINTF(b, s, m, f, ...)	_vsnwprintf_s(b, s, m, f, __VA_ARGS__)
#	define	SCVSCPRINTF					_vscwprintf
#	define	SCMKDIR(d)					_wmkdir(d)
#	define	SCACCESS					_waccess_s
#	define	STRNCPY						wcsncpy_s
#else
#	define	SCVSPRINTF(b, s, m, f, ...)	vsnwprintf(b, s, f, __VA_ARGS__)
#	define	SCMKDIR(d)					wmkdir(d)
#	define	SCACCESS					waccess
#	define	STRNCPY						wcsncpy
#endif	/ / defined(_WIN32) || defined(_WIN64)
#else
#	define	SCChar						char
#	define	SCString					std::string
#	define	SCOFStream					std::ofstream
#	define	SCPRINTF					printf
#	define	SCTEXT(x)					x
#	define	WIDEN(x)					SCTEXT(x)
#	define	__SCFILE__					__FILE__
#	define	SCFPRINTF(p, f, ...)		fprintf(p, f, __VA_ARGS__)
#	define	STRLEN						strlen
#if defined(_WIN32) || defined(_WIN64)
#	define	SCVSPRINTF(b, s, m, f, ...)	_vsnprintf_s(b, s, m, f, __VA_ARGS__) // vsprintf_s
#	define	SCVSCPRINTF					_vscprintf
#	define	SCSPRINTF(b, s, f, ...)		sprintf_s(b, s, f, __VA_ARGS__)
#	define	STRNCPY						strncpy_s
#	define	SCMKDIR(d)					_mkdir(d)
#	define	SCACCESS					_access
#else
#	define	SCVSPRINTF(b, s, m, f, ...)	vsnprintf(b, s, f, __VA_ARGS__)
#	define	SCSPRINTF(b, s, f, ...)		snprintf(b, s, f, __VA_ARGS__)
#	define	STRNCPY						strncpy
#	define	SCMKDIR(d)					mkdir(d, 0755)
#	define	SCSTAT						stat
#	define	SCACCESS					access
#endif	// defined(_WIN32) || defined(_WIN64)
#endif // UNICODE

extern const SCString TOSCChar(const char* data);
extern const std::string TOChar(const SCChar* data);

#endif // !__SCTYPES_H

