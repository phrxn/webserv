#include <string>

#include "../../libs/googletest/googlemock/include/gmock/gmock.h"
#include "../../libs/googletest/googletest/include/gtest/gtest.h"
#include "../net/ServerSocketFileDescriptor.hpp"
#include "../net/SocketFileDescriptorImpl.hpp"
#include "../system/SystemCalls.hpp"
#include "Epoll.hpp"

namespace EpollTest {

class SystemCallsMock : public SystemCalls {
 public:
  MOCK_METHOD(error::StatusOr<int>, epoll_wait,
              (int epfd, struct epoll_event *events, int maxevents,
               int timeout),
              (const override));

  MOCK_METHOD(error::StatusOr<int>, close, (int fd), (const override));

  MOCK_METHOD(error::StatusOr<int>, epoll_create, (int fd), (const override));
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

TEST(EpollTest, createPoll_ok) {
  LogMock *logMock = new LogMock;
  SystemCallsMock *systemCallMock = new SystemCallsMock;

  EXPECT_CALL(*systemCallMock, epoll_create(1))
      .WillOnce(::testing::Invoke([](int options) {
        (void)options;
        return 42;
      }));

  EXPECT_CALL(*systemCallMock, close(42))
      .WillOnce(::testing::Invoke([](int options) {
        (void)options;
        return 42;
      }));

  EXPECT_CALL(*logMock, log(::testing::A<Log::LogLevel>(),
                            ::testing::A<const std::string &>(),
                            ::testing::A<const std::string &>(),
                            ::testing::A<const std::string &>(),
                            ::testing::A<const std::string &>()))
      .Times(0);

  Epoll epoll(logMock);
  epoll.setSystemCalls(systemCallMock);

  bool isEpollCreated = epoll.createPoll();
  EXPECT_TRUE(isEpollCreated);

  EXPECT_EQ(42, epoll.getFileDescriptor());

  delete logMock;
}

//-----------------------------------------------------------------

class SocketFileDescriptorImplMock1 : public SocketFileDescriptorImpl {
 public:
  SocketFileDescriptorImplMock1(int fd, Log *logger)
      : SocketFileDescriptorImpl(fd, logger) {}
  MOCK_METHOD(void, setReadyToRead, (bool), (override));
  MOCK_METHOD(void, setReadyToWrite, (bool), (override));
};

TEST(EpollTest, setFileDescriptorEvents_clientReadyToRead) {
  struct epoll_event event;
  event.data.fd = 42;
  event.events = EPOLLIN;

  LogMock loggerNothing;
  SystemCallsMock systemCalls;

  SocketFileDescriptorImplMock1 *sdi =
      new SocketFileDescriptorImplMock1(42, &loggerNothing);

  EXPECT_CALL(*sdi, setReadyToRead(true)).Times(1);
  EXPECT_CALL(*sdi, setReadyToWrite(false)).Times(1);

  Epoll epoll(&loggerNothing);

  epoll.setFileDescriptorEvents(sdi, event);

  delete sdi;
}

TEST(EpollTest, setFileDescriptorEvents_clientReadyToWrite) {
  struct epoll_event event;
  event.data.fd = 42;
  event.events = EPOLLOUT;

  LogMock loggerNothing;
  SystemCallsMock systemCalls;

  SocketFileDescriptorImplMock1 *sdi =
      new SocketFileDescriptorImplMock1(42, &loggerNothing);

  EXPECT_CALL(*sdi, setReadyToRead(false)).Times(1);
  EXPECT_CALL(*sdi, setReadyToWrite(true)).Times(1);

  Epoll epoll(&loggerNothing);

  epoll.setFileDescriptorEvents(sdi, event);

  delete sdi;
}

TEST(EpollTest, setFileDescriptorEvents_clientReadyToReadAndWrite) {
  struct epoll_event event;
  event.data.fd = 42;
  event.events = EPOLLOUT | EPOLLIN;

  LogMock loggerNothing;
  SystemCallsMock systemCalls;

  SocketFileDescriptorImplMock1 *sdi =
      new SocketFileDescriptorImplMock1(42, &loggerNothing);

  EXPECT_CALL(*sdi, setReadyToRead(true)).Times(1);
  EXPECT_CALL(*sdi, setReadyToWrite(true)).Times(1);

  Epoll epoll(&loggerNothing);

  epoll.setFileDescriptorEvents(sdi, event);

  delete sdi;
}

//-----------------------------------------------------------------

TEST(EpollTest, prepareStructEpollEvent_Nothing) {
  LogMock loggerNothing;
  SystemCallsMock systemCallsNothing;
  Epoll epoll(&loggerNothing);

  struct epoll_event event;

  epoll.prepareStructEpollEvent(42, Poll::NOTHING, &event);
  EXPECT_EQ(42, event.data.fd);
  EXPECT_EQ((uint32_t)0, event.events);
}

TEST(EpollTest, prepareStructEpollEvent_Input) {
  LogMock loggerNothing;
  SystemCallsMock systemCallsNothing;
  Epoll epoll(&loggerNothing);

  struct epoll_event event;

  epoll.prepareStructEpollEvent(42, Poll::INPUT, &event);
  EXPECT_EQ(42, event.data.fd);
  EXPECT_TRUE(event.events & EPOLLIN);
  EXPECT_FALSE(event.events & EPOLLOUT);
}

TEST(EpollTest, prepareStructEpollEvent_Output) {
  LogMock loggerNothing;
  SystemCallsMock systemCallsNothing;
  Epoll epoll(&loggerNothing);

  struct epoll_event event;

  epoll.prepareStructEpollEvent(42, Poll::OUTPUT, &event);
  EXPECT_EQ(42, event.data.fd);
  EXPECT_FALSE(event.events & EPOLLIN);
  EXPECT_TRUE(event.events & EPOLLOUT);
}

TEST(EpollTest, prepareStructEpollEvent_InputAndOutput) {
  LogMock loggerNothing;
  SystemCallsMock systemCallsNothing;
  Epoll epoll(&loggerNothing);

  struct epoll_event event;

  epoll.prepareStructEpollEvent(42, Poll::INPUT_AND_OUTPUT, &event);
  EXPECT_EQ(42, event.data.fd);
  EXPECT_TRUE(event.events & EPOLLIN);
  EXPECT_TRUE(event.events & EPOLLOUT);
}

//-----------------------------------------------------------------

class SystemCallsMock2 : public SystemCalls {
 public:
  MOCK_METHOD(error::StatusOr<int>, epoll_wait,
              (int epfd, struct epoll_event *events, int maxevents,
               int timeout),
              (const override));

  MOCK_METHOD(error::StatusOr<int>, epoll_create, (int fd), (const override));

  error::StatusOr<int> close(int fd) const {
    (void)fd;
    return 0;
  }
};

class ServerSocketFileDescriptorWait1Mock : public ServerSocketFileDescriptor {
 public:
  ServerSocketFileDescriptorWait1Mock(Log *logger)
      : ServerSocketFileDescriptor(logger){};

  MOCK_METHOD(void, setReadyToRead, (bool), (override));
  MOCK_METHOD(void, setReadyToWrite, (bool), (override));
};

class SocketFileDescriptorWait1Mock : public SocketFileDescriptorImpl {
 public:
  SocketFileDescriptorWait1Mock(int fd, Log *logger)
      : SocketFileDescriptorImpl(fd, logger) {}
  MOCK_METHOD(void, setReadyToRead, (bool), (override));
  MOCK_METHOD(void, setReadyToWrite, (bool), (override));
};

TEST(EpollTest, wait_2Client_2Server_mocked_1client_ready_and_1_server_ready) {
  LogMock loggerMakeNothing;
  SystemCallsMock *syscallMock = new SystemCallsMock;
  SystemCallsMock2 syscallMock2;

  Epoll epoll(&loggerMakeNothing);
  epoll.setSystemCalls(syscallMock);

  ServerSocketFileDescriptorWait1Mock *serverSocket1 =
      new ServerSocketFileDescriptorWait1Mock(&loggerMakeNothing);
  serverSocket1->setSystemCalls(new SystemCallsMock2);
  ServerSocketFileDescriptorWait1Mock *serverSocket2 =
      new ServerSocketFileDescriptorWait1Mock(&loggerMakeNothing);
  serverSocket2->setSystemCalls(new SystemCallsMock2);
  SocketFileDescriptorWait1Mock *clientSocket1 =
      new SocketFileDescriptorWait1Mock(200, &loggerMakeNothing);
  clientSocket1->setSystemCalls(new SystemCallsMock2);
  SocketFileDescriptorWait1Mock *clientSocket2 =
      new SocketFileDescriptorWait1Mock(202, &loggerMakeNothing);
  clientSocket2->setSystemCalls(new SystemCallsMock2);

  epoll.getFileDescriptorsInPoll()[100] = serverSocket1;
  epoll.getFileDescriptorsInPoll()[102] = serverSocket2;
  epoll.getFileDescriptorsInPoll()[200] = clientSocket1;
  epoll.getFileDescriptorsInPoll()[202] = clientSocket2;

  EXPECT_CALL(*serverSocket1, setReadyToRead(true)).Times(1);
  EXPECT_CALL(*serverSocket1, setReadyToWrite(false)).Times(1);

  EXPECT_CALL(*serverSocket2, setReadyToRead(::testing::A<bool>())).Times(0);
  EXPECT_CALL(*serverSocket2, setReadyToWrite(::testing::A<bool>())).Times(0);

  EXPECT_CALL(*clientSocket1, setReadyToRead(::testing::A<bool>())).Times(0);
  EXPECT_CALL(*clientSocket1, setReadyToWrite(::testing::A<bool>())).Times(0);

  EXPECT_CALL(*clientSocket2, setReadyToRead(true)).Times(1);
  EXPECT_CALL(*clientSocket2, setReadyToWrite(true)).Times(1);

  EXPECT_CALL(*syscallMock,
              epoll_wait(-1, ::testing::A<struct epoll_event *>(), 4, 1))
      .WillOnce(::testing::Invoke(
          [](int epfd, struct epoll_event *events, int maxevents, int timeout) {
            (void)epfd;
            (void)maxevents;
            (void)timeout;
            events[0].data.fd = 202;
            events[0].events = EPOLLIN | EPOLLOUT;
            events[1].data.fd = 100;
            events[1].events = EPOLLIN;
            return 2;
          }));

  EXPECT_CALL(*syscallMock, close(::testing::_))
      .WillOnce(::testing::Invoke([](int options) {
        (void)options;
        return 42;
      }));

  std::vector<FileDescriptor *> fdsReady = epoll.wait();

  EXPECT_EQ((std::size_t)2, fdsReady.size());
  EXPECT_EQ(fdsReady[0], clientSocket2);
  EXPECT_EQ(fdsReady[1], serverSocket1);

  delete serverSocket1;
  delete serverSocket2;
  delete clientSocket1;
  delete clientSocket2;
}

//-------------------------------------------------------------------------------

TEST(EpollTest, wait_3Client_2Server_mocked_all_ready) {
  LogMock loggerMakeNothing;
  SystemCallsMock *syscallMock = new SystemCallsMock;
  SystemCallsMock2 syscallMock2;

  Epoll epoll(&loggerMakeNothing);
  epoll.setSystemCalls(syscallMock);

  ServerSocketFileDescriptorWait1Mock *serverSocket1 =
      new ServerSocketFileDescriptorWait1Mock(&loggerMakeNothing);
  serverSocket1->setSystemCalls(new SystemCallsMock2);
  ServerSocketFileDescriptorWait1Mock *serverSocket2 =
      new ServerSocketFileDescriptorWait1Mock(&loggerMakeNothing);
  serverSocket2->setSystemCalls(new SystemCallsMock2);
  SocketFileDescriptorWait1Mock *clientSocket1 =
      new SocketFileDescriptorWait1Mock(200, &loggerMakeNothing);
  clientSocket1->setSystemCalls(new SystemCallsMock2);
  SocketFileDescriptorWait1Mock *clientSocket2 =
      new SocketFileDescriptorWait1Mock(202, &loggerMakeNothing);
  clientSocket2->setSystemCalls(new SystemCallsMock2);
  SocketFileDescriptorWait1Mock *clientSocket3 =
      new SocketFileDescriptorWait1Mock(203, &loggerMakeNothing);
  clientSocket2->setSystemCalls(new SystemCallsMock2);

  epoll.getFileDescriptorsInPoll()[100] = serverSocket1;
  epoll.getFileDescriptorsInPoll()[102] = serverSocket2;
  epoll.getFileDescriptorsInPoll()[200] = clientSocket1;
  epoll.getFileDescriptorsInPoll()[202] = clientSocket2;
  epoll.getFileDescriptorsInPoll()[203] = clientSocket3;

  EXPECT_CALL(*serverSocket1, setReadyToRead(true)).Times(1);
  EXPECT_CALL(*serverSocket1, setReadyToWrite(false)).Times(1);

  EXPECT_CALL(*serverSocket2, setReadyToRead(true)).Times(1);
  EXPECT_CALL(*serverSocket2, setReadyToWrite(false)).Times(1);

  EXPECT_CALL(*clientSocket1, setReadyToRead(true)).Times(1);
  EXPECT_CALL(*clientSocket1, setReadyToWrite(false)).Times(1);

  EXPECT_CALL(*clientSocket2, setReadyToRead(false)).Times(1);
  EXPECT_CALL(*clientSocket2, setReadyToWrite(true)).Times(1);

  EXPECT_CALL(*clientSocket3, setReadyToRead(true)).Times(1);
  EXPECT_CALL(*clientSocket3, setReadyToWrite(true)).Times(1);

  EXPECT_CALL(*syscallMock,
              epoll_wait(-1, ::testing::A<struct epoll_event *>(), 5, 1))
      .WillOnce(::testing::Invoke(
          [](int epfd, struct epoll_event *events, int maxevents, int timeout) {
            (void)epfd;
            (void)maxevents;
            (void)timeout;
            events[0].data.fd = 203;
            events[0].events = EPOLLIN | EPOLLOUT;
            events[1].data.fd = 102;
            events[1].events = EPOLLIN;
            events[2].data.fd = 200;
            events[2].events = EPOLLIN;
            events[3].data.fd = 202;
            events[3].events = EPOLLOUT;
            events[4].data.fd = 100;
            events[4].events = EPOLLIN;
            return 5;
          }));

  EXPECT_CALL(*syscallMock, close(::testing::_))
      .WillOnce(::testing::Invoke([](int options) {
        (void)options;
        return 42;
      }));

  std::vector<FileDescriptor *> fdsReady = epoll.wait();

  EXPECT_EQ((std::size_t)5, fdsReady.size());
  EXPECT_EQ(fdsReady[0], clientSocket3);
  EXPECT_EQ(fdsReady[1], serverSocket2);

  delete serverSocket1;
  delete serverSocket2;
  delete clientSocket1;
  delete clientSocket2;
  delete clientSocket3;
}

}  // namespace EpollTest