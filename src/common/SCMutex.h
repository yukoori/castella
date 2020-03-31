#ifndef __SCMUTEX_H
#define	__SCMUTEX_H

#include "SCThread.h"

class SCMutex
{
public:
	SCMutex()
	{
		_mutex = new SC_MUTEX_CREATOR;
		SC_MUTEX_INIT(_mutex);
	}
	~SCMutex()
	{
		if (_mutex != 0)
		{
			SC_MUTEX_DESTRUCTOR(_mutex);
			delete _mutex;
		}
		_mutex = 0;
	}

	void lock()
	{ 
		SC_MUTEX_LOCK(_mutex);
	}
	void unlock()
	{ 
		SC_MUTEX_UNLOCK(_mutex);
	}

private:
	SC_MUTEX_T			_mutex;
};

class SCMutexMgr
{
public:
	SCMutexMgr(SCMutex& mutex) 
		: _mutex(mutex)
	{ 
		_mutex.lock();
	}
	~SCMutexMgr()
	{ 
		_mutex.unlock();
	}

private:
	SCMutexMgr(const SCMutexMgr& o);
	const SCMutexMgr& operator=(const SCMutexMgr& o);

	SCMutex& _mutex;
};

#endif	// !__SCMUTEX_H
