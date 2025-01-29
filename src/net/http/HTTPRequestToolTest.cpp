#include "../../../libs/googletest/googlemock/include/gmock/gmock.h"
#include "../../../libs/googletest/googletest/include/gtest/gtest.h"

#include "HTTPRequestTool.hpp"

TEST(HTTPRequestToolTest, splitFirstLine) {

    HTTPRequestTool requestTool;
    requestTool.splitFirstLine("GET / HTTP/1.1\r\n");
    
    EXPECT_EQ("GET",requestTool.getHeaders()["Method"]);
    EXPECT_EQ("/", requestTool.getHeaders()["URL"]);
    EXPECT_EQ("HTTP/1.1", requestTool.getHeaders()["HTTP-Version"]);
}

TEST(HTTPRequestToolTest, splitOtherLines) {

    HTTPRequestTool requestTool;
    requestTool.splitOtherLines("Host: localhost:8080\r\n"
                                "User-Agent: curl/7.68.0\r\n"
                                "Accept: */*\r\n"
                                "\r\n");
    
    EXPECT_EQ("localhost:8080",requestTool.getHeaders()["Host"]);
    EXPECT_EQ(requestTool.getHeaders()["User-Agent"], "curl/7.68.0");
    EXPECT_EQ(requestTool.getHeaders()["Accept"], "*/*");
}

TEST(HTTPRequestToolTest, parseRequest) {

    HTTPRequestTool requestTool;
    requestTool.parseRequest("GET / HTTP/1.1\r\n"
                             "Host: localhost:8080\r\n"
                             "User-Agent: curl/7.68.0\r\n"
                             "Accept: */*\r\n"
                             "\r\n");
    
    EXPECT_EQ("GET",requestTool.getHeaders()["Method"]);
    EXPECT_EQ("/", requestTool.getHeaders()["URL"]);
    EXPECT_EQ("HTTP/1.1", requestTool.getHeaders()["HTTP-Version"]);
    EXPECT_EQ("localhost:8080",requestTool.getHeaders()["Host"]);
    EXPECT_EQ("curl/7.68.0", requestTool.getHeaders()["User-Agent"]);
    EXPECT_EQ("*/*", requestTool.getHeaders()["Accept"]);
}