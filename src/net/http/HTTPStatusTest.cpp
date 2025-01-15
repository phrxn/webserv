#include "../../../libs/googletest/googlemock/include/gmock/gmock.h"
#include "../../../libs/googletest/googletest/include/gtest/gtest.h"

#include "HTTPStatus.hpp"

TEST(HTTPStatusTest, getStringToStatus_validValue){

	HTTPStatus httpStatus;

	//valid value
	EXPECT_EQ(HTTPStatus::OK, httpStatus.getStringToStatus("OK"));
}

TEST(HTTPStatusTest, getStringToStatus_invalidValue){

	HTTPStatus httpStatus;

	//valid value
	EXPECT_EQ(HTTPStatus::INVALID, httpStatus.getStringToStatus("zzzfoofoozzz"));
}

TEST(HTTPStatusTest, getStatusToString){

	HTTPStatus httpStatus;

	EXPECT_EQ("OK", httpStatus.getStatusToString(HTTPStatus::OK));
}