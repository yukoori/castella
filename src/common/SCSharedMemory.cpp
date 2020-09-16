#include "SCSharedMemory.h"

#if defined(_WIN32) || defined(_WIN64)
SCSharedMemoryWIndows::SCSharedMemoryWIndows()
	: _map_file(INVALID_HANDLE_VALUE)
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

	_map_file = OpenFileMapping( FILE_MAP_ALL_ACCESS, FALSE, key);
	if (_map_file != NULL)
	{
		// 이미 생성되어 있으므로 종료
		return 0;
	}

	_map_file = CreateFileMapping( INVALID_HANDLE_VALUE, NULL, PAGE_READWRITE, 0, _max_size, key);
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

	_id = shmget(key, _max_size, IPC_CREATE|0664);
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
		close(_id);
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
	if (_base_addr == -1)
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
