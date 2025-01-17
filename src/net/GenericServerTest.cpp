#include "../../libs/googletest/googlemock/include/gmock/gmock.h"
#include "../../libs/googletest/googletest/include/gtest/gtest.h"
#include "../config/ProgramConfiguration.hpp"
#include "../error/Log.hpp"
#include "../io/Poll.hpp"
#include "../net/SocketFileDescriptorImpl.hpp"
#include "GenericServer.hpp"

namespace GenericServerTest {

class SystemCallsMock : public SystemCalls {
  error::StatusOr<int> close(int fd) const {
    (void)fd;
    return 0;
  }
};

class LogMock : public Log {
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

class PollNothingMock : public Poll {
 public:
  MOCK_METHOD((bool), createPoll, (), (override));
  MOCK_METHOD((bool), addFileDescriptor,
              (FileDescriptor * fd, EVENTS_TO_LISTENER option), (override));
  MOCK_METHOD((bool), removeFileDescriptor, (FileDescriptor * fd), (override));

  MOCK_METHOD((bool), changeOptionFileDescriptor,
              (FileDescriptor * fd, EVENTS_TO_LISTENER option), (override));
  MOCK_METHOD((std::vector<FileDescriptor *>), wait, (), (override));

  MOCK_METHOD((std::map<int, FileDescriptor *> &), getFileDescriptorsInPoll, (),
              (override));
};

class SocketFileDescriptorMock : public SocketFileDescriptor {
 public:
  SocketFileDescriptorMock(int fd) : SocketFileDescriptor(fd) {}
  void acceptVisit(FileDescriptorVisitor *fdv) { (void)fdv; }
  ~SocketFileDescriptorMock() {}
};

class GenericServerRequestMock : public GenericServerRequestManager {
 public:
  GenericServerRequestMock(Log *log, ProgramConfiguration &config)
      : GenericServerRequestManager(NULL, NULL, log, config) {}
};

class ConfigurationMock : public ProgramConfiguration{

};

TEST(GenericServerTest, processClientRequest_clientDoesntExist) {
  LogMock loggerMock, loggerMock2;
  PollNothingMock poll;
  SystemCallsMock systemCallsMock;
  ConfigurationMock configMock;

  EXPECT_CALL(
      loggerMock,
      log(Log::ERROR, "GenericServer", "processClientRequest",
          "The client doesn't have a generic server request manager", -1))
      .Times(1);

  GenericServer gs(poll, loggerMock, configMock);

  SocketFileDescriptorImpl *sdi = new SocketFileDescriptorImpl(-1, NULL);
  sdi->setSystemCalls(new SystemCallsMock);

  gs.processClientRequest(sdi);

  delete sdi;
}

//--------------------------------------------------------------

TEST(GenericServerTest, checkMemoryLeak) {
  SystemCallsMock sm;
  PollNothingMock poll;
  LogMock log;
  ConfigurationMock configMock;

  //this expect_call is to hide warning messages form googletest
  EXPECT_CALL(log, log(::testing::A<Log::LogLevel>(),
                              ::testing::A<const std::string &>(),
                              ::testing::A<const std::string &>(),
                              ::testing::A<const std::string &>(),
                              ::testing::A<const std::string &>()))
      .Times(::testing::AtLeast(0));

  SocketFileDescriptorMock *fd = new SocketFileDescriptorMock(-1);
  fd->setSystemCalls(new SystemCallsMock);

  GenericServerRequestMock *gsrm = new GenericServerRequestMock(&log, configMock);

  // empty
  GenericServer genericServer(poll, log, configMock);

  // one item
  GenericServer genericServer2(poll, log, configMock);
  genericServer2.getMapClientRequestHandler()[fd] = gsrm;

  // two item
  SocketFileDescriptorMock *fd2 = new SocketFileDescriptorMock(-1);
  fd2->setSystemCalls(new SystemCallsMock);
  SocketFileDescriptorMock *fd3 = new SocketFileDescriptorMock(-1);
  fd3->setSystemCalls(new SystemCallsMock);

  GenericServerRequestMock *gsrm2 = new GenericServerRequestMock(&log, configMock);
  GenericServerRequestMock *gsrm3 = new GenericServerRequestMock(&log, configMock);

  GenericServer genericServer3(poll, log, configMock);
  genericServer3.getMapClientRequestHandler()[fd2] = gsrm2;
  genericServer3.getMapClientRequestHandler()[fd3] = gsrm3;
}

}  // namespace GenericServerTest