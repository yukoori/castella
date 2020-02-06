#ifndef __SCTHREAD_H
#define __SCTHREAD_H

#if defined(_WIN32) || defined(_WIN64)
#	include <Windows.h>
#	define	SCPID_T			DWORD
#	define	SCTHREAD_T		DWORD
#elif	defined(_PTHREAD)
#	include <pthread.h>
#	include <sys/types.h>
#	include <unistd.h>
#	define	SCPID_T			pid_t
#	define	SCTHREAD_T		pthread_t
#else
#	define	SCPID_T			unsigned int
#	define	SCTHREAD_T		unsigned int
#endif // defined(_WIN32) || defined(_WIN64)


namespace SCThread {
#if defined(_WIN32) || defined(_WIN64)
	SCPID_T pid()
	{
		SCPID_T pid = GetCurrentProcessId();
		return pid;
	}
	SCTHREAD_T tid()
	{
		SCTHREAD_T tid = GetCurrentThreadId();
		return tid;
	}
#else
	SCPID_T pid()
	{
		SCPID_T pid = getpid();
		return pid;
	}
	SCTHREAD_T tid()
	{
		SCTHREAD_T tid = gettid();
		return tid;
	}
#endif // defined(_WIN32) || defined(_WIN64)
}

#endif // !__SCTHREAD_H

