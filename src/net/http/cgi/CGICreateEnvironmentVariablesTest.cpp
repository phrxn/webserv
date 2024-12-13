#include "../../../../libs/googletest/googlemock/include/gmock/gmock.h"
#include "../../../../libs/googletest/googletest/include/gtest/gtest.h"
#include "../../URL.hpp"
#include "CGICreateEnvironmentVariables.hpp"

class ULRMock : public URL {
 public:
  MOCK_METHOD(std::string, getPath, (), (const override));
};

TEST(CGICreateEnvironmentVariablesTest,
     extractScriptPath_stringIsOnlyScriptPath) {

  ULRMock urlMock;

  EXPECT_CALL(urlMock, getPath())
      .Times(1)
      .WillOnce(::testing::Return("/foo/bar.php"));

  CGICreateEnvironmentVariables cgi;

  std::string pathToScript = cgi.extractScriptPath(urlMock, ".php");

  EXPECT_EQ("/foo/bar.php", pathToScript);
}

TEST(CGICreateEnvironmentVariablesTest,
     extractScriptPath_stringIsOnlyScriptPathWithADifferentExtension) {

  ULRMock urlMock;

  EXPECT_CALL(urlMock, getPath())
      .Times(1)
      .WillOnce(::testing::Return("/foo/bar.php"));

  CGICreateEnvironmentVariables cgi;

  std::string pathToScript = cgi.extractScriptPath(urlMock, ".py");

  EXPECT_EQ("/foo/bar.php", pathToScript);
}

TEST(CGICreateEnvironmentVariablesTest,
     extractScriptPath_stringIsAPathAndExtraPath) {

  ULRMock urlMock;

  EXPECT_CALL(urlMock, getPath())
      .Times(1)
      .WillOnce(::testing::Return("/foo/bar.php/"));

  CGICreateEnvironmentVariables cgi;

  std::string pathToScript = cgi.extractScriptPath(urlMock, ".php");

  EXPECT_EQ("/foo/bar.php", pathToScript);
}

TEST(CGICreateEnvironmentVariablesTest,
     extractScriptPath_stringIsAPathAndExtraPathWithADifferentExtension) {

  ULRMock urlMock;

  EXPECT_CALL(urlMock, getPath())
      .Times(1)
      .WillOnce(::testing::Return("/foo/bar.php/"));

  CGICreateEnvironmentVariables cgi;

  std::string pathToScript = cgi.extractScriptPath(urlMock, ".py");

  EXPECT_EQ("/foo/bar.php/", pathToScript);
}


TEST(CGICreateEnvironmentVariablesTest,
     extractScriptPath_stringIsAPathAndExtraPathLong) {

  ULRMock urlMock;

  EXPECT_CALL(urlMock, getPath())
      .Times(1)
      .WillOnce(::testing::Return("/foo/bar.php/aa/bb"));

  CGICreateEnvironmentVariables cgi;

  std::string pathToScript = cgi.extractScriptPath(urlMock, ".php");

  EXPECT_EQ("/foo/bar.php", pathToScript);
}

TEST(CGICreateEnvironmentVariablesTest,
     extractScriptPath_stringIsAPathAndExtraPathLongWithADifferentExtension) {

  ULRMock urlMock;

  EXPECT_CALL(urlMock, getPath())
      .Times(1)
      .WillOnce(::testing::Return("/foo/bar.php/aa/bb"));

  CGICreateEnvironmentVariables cgi;

  std::string pathToScript = cgi.extractScriptPath(urlMock, ".py");

  EXPECT_EQ("/foo/bar.php/aa/bb", pathToScript);
}

TEST(CGICreateEnvironmentVariablesTest,
     extractExtraPath_pathWithoutExtraPath) {

  ULRMock urlMock;

  EXPECT_CALL(urlMock, getPath())
      .Times(2)
      .WillRepeatedly(::testing::Return("/foo/bar.php"));

  CGICreateEnvironmentVariables cgi;

  std::string pathToScript = cgi.extractExtraPath(urlMock, ".php");

  EXPECT_EQ("", pathToScript);
}

TEST(CGICreateEnvironmentVariablesTest,
     extractExtraPath_pathWithoutExtraPathAndWrongExtension) {

  ULRMock urlMock;

  EXPECT_CALL(urlMock, getPath())
      .Times(2)
      .WillRepeatedly(::testing::Return("/foo/bar.php"));

  CGICreateEnvironmentVariables cgi;

  std::string pathToScript = cgi.extractExtraPath(urlMock, ".py");

  EXPECT_EQ("", pathToScript);
}


TEST(CGICreateEnvironmentVariablesTest,
     extractExtraPath_pathWithASlashAsAnExtraPath) {

  ULRMock urlMock;

  EXPECT_CALL(urlMock, getPath())
      .Times(2)
      .WillRepeatedly(::testing::Return("/foo/bar.php/"));

  CGICreateEnvironmentVariables cgi;

  std::string pathToScript = cgi.extractExtraPath(urlMock, ".php");

  EXPECT_EQ("/", pathToScript);
}


TEST(CGICreateEnvironmentVariablesTest,
     extractExtraPath_pathWithAExtrapath) {

  ULRMock urlMock;

  EXPECT_CALL(urlMock, getPath())
      .Times(2)
      .WillRepeatedly(::testing::Return("/foo/bar.php/manga"));

  CGICreateEnvironmentVariables cgi;

  std::string pathToScript = cgi.extractExtraPath(urlMock, ".php");

  EXPECT_EQ("/manga", pathToScript);
}

TEST(CGICreateEnvironmentVariablesTest,
     extractExtraPath_pathWithAExtrapathAndWrongExtension) {

  ULRMock urlMock;

  EXPECT_CALL(urlMock, getPath())
      .Times(2)
      .WillRepeatedly(::testing::Return("/foo/bar.php/manga"));

  CGICreateEnvironmentVariables cgi;

  std::string pathToScript = cgi.extractExtraPath(urlMock, ".py");

  EXPECT_EQ("", pathToScript);
}

TEST(CGICreateEnvironmentVariablesTest, getServerPort) {

  CGICreateEnvironmentVariables cgi;

  std::string serverPort = cgi.getServerPort(8080);

  EXPECT_EQ("8080", serverPort);
}