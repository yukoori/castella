#include "SCLogFormat.h"
#include "SCThread.h"

#include <time.h>
#include <sys/timeb.h>
#if defined(_WIN32) || defined(_WIN64)
#	include <Windows.h>
#	if _MSC_VER < 1600
#		define va_copy(d, s) ((d) = (s))
#	endif // MSVC_VERSION < 1600
#endif // defined(_WIN32) || defined(_WIN64)

#define MAX_BUFFER_SIZE	2048

SCLogFormat::SCLogFormat()
	: _data(SCTEXT(""))
{

}

SCLogFormat::~SCLogFormat()
{

}

void SCLogFormat::setRecord(ELogLevel logLevel, const SCChar* format, va_list argp)
{
	// 
	_data = getLevelPrefix(logLevel);
	_data += getTimePrefix();
	_data += getThreadPrefix();

#if	defined(_WIN32) || defined(_WIN64)
	va_list copy;
	va_copy(copy, argp);
	int count = SCVSCPRINTF(format, copy) + sizeof(SCChar) /* For null */;
	va_end(copy);

	if (count > MAX_BUFFER_SIZE)
	{
		SCChar* buffer = new SCChar[count];
		SCVSPRINTF(buffer, count, count, format, argp);

		_data += buffer;

		if (buffer) delete buffer; buffer = NULL;
	}
	else
	{
		SCChar buffer[MAX_BUFFER_SIZE] = { '\0', };
		SCVSPRINTF(buffer, count, MAX_BUFFER_SIZE, format, argp);
		_data += buffer;
	}
#else
	SCChar buffer[MAX_BUFFER_SIZE] = { '\0', };
	SCVSPRINTF(buffer, MAX_BUFFER_SIZE, MAX_BUFFER_SIZE, format, argp);
	_data += buffer;
#endif

	return;
}

void SCLogFormat::setRecord(ELogLevel logLevel, const unsigned char* data, const int length)
{
	_data = getLevelPrefix(logLevel);
	_data += getTimePrefix();
	_data += getThreadPrefix();

	int target = 0;
	if (length > 192)
	{
		// 최초 192byte 만 출력한다.
		target = 192;
	}
	else
	{
		target = length;
	}

	SCChar prefixLength[32] = { '\0', };
	SCSPRINTF(prefixLength, 32, SCTEXT("HEX DUMP %d(%d) byte = \n"), length, target);

	_data += prefixLength;

	SCChar msg[192] = { '\0', };
	unsigned char* b = const_cast<unsigned char*>(data);

	const int loop = target / 16;
	for (int i = 0; i < loop; ++i)
	{
		SCSPRINTF(msg, 192, SCTEXT("\t%02X %02X %02X %02X %02X %02X %02X %02X %02X %02X %02X %02X %02X %02X %02X %02X\n"),
			b[0], b[1], b[2], b[3], b[4], b[5], b[6], b[7], b[8], b[9], b[10], b[11], b[12], b[13], b[14], b[15]);

		b += 16;

		_data += msg;
	}

	// 나머지 출력
	const int remain = target % 16;
	for (int i = 0; i < remain; ++i, ++b)
	{
		if (i == 0)
		{
			SCSPRINTF(msg, 192, SCTEXT("\t%02X "), *b);
		}
		else
		{
			SCSPRINTF(msg, 192, SCTEXT("%02X "), *b);
		}
		_data += msg;
	}

	return;
}

const SCChar* SCLogFormat::data() const
{
	return _data.c_str();
}

const SCString SCLogFormat::getLevelPrefix(ELogLevel logLevel)
{
	SCString prefixLevel = SCTEXT("");
	switch (logLevel)
	{
	case SC_E_LOG_ERROR:
		prefixLevel = SCTEXT("ERRO ");
		break;
	case SC_E_LOG_WARNING:
		prefixLevel = SCTEXT("WARN ");
		break;
	case SC_E_LOG_INFO:
		prefixLevel = SCTEXT("INFO ");
		break;
	case SC_E_LOG_DEBUG:
		prefixLevel = SCTEXT("DEBU ");
		break;
	default:
		prefixLevel = SCTEXT("UNKN ");
		break;
	}

	return prefixLevel;
}

const SCString SCLogFormat::getTimePrefix()
{
	struct timeb tCurrent;
	ftime(&tCurrent);

	// time_t	tCurrent = time(NULL);
	struct tm tmCurrent;

	SCChar prefixTime[64] = { '\0', };

#if defined(_WIN32) || defined(_WIN64)
	errno_t error = localtime_s(&tmCurrent, &tCurrent.time);
	if (error == 0)
	{
		SCSPRINTF(prefixTime, 64, SCTEXT("[%04d.%02d.%02d %02d:%02d:%02d.%03d] "), tmCurrent.tm_year + 1900,
			tmCurrent.tm_mon + 1,
			tmCurrent.tm_mday,
			tmCurrent.tm_hour,
			tmCurrent.tm_min,
			tmCurrent.tm_sec,
			tCurrent.millitm);
	}
#else
	struct tm* result = localtime_r(&tCurrent.time, &tmCurrent);
	if (result != NULL)
	{
		SCSPRINTF(prefixTime, 64, SCTEXT("[%04d.%02d.%02d %02d:%02d:%02d.%03d] "), tmCurrent.tm_year + 1900,
			tmCurrent.tm_mon + 1,
			tmCurrent.tm_mday,
			tmCurrent.tm_hour,
			tmCurrent.tm_min,
			tmCurrent.tm_sec,
			tCurrent.millitm);
	}
#endif // defined(_WIN32) || defined(_WIN64)

	return SCString(prefixTime);
}

const SCString SCLogFormat::getThreadPrefix()
{
	SCChar prefixThread[32] = { '\0', };
	SCSPRINTF(prefixThread, 32, SCTEXT("[%d|%lu] "), SCThread::pid(), SCThread::tid());

	return SCString(prefixThread);
}