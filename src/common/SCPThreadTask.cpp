#include "SCTask.h"

SCTask::SCTask()
	: _thread(0)
	, _thread_id(0)
	, _status(NULL)
	, _time_out(0)
{

}

SCTask::~SCTask()
{

}

int SCTask::Open()
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

	_thread_id = pthread_create(&_thread, NULL, SCTask::svc_run, this);
	if (_thread_id < 0) {
		return -1;
	}

	if (pthread_attr_destroy(&_attr) != 0)
	{
		return -1;
	}

	return 0;
}

int SCTask::Close()
{	
	return pthread_join(_thread, &_status);
}

pthread_t SCTask::getHandle()
{
	return _thread;
}

unsigned int SCTask::getThreadId()
{
	return pthread_self();
}

void* SCTask::svc_run(void* arg)
{
	SCTask* task = (SCTask*)arg;
	int nRet = task->svc();
	return &nRet;
}
