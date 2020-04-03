#include "SCThread.h"

namespace SCThread 
{
#if defined(_WIN32) || defined(_WIN64)
	SC_PID_T pid()
	{
		SC_PID_T pid = GetCurrentProcessId();
		return pid;
	}
	SC_THREAD_T tid()
	{
		SC_THREAD_T tid = GetCurrentThreadId();
		return tid;
	}
#else
	SC_PID_T pid()
	{
		SC_PID_T pid = getpid();
		return pid;
	}
	SC_THREAD_T tid()
	{
		SC_THREAD_T tid = pthread_self();
		return tid;
	}
#endif // defined(_WIN32) || defined(_WIN64)
}

