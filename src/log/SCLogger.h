#ifndef __SCLOGGER_H
#define __SCLOGGER_H

#include "SCLogDefine.h"
#include "SCLogStream.h"
#include "SCLogFormat.h"

#include <cstdarg>
#include <vector>
#include <string>

class SCLogger
{
public:
	SCLogger();
	~SCLogger();

	//
	friend const SCLogger& operator<<(const SCLogger& in, const SCChar* pszData);
	friend const SCLogger& operator<<(const SCLogger& in, SCString strData);
	friend const SCLogger& operator<<(const SCLogger& in, int n);
	friend const SCLogger& operator<<(const SCLogger& in, double d);

	// functions
	void setLevel(ELogLevel logLevel);
	const SCLogger& level(ELogLevel logLevel);

	void addStream(SCLogStream* stream);
	void setFormatSpecifier(const SCLogFormat* format = new SCLogFormat, bool bFormatDelete = true);

	void log(ELogLevel logLevel, const SCChar* format, ...);
	
protected:
private:
	// member values
	std::vector<SCLogStream*>	_stream;
	SCLogFormat*				_format;
	bool						_bFormatDelete;
	ELogLevel					_logLevel;
};

#include "SCLogger.inl"

#endif // !__SCLOGGER_H