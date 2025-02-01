#include "../../libs/googletest/googlemock/include/gmock/gmock.h"
#include "../../libs/googletest/googletest/include/gtest/gtest.h"

#include "VirtualHostDefault.hpp"

TEST(VirtualHostDefault, equalsOperator){

	VirtualHostDefault a;
	a.setPort(100);
	a.setServername("foo");

	VirtualHostDefault b;
	b.setPort(100);
	b.setServername("foo");

	VirtualHostDefault c;
	c.setPort(42);
	c.setServername("foo");

	VirtualHostDefault d;
	d.setPort(100);
	d.setServername("bar");

	EXPECT_TRUE((a == b));
	EXPECT_FALSE((a == c));
	EXPECT_FALSE((a == d));
}