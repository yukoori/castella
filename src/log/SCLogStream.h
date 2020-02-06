#ifndef __SCLOGSTREAM_H
#define	__SCLOGSTREAM_H

#include "SCLogDefine.h"

class SCLogStream
{
public:
	SCLogStream()
		: _open(false)
	{

	}
	virtual ~SCLogStream()
	{
		_open = false;
	}

	// virtual function
	virtual int open() = 0;
	virtual int close() = 0;

	virtual void print(const SCChar* record) = 0;

	// member function
	bool	isOpen() 
	{
		return _open;
	}

protected:
	bool	_open;
};

#endif // !__SCLOGSTREAM_H
