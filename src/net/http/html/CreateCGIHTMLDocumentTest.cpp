#include "../../../../libs/googletest/googlemock/include/gmock/gmock.h"
#include "../../../../libs/googletest/googletest/include/gtest/gtest.h"

#include "CreateCGIHTMLDocument.hpp"

TEST(CreateCGIHTMLDocumentTest, getHeaders_onlyOneHeader){

	std::string headers_part = "Content-Type: text/html";

	HTTPResponse response(NULL);

	CreateCGIHTMLDocument create(response, NULL);

	std::map<std::string, std::vector<std::string>> toCompare {
		{"Content-Type", {"text/html"}}
	};

	EXPECT_EQ(toCompare, create.getHeaders(headers_part));
}

TEST(CreateCGIHTMLDocumentTest, getHeaders_twoHeaders){

	std::string headers_part = "Content-Length: 42\r\nContent-Type: text/html";

	HTTPResponse response(NULL);

	CreateCGIHTMLDocument create(response, NULL);

	std::map<std::string, std::vector<std::string>> toCompare {
		{"Content-Length", {"42"}},
		{"Content-Type", {"text/html"}}
	};

	EXPECT_EQ(toCompare, create.getHeaders(headers_part));
}

TEST(CreateCGIHTMLDocumentTest, getHeaders_twoHeadersEquals){

	std::string headers_part = "Content-Length: 42\r\nContent-Type: text/html\r\nSet-Cookie: session=123456\r\nSet-Cookie: day=Monday";

	HTTPResponse response(NULL);

	CreateCGIHTMLDocument create(response, NULL);

	std::map<std::string, std::vector<std::string>> toCompare {
		{"Content-Length", {"42"}},
		{"Content-Type", {"text/html"}},
		{"Set-Cookie", {"session=123456", "day=Monday"}}
	};

	EXPECT_EQ(toCompare, create.getHeaders(headers_part));
}




// ------------------------------------------------------------------

TEST(CreateCGIHTMLDocumentTest, checkByStatusHeader_haveHeaderStatus){

	std::string headers_part = "Content-Length: 42\r\nContent-Type: text/html";

	HTTPResponse response(NULL);

	CreateCGIHTMLDocument create(response, NULL);

	std::map<std::string, std::vector<std::string>> toCompare {
		{"Content-Type", {"text/html"}}
	};

	std::map<std::string, std::vector<std::string>> headers {
		{"Status", {"301 Moved Permanently"}},
		{"Content-Type", {"text/html"}}
	};

	EXPECT_EQ(HTTPStatus::MOVED_PERMANENTLY, create.checkByStatusHeader(headers));
	EXPECT_EQ(static_cast<std::size_t>(1), headers.size());
	EXPECT_EQ(toCompare, headers);
}

TEST(CreateCGIHTMLDocumentTest, checkByStatusHeader_doesntHaveHeaderStatus){

	std::string headers_part = "Content-Length: 42\r\nContent-Type: text/html";

	HTTPResponse response(NULL);

	CreateCGIHTMLDocument create(response, NULL);

	std::map<std::string, std::vector<std::string>> toCompare {
		{"Content-Type", {"text/html"}},
		{"Server", {"fakeServer"}}
	};

	std::map<std::string, std::vector<std::string>> headers {
		{"Content-Type", {"text/html"}},
		{"Server", {"fakeServer"}}
	};

	EXPECT_EQ(HTTPStatus::OK, create.checkByStatusHeader(headers));
	EXPECT_EQ(static_cast<std::size_t>(2), headers.size());
	EXPECT_EQ(toCompare, headers);
}