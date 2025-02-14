#include "../../../libs/googletest/googlemock/include/gmock/gmock.h"
#include "../../../libs/googletest/googletest/include/gtest/gtest.h"

#include "HTTPServletManager.hpp"

TEST(HTTPServletManagerTest, absolutePathEndsWithSlash_emptyPath){

	HTTPServletManager h1(NULL, NULL);

	EXPECT_FALSE(h1.absolutePathEndsWithSlash(""));
}

TEST(HTTPServletManagerTest, absolutePathEndsWithSlash_onlySlash){

	HTTPServletManager h1(NULL, NULL);

	EXPECT_TRUE(h1.absolutePathEndsWithSlash("/"));
}

TEST(HTTPServletManagerTest, absolutePathEndsWithSlash_pathWithoutSlash){

	HTTPServletManager h1(NULL, NULL);

	EXPECT_FALSE(h1.absolutePathEndsWithSlash("/foo"));
}

TEST(HTTPServletManagerTest, absolutePathEndsWithSlash_pathEndsWithSlash){

	HTTPServletManager h1(NULL, NULL);

	EXPECT_TRUE(h1.absolutePathEndsWithSlash("/foo/"));
}