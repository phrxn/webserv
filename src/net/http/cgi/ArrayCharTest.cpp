#include "../../../../libs/googletest/googlemock/include/gmock/gmock.h"
#include "../../../../libs/googletest/googletest/include/gtest/gtest.h"
#include "ArrayChar.hpp"


TEST(ArrayCharTest, getPointerToArray_emptyClass) {
  ArrayChar ac;

  EXPECT_TRUE((ac.getPointerToArray() == NULL));
}

TEST(ArrayCharTest, getPointerToArray_haveOneString) {
  ArrayChar ac;

  ac.addString("one");
  char **array = ac.getPointerToArray();

  EXPECT_FALSE((array == NULL));

  ac.freePointerToArray(array);
}

TEST(ArrayCharTest, addString_areItemsInTheOrder) {
  ArrayChar ac;

  ac.addString("one");
  ac.addString("two");
  char **array = ac.getPointerToArray();

  EXPECT_TRUE((array != NULL));

  const char *toCompare[] = {"one", "two", nullptr};

  bool areArraysEquals = ac.compareCharArrays(array, toCompare);
  EXPECT_TRUE(areArraysEquals);

  ac.freePointerToArray(array);
}

TEST(ArrayCharTest, compareCharArrays_emptyArrays) {
  const char *arrayA[] = {nullptr};
  const char *arrayB[] = {nullptr};

  ArrayChar ac;
  EXPECT_TRUE(ac.compareCharArrays(arrayA, arrayB));
}

TEST(ArrayCharTest, compareCharArrays_leftArrayIsEmptyTheRightOneIsNot) {
  const char *arrayA[] = {nullptr};
  const char *arrayB[] = {"one", nullptr};

  ArrayChar ac;
  EXPECT_FALSE(ac.compareCharArrays(arrayA, arrayB));
}

TEST(ArrayCharTest, compareCharArrays_RightArrayIsEmptyTheLeftOneIsNot) {
  const char *arrayA[] = {"one", nullptr};
  const char *arrayB[] = {nullptr};

  ArrayChar ac;
  EXPECT_FALSE(ac.compareCharArrays(arrayA, arrayB));
}


TEST(ArrayCharTest, compareCharArrays_BothArraysHaveOneWordsAndThoseWordsAreEquals) {
	const char *arrayA[] = {"one", nullptr};
	const char *arrayB[] = {"one", nullptr};

	ArrayChar ac;
	EXPECT_TRUE(ac.compareCharArrays(arrayA, arrayB));
}

TEST(ArrayCharTest, compareCharArrays_BothArraysHaveOneWordsAndThoseWordsAreDifferent) {
	const char *arrayA[] = {"one", nullptr};
	const char *arrayB[] = {"two", nullptr};

	ArrayChar ac;
	EXPECT_FALSE(ac.compareCharArrays(arrayA, arrayB));
}
