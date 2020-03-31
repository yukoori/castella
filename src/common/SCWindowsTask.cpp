#include "SCTask.h"

SCTask::SCTask()
	: _handle(NULL)
	, _thread_id(0)
	, _time_out(0)
{

}

SCTask::~SCTask()
{

}

int	SCTask::Open()
{
	_handle = (HANDLE)CreateThread(NULL, 0, SCTask::svc_run, this, 0, &_thread_id);
	if (_handle == 0)
	{
		return -1;
	}

	return 0;
}

int SCTask::Close()
{
	if (_time_out == 0)
	{
		::WaitForSingleObject(_handle, INFINITE);
	}
	else
	{
		::WaitForSingleObject(_handle, _time_out);
	}
	
	return ::CloseHandle(_handle) ? 0 : -1;
}

HANDLE SCTask::getHandle()
{
	return _handle; 
}

DWORD SCTask::getThreadId()
{ 
	return _thread_id;
}

void SCTask::setTimeOut(long nTimeOut)
{
	_time_out = nTimeOut;
}

unsigned long WINAPI SCTask::svc_run(void* arg)
{
	SCTask* task = (SCTask*)arg;
	return task->svc();
};