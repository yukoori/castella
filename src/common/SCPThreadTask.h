#ifndef __SCPTHREADTASK_H
#define	__SCPTHREADTASK_H

#include "config.h"

#include <sys/socket.h>
#include <netinet/in.h>
#include <arpa/inet.h>
#include <netdb.h>
#include <unistd.h>
#include <pthread.h>

class SCPThreadTask
{
public:
	SCPThreadTask();
	virtual ~SCPThreadTask();

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

#endif // __SCPTHREADTASK_H