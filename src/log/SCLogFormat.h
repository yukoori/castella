#ifndef __SCLOGFORMAT_H
#define	__SCLOGFORMAT_H

#include "SCLogDefine.h"

class SCLogFormat
{
public:
	SCLogFormat();
	virtual ~SCLogFormat();

	virtual void setRecord(ELogLevel logLevel, const SCChar* format, va_list argp);
	virtual void setRecord(ELogLevel logLevel, const unsigned char* data, const int length);

	const SCChar* data() const;

protected:
	// member functions
	virtual const SCString getLevelPrefix(ELogLevel logLevel);
	virtual const SCString getTimePrefix();
	virtual const SCString getThreadPrefix();

	// member values
	SCString	_data;
};


#endif // !__SCLOGFORMAT_H
