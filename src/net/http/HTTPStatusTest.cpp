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

//---------------------------------------------------

TEST(HTTPStatusTest, getIntToStatus_validValue){

	HTTPStatus httpStatus;

	EXPECT_EQ(HTTPStatus::NOT_FOUND, httpStatus.getIntToStatus(404));
}

TEST(HTTPStatusTest, getIntToStatus_invalidValue){

	HTTPStatus httpStatus;

	EXPECT_EQ(HTTPStatus::INVALID, httpStatus.getIntToStatus(-1));
}

