#ifndef __SCTHREAD_H
#define __SCTHREAD_H

#if defined(USE_PTHREAD)
#	include <pthread.h>
#	include <sys/types.h>
#	include <unistd.h>
#	define	SC_MUTEX_T				pthread_mutex_t*
#	define	SC_MUTEX_CREATOR		pthread_mutex_t()
#	define  SC_MUTEX_DESTRUCTOR		pthread_mutex_destroy
#	define  SC_MUTEX_INIT(X)		pthread_mutex_init(X, 0)
#	define	SC_MUTEX_LOCK			pthread_mutex_lock
#	define  SC_MUTEX_UNLOCK			pthread_mutex_unlock
#	define	SC_PID_T				pid_t
#	define	SC_THREAD_T				pthread_t
#elif defined(__SUN__)
#	include <thread.h> 
#	define	SC_MUTEX_T				mutex_t*
#	define	SC_MUTEX_CREATOR		mutex_t()
#	define  SC_MUTEX_DESTRUCTOR		mutex_destroy
#	define  SC_MUTEX_INIT(X)		mutex_init(X, USYNC_THREAD, 0)
#	define	SC_MUTEX_LOCK			mutex_lock
#	define  SC_MUTEX_UNLOCK			mutex_unlock
#	define	SC_PID_T				unsigned int
#	define	SC_THREAD_T				unsigned int
#elif defined(_WIN32) || defined(_WIN64)
#	include <windows.h>
#	define	SC_MUTEX_T				CRITICAL_SECTION*
#	define	SC_MUTEX_CREATOR		CRITICAL_SECTION()
#	define  SC_MUTEX_DESTRUCTOR		DeleteCriticalSection
#	define  SC_MUTEX_INIT(X)		InitializeCriticalSection(X)
#	define	SC_MUTEX_LOCK			EnterCriticalSection
#	define  SC_MUTEX_UNLOCK			LeaveCriticalSection
#	define	SC_PID_T				DWORD
#	define	SC_THREAD_T				DWORD
#else
#	define	SC_MUTEX_T				int*
#	define	SC_MUTEX_CREATOR		int
#	define  SC_MUTEX_DESTRUCTOR		
#	define  SC_MUTEX_INIT(X)	
#	define	SC_MUTEX_LOCK		
#	define  SC_MUTEX_UNLOCK		
#	define	SC_PID_T				unsigned int
#	define	SC_THREAD_T				unsigned int
#endif 

namespace SCThread
{
#if defined(_WIN32) || defined(_WIN64)
	SC_PID_T pid();
	SC_THREAD_T tid();
#else
	SC_PID_T pid();
	SC_THREAD_T tid();
#endif // defined(_WIN32) || defined(_WIN64)
}

#endif // !__SCTHREAD_H

