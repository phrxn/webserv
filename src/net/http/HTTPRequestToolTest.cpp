#include "../../../libs/googletest/googlemock/include/gmock/gmock.h"
#include "../../../libs/googletest/googletest/include/gtest/gtest.h"

#include "HTTPRequestTool.hpp"

TEST(HTTPRequestToolTest, parseRequest) {

    HTTPRequestTool requestTool;
    requestTool.parseRequest("GET / HTTP/1.1\r\nHost: localhost:8080\r\nUser-Agent: curl/7.68.0\r\nAccept: */*\r\n\r\n");
    
    EXPECT_EQ("GET",requestTool.getHeaders()["Method"]);
    EXPECT_EQ("/", requestTool.getHeaders()["URL"]);
    EXPECT_EQ("HTTP/1.1", requestTool.getHeaders()["HTTP-Version"]);
    EXPECT_EQ("localhost:8080",requestTool.getHeaders()["Host"]);
    EXPECT_EQ("curl/7.68.0", requestTool.getHeaders()["User-Agent"]);
    EXPECT_EQ("*/*", requestTool.getHeaders()["Accept"]);
}