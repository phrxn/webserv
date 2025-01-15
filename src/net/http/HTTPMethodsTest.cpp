#include "../../../libs/googletest/googlemock/include/gmock/gmock.h"
#include "../../../libs/googletest/googletest/include/gtest/gtest.h"

#include "HTTPMethods.hpp"

TEST(HTTPMethodsTest, getStringToMethod_validValue){

	HTTPMethods httpStatus;

	//valid value
	EXPECT_EQ(HTTPMethods::GET, httpStatus.getStringToMethod("GET"));
}

TEST(HTTPMethodsTest, getStringToMethod_invalidValue){

	HTTPMethods httpStatus;

	//valid value
	EXPECT_EQ(HTTPMethods::INVALID, httpStatus.getStringToMethod("barbarfoo"));
}

TEST(HTTPMethodsTest, getMethodToString){

	HTTPMethods httpStatus;

	EXPECT_EQ("POST", httpStatus.getMethodToString(HTTPMethods::POST));
}