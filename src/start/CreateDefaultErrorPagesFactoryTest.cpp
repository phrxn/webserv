#include "../../libs/googletest/googlemock/include/gmock/gmock.h"
#include "../../libs/googletest/googletest/include/gtest/gtest.h"
#include "CreateDefaultErrorPagesFactory.hpp"

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

TEST(CreateDefaultErrorPagesFactoryTest,
     getDefaulErrorPage_theHTTPStatusDoesntExistInTheFactoryMap) {
  std::map<HTTPStatus::Status, DefaultErrorPage> mapToFilTheFactory = {
      {HTTPStatus::SERVER_ERROR, DefaultErrorPage("500")}};

  LogMock *logMock = new LogMock;

  EXPECT_CALL(
      *logMock,
      log(Log::FATAL, "CreateDefaultErrorPagesFactory", "getDefaultErrorPages",
          "An HTML error page was requested, but its status does not exist! "
          "Therefore, the page with code 500 was returned. Code",
          404))
      .Times(1);

  CreateDefaultErrorPagesFactory cFactory;
  cFactory.fillTheFactory(mapToFilTheFactory);
  cFactory.setLogger(logMock);

  DefaultErrorPage dep = cFactory.getDefaultErrorPages(HTTPStatus::NOT_FOUND);

  delete logMock;
}

TEST(CreateDefaultErrorPagesFactoryTest,
     getDefaulErrorPage_theHTTPStatusExistsInTheFactoryMap) {

  std::map<HTTPStatus::Status, DefaultErrorPage> mapToFilTheFactory = {
      {HTTPStatus::SERVER_ERROR, DefaultErrorPage("500")},
      {HTTPStatus::NOT_FOUND, DefaultErrorPage("404")}};

  LogMock *logMock = new LogMock;

  EXPECT_CALL(
      *logMock,
      log(::testing::A<Log::LogLevel>(), ::testing::A<const std::string &>(),
          ::testing::A<const std::string &>(),
          ::testing::A<const std::string &>(), ::testing::A<int>()))
      .Times(0);

  CreateDefaultErrorPagesFactory cFactory;
  cFactory.fillTheFactory(mapToFilTheFactory);
  cFactory.setLogger(logMock);

  DefaultErrorPage dep = cFactory.getDefaultErrorPages(HTTPStatus::NOT_FOUND);

  EXPECT_EQ("404", dep.getData());

  delete logMock;
}