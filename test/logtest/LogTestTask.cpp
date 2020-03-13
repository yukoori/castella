#include "LogTestTask.h"

#include "SCOS.h"

LogTestTask::LogTestTask()
	: _logger(NULL)
	, _sid(0)
{

}

LogTestTask::~LogTestTask()
{

}

void LogTestTask::setLogger(SCLogger& logger)
{
	_logger = &logger;
}

void LogTestTask::setSid(int sid)
{
	_sid = sid;
}

int LogTestTask::svc()
{
	if (_logger == NULL)
	{
		return 0;
	}

	for (int i = 0; i < 100; ++i)
	{
		SCOS::sleep(_sid * 100);

		SCLOG((*_logger), ELogLevel::SC_E_LOG_INFO, SCTEXT("(%d) %s"), _sid, SCTEXT("Test INFO String."));
		SCLOG((*_logger), ELogLevel::SC_E_LOG_ERROR, SCTEXT("(%d) %s"), _sid, SCTEXT("Test ERROR String."));
		SCLOG((*_logger), ELogLevel::SC_E_LOG_WARNING, SCTEXT("(%d) %s"), _sid, SCTEXT("Test WARNING String."));
	}

	return 0;
}