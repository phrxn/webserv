#include "../../../libs/googletest/googlemock/include/gmock/gmock.h"
#include "../../../libs/googletest/googletest/include/gtest/gtest.h"

#include "HTTPTypeOfPages.hpp"

TEST(HTTPTypeOfPages, getTypeOfPathFromPath_pathOnlyWithPHP){

	HTTPTypeOfPages h1;

	EXPECT_EQ(HTTPTypeOfPages::PHP, h1.getTypeOfPathFromPath(".php"));
}

TEST(HTTPTypeOfPages, getTypeOfPathFromPath_pathStartWithPHP){

	HTTPTypeOfPages h1;

	EXPECT_EQ(HTTPTypeOfPages::PHP, h1.getTypeOfPathFromPath(".php/foo"));
}

TEST(HTTPTypeOfPages, getTypeOfPathFromPath_pathHavePHPBetweenOtherThings){

	HTTPTypeOfPages h1;

	EXPECT_EQ(HTTPTypeOfPages::PHP, h1.getTypeOfPathFromPath("/bar/foo.php/zzz"));
}


TEST(HTTPTypeOfPages, getTypeOfPathFromPath_pathOnlyWithPY){

	HTTPTypeOfPages h1;

	EXPECT_EQ(HTTPTypeOfPages::PYTHON, h1.getTypeOfPathFromPath(".py"));
}

TEST(HTTPTypeOfPages, getTypeOfPathFromPath_pathStartWithPY){

	HTTPTypeOfPages h1;

	EXPECT_EQ(HTTPTypeOfPages::PYTHON, h1.getTypeOfPathFromPath(".py/foo"));
}

TEST(HTTPTypeOfPages, getTypeOfPathFromPath_pathHavePYBetweenOtherThings){

	HTTPTypeOfPages h1;

	EXPECT_EQ(HTTPTypeOfPages::PYTHON, h1.getTypeOfPathFromPath("/bar/foo.py/zzz"));
}


TEST(HTTPTypeOfPages, getTypeOfPathFromPath_pathDoesntHavePHPorPY){

	HTTPTypeOfPages h1;

	EXPECT_EQ(HTTPTypeOfPages::STATIC, h1.getTypeOfPathFromPath("/bar/foo.xxx/zzz"));
}

TEST(HTTPTypeOfPages, getTypeOfPathFromPath_pathEmpty){

	HTTPTypeOfPages h1;

	EXPECT_EQ(HTTPTypeOfPages::STATIC, h1.getTypeOfPathFromPath(""));
}