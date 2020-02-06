#include "SCWindowsTask.h"

SCWindowsTask::SCWindowsTask()
	: _handle(NULL)
	, _thread_id(0)
	, _time_out(1000)
{

}

SCWindowsTask::~SCWindowsTask()
{

}

int	SCWindowsTask::Open()
{
	_handle = (HANDLE)CreateThread(NULL, 0, SCWindowsTask::svc_run, this, 0, &_thread_id);
	if (_handle == 0)
	{
		return -1;
	}
	return 0;
}

void SCWindowsTask::Close()
{
	if (_time_out == 0)
	{
		::WaitForSingleObject(_handle, INFINITE);
	}
	else
	{
		::WaitForSingleObject(_handle, _time_out);
	}
	::CloseHandle(_handle);
}

HANDLE SCWindowsTask::getHandle()
{
	return _handle; 
}

DWORD SCWindowsTask::getThreadId()
{ 
	return _thread_id;
}

void SCWindowsTask::setTimeOut(long nTimeOut)
{
	_time_out = nTimeOut;
}

unsigned long WINAPI SCWindowsTask::svc_run(void* arg)
{
	SCWindowsTask* task = (SCWindowsTask*)arg;
	return task->svc();
};