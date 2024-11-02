#include "gtest/gtest.h"

#include <string>

int main(int argc, char **argv)
{
	::testing::InitGoogleTest(&argc, argv);

	if (argc > 1)
	{
		std::string filter = argv[1];
		::testing::GTEST_FLAG(filter) = filter;
	}

	return RUN_ALL_TESTS();
}