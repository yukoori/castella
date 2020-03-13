#include <iostream>

#include "SCLogger.h"
#include "SCFileStream.h"

#include "LogTestTask.h"

int main(int argc, char* argv[])
{
	SCFileStream stream;
	stream.path(SCTEXT(".\\"));
	stream.componet(SCTEXT("dslogtest"));

	SCLogger logger;
	logger.setLevel(ELogLevel::SC_E_LOG_DEBUG);
	logger.addStream(&stream);
	logger.setFormatSpecifier();

	// iostream ���
	// logger.level(DS_E_LOG_DEBUG) << "Test DEBUG String." << 11 << 1.02;

	// �������� ���
	SCLOG(logger, ELogLevel::SC_E_LOG_INFO, SCTEXT("%s"), SCTEXT("Test INFO String."));
	SCLOG(logger, ELogLevel::SC_E_LOG_ERROR, SCTEXT("%s"), SCTEXT("Test ERROR String."));
	SCLOG(logger, ELogLevel::SC_E_LOG_WARNING, SCTEXT("%s"), SCTEXT("Test WARNING String."));

	// multi thread �׽�Ʈ
	std::vector<SCTask<LogTestTask>*> vTask;
	for (int i = 0; i < 10; ++i)
	{
		SCTask<LogTestTask>* pTask = new SCTask<LogTestTask>;
		if (pTask == NULL)
		{
			continue;
		}

		LogTestTask* p = const_cast<LogTestTask*>(reinterpret_cast<const LogTestTask*>(pTask->getObject()));
		if (p == NULL)
		{
			delete pTask;
			pTask = NULL;
			continue;
		}

		p->setLogger(logger);
		p->setSid(i);

		if (pTask->Open() != 0)
		{
			continue;
		}

		vTask.push_back(pTask);
	}

	std::vector<SCTask<LogTestTask>*>::iterator iter_s = vTask.begin();
	std::vector<SCTask<LogTestTask>*>::iterator iter_e = vTask.end();
	for (; iter_s != iter_e; ++iter_s)
	{
		SCTask<LogTestTask>* pTask = (*iter_s);
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
