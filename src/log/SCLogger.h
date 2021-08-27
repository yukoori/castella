#ifndef __SCLOGGER_H
#define __SCLOGGER_H

#include "SCLogStream.h"
#include "SCMutex.h"

#include <cstdarg>
#include <vector>
#include <string>

class SCLogger
{
public:
	SCLogger();
	virtual ~SCLogger();

// 	//
// 	friend const SCLogger& operator<<(const SCLogger& in, const SCChar* pszData);
// 	friend const SCLogger& operator<<(const SCLogger& in, SCString strData);
// 	friend const SCLogger& operator<<(const SCLogger& in, int n);
// 	friend const SCLogger& operator<<(const SCLogger& in, double d);

	// functions
	virtual void setLevel(ELogLevel logLevel);
	virtual void addStream(SCLogStream* stream);

	virtual void log(ELogLevel logLevel, const SCChar* format, ...);
	virtual void hex(ELogLevel logLevel, const unsigned char* data, const int length);
	
protected:
	bool isAvailable(ELogLevel logLevel);

private:
	// member values
	std::vector<SCLogStream*>	_stream;
	ELogLevel					_logLevel;

	SCMutex						_mutex;
};

// #include "SCLogger.inl"

#endif // !__SCLOGGER_H
