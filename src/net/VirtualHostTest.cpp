#include "../../libs/googletest/googlemock/include/gmock/gmock.h"
#include "../../libs/googletest/googletest/include/gtest/gtest.h"

#include "VirtualHost.hpp"

TEST(VirtualHostTest, equalsOperator){

	VirtualHost a;
	a.setPort(100);
	a.setServername("foo");

	VirtualHost b;
	b.setPort(100);
	b.setServername("foo");

	VirtualHost c;
	c.setPort(42);
	c.setServername("foo");

	VirtualHost d;
	d.setPort(100);
	d.setServername("bar");

	EXPECT_TRUE((a == b));
	EXPECT_FALSE((a == c));
	EXPECT_FALSE((a == d));
}