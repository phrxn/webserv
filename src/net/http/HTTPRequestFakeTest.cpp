#include "../../../libs/googletest/googlemock/include/gmock/gmock.h"
#include "../../../libs/googletest/googletest/include/gtest/gtest.h"

#include "HTTPRequestFake.hpp"

TEST(HTTPRequestFakeTest, isTheHTTPHeaderComplete_emptyString){

	HTTPRequestFake http(NULL, NULL);

	EXPECT_FALSE(http.isTheHTTPHeaderComplete(""));
}

TEST(HTTPRequestFakeTest, isTheHTTPHeaderComplete_oneSpace){

	HTTPRequestFake http(NULL, NULL);

	EXPECT_FALSE(http.isTheHTTPHeaderComplete(" "));
}

TEST(HTTPRequestFakeTest, isTheHTTPHeaderComplete_return_new_line){

	HTTPRequestFake http(NULL, NULL);

	EXPECT_FALSE(http.isTheHTTPHeaderComplete("\r\n"));
}

TEST(HTTPRequestFakeTest, isTheHTTPHeaderComplete_return_new_line_return){

	HTTPRequestFake http(NULL, NULL);

	EXPECT_FALSE(http.isTheHTTPHeaderComplete("\r\n\r"));
}


TEST(HTTPRequestFakeTest, isTheHTTPHeaderComplete_only_rnrn){

	HTTPRequestFake http(NULL, NULL);

	EXPECT_TRUE(http.isTheHTTPHeaderComplete("\r\n\r\n"));
}

TEST(HTTPRequestFakeTest, isTheHTTPHeaderComplete_string_arnrn){

	HTTPRequestFake http(NULL, NULL);

	EXPECT_TRUE(http.isTheHTTPHeaderComplete("a\r\n\r\n"));
}

TEST(HTTPRequestFakeTest, isTheHTTPHeaderComplete_string_arnrna){

	HTTPRequestFake http(NULL, NULL);

	EXPECT_TRUE(http.isTheHTTPHeaderComplete("a\r\n\r\na"));
}