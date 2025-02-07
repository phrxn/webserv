#include "../../../../libs/googletest/googlemock/include/gmock/gmock.h"
#include "../../../../libs/googletest/googletest/include/gtest/gtest.h"
#include "ParentExecuteProcessCGI.hpp"

class SystemCallsMockToParent : public SystemCalls {
 public:
  MOCK_METHOD(error::StatusOr<pid_t>, waitpid,
              (pid_t pid, int *stat_loc, int options), (const override));

  MOCK_METHOD(error::StatusOr<int>, kill, (pid_t pid, int sig),
              (const override));
};

class LogMockToParent : public Log {
 public:
  MOCK_METHOD(void, log,
              (LogLevel level, const std::string &clazzName,
               const std::string &methodName, const std::string &message,
               const std::string &details),
              (override));

  MOCK_METHOD(void, log,
              (LogLevel level, const std::string &clazzName,
               const std::string &methodName, const std::string &message,
               int details),
              (override));
};


TEST(ParentExecuteProcessCGITest, execute_killSystemCallError) {
  SystemCallsMockToParent *sysCall = new SystemCallsMockToParent;
  EXPECT_CALL(*sysCall, kill(testing::_, testing::_))
      .WillOnce(testing::Return(
          error::Status(error::Status::SystemCall, "kill error")));

  LogMockToParent *log = new LogMockToParent;
  EXPECT_CALL(*log, log(Log::ERROR, "ParentExecuteProcessCGI", "execute", std::string("kill error"), 42)).Times(1);

  ParentExecuteProcessCGI parent(42, -1);
  parent.setSystemCalls(sysCall);
  parent.setLogger(log);

  ExecuteProcessCGI::ExitStatus status = parent.execute();
  EXPECT_EQ(ExecuteProcessCGI::PARENT_ERROR, status);

  delete log;
}

TEST(ParentExecuteProcessCGITest, execute_waitpidSystemCallError) {
  SystemCallsMockToParent *sysCall = new SystemCallsMockToParent;
  EXPECT_CALL(*sysCall, waitpid(testing::_, testing::_, testing::_))
	  .WillOnce(testing::Return(
		  error::Status(error::Status::SystemCall, "waitpid error")));
  LogMockToParent *log = new LogMockToParent;
  EXPECT_CALL(*log, log(Log::ERROR, "ParentExecuteProcessCGI", "execute", std::string("waitpid error"), 42)).Times(1);

  ParentExecuteProcessCGI parent(42, 100000);
  parent.setSystemCalls(sysCall);
  parent.setLogger(log);

  ExecuteProcessCGI::ExitStatus status = parent.execute();
  EXPECT_EQ(ExecuteProcessCGI::PARENT_ERROR, status);

  delete log;
}


//
//
//
// -----------------------------------------------------------------------
// ======================= Integration Tests =============================
// -----------------------------------------------------------------------

// Test if the child EXIT WAS OK (value 0)
TEST(ParentExecuteProcessCGITest, execute_ChildReturn0) {
  SystemCalls systemCalls;

  error::StatusOr<pid_t> pid = systemCalls.fork();

  if (!pid.ok()) {
    FAIL() << "Fork failed";
  }
  pid_t thePid = pid.value();
  if (thePid == 0) {
    exit(0);
  } else {
    ParentExecuteProcessCGI parentExecuteProcessCGI(thePid, 3);
    ExecuteProcessCGI::ExitStatus status = parentExecuteProcessCGI.execute();
    EXPECT_EQ(ExecuteProcessCGI::CHILD_EXIT_OK, status);
  }
}

// Test if the child EXIT WAS A FAILURE (value different from 0)
TEST(ParentExecuteProcessCGITest, execute_ChildReturnAValueDifferentOf0) {
  SystemCalls systemCalls;

  error::StatusOr<pid_t> pid = systemCalls.fork();

  if (!pid.ok()) {
    FAIL() << "Fork failed";
  }
  pid_t thePid = pid.value();
  if (thePid == 0) {
    exit(1);
  } else {
    ParentExecuteProcessCGI parentExecuteProcessCGI(thePid, 3);
    ExecuteProcessCGI::ExitStatus status = parentExecuteProcessCGI.execute();
    EXPECT_EQ(ExecuteProcessCGI::CHILD_EXIT_WITH_ERROR, status);
  }
}

// Test if the child EXIT BY KILL (Timeout)
// In this test we will run a child process that never ends! And we will kill it
// because of the timeout!
TEST(ParentExecuteProcessCGITest, execute_testKillByTimeout) {

  LogMockToParent *logMock = new LogMockToParent;
  EXPECT_CALL(*logMock, log(Log::ERROR, "ParentExecuteProcessCGI", "execute", "the CGI child process took too long to execute", ::testing::A<int>())).Times(1);

  SystemCalls systemCalls;

  error::StatusOr<pid_t> pid = systemCalls.fork();

  Time time;

  std::time_t startTime = time.getCurrentTime();

  if (!pid.ok()) {
    FAIL() << "Fork failed";
  }
  pid_t thePid = pid.value();
  if (thePid == 0) {
    while (true) {
      // Do nothing
    }
    exit(1);
  } else {
    ParentExecuteProcessCGI parentExecuteProcessCGI(thePid, 3);
	parentExecuteProcessCGI.setLogger(logMock);
    ExecuteProcessCGI::ExitStatus status = parentExecuteProcessCGI.execute();
    EXPECT_EQ(ExecuteProcessCGI::CHILD_FINISHED_BY_SIGNAL, status);
  }

  delete logMock;

  // check if the time is greater than 3 seconds
  EXPECT_TRUE(time.isTimeOut(startTime, 3));
}