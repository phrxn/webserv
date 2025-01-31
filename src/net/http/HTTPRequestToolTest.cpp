#include "../../../libs/googletest/googlemock/include/gmock/gmock.h"
#include "../../../libs/googletest/googletest/include/gtest/gtest.h"

#include "HTTPRequestTool.hpp"

TEST(HTTPRequestToolTest, parseRequest) {

    HTTPRequestTool requestTool;
    requestTool.parserHeader("GET / HTTP/1.1\r\nHost: localhost:8080\r\nUser-Agent: curl/7.68.0\r\nAccept: */*\r\n\r\n");
    
    EXPECT_EQ("GET",requestTool.getHeaders()["Method"]);
    EXPECT_EQ("/", requestTool.getHeaders()["URL"]);
    EXPECT_EQ("HTTP/1.1", requestTool.getHeaders()["HTTP-Version"]);
    EXPECT_EQ("localhost:8080",requestTool.getHeaders()["Host"]);
    EXPECT_EQ("curl/7.68.0", requestTool.getHeaders()["User-Agent"]);
    EXPECT_EQ("*/*", requestTool.getHeaders()["Accept"]);
}


TEST(HTTPRequestToolTest, parsePostRequest) {

    HTTPRequestTool requestTool;
    std::string requestString = "POST /api/usuarios HTTP/1.1\r\n"
                                 "Host: api.exemplo.com\r\n"
                                 "Content-Type: application/json\r\n"
                                 "Content-Length: 36\r\n"
                                "\r\n"// Important: Empty line separating headers from body
                                 "{\"nome\": \"Novo Usuário\", \"email\": \"novo@exemplo.com\"}\r\n"// Body
                                 "{\"nome\": \"Novo Usuário\", \"email\": \"novo@exemplo.com\"}"; // Body

    requestTool.parserHeader(requestString);

    EXPECT_EQ("POST", requestTool.getHeaders()["Method"]);
    EXPECT_EQ("/api/usuarios", requestTool.getHeaders()["URL"]);
    EXPECT_EQ("HTTP/1.1", requestTool.getHeaders()["HTTP-Version"]);
    EXPECT_EQ("api.exemplo.com", requestTool.getHeaders()["Host"]);
    EXPECT_EQ("application/json", requestTool.getHeaders()["Content-Type"]);
    EXPECT_EQ("36", requestTool.getHeaders()["Content-Length"]);
    EXPECT_EQ(6u, requestTool.getHeaders().size());  // Content-Length is a string

    //  Check the body (Important!)
  //  EXPECT_EQ("{\"nome\": \"Novo Usuário\", \"email\": \"novo@exemplo.com\"}", requestTool.getBody());
}


TEST(HTTPRequestToolTest, parseDeleteRequest) {
    HTTPRequestTool requestTool;
    std::string requestString = "DELETE /api/produtos/123 HTTP/1.1\r\n"
                                 "Host: api.exemplo.com\r\n"
                                 "\r\n"; // Empty body for DELETE

    requestTool.parserHeader(requestString);

    EXPECT_EQ(4u, requestTool.getHeaders().size()); // Expecting 3 headers

    EXPECT_EQ("DELETE", requestTool.getHeaders()["Method"]);
    EXPECT_EQ("/api/produtos/123", requestTool.getHeaders()["URL"]);
    EXPECT_EQ("HTTP/1.1", requestTool.getHeaders()["HTTP-Version"]);
    EXPECT_EQ("api.exemplo.com", requestTool.getHeaders()["Host"]);

    //EXPECT_EQ(0u, requestTool.getBody().length()); // DELETE usually has no body
}

