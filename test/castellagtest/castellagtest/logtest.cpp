#include "pch.h"

#include "SCFileStream.h"
#include "SCLogFormat.h"
#include "SCLogger.h"

#include <cstdarg>

TEST(TestLog, TestSCFileStream)
{
    // 1. ���ϸ� �ڵ� ����
    // 2. ���� ��Ʈ�� ����
    // 3. ���Ͽ� ������ ����

    SCFileStream stream;
    stream.path(SCTEXT(".\\"));
    EXPECT_STREQ(stream.path(), SCTEXT(".\\"));

    stream.componet(SCTEXT("logtest"));
    EXPECT_STREQ(stream.componet(), SCTEXT("logtest"));

    SCString strFileName = stream.getFileName();
    EXPECT_FALSE(strFileName.length() == 0);
  
    EXPECT_EQ(stream.open(), 0);
    EXPECT_TRUE(stream.isOpen());

    // todo :: stream check!!!
    // using mock???
    stream.print(SCTEXT("TEST LOG ��� Ȯ��!!!"));
}

void LogFormatTest(const SCChar* formatString, ...)
{
    va_list param;
    va_start(param, formatString);

    SCLogFormat format;
    format.setRecord(ELogLevel::SC_E_LOG_WARNING, formatString, param);

    va_end(param);

    EXPECT_STRNE(format.data(), SCTEXT(""));
}

TEST(TestLog, TestSCLogFormat)
{
    // 1. ��� ��Ʈ�� ����
    LogFormatTest(SCTEXT("TEST STRING = %s %s"), SCTEXT("Test1"), SCTEXT("Test2"));
}

TEST(TestLog, TestSCLogger)
{
    SCFileStream filestream;
    filestream.path(SCTEXT(".\\"));
    filestream.componet(SCTEXT("logtest"));

    SCLogger logger;
    logger.setLevel(ELogLevel::SC_E_LOG_DEBUG);
    logger.addStream(&filestream);
    logger.setFormatSpecifier();

    SCLOG(logger, ELogLevel::SC_E_LOG_WARNING, SCTEXT("%s"), SCTEXT("Test WARNING String."));
}