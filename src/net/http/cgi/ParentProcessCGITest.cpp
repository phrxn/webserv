#include "../../../../libs/googletest/googlemock/include/gmock/gmock.h"
#include "../../../../libs/googletest/googletest/include/gtest/gtest.h"
#include "ParentProcessCGI.hpp"

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


TEST(ParentProcessCGITest, execute_killSystemCallError) {
  SystemCallsMockToParent *sysCall = new SystemCallsMockToParent;
  EXPECT_CALL(*sysCall, kill(testing::_, testing::_))
      .WillOnce(testing::Return(
          error::Status(error::Status::SystemCall, "kill error")));

  LogMockToParent *log = new LogMockToParent;
  EXPECT_CALL(*log, log(Log::ERROR, "ParentProcessCGI", "execute", std::string("kill error"), 42)).Times(1);

  ParentProcessCGI parent(42, -1);
  parent.setSystemCalls(sysCall);
  parent.setLogger(log);

  ProcessCGI::ExitStatus status = parent.execute();
  EXPECT_EQ(ProcessCGI::PARENT_ERROR, status);

  delete log;
}

TEST(ParentProcessCGITest, execute_waitpidSystemCallError) {
  SystemCallsMockToParent *sysCall = new SystemCallsMockToParent;
  EXPECT_CALL(*sysCall, waitpid(testing::_, testing::_, testing::_))
	  .WillOnce(testing::Return(
		  error::Status(error::Status::SystemCall, "waitpid error")));
  LogMockToParent *log = new LogMockToParent;
  EXPECT_CALL(*log, log(Log::ERROR, "ParentProcessCGI", "execute", std::string("waitpid error"), 42)).Times(1);

  ParentProcessCGI parent(42, 100000);
  parent.setSystemCalls(sysCall);
  parent.setLogger(log);

  ProcessCGI::ExitStatus status = parent.execute();
  EXPECT_EQ(ProcessCGI::PARENT_ERROR, status);

  delete log;
}


//
//
//
// -----------------------------------------------------------------------
// ======================= Integration Tests =============================
// -----------------------------------------------------------------------

// Test if the child EXIT WAS OK (value 0)
TEST(ParentProcessCGITest, execute_ChildReturn0) {
  SystemCalls systemCalls;

  error::StatusOr<pid_t> pid = systemCalls.fork();

  if (!pid.ok()) {
    FAIL() << "Fork failed";
  }
  pid_t thePid = pid.value();
  if (thePid == 0) {
    exit(0);
  } else {
    ParentProcessCGI parentProcessCGI(thePid, 3);
    ProcessCGI::ExitStatus status = parentProcessCGI.execute();
    EXPECT_EQ(ProcessCGI::CHILD_EXIT_OK, status);
  }
}

// Test if the child EXIT WAS A FAILURE (value different from 0)
TEST(ParentProcessCGITest, execute_ChildReturnAValueDifferentOf0) {
  SystemCalls systemCalls;

  error::StatusOr<pid_t> pid = systemCalls.fork();

  if (!pid.ok()) {
    FAIL() << "Fork failed";
  }
  pid_t thePid = pid.value();
  if (thePid == 0) {
    exit(1);
  } else {
    ParentProcessCGI parentProcessCGI(thePid, 3);
    ProcessCGI::ExitStatus status = parentProcessCGI.execute();
    EXPECT_EQ(ProcessCGI::CHILD_EXIT_WITH_ERROR, status);
  }
}

// Test if the child EXIT BY KILL (Timeout)
// In this test we will run a child process that never ends! And we will kill it
// because of the timeout!
TEST(ParentProcessCGITest, execute_testKillByTimeout) {

  LogMockToParent *logMock = new LogMockToParent;
  EXPECT_CALL(*logMock, log(Log::ERROR, "ParentProcessCGI", "execute", "the CGI child process took too long to execute. Time in seconds", ::testing::A<int>())).Times(1);

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
    ParentProcessCGI parentProcessCGI(thePid, 3);
	parentProcessCGI.setLogger(logMock);
    ProcessCGI::ExitStatus status = parentProcessCGI.execute();
    EXPECT_EQ(ProcessCGI::CHILD_FINISHED_BY_SIGNAL, status);
  }

  delete logMock;

  // check if the time is greater than 3 seconds
  EXPECT_TRUE(time.isTimeOut(startTime, 3));
}