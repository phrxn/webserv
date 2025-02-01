#include "../../../libs/googletest/googlemock/include/gmock/gmock.h"
#include "../../../libs/googletest/googletest/include/gtest/gtest.h"
#include "HTTPResponse.hpp"

TEST(HTTPResponseTest, getStatus) {
  HTTPStatus httpStatus;

  HTTPResponse response(nullptr);

  response.setStatus(HTTPStatus::Status::OK);

  EXPECT_EQ("200 OK", response.getStatusStr());
}

//----------------------------------------------------

TEST(HTTPResponseTest, createResponseString_withAllThings) {
  HTTPResponse response(nullptr);

  response.setStatus(HTTPStatus::Status::OK);
  response.setHTTPVersion("HTTP/1.1");
  response.setServer("webserv");
  response.setDate("Mon, 27 Jul 2009 12:28:53 GMT");
  response.setContentType("text/html");
  response.setContentLength("11");
  response.setLastModified("Wed, 22 Jul 2009 19:15:56 GMT");
  response.setConnection("close");
  response.addHeader("header1", "value1");
  response.addHeader("header2", "value2");
  response.setBody("Hello World");

  std::string fullResponse =
      "HTTP/1.1 200 OK\r\n"
      "Server: webserv\r\n"
      "Date: Mon, 27 Jul 2009 12:28:53 GMT\r\n"
      "Content-Type: text/html\r\n"
      "Content-Length: 11\r\n"
      "Last-Modified: Wed, 22 Jul 2009 19:15:56 GMT\r\n"
      "Connection: close\r\n"
      "header1: value1\r\n"
      "header2: value2\r\n"
      "\r\n"
      "Hello World";

  EXPECT_EQ(fullResponse, response.createResponseString());
}

TEST(HTTPResponseTest, createResponseString_withSomeThings) {
  HTTPResponse response(nullptr);

  response.setStatus(HTTPStatus::Status::OK);
  response.setHTTPVersion("HTTP/1.1");
  response.setServer("webserv");
  response.setDate("Mon, 27 Jul 2009 12:28:53 GMT");
  response.setContentType("text/html");
  response.setContentLength("11");
  response.setConnection("close");
  response.setBody("Hello World");

  std::string fullResponse =
      "HTTP/1.1 200 OK\r\n"
      "Server: webserv\r\n"
      "Date: Mon, 27 Jul 2009 12:28:53 GMT\r\n"
      "Content-Type: text/html\r\n"
      "Content-Length: 11\r\n"
      "Connection: close\r\n"
      "\r\n"
      "Hello World";

  EXPECT_EQ(fullResponse, response.createResponseString());
}

//----------------------------------------------------

TEST(HTTPResponseTest, setConnection){

  HTTPResponse response(nullptr);

  //in the start, keepAlive must be false
  EXPECT_EQ(false, response.getKeepAlive());

  response.setConnection("close");
  EXPECT_EQ(false, response.getKeepAlive());

  response.setConnection("keep-alive");
  EXPECT_EQ(true, response.getKeepAlive());
}