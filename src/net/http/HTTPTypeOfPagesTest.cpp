#include "../../../libs/googletest/googlemock/include/gmock/gmock.h"
#include "../../../libs/googletest/googletest/include/gtest/gtest.h"

#include "HTTPTypeOfPages.hpp"

TEST(HTTPTypeOfPagesTest, getStringToTypeOfPageFromPath_emptyPath){

	HTTPTypeOfPages h1;

	EXPECT_EQ(HTTPTypeOfPages::STATIC, h1.getStringToTypeOfPageFromPath(""));
}

TEST(HTTPTypeOfPagesTest, getStringToTypeOfPageFromPath_withOneLetter){

	HTTPTypeOfPages h1;

	EXPECT_EQ(HTTPTypeOfPages::STATIC, h1.getStringToTypeOfPageFromPath("a"));
}

TEST(HTTPTypeOfPagesTest, getStringToTypeOfPageFromPath_thePathIsOnlyPHPExtension){

	HTTPTypeOfPages h1;

	EXPECT_EQ(HTTPTypeOfPages::PHP, h1.getStringToTypeOfPageFromPath(".php"));
}

TEST(HTTPTypeOfPagesTest, getStringToTypeOfPageFromPath_thePathIsOnlyPythonExtension){

	HTTPTypeOfPages h1;

	EXPECT_EQ(HTTPTypeOfPages::PYTHON, h1.getStringToTypeOfPageFromPath(".py"));
}

TEST(HTTPTypeOfPagesTest, getStringToTypeOfPageFromPath_thePathIsOnlyOneWordWithPHPExtension){

	HTTPTypeOfPages h1;

	EXPECT_EQ(HTTPTypeOfPages::PHP, h1.getStringToTypeOfPageFromPath("a.php"));
}

TEST(HTTPTypeOfPagesTest, getStringToTypeOfPageFromPath_thePathIsOnlyOneWordWithPythonExtension){

	HTTPTypeOfPages h1;

	EXPECT_EQ(HTTPTypeOfPages::PYTHON, h1.getStringToTypeOfPageFromPath("a.py"));
}



// --------------------------------------------

TEST(HTTPTypeOfPagesTest, getTypeOfPathFromPath_pathOnlyWithPHP){

	HTTPTypeOfPages h1;

	EXPECT_EQ(HTTPTypeOfPages::PHP, h1.getTypeOfPathFromPath(".php"));
}

TEST(HTTPTypeOfPagesTest, getTypeOfPathFromPath_pathStartWithPHP){

	HTTPTypeOfPages h1;

	EXPECT_EQ(HTTPTypeOfPages::PHP, h1.getTypeOfPathFromPath(".php/foo"));
}

TEST(HTTPTypeOfPagesTest, getTypeOfPathFromPath_pathHavePHPBetweenOtherThings){

	HTTPTypeOfPages h1;

	EXPECT_EQ(HTTPTypeOfPages::PHP, h1.getTypeOfPathFromPath("/bar/foo.php/zzz"));
}


TEST(HTTPTypeOfPagesTest, getTypeOfPathFromPath_pathOnlyWithPY){

	HTTPTypeOfPages h1;

	EXPECT_EQ(HTTPTypeOfPages::PYTHON, h1.getTypeOfPathFromPath(".py"));
}

TEST(HTTPTypeOfPagesTest, getTypeOfPathFromPath_pathStartWithPY){

	HTTPTypeOfPages h1;

	EXPECT_EQ(HTTPTypeOfPages::PYTHON, h1.getTypeOfPathFromPath(".py/foo"));
}

TEST(HTTPTypeOfPagesTest, getTypeOfPathFromPath_pathHavePYBetweenOtherThings){

	HTTPTypeOfPages h1;

	EXPECT_EQ(HTTPTypeOfPages::PYTHON, h1.getTypeOfPathFromPath("/bar/foo.py/zzz"));
}


TEST(HTTPTypeOfPagesTest, getTypeOfPathFromPath_pathDoesntHavePHPorPY){

	HTTPTypeOfPages h1;

	EXPECT_EQ(HTTPTypeOfPages::STATIC, h1.getTypeOfPathFromPath("/bar/foo.xxx/zzz"));
}

TEST(HTTPTypeOfPagesTest, getTypeOfPathFromPath_pathEmpty){

	HTTPTypeOfPages h1;

	EXPECT_EQ(HTTPTypeOfPages::STATIC, h1.getTypeOfPathFromPath(""));
}