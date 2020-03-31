#include "SCOS.h"

namespace SCOS
{
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
