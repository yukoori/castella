#ifndef __SCLOGFORMAT_H
#define	__SCLOGFORMAT_H

#include "SCLogDefine.h"

class SCLogFormat
{
public:
	SCLogFormat();
	virtual ~SCLogFormat();

	virtual void setRecord(ELogLevel logLevel, const SCChar* format, va_list argp);

	const SCChar* data() const;

private:
	SCString	_data;
};


#endif // !__SCLOGFORMAT_H
