#include <cstring>
#include <string>
#include <vector>

#include "../../libs/googletest/googlemock/include/gmock/gmock.h"
#include "../../libs/googletest/googletest/include/gtest/gtest.h"
#include "../error/Log.hpp"
#include "../error/Status.hpp"
#include "../net/Address.hpp"
#include "../system/Errno.hpp"
#include "../system/SystemCalls.hpp"
#include "SocketFileDescriptorImpl.hpp"

namespace SocketFileDescriptorImplTest {

class SystemCallsMock : public SystemCalls {
 public:
  MOCK_METHOD(error::StatusOr<ssize_t>, read, (int fd, void *buf, size_t count),
              (const override));
  MOCK_METHOD(error::StatusOr<ssize_t>, write,
              (int fd, const void *buf, size_t count), (const override));
  MOCK_METHOD(error::StatusOr<int>, close, (int fd), (const overrided));
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

//-----------------------------------------------------------------

TEST(SocketFileDescriptorImplTest, doRead_testOneRead) {
  SystemCallsMock *systemCallsMock = new SystemCallsMock;
  Address address;
  LogMock logMock;

  EXPECT_CALL(
      *systemCallsMock,
      read(::testing::A<int>(), ::testing::A<void *>(), ::testing::A<size_t>()))
      .WillOnce(::testing::Invoke([](int fd, void *buf, size_t size) {
        (void)fd;
        std::memcpy(buf, "aaaaa", size);
        return 5;
      }));
  EXPECT_CALL(*systemCallsMock, close(::testing::A<int>()))
      .Times(1)
      .WillOnce(::testing::Return(0));

  EXPECT_CALL(
      logMock,
      log(::testing::A<Log::LogLevel>(), ::testing::A<const std::string &>(),
          ::testing::A<const std::string &>(),
          ::testing::A<const std::string &>(), ::testing::A<int>()))
      .Times(2);

  SocketFileDescriptorImpl socketFDimpl(-1, address, 5, &logMock);
  socketFDimpl.setSystemCalls(systemCallsMock);

  socketFDimpl.doRead();

  std::vector<char> vectorToCompare;
  for (int a = 0; a < 5; ++a) vectorToCompare.push_back('a');

  EXPECT_EQ(vectorToCompare, socketFDimpl.getInputStream());
}

TEST(SocketFileDescriptorImplTest, doRead_testTwoReads) {
  SystemCallsMock *systemCallsMock = new SystemCallsMock;
  Address address;
  LogMock logMock;

  EXPECT_CALL(*systemCallsMock,
              read(::testing::A<int>(), ::testing::A<void *>(), 5))
      .Times(2)
      .WillOnce(::testing::Invoke([](int fd, void *buf, size_t size) {
        (void)fd;
        std::memcpy(buf, "aaaaa", size);
        return 5;
      }))
      .WillOnce(::testing::Invoke([](int fd, void *buf, size_t size) {
        (void)fd;
        std::memcpy(buf, "bbbbb", size);
        return 5;
      }));
  EXPECT_CALL(*systemCallsMock, close(::testing::A<int>()))
      .WillOnce(::testing::Return(0));
  EXPECT_CALL(
      logMock,
      log(::testing::A<Log::LogLevel>(), ::testing::A<const std::string &>(),
          ::testing::A<const std::string &>(),
          ::testing::A<const std::string &>(), ::testing::A<int>()))
      .Times(::testing::AtLeast(0));

  SocketFileDescriptorImpl socketFDimpl(-1, address, 5, &logMock);
  socketFDimpl.setSystemCalls(systemCallsMock);

  bool readed = socketFDimpl.doRead();
  EXPECT_TRUE(readed);
  readed = socketFDimpl.doRead();
  EXPECT_TRUE(readed);

  std::vector<char> vectorToCompare;
  for (int a = 0; a < 5; ++a) vectorToCompare.push_back('a');
  for (int a = 0; a < 5; ++a) vectorToCompare.push_back('b');

  EXPECT_EQ(vectorToCompare, socketFDimpl.getInputStream());
}

//-----------------------------------------------------------------

TEST(SocketFileDescriptorImplTest, dowrite_writedAllCharacters) {
  SystemCallsMock *systemCallsMock = new SystemCallsMock;
  Address address;
  LogMock logMock;

  EXPECT_CALL(*systemCallsMock,
              write(::testing::A<int>(), ::testing::A<const void *>(), 5))
      .WillOnce(::testing::Return(5));
  EXPECT_CALL(*systemCallsMock, close(::testing::A<int>()))
      .WillOnce(::testing::Return(0));
  EXPECT_CALL(
      logMock,
      log(::testing::A<Log::LogLevel>(), ::testing::A<const std::string &>(),
          ::testing::A<const std::string &>(),
          ::testing::A<const std::string &>(), ::testing::A<int>()))
      .Times(::testing::AtLeast(0));
  EXPECT_CALL(logMock, log(::testing::A<Log::LogLevel>(),
                           ::testing::A<const std::string &>(),
                           ::testing::A<const std::string &>(),
                           ::testing::A<const std::string &>(),
                           ::testing::A<const std::string &>()))
      .Times(::testing::AtLeast(0));

  SocketFileDescriptorImpl socketFDimpl(-1, address, 5, &logMock);
  socketFDimpl.setSystemCalls(systemCallsMock);

  for (int count = 0; count < 5; count++)
    socketFDimpl.getOutputStream().push_back('a');

  ssize_t sizeOfBuffer = socketFDimpl.doWrite();
  EXPECT_EQ((ssize_t)0, sizeOfBuffer);
}

TEST(SocketFileDescriptorImplTest, dowrite_doesntWritedAllCharacters) {
  SystemCallsMock *systemCallsMock = new SystemCallsMock;
  Address address;
  LogMock logMock;

  EXPECT_CALL(*systemCallsMock,
              write(::testing::A<int>(), ::testing::A<const void *>(), 10))
      .WillOnce(::testing::Return(5));
  EXPECT_CALL(*systemCallsMock, close(::testing::A<int>()))
      .WillOnce(::testing::Return(0));
  EXPECT_CALL(
      logMock,
      log(::testing::A<Log::LogLevel>(), ::testing::A<const std::string &>(),
          ::testing::A<const std::string &>(),
          ::testing::A<const std::string &>(), ::testing::A<int>()))
      .Times(::testing::AtLeast(0));
  EXPECT_CALL(logMock, log(::testing::A<Log::LogLevel>(),
                           ::testing::A<const std::string &>(),
                           ::testing::A<const std::string &>(),
                           ::testing::A<const std::string &>(),
                           ::testing::A<const std::string &>()))
      .Times(::testing::AtLeast(0));

  SocketFileDescriptorImpl socketFDimpl(-1, address, 5, &logMock);
  socketFDimpl.setSystemCalls(systemCallsMock);

  for (int count = 0; count < 5; count++)
    socketFDimpl.getOutputStream().push_back('a');
  for (int count = 0; count < 5; count++)
    socketFDimpl.getOutputStream().push_back('b');

  ssize_t sizeOfBuffer = socketFDimpl.doWrite();
  EXPECT_EQ((ssize_t)5, sizeOfBuffer);

  std::vector<char> compare = {'b', 'b', 'b', 'b', 'b'};

  EXPECT_EQ(compare, socketFDimpl.getOutputStream());
}

}  // namespace SocketFileDescriptorImplTest
