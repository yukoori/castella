#include <iostream>

#include "SCLogger.h"
#include "SCFileStream.h"

#include "LogTestTask.h"

int main(int argc, char* argv[])
{
	SCFileStream stream;
#if defined(_WIN32) || defined(_WIN64)
	stream.path(SCTEXT(".\\"));
#else	// defined(_WIN32) || defined(_WIN64)
	stream.path(SCTEXT("./"));
#endif	// defined(_WIN32) || defined(_WIN64)
	stream.componet(SCTEXT("dslogtest"));

	SCLogger logger;
	logger.setLevel(ELogLevel::SC_E_LOG_DEBUG);
	logger.addStream(&stream);
	logger.setFormatSpecifier();

	// iostream 방식
	// logger.level(DS_E_LOG_DEBUG) << "Test DEBUG String." << 11 << 1.02;

	// 가변인자 방식
	SCLOG(logger, ELogLevel::SC_E_LOG_INFO, SCTEXT("%s"), SCTEXT("Test INFO String."));
	SCLOG(logger, ELogLevel::SC_E_LOG_ERROR, SCTEXT("%s"), SCTEXT("Test ERROR String."));
	SCLOG(logger, ELogLevel::SC_E_LOG_WARNING, SCTEXT("%s"), SCTEXT("Test WARNING String."));

	// multi thread 테스트
	std::vector<LogTestTask*> vTask;
	for (int i = 0; i < 10; ++i)
	{
		LogTestTask* pTask = new LogTestTask;
		if (pTask == NULL)
		{
			continue;
		}

		pTask->setLogger(logger);
		pTask->setSid(i);

		if (pTask->Open() != 0)
		{
			continue;
		}

		vTask.push_back(pTask);
	}

	std::vector<LogTestTask*>::iterator iter_s = vTask.begin();
	std::vector<LogTestTask*>::iterator iter_e = vTask.end();
	for (; iter_s != iter_e; ++iter_s)
	{
		LogTestTask* pTask = (*iter_s);
		if (pTask == NULL)
		{
			continue;
		}

		SCLOG(logger, ELogLevel::SC_E_LOG_INFO, SCTEXT("==============> Start Close Thread!!!"));
		pTask->Close(); 
		SCLOG(logger, ELogLevel::SC_E_LOG_INFO, SCTEXT("==============> End Close Thread!!!"));
		delete (*iter_s);
		SCLOG(logger, ELogLevel::SC_E_LOG_INFO, SCTEXT("==============> Delete Object!!!"));
	}
	vTask.clear();

	return 0;
}
