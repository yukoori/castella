#include "SCFileStream.h"

#include <time.h>
#include <Windows.h>

SCFileStream::SCFileStream()
	: _output(NULL)
{

}

SCFileStream::~SCFileStream()
{
	close();
	_output = NULL;
}

int SCFileStream::open()
{
	if (this->isOpen())
	{
		return 0;
	}

	_output = new SCOFStream();

	time_t	tCurrent = time(NULL);
	struct tm tmCurrent;
	
	errno_t error = localtime_s(&tmCurrent, &tCurrent);
	if (error != 0)
	{
		SCPRINTF(SCTEXT("Fail to get localtime for log file.\n"));
		return -1;
	}

	SCChar	logPath[1024] = { '\0', };
	SCSPRINTF(logPath, 1024, SCTEXT("%s%s.%04d%02d%02d.log"), _path.c_str(), _component.c_str(),
														 tmCurrent.tm_year + 1900, 
														 tmCurrent.tm_mon + 1,
														 tmCurrent.tm_mday);

	_output->open(logPath, std::ios::app);
	if (!_output->good())
	{
		SCPRINTF(SCTEXT("Log File open Failed(%s)\n"), logPath);
		return -1;
	}

	_open = true;
	return 0;
}

int SCFileStream::close()
{
	if (_output == NULL)
	{
		return 0;
	}

	if (_output->is_open())
	{
		_output->close();
	}

	return 0;
}

void SCFileStream::print(const SCChar* record)
{
	if (_output->good()) 
	{
		*_output << record;
		*_output << std::endl;
	}
}

void SCFileStream::path(const SCChar* pPath)
{
	_path = pPath;
}

const SCChar* SCFileStream::path() const
{
	return _path.c_str();
}

void SCFileStream::componet(const SCChar* pComponent)
{
	_component = pComponent;
}

const SCChar* SCFileStream::componet() const
{
	return _component.c_str();
}