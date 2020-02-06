#include <iostream>

#include "SCLogger.h"
#include "SCFileStream.h"

int main(int argc, char* argv[])
{
	SCFileStream stream;
	stream.path(SCTEXT(".\\"));
	stream.componet(SCTEXT("dslogtest"));

	SCLogger logger;
	logger.setLevel(ELogLevel::SC_E_LOG_DEBUG);
	logger.addStream(&stream);
	logger.setFormatSpecifier();

	// iostream 방식
	// logger.level(DS_E_LOG_DEBUG) << "Test DEBUG String." << 11 << 1.02;

	// 가변인자 방식
	SCLOG(logger, ELogLevel::SC_E_LOG_INFO, SCTEXT("%s"), SCTEXT("Test INFO String."));
	SCLOG(logger, ELogLevel::SC_E_LOG_ERROR, SCTEXT("%s"), SCTEXT("Test ERROR String."));
	SCLOG(logger, ELogLevel::SC_E_LOG_WARNING, SCTEXT("%s"), SCTEXT("Test WARNING String."));

	return 0;
}
