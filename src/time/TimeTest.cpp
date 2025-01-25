#include "../../libs/googletest/googlemock/include/gmock/gmock.h"
#include "../../libs/googletest/googletest/include/gtest/gtest.h"

#include "Time.hpp"

#include <iostream>

TEST(TimeTest, convertTimeToHTTPRequestPattern){

	Time time;

	std::string timez = time.convertTimeToHTTPRequestPattern(1737763200);

	EXPECT_EQ("Sat, 25 Jan 2025 00:00:00 GMT", timez);
}