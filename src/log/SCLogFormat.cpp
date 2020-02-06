#include "SCLogFormat.h"
#include "SCThread.h"

#include <time.h>
#include <Windows.h>

SCLogFormat::SCLogFormat()
{

}

SCLogFormat::~SCLogFormat()
{

}

void SCLogFormat::setRecord(ELogLevel logLevel, const SCChar* format, va_list argp)
{
	SCString prefixLevel;
	switch (logLevel)
	{
	case ELogLevel::SC_E_LOG_ERROR:
		prefixLevel = SCTEXT("ERRO ");
		break;
	case ELogLevel::SC_E_LOG_WARNING:
		prefixLevel = SCTEXT("WARN ");
		break;
	case ELogLevel::SC_E_LOG_INFO:
		prefixLevel = SCTEXT("INFO ");
		break;
	case ELogLevel::SC_E_LOG_DEBUG:
		prefixLevel = SCTEXT("DEBU ");
		break;
	default:
		prefixLevel = SCTEXT("UNKN ");
		break;
	}

	time_t	tCurrent = time(NULL);
	struct tm tmCurrent;

	SCChar prefixTime[64] = { '\0', };
	errno_t error = localtime_s(&tmCurrent, &tCurrent);
	if (error == 0)
	{
		SCSPRINTF(prefixTime, 64, SCTEXT("[%04d.%02d.%02d %02d:%02d:%02d] "), tmCurrent.tm_year + 1900,
																			  tmCurrent.tm_mon + 1,
																			  tmCurrent.tm_mday,
																			  tmCurrent.tm_hour,
																			  tmCurrent.tm_min,
																			  tmCurrent.tm_sec);
	}

	// 
	SCChar prefixThread[32] = { '\0', };
	SCSPRINTF(prefixThread, 32, SCTEXT("[%d|%d] "), SCThread::pid(), SCThread::tid());

	SCChar buffer[2048] = { '\0', };
	SCVSPRINTF(buffer, format, argp);

	_data  = prefixLevel;
	_data += prefixTime;
	_data += prefixThread;
	_data += buffer;

	return;
}

const SCChar* SCLogFormat::data() const
{
	return _data.c_str();
}

