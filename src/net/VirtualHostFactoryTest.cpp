#include "../../libs/googletest/googlemock/include/gmock/gmock.h"
#include "../../libs/googletest/googletest/include/gtest/gtest.h"
#include "VirtualHostFactory.hpp"

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

class VirtualHostClusterMock : public VirtualHostCluster {
 public:
  MOCK_METHOD(error::StatusOr<VirtualHostDefault>, getVirtualHost,
              (int port, const std::string &serverName), (const override));
};

TEST(VirtualHostFactoryTest, getVirtualHost_virtualHostDoesntExists) {
  VirtualHostClusterMock vhCmock;
  LogMock *logMock = new LogMock;


  EXPECT_CALL(*logMock,
              log(Log::FATAL, "VirtualHostFactory", "getVirtualHost",
                  "using default VirtualHostDefault, the virtualhost wasn't found",
                  "port: 80, hostname: foo"))
      .Times(1);
  VirtualHostFactory vFactory;
  vFactory.setLogger(logMock);

  VirtualHostDefault vh = vFactory.getVirtualHost(80, "foo");

  VirtualHostDefault toCompare(-1, "");

  EXPECT_EQ(toCompare, vh);

  delete logMock;
}