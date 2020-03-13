#ifndef __SCOS_H
#define	__SCOS_H

#if defined(_WIN32) || defined(_WIN64)
#	include <Windows.h>
#else
#	include <unistd.h>
#endif // defined(_WIN32) || defined(_WIN64)

namespace SCOS {
#if defined(_WIN32) || defined(_WIN64)
	void sleep(int ms)
	{
		Sleep(ms);
	}
#else
	void sleep(int ms)
	{
		usleep(ms * 1000);
	}
#endif // defined(_WIN32) || defined(_WIN64)
}

#endif // !__SCOS_H
