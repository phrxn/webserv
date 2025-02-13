#include "../../libs/googletest/googlemock/include/gmock/gmock.h"
#include "../../libs/googletest/googletest/include/gtest/gtest.h"

#include "VirtualHostFake.hpp"

TEST(VirtualHostFake, equalsOperator){

	VirtualHostFake a;
	a.setPort(100);
	a.setServerName("foo");

	VirtualHostFake b;
	b.setPort(100);
	b.setServerName("foo");

	VirtualHostFake c;
	c.setPort(42);
	c.setServerName("foo");

	VirtualHostFake d;
	d.setPort(100);
	d.setServerName("bar");

	EXPECT_TRUE((a == b));
	EXPECT_FALSE((a == c));
	EXPECT_FALSE((a == d));
}