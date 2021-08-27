#include "SCLogger.h"
#include <iostream>

SCLogger::SCLogger()
	: _logLevel(SC_E_LOG_DEBUG)
{
	_stream.reserve(0);
}

SCLogger::~SCLogger()
{
	if (!_stream.empty())
	{
		std::vector<SCLogStream*>::iterator iter_s = _stream.begin();
		std::vector<SCLogStream*>::iterator iter_e = _stream.end();
		for (; iter_s != iter_e; ++iter_s)
		{
			SCLogStream* stream = (*iter_s);
			if (stream)
			{
				if (stream->isOpen())
				{
					stream->close();
				}
				// stream life cycle does not depend on this class.
				// delete stream;
			}
			(*iter_s) = NULL;
		}
	}
	_stream.clear();
	std::vector<SCLogStream*>().swap(_stream);
}

void SCLogger::addStream(SCLogStream* stream)
{
	_stream.push_back(stream);
}

void SCLogger::setLevel(ELogLevel logLevel)
{
	_logLevel = logLevel;
}

void SCLogger::log(ELogLevel logLevel, const SCChar* format, ...)
{
	if (!isAvailable(logLevel))
	{
		return;
	}

	SCMutexMgr mgr(_mutex);

	std::vector<SCLogStream*>::iterator iter_s = _stream.begin();
	std::vector<SCLogStream*>::iterator iter_e = _stream.end();
	for (; iter_s != iter_e; ++iter_s)
	{
		SCLogStream* stream = (*iter_s);
		if (stream == NULL)
		{
			continue;
		}

		if (stream->open() != 0)
		{
			continue;
		}

		SCLogFormat* logformat = stream->getFormat();
		if (logformat == NULL)
		{
			continue;
		}
		
		va_list argp;
		va_start(argp, format);

		logformat->setRecord(logLevel, format, argp);

		va_end(argp);

		stream->print(logformat->data(), logLevel);
	}
}

void SCLogger::hex(ELogLevel logLevel, const unsigned char* data, const int length)
{
	if (!isAvailable(logLevel))
	{
		return;
	}

	SCMutexMgr mgr(_mutex);

	std::vector<SCLogStream*>::iterator iter_s = _stream.begin();
	std::vector<SCLogStream*>::iterator iter_e = _stream.end();
	for (; iter_s != iter_e; ++iter_s)
	{
		SCLogStream* stream = (*iter_s);
		if (stream == NULL)
		{
			continue;
		}

		if (stream->open() != 0)
		{
			continue;
		}

		SCLogFormat* format = stream->getFormat();
		if (format == NULL)
		{
			continue;
		}

		format->setRecord(logLevel, data, length);
		stream->print(format->data(), logLevel);
	}
}

bool SCLogger::isAvailable(ELogLevel logLevel)
{
	if ((int)logLevel > (int)_logLevel)
	{
		return false;
	}

	return true;
}
