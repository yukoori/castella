#include "SCSharedMemory.h"

#if defined(_WIN32) || defined(_WIN64)
SCSharedMemoryWIndows::SCSharedMemoryWIndows()
	: _file(INVALID_HANDLE_VALUE)
	, _map_file(INVALID_HANDLE_VALUE)
	, _max_size(0)
	, _base_addr(NULL)
{
}

SCSharedMemoryWIndows::~SCSharedMemoryWIndows()
{
	this->close();
}

int SCSharedMemoryWIndows::open(const SCChar* key, size_t size)
{
	if (key == NULL || size < 0)
	{
		return -1;
	}

	_max_size = size;

	_file = CreateFile(key, GENERIC_READ | GENERIC_WRITE, 0, NULL, OPEN_ALWAYS, FILE_ATTRIBUTE_NORMAL, NULL);
	if (_file == NULL)
	{
		// 오류가 발생하였으므로 실패처리
		return -1;
	}

	_map_file = CreateFileMapping(_file, NULL, PAGE_READWRITE, 0, _max_size, NULL);
	if (_map_file == NULL)
	{
		return -1;
	}

	return 0;
}

void SCSharedMemoryWIndows::close()
{
	if (_base_addr)
	{
		UnmapViewOfFile(_base_addr);
	}
	_base_addr = NULL;
	
	if (_map_file != INVALID_HANDLE_VALUE)
	{
		CloseHandle(_map_file);
	}
	_map_file = INVALID_HANDLE_VALUE;

	if (_file != INVALID_HANDLE_VALUE)
	{
		CloseHandle(_file);
	}
	_file = INVALID_HANDLE_VALUE;

	return;
}

void* SCSharedMemoryWIndows::malloc()
{
	if (_base_addr != NULL)
	{
		return _base_addr;
	}

	_base_addr = MapViewOfFile(_map_file, FILE_MAP_ALL_ACCESS, 0, 0, _max_size);
	if (_base_addr == NULL)
	{
		return nullptr;
	}

	return _base_addr;
}

#else
#include <sys/ipc.h>
#include <sys/shm.h>
#include <climits>

SCSharedMemoryPosix::SCSharedMemoryPosix()
	: _id(-1)
	, _max_size(0)
	, _base_addr(NULL)
{

}

SCSharedMemoryPosix::~SCSharedMemoryPosix()
{
	this->close();
}

int SCSharedMemoryPosix::open(const SCChar* key, size_t size)
{
	if (key == NULL || size < 0)
	{
		return -1;
	}

	_max_size = size;

	key_t key_value = atoi(key);
	if (key_value < 0 || key_value > INT_MAX)
	{
		return -1;
	}

	_id = shmget(key_value, _max_size, IPC_CREAT|0664);
	if (_id == -1)
	{
		return -1;
	}

	return 0;
}

void SCSharedMemoryPosix::close()
{
	if (_base_addr)
	{
		shmdt(_base_addr);
	}
	_base_addr = NULL;

	if (_id != -1)
	{
		::close(_id);
	}
	_id = -1;

	return;
}

void* SCSharedMemoryPosix::malloc()
{
	if (_base_addr != NULL)
	{
		return _base_addr;
	}

	_base_addr = shmat(_id, NULL, 0);
	if (_base_addr == NULL)
	{
		_base_addr = NULL;
	}

	return _base_addr;
}

#endif // defined(_WIN32) || defined(_WIN64)

SCSharedMemory::SCSharedMemory()
{

}

SCSharedMemory::~SCSharedMemory()
{

}

int SCSharedMemory::open(const SCChar* key, size_t size)
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
