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

  std::string fullResponse = "HTTP/1.1 200 OK\r\n"
     "Connection: close\r\n"
     "Content-Length: 11\r\n"
     "Content-Type: text/html\r\n"
     "Date: Mon, 27 Jul 2009 12:28:53 GMT\r\n"
     "Last-Modified: Wed, 22 Jul 2009 19:15:56 GMT\r\n"
     "Server: webserv\r\n"
     "header1: value1\r\n"
     "header2: value2\r\n"
     "\r\n"
     "Hello World";

  EXPECT_EQ(fullResponse, response.createResponseString());
}

//----------------------------------------------------

TEST(HTTPResponseTest, createResponseString_withAllThingsButWith2EqualsKeys) {
	HTTPResponse response(nullptr);

	response.setStatus(HTTPStatus::Status::OK);
	response.setHTTPVersion("HTTP/1.1");
	response.setServer("webserv");
	response.setDate("Mon, 27 Jul 2009 12:28:53 GMT");
	response.setContentType("text/html");
	response.setContentLength("11");
	response.setLastModified("Wed, 22 Jul 2009 19:15:56 GMT");
	response.setConnection("close");
	response.addHeader("Set-Cookie", "111");
	response.addHeader("Header1", "value1");
	response.addHeader("Header2", "value2");
	response.addHeader("Set-Cookie", "222");
	response.setBody("Hello World");

	std::string fullResponse = "HTTP/1.1 200 OK\r\n"
	   "Connection: close\r\n"
	   "Content-Length: 11\r\n"
	   "Content-Type: text/html\r\n"
	   "Date: Mon, 27 Jul 2009 12:28:53 GMT\r\n"
	   "Header1: value1\r\n"
	   "Header2: value2\r\n"
	   "Last-Modified: Wed, 22 Jul 2009 19:15:56 GMT\r\n"
	   "Server: webserv\r\n"
	   "Set-Cookie: 111\r\n"
	   "Set-Cookie: 222\r\n"
	   "\r\n"
	   "Hello World";

	EXPECT_EQ(fullResponse, response.createResponseString());
  }

#include <iostream>
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

  std::string fullResponse=
       "HTTP/1.1 200 OK\r\n"
       "Connection: close\r\n"
       "Content-Length: 11\r\n"
       "Content-Type: text/html\r\n"
       "Date: Mon, 27 Jul 2009 12:28:53 GMT\r\n"
       "Server: webserv\r\n"
       "\r\n"
       "Hello World";

  EXPECT_EQ(fullResponse, response.createResponseString());
}

//----------------------------------------------------

TEST(HTTPResponseTest, setConnection){

  HTTPResponse response(nullptr);

  //in the start, keepAlive must be false
  EXPECT_EQ(true, response.closeConnectionAfterThatResponse());

  response.setConnection("close");
  EXPECT_EQ(true, response.closeConnectionAfterThatResponse());

  response.setConnection("keep-alive");
  EXPECT_EQ(false, response.closeConnectionAfterThatResponse());
}
