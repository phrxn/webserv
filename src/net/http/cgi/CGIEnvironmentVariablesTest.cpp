#include "../../../../libs/googletest/googlemock/include/gmock/gmock.h"
#include "../../../../libs/googletest/googletest/include/gtest/gtest.h"
#include "CGIEnvironmentVariables.hpp"

#include <iostream>
#include <list>
#include <string>
#include <cstring>

std::string env1("YYYYYY1111=FOO");
std::string env2("ZZZZZZ2222=BAR");

const char *fake_env[]{env1.c_str(), env2.c_str(), nullptr};

class HTTPRequestMock : public HTTPRequest {
 public:
  HTTPRequestMock(SocketFileDescriptor *socketFD, Log *logger)
      : HTTPRequest(socketFD, logger) {}

  MOCK_METHOD(std::string, getContentLength, (), (const override));
  MOCK_METHOD(std::string, getContentType, (), (const override));
  MOCK_METHOD(URL, getURL, (), (const override));
  MOCK_METHOD(std::string, getClientAddressIPv4, (), (const override));
  MOCK_METHOD(HTTPMethods::Method, getMethod, (), (const override));
  MOCK_METHOD(std::string, getHost, (), (const override));
  MOCK_METHOD(std::string, getCookie, (), (const override));
  MOCK_METHOD(int, getPort, (), (const override));
};


bool compareCharArrays(char** arr1, char** arr2) {

    for (int i = 0; arr1[i] != nullptr && arr2[i] != nullptr; ++i) {
        if (std::string(arr1[i]) != std::string(arr2[i])) {
            return false;
        }
    }
    return arr1 != nullptr && arr2 != nullptr;
}

char** listToCharArray(const std::list<std::string>& strList) {

    char** charArray = new char*[strList.size() + 1];

    int i = 0;
    for (const auto& str : strList) {
		charArray[i] = new char[str.size() + 1];
        std::strcpy(charArray[i], str.c_str());
        ++i;
    }

    charArray[i] = nullptr;

    return charArray;
}

void freeCharArray(char** charArray) {
    if (charArray) {
        int i = 0;
        while (charArray[i] != nullptr) {
            delete[] charArray[i];
            ++i;
        }
        delete[] charArray;
    }
}

void printCharArray(char** charArray) {
  std::cout << "==============================================" << std::endl;
  for (auto it = charArray; *it != nullptr; ++it) {
        std::cout << *it << std::endl;  // Imprime o valor apontado por 'it' (que é um char*)
  }
  std::cout << "==============================================" << std::endl;
}

TEST(CGIEnvironmentVariablesTest, createEnvironmentVariables) {

  ProgramConfiguration programConfigurationFake;
  programConfigurationFake.setCGIVersion("CGI/2.2");
  programConfigurationFake.setHTTPVersion("HTTP/2.2");
  programConfigurationFake.setServerName("serverNameTest");
  programConfigurationFake.setEnvironmentVariables(fake_env);

  HTTPRequestMock *httpReq = new HTTPRequestMock(NULL, NULL);
  EXPECT_CALL(*httpReq, getContentLength()).WillOnce(::testing::Return("100"));
  EXPECT_CALL(*httpReq, getContentType()).WillOnce(::testing::Return("text/html"));
  EXPECT_CALL(*httpReq, getURL()).WillRepeatedly(::testing::Return(URL("http://192.168.3.210/sub/cgi_variables.php/relatorio%20simples;ano=2024&mes=06?tipo=pdf;param1=valor1;param2=valor2%3F")));
  EXPECT_CALL(*httpReq, getClientAddressIPv4()).WillOnce(::testing::Return("000.000.000.000"));
  EXPECT_CALL(*httpReq, getMethod()).WillOnce(::testing::Return(HTTPMethods::GET));
  EXPECT_CALL(*httpReq, getHost()).WillOnce(::testing::Return("localhostfoo"));
  EXPECT_CALL(*httpReq, getPort()).WillOnce(::testing::Return(8080));
  EXPECT_CALL(*httpReq, getCookie()).Times(2).WillRepeatedly(::testing::Return("cookie1=valor1;cookie2=valor2"));

  //list to compare
  std::list<std::string> listToCompare{
    "AUTH_TYPE=",
	"CONTENT_LENGTH=100",
	"CONTENT_TYPE=text/html",
	"GATEWAY_INTERFACE=CGI/2.2",
	"HTTP_COOKIE=cookie1=valor1;cookie2=valor2",
	"PATH_INFO=/relatorio simples;ano=2024&mes=06",
	"PATH_TRANSLATED=/www/var/html/relatorio simples;ano=2024&mes=06",
	"QUERY_STRING=tipo=pdf;param1=valor1;param2=valor2%3F",
	"REDIRECT_STATUS=true",
	"REMOTE_ADDR=000.000.000.000",
	"REMOTE_HOST=",
	"REMOTE_IDENT=",
	"REMOTE_USER=",
	"REQUEST_METHOD=GET",
	"SCRIPT_FILENAME=/foo/file.php",
	"SCRIPT_NAME=/sub/cgi_variables.php",
	"SERVER_NAME=localhostfoo",
	"SERVER_PORT=8080",
	"SERVER_PROTOCOL=HTTP/2.2",
	"SERVER_SOFTWARE=serverNameTest",
	"YYYYYY1111=FOO",
	"ZZZZZZ2222=BAR"
  };

  auto allVariablesToCompare = listToCharArray(listToCompare);

  CGIEnvironmentVariables cgiEnv("/foo/file.php", "/www/var/html", httpReq, programConfigurationFake);
  auto allVariables = cgiEnv.createEnvironmentVariables();
  delete httpReq;

  EXPECT_TRUE(compareCharArrays(allVariables, allVariablesToCompare));

  freeCharArray(allVariables);
  freeCharArray(allVariablesToCompare);

}