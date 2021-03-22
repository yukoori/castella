#include "SCFileStream.h"

#include <time.h>
#if defined(_WIN32) || defined(_WIN64)
#	include <Windows.h>
#endif // defined(_WIN32) || defined(_WIN64)

SCFileStream::SCFileStream()
	: _output(NULL)
	, _path(SCTEXT(""))
	, _component(SCTEXT(""))
{

}

SCFileStream::~SCFileStream()
{
	close();
	_output = NULL;
}

int SCFileStream::open()
{
	SCString logPath = this->getFileName();
	if (logPath.length() == 0)
	{
		return -1;
	}

	if (!exist(logPath.c_str()))
	{
		close();
	}

	if (this->isOpen())
	{
		return 0;
	}

	_output = new SCOFStream();

	_output->open(logPath.c_str(), std::ios::app);
	if (!_output->good())
	{
		SCPRINTF(SCTEXT("Log File open Failed(%s)\n"), logPath.c_str());
		return -1;
	}

	_open = true;
	return 0;
}

int SCFileStream::close()
{
	if (!this->isOpen())
	{
		// _output에 대한 체크를 하였으나,
		// windows debug버전에서 유효하지 않은 값으로 설정되어 있음.
		// 분명히 NULL로 초기화했는데..뭐지???
		return 0;
	}

	if (_output->is_open())
	{
		_output->close();
	}

	_open = false;
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

void SCFileStream::path(const SCChar* path)
{
	_path = path;

	SCChar lastChar = _path.at(_path.size() - 1);
	if (lastChar != '\\' && lastChar != '/')
	{
#if	defined(_WIN32) || defined(_WIN64)
		_path += SCTEXT("\\");
#else
		_path += "/";
#endif	// defined(_WIN32) || defined(_WIN64)
	}

	create_directory(_path.c_str());
}

const SCChar* SCFileStream::path() const
{
	return _path.c_str();
}

void SCFileStream::componet(const SCChar* component)
{
	_component = component;
}

const SCChar* SCFileStream::componet() const
{
	return _component.c_str();
}

const SCString SCFileStream::getFileName() const
{
	SCString fileName = SCTEXT("");

	time_t	tCurrent = time(NULL);
	struct tm tmCurrent;

#if defined(_WIN32) || defined(_WIN64)
	errno_t error = localtime_s(&tmCurrent, &tCurrent);
	if (error != 0)
	{
		SCPRINTF(SCTEXT("Fail to get localtime for log file.\n"));
		return fileName;
	}
#else
	struct tm* result = localtime_r(&tCurrent, &tmCurrent);
	if (result == NULL)
	{
		SCPRINTF(SCTEXT("Fail to get localtime for log file.\n"));
		return fileName;
	}
#endif // defined(_WIN32) || defined(_WIN64)

	SCChar	logPath[1024] = { '\0', };
	SCSPRINTF(logPath, 1024, SCTEXT("%s%s.%04d%02d%02d.log"), _path.c_str(), _component.c_str(),
																tmCurrent.tm_year + 1900,
																tmCurrent.tm_mon + 1,
																tmCurrent.tm_mday);
	fileName = logPath;
	return fileName;
}

void SCFileStream::create_directory(const SCChar* path)
{
	if (SCACCESS(path, 0) != -1)
	{
		return ;
	}

	SCChar currentPath[256] = {'\0',};

	SCChar* p = const_cast<SCChar*>(path);
	SCChar* q = currentPath;
	while( *p )
	{
		if( ('\\' == *p) || ('/' == *p) )
		{
			if ( ':' != *(p-1) )
			{
				SCMKDIR(currentPath);
			}
		}
		*q++ = *p++;
		*q = '\0';
	}

	SCMKDIR(currentPath);
	return;
}

bool SCFileStream::exist(const SCChar* path)
{
#if defined(_WIN32) || defined(_WIN64)
	if (0 == _access(path, 0))
#else
	if (0 == access(path, 0))
#endif	// defined(_WIN32) || defined(_WIN64)
	{
		return true;
	}

	return false;
}