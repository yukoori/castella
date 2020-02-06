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
#endif // UNICODE


#endif // !__SCTYPES_H

