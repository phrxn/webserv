#include <string>

#include "../../libs/googletest/googlemock/include/gmock/gmock.h"
#include "../../libs/googletest/googletest/include/gtest/gtest.h"
#include "../time/Time.hpp"
#include "LogWriter.hpp"

namespace LogWriterTest {

class TimeMock : public Time {
 public:
  MOCK_METHOD(std::string, getTimeToLog, (), (const override));
};

class Concreate1LogWriter : public LogWriter {
 public:
  Concreate1LogWriter(Time *time, std::string &toWrite)
      : LogWriter(time), _toWrite(toWrite){};

  // the implement MUST save the log string
  void writeLog(const std::string &formattedLog) { _toWrite = formattedLog; }

  std::string getLogLevelString(LogLevel level) {
    return LogWriter::logToString(level);
  }

 private:
  std::string &_toWrite;
};

TEST(LogWriterTest, log_simpleValidLogWithContext) {
  TimeMock *timeMock = new TimeMock;

  EXPECT_CALL(*timeMock, getTimeToLog())
      .WillRepeatedly(::testing::Return("2000-01-02 03:04:05"));

  std::string toWriteAndCompare;
  Concreate1LogWriter cLog(timeMock, toWriteAndCompare);

  cLog.log(Log::DEBUG, "Clazz", "Method", "message", "details");

  std::string expectedLogStrig(
      "[2000-01-02 03:04:05] [DEBUG] [Clazz] [Method] message (details)\n");
  EXPECT_EQ(expectedLogStrig, toWriteAndCompare);
}

TEST(LogWriterTest, log_simpleValidLogWithoutContext) {
  TimeMock *timeMock = new TimeMock;

  EXPECT_CALL(*timeMock, getTimeToLog())
      .WillRepeatedly(::testing::Return("2000-01-02 03:04:05"));

  std::string toWriteAndCompare;
  Concreate1LogWriter cLog(timeMock, toWriteAndCompare);

  cLog.log(Log::DEBUG, "Clazz", "Method", "message", "");

  std::string expectedLogStrig(
      "[2000-01-02 03:04:05] [DEBUG] [Clazz] [Method] message\n");
  EXPECT_EQ(expectedLogStrig, toWriteAndCompare);
}

}  // namespace LogWriterTest