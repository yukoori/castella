#ifndef __SCLOGFORMAT_H
#define	__SCLOGFORMAT_H

#include "SCLogDefine.h"
#include <functional>

class SCLogFormat
{
public:
	SCLogFormat();
	virtual ~SCLogFormat();

	virtual void setRecord(ELogLevel logLevel, const SCChar* format, va_list argp);
	virtual void setRecord(ELogLevel logLevel, const unsigned char* data, const int length);

	const SCChar* data() const;

	// member functions
	virtual const SCString getLevelPrefix(ELogLevel logLevel);
	virtual const SCString getTimePrefix();
	virtual const SCString getThreadPrefix();

	using CustomFormatter = std::function<void(SCLogFormat* self, SCString& data, ELogLevel level)>;
	void setCustomFormatter(CustomFormatter f);

protected:
	// member values
	SCString	_data;
	CustomFormatter _customFormatter;
};


#endif // !__SCLOGFORMAT_H
