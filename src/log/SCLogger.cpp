#include "SCLogger.h"
#include <iostream>

SCLogger::SCLogger()
	: _logLevel(SC_E_LOG_DEBUG)
	, _format(NULL)
	, _bFormatDelete(false)
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

	// stream life cycle does not depend on this class.
	if (_format && _bFormatDelete)
	{
		delete _format;
	}
	_format = NULL;
}

void SCLogger::addStream(SCLogStream* stream)
{
	_stream.push_back(stream);
}

void SCLogger::setFormatSpecifier(const SCLogFormat* format, bool bFormatDelete)
{
	_format = const_cast<SCLogFormat*>(format);
	_bFormatDelete = bFormatDelete;
}

void SCLogger::setLevel(ELogLevel logLevel)
{
	_logLevel = logLevel;
}

void SCLogger::log(ELogLevel logLevel, const SCChar* format, ...)
{
	if (_format == NULL)
	{
		return;
	}

	SCMutexMgr mgr(_mutex);

	va_list argp;
	va_start(argp, format);

	_format->setRecord(logLevel, format, argp);

	va_end(argp);

	print();
}

void SCLogger::hex(ELogLevel logLevel, const unsigned char* data, const int length)
{
	if (!isAvailable(logLevel))
	{
		return;
	}

	if (_format == NULL)
	{
		return;
	}

	SCMutexMgr mgr(_mutex);

	_format->setRecord(logLevel, data, length);

	print();
}

void SCLogger::print()
{
	if (_stream.size() == 0)
	{
		std::cout << _format->data() << std::endl;
		return;
	}

	std::vector<SCLogStream*>::iterator iter_s = _stream.begin();
	std::vector<SCLogStream*>::iterator iter_e = _stream.end();
	for (; iter_s != iter_e; ++iter_s)
	{
		SCLogStream* stream = (*iter_s);
		stream->open();
		stream->print(_format->data());
	}

	return;
}

bool SCLogger::isAvailable(ELogLevel logLevel)
{
	if ((int)logLevel > (int)_logLevel)
	{
		return false;
	}

	return true;
}
