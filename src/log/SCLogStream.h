#ifndef __SCLOGSTREAM_H
#define	__SCLOGSTREAM_H

#include "SCLogDefine.h"
#include "SCLogFormat.h"

class SCLogStream
{
public:
	SCLogStream()
		: _format(NULL)
		, _format_delete(false)
		, _open(false)
	{

	}
	virtual ~SCLogStream()
	{
		if (_format && _format_delete)
		{
			delete _format;
		}
		_format = NULL;

		_open = false;
	}

	// virtual function
	virtual int open() = 0;
	virtual int close() = 0;

	virtual void print(const SCChar* record, ELogLevel level) = 0;

	// member function
	void setFormatSpecifier(const SCLogFormat* format = new SCLogFormat, bool format_delete = true)
	{
		_format = const_cast<SCLogFormat*>(format);
		_format_delete = format_delete;
	}
	SCLogFormat* getFormat() const { return _format; }

	bool	isOpen() 
	{
		return _open;
	}

protected:
	SCLogFormat*	_format;
	bool			_format_delete;
	bool			_open;
};

#endif // !__SCLOGSTREAM_H
