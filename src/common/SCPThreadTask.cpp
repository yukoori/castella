#include "SCPThreadTask.h"

SCPThreadTask::SCPThreadTask()
	: _thread(0)
	, _thread_id(0)
	, _status(NULL)
	, _time_out(1000)
{

}

SCPThreadTask::~SCPThreadTask()
{

}

int SCPThreadTask::Open()
{
	pthread_attr_t _attr;
	if (pthread_attr_init(&_attr) != 0)
	{
		return -1;
	}

	if (pthread_attr_setdetachstate(&_attr, PTHREAD_CREATE_DETACHED) != 0)
	{
		return -1;
	}

	_thread_id = pthread_create(&_thread, NULL, CNCIPMSAbstractThread::svc_run, this);
	if (_thread_id < 0) {
		return -1;
	}

	if (pthread_attr_destroy(&_attr) != 0)
	{
		return -1;
	}

	return 0;
}

void SCPThreadTask::Close()
{
	pthread_join(_thread, &_status);
}

pthread_t SCPThreadTask::getHandle()
{
	return _thread;
}

unsigned int SCPThreadTask::getThreadId()
{
	return pthread_self();
}

void* SCPThreadTask::svc_run(void* arg)
{
	SCPThreadTask* task = (SCPThreadTask*)arg;
	int nRet = task->svc();
	return &nRet;
}
