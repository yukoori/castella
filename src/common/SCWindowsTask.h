#ifndef __SCWINDOWSTASK_H
#define	__SCWINDOWSTASK_H

#include <windows.h>

class SCWindowsTask
{
public:
	SCWindowsTask();
	virtual ~SCWindowsTask();

	virtual int		Open();
	virtual int		Close();

	HANDLE	getHandle();
	DWORD	getThreadId();

	void	setTimeOut(long nTimeOut);

protected:
	virtual	int svc() = 0;

	HANDLE	_handle;
	DWORD	_thread_id;

	DWORD	_time_out;

private:
	static unsigned long WINAPI svc_run(void* arg);
};

#endif // !__SCWINDOWSTASK_H

