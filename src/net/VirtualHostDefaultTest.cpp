#include "../../libs/googletest/googlemock/include/gmock/gmock.h"
#include "../../libs/googletest/googletest/include/gtest/gtest.h"

#include "VirtualHostDefault.hpp"

TEST(VirtualHostDefault, equalsOperator){

	VirtualHostDefault a;
	a.setPort(100);
	a.setServerName("foo");

	VirtualHostDefault b;
	b.setPort(100);
	b.setServerName("foo");

	VirtualHostDefault c;
	c.setPort(42);
	c.setServerName("foo");

	VirtualHostDefault d;
	d.setPort(100);
	d.setServerName("bar");

	EXPECT_TRUE((a == b));
	EXPECT_FALSE((a == c));
	EXPECT_FALSE((a == d));
}