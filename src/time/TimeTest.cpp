#include "../../libs/googletest/googlemock/include/gmock/gmock.h"
#include "../../libs/googletest/googletest/include/gtest/gtest.h"

#include "Time.hpp"

TEST(TimeTest, convertTimeToHTTPHeaderPattern){

	Time time;

	std::string timez = time.convertTimeToHTTPHeaderPattern(1112486462);

	EXPECT_EQ("Sun, 03 Apr 2005 00:01:02 GMT", timez);
}

TEST(TimeTest, convertTimeToItemDirectoryHTML){
	Time time;

	std::string timez = time.convertTimeToItemDirectoryHTML(1112486462);

	EXPECT_EQ("03-Apr-2005 00:01", timez);
}