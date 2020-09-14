#ifndef __SCSHAREDMEMORY_H
#define	__SCSHAREDMEMORY_H

#if defined(_WIN32) || defined(_WIN64)
class SCSharedMemoryWIndows
{
public:
	SCSharedMemoryWIndows();
	~SCSharedMemoryWIndows();

	int open(const char* key, size_t size);
	void close();

	void* malloc();

private:

};
#else
class SCSharedMemoryPosix
{
public:
	SCSharedMemoryPosix();
	~SCSharedMemoryPosix();

	int open(const char* key, size_t size);
	void close();

	void* malloc();

private:

};
#endif // defined(_WIN32) || defined(_WIN64)

class SCSharedMemory
{
public:
	SCSharedMemory();
	~SCSharedMemory();

	int open(const char* key, size_t size);
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