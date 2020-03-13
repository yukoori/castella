#ifndef __SCMUTEX_H
#define	__SCMUTEX_H

#if defined(_PTHREAD)
#	include <pthread.h>
#	define	SC_MUTEX_T				pthread_mutex_t*
#	define	SC_MUTEX_CREATOR		pthread_mutex_t()
#	define  SC_MUTEX_DESTRUCTOR		pthread_mutex_destroy
#	define  SC_MUTEX_INIT(X)		pthread_mutex_init(X, 0)
#	define	SC_MUTEX_LOCK			pthread_mutex_lock
#	define  SC_MUTEX_UNLOCK			pthread_mutex_unlock
#elif defined(__SUN__)
#	include <thread.h> 
#	define	SC_MUTEX_T				mutex_t*
#	define	SC_MUTEX_CREATOR		mutex_t()
#	define  SC_MUTEX_DESTRUCTOR		mutex_destroy
#	define  SC_MUTEX_INIT(X)		mutex_init(X, USYNC_THREAD, 0)
#	define	SC_MUTEX_LOCK			mutex_lock
#	define  SC_MUTEX_UNLOCK			mutex_unlock
#elif defined(_WIN32) || defined(_WIN64)
#	include <windows.h>
#	define	SC_MUTEX_T				CRITICAL_SECTION*
#	define	SC_MUTEX_CREATOR		CRITICAL_SECTION()
#	define  SC_MUTEX_DESTRUCTOR		DeleteCriticalSection
#	define  SC_MUTEX_INIT(X)		InitializeCriticalSection(X)
#	define	SC_MUTEX_LOCK			EnterCriticalSection
#	define  SC_MUTEX_UNLOCK			LeaveCriticalSection
#else
#	define	SC_MUTEX_T				int*
#	define	SC_MUTEX_CREATOR		int
#	define  SC_MUTEX_DESTRUCTOR		
#	define  SC_MUTEX_INIT(X)	
#	define	SC_MUTEX_LOCK		
#	define  SC_MUTEX_UNLOCK		
#endif 

class SCMutex
{
public:
	SCMutex()
	{
		m_pMutex = new SC_MUTEX_CREATOR;
		SC_MUTEX_INIT(m_pMutex);
	}
	~SCMutex()
	{
		if (m_pMutex != 0)
		{
			SC_MUTEX_DESTRUCTOR(m_pMutex);
			delete m_pMutex;
		}
		m_pMutex = 0;
	}

	void lock()
	{ 
		SC_MUTEX_LOCK(m_pMutex);
	}
	void unlock()
	{ 
		SC_MUTEX_UNLOCK(m_pMutex);
	}

private:
	SC_MUTEX_T			m_pMutex;
};

class SCMutexMgr
{
public:
	SCMutexMgr(SCMutex& tMutex) 
		: m_tMutex(tMutex)
	{ 
		m_tMutex.lock(); 
	}
	~SCMutexMgr()
	{ 
		m_tMutex.unlock(); 
	}

private:
	SCMutexMgr(const SCMutexMgr& o);
	const SCMutexMgr& operator=(const SCMutexMgr& o);

	SCMutex& m_tMutex;
};

#endif	// !__SCMUTEX_H
