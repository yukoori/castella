#ifndef __SCTYPES_H
#define	__SCTYPES_H

#include <string>

#ifdef UNICODE
#	include	<tchar.h>
#	define	SCChar						wchar_t
#	define	SCString					std::wstring
#	define	SCOFStream					std::wofstream
#	define	SCSPRINTF(b, s, f, ...)		wsprintf(b, f, __VA_ARGS__)
#	define	SCVSPRINTF					wvsprintf
#	define	SCPRINTF					wprintf
#	define	SCTEXT(x)					L ## x
#	define	WIDEN(x)					SCTEXT(x)
#	define	__SCFILE__					WIDEN(__FILE__)
#if defined(_WIN32) || defined(_WIN64)
#	define	STRNCPY						wcsncpy_s
#else
#	define	STRNCPY						wcsncpy
#endif	// defined(_WIN32) || defined(_WIN64)
#	define	STRLEN						wcslen
#else
#	define	SCChar						char
#	define	SCString					std::string
#	define	SCOFStream					std::ofstream
#	define	SCSPRINTF(b, s, f, ...)		snprintf(b, s, f, __VA_ARGS__)
#	define	SCVSPRINTF					vsprintf_s
#	define	SCPRINTF					printf
#	define	SCTEXT(x)					x
#	define	WIDEN(x)					SCTEXT(x)
#	define	__SCFILE__					__FILE__
#if defined(_WIN32) || defined(_WIN64)
#	define	STRNCPY						strncpy_s
#else
#	define	STRNCPY						strncpy
#endif	// defined(_WIN32) || defined(_WIN64)
#	define	STRLEN						strlen
#endif // UNICODE

extern const SCChar* TOSCChar(const char* data);
extern const char* TOChar(const SCChar* data);

#endif // !__SCTYPES_H

