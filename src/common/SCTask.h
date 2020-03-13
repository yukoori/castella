#ifndef __SCTASK_H
#define	__SCTASK_H

#if defined(_WIN32) || defined(WIN64)
#	include "SCWindowsTask.h"
#elif defined(USE_PTHREAD)
#	include "SCPThreadTask.h"
#endif // defined(_WIN32) || defined(WIN64)

template<class T>
class SCTask
{
public:
	SCTask();
	virtual ~SCTask();

	virtual int Open();
	virtual int Close();

	const T*	getObject() const;
private:
	T*	_task;
};

template<class T>
SCTask<T>::SCTask()
{
	_task = new T;
}

template<class T>
SCTask<T>::~SCTask()
{
	if (_task)
	{
		delete _task;
	}
	_task = NULL;
}

template<class T>
int SCTask<T>::Open()
{
	return _task->Open();
}

template<class T>
int SCTask<T>::Close()
{
	return _task->Close();
}

template<class T>
const T* SCTask<T>::getObject() const
{
	return _task;
}

#endif // !__SCTASK_H

