#include "SCSharedMemory.h"

#if defined(_WIN32) || defined(_WIN64)
SCSharedMemoryWIndows::SCSharedMemoryWIndows()
{
}

SCSharedMemoryWIndows::~SCSharedMemoryWIndows()
{
}

int SCSharedMemoryWIndows::open(const char* key, size_t size)
{
	return 0;
}

void SCSharedMemoryWIndows::close()
{
	return;
}

void* SCSharedMemoryWIndows::malloc()
{
	return nullptr;
}

#else
SCSharedMemoryPosix::SCSharedMemoryPosix()
{
}

SCSharedMemoryPosix::~SCSharedMemoryPosix()
{
}

int SCSharedMemoryPosix::open(const char* key, size_t size)
{
	return 0;
}

void SCSharedMemoryPosix::close()
{
	return;
}

void* SCSharedMemoryPosix::malloc()
{
	return nullptr;
}

#endif // defined(_WIN32) || defined(_WIN64)

SCSharedMemory::SCSharedMemory()
{

}

SCSharedMemory::~SCSharedMemory()
{

}

int SCSharedMemory::open(const char* key, size_t size)
{
	return _shm.open(key, size);
}

void SCSharedMemory::close()
{
	_shm.close();
	return;
}

void* SCSharedMemory::malloc()
{
	return _shm.malloc();
}
