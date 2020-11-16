#ifndef __SCTASK_H
#define	__SCTASK_H

#include "config.h"

#if defined(_WIN32) || defined(WIN64)
#include <windows.h>

class SCTask
{
public:
	SCTask();
	virtual ~SCTask();

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

#elif defined(USE_PTHREAD)
#include <sys/socket.h>
#include <netinet/in.h>
#include <arpa/inet.h>
#include <netdb.h>
#include <unistd.h>
#include <pthread.h>

class SCTask
{
public:
	SCTask();
	virtual ~SCTask();

	virtual int		Open();
	virtual int		Close();

	pthread_t		getHandle();
	unsigned int	getThreadId();

	void	setTimeOut(long nTimeOut);

protected:
	virtual	int svc() = 0;

	pthread_t		_thread;
	unsigned int	_thread_id;

	void* _status;

	unsigned int	_time_out;

private:
	static void* svc_run(void* arg);
};
#endif // defined(_WIN32) || defined(WIN64)

#endif // !__SCTASK_H

