#include "../../../../libs/googletest/googlemock/include/gmock/gmock.h"
#include "../../../../libs/googletest/googletest/include/gtest/gtest.h"
#include "../../URL.hpp"
#include "../../SocketFileDescriptor.hpp"
#include "CGICreateEnvironmentVariables.hpp"

class ULRMock : public URL {
 public:
  MOCK_METHOD(std::string, getPath, (), (const override));
};

class HTTPRequestMock : public HTTPRequest {
 public:
  HTTPRequestMock(SocketFileDescriptor *socketFD, Log *logger) : HTTPRequest(socketFD, logger) {}

  MOCK_METHOD(std::string, getContentLength, (), (const override));
  MOCK_METHOD(std::string, getContentType, (), (const override));
  MOCK_METHOD(URL, getURL, (), (const override));
  MOCK_METHOD(std::string, getClientAddressIPv4, (), (const override));
  MOCK_METHOD(HTTPMethods::Method, getMethod, (), (const override));
  MOCK_METHOD(std::string, getHost, (), (const override));
  MOCK_METHOD(std::string, getCookie, (), (const override));
  MOCK_METHOD(int, getPort, (), (const override));
};



TEST(CGICreateEnvironmentVariablesTest, create){

ProgramConfiguration programConfigurationFake;
programConfigurationFake.setCGIVersion("CGI/2.2");
programConfigurationFake.setHTTPVersion("HTTP/2.2");
programConfigurationFake.setServerName("serverNameTest");


HTTPRequestMock *httpReq = new HTTPRequestMock(NULL, NULL);
EXPECT_CALL(*httpReq, getContentLength()).WillOnce(::testing::Return("100"));
EXPECT_CALL(*httpReq, getContentType()).WillOnce(::testing::Return("text/html"));
EXPECT_CALL(*httpReq, getURL()).WillRepeatedly(::testing::Return(URL("http://192.168.3.210/sub/cgi_variables.php/relatorio%20simples;ano=2024&mes=06?tipo=pdf;param1=valor1;param2=valor2%3F")));
EXPECT_CALL(*httpReq, getClientAddressIPv4()).WillOnce(::testing::Return("000.000.000.000"));
EXPECT_CALL(*httpReq, getMethod()).WillOnce(::testing::Return(HTTPMethods::GET));
EXPECT_CALL(*httpReq, getHost()).WillOnce(::testing::Return("localhostfoo"));
EXPECT_CALL(*httpReq, getPort()).WillOnce(::testing::Return(8080));
EXPECT_CALL(*httpReq, getCookie()).Times(2).WillRepeatedly(::testing::Return("cookie1=valor1;cookie2=valor2"));


CGICreateEnvironmentVariables cgi("/foo/file.php", "/www/var/html");
cgi.setProgramConfiguration(programConfigurationFake);


std::map<std::string, std::string> mapToCompare{
        {"AUTH_TYPE", ""},
        {"CONTENT_LENGTH", "100"},
        {"CONTENT_TYPE", "text/html"},
        {"GATEWAY_INTERFACE", "CGI/2.2"},
        {"HTTP_COOKIE", "cookie1=valor1;cookie2=valor2"},
        {"PATH_INFO", "/relatorio simples;ano=2024&mes=06"},
        {"PATH_TRANSLATED", "/www/var/html/relatorio simples;ano=2024&mes=06"},
        {"QUERY_STRING", "tipo=pdf;param1=valor1;param2=valor2%3F"},
        {"REDIRECT_STATUS", "true"},
        {"REMOTE_ADDR", "000.000.000.000"},
        {"REMOTE_HOST", ""},
        {"REMOTE_IDENT", ""},
        {"REMOTE_USER", ""},
        {"REQUEST_METHOD", "GET"},
        {"SCRIPT_FILENAME", "/foo/file.php"},
        {"SCRIPT_NAME", "/sub/cgi_variables.php"},
        {"SERVER_NAME", "localhostfoo"},
        {"SERVER_PORT", "8080"},
        {"SERVER_PROTOCOL", "HTTP/2.2"},
        {"SERVER_SOFTWARE", "serverNameTest"},
};

auto mapCreated = cgi.createCGIVariables(httpReq);

EXPECT_EQ(mapToCompare, mapCreated);

delete httpReq;

}

TEST(CGICreateEnvironmentVariablesTest, operatorEquals){

ProgramConfiguration programConfigurationFake;
programConfigurationFake.setCGIVersion("CGI/2.2");
programConfigurationFake.setHTTPVersion("HTTP/2.2");
programConfigurationFake.setServerName("serverNameTest");


HTTPRequestMock *httpReq = new HTTPRequestMock(NULL, NULL);
EXPECT_CALL(*httpReq, getContentLength()).WillOnce(::testing::Return("100"));
EXPECT_CALL(*httpReq, getContentType()).WillOnce(::testing::Return("text/html"));
EXPECT_CALL(*httpReq, getURL()).WillRepeatedly(::testing::Return(URL("http://192.168.3.210/sub/cgi_variables.php/relatorio%20simples;ano=2024&mes=06?tipo=pdf;param1=valor1;param2=valor2%3F")));
EXPECT_CALL(*httpReq, getClientAddressIPv4()).WillOnce(::testing::Return("000.000.000.000"));
EXPECT_CALL(*httpReq, getMethod()).WillOnce(::testing::Return(HTTPMethods::GET));
EXPECT_CALL(*httpReq, getHost()).WillOnce(::testing::Return("localhostfoo"));
EXPECT_CALL(*httpReq, getPort()).WillOnce(::testing::Return(8080));
EXPECT_CALL(*httpReq, getCookie()).Times(2).WillRepeatedly(::testing::Return("cookie1=valor1;cookie2=valor2"));


CGICreateEnvironmentVariables cgi("/foo/file.php", "/www/var/html");
cgi.setProgramConfiguration(programConfigurationFake);


std::map<std::string, std::string> mapToCompare{
        {"AUTH_TYPE", ""},
        {"CONTENT_LENGTH", "100"},
        {"CONTENT_TYPE", "text/html"},
        {"GATEWAY_INTERFACE", "CGI/2.2"},
        {"HTTP_COOKIE", "cookie1=valor1;cookie2=valor2"},
        {"PATH_INFO", "/relatorio simples;ano=2024&mes=06"},
        {"PATH_TRANSLATED", "/www/var/html/relatorio simples;ano=2024&mes=06"},
        {"QUERY_STRING", "tipo=pdf;param1=valor1;param2=valor2%3F"},
        {"REDIRECT_STATUS", "true"},
        {"REMOTE_ADDR", "000.000.000.000"},
        {"REMOTE_HOST", ""},
        {"REMOTE_IDENT", ""},
        {"REMOTE_USER", ""},
        {"REQUEST_METHOD", "GET"},
        {"SCRIPT_FILENAME", "/foo/file.php"},
        {"SCRIPT_NAME", "/sub/cgi_variables.php"},
        {"SERVER_NAME", "localhostfoo"},
        {"SERVER_PORT", "8080"},
        {"SERVER_PROTOCOL", "HTTP/2.2"},
        {"SERVER_SOFTWARE", "serverNameTest"},
};

cgi.createCGIVariables(httpReq);

CGICreateEnvironmentVariables toTestCopy("aaa", "bbb");
toTestCopy = cgi;

EXPECT_EQ(toTestCopy, cgi);

 delete httpReq;

}