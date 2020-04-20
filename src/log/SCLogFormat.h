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

private:
	// member functions
	const SCString getLevelPrefix(ELogLevel logLevel);
	const SCString getTimePrefix();
	const SCString getThreadPrefix();

	// member values
	SCString	_data;
};


#endif // !__SCLOGFORMAT_H
