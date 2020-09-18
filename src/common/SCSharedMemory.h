#ifndef __SCSHAREDMEMORY_H
#define	__SCSHAREDMEMORY_H

#include "SCTypes.h"

#if defined(_WIN32) || defined(_WIN64)
#include <windows.h>
class SCSharedMemoryWIndows
{
public:
	SCSharedMemoryWIndows();
	~SCSharedMemoryWIndows();

	int open(const SCChar* key, size_t size);
	void close();

	void* malloc();

private:
	HANDLE	_file;
	HANDLE	_map_file;
	size_t	_max_size;

	void*	_base_addr;
};
#else
class SCSharedMemoryPosix
{
public:
	SCSharedMemoryPosix();
	~SCSharedMemoryPosix();

	int open(const SCChar* key, size_t size);
	void close();

	void* malloc();

private:
	int		_id;
	int		_max_size;

	void*	_base_addr;
};
#endif // defined(_WIN32) || defined(_WIN64)

class SCSharedMemory
{
public:
	SCSharedMemory();
	~SCSharedMemory();

	int open(const SCChar* key, size_t size);
	void close();

	void* malloc();

protected:
private:
#if defined(_WIN32) || defined(_WIN64)
	SCSharedMemoryWIndows	_shm;
#else
	SCSharedMemoryPosix		_shm;
#endif // defined(_WIN32) || defined(_WIN64)
};

#endif	//!__SCSHAREDMEMORY_H