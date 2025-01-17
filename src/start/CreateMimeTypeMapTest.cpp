#include "../../libs/googletest/googlemock/include/gmock/gmock.h"
#include "../../libs/googletest/googletest/include/gtest/gtest.h"
#include "CreateMimeTypeMap.hpp"

TEST(CreateMimeTypeMapTest, lineHasAMimetypeAndAtLeastOneExtesion_emptyLine) {
  CreateMimeTypeMap create;

  std::string theLine("");
  bool test = create.lineHasAMimetypeAndAtLeastOneExtesion(theLine);
  EXPECT_FALSE(test);
}

TEST(CreateMimeTypeMapTest,
     lineHasAMimetypeAndAtLeastOneExtesion_lineHasOnlySpaces) {
  CreateMimeTypeMap create;

  std::string theLine("   ");
  bool test = create.lineHasAMimetypeAndAtLeastOneExtesion(theLine);
  EXPECT_FALSE(test);
}

TEST(CreateMimeTypeMapTest,
     lineHasAMimetypeAndAtLeastOneExtesion_lineHasOneWord) {
  CreateMimeTypeMap create;

  std::string theLine("foo");
  bool test = create.lineHasAMimetypeAndAtLeastOneExtesion(theLine);
  EXPECT_FALSE(test);
}

TEST(CreateMimeTypeMapTest,
     lineHasAMimetypeAndAtLeastOneExtesion_lineHasOneWordBetweenSpaces) {
  CreateMimeTypeMap create;

  std::string theLine("  foo  ");
  bool test = create.lineHasAMimetypeAndAtLeastOneExtesion(theLine);
  EXPECT_FALSE(test);
}

TEST(CreateMimeTypeMapTest,
     lineHasAMimetypeAndAtLeastOneExtesion_lineHasOneWordAndEndsWithSpaces) {
  CreateMimeTypeMap create;

  std::string theLine("foo  ");
  bool test = create.lineHasAMimetypeAndAtLeastOneExtesion(theLine);
  EXPECT_FALSE(test);
}

TEST(CreateMimeTypeMapTest,
     lineHasAMimetypeAndAtLeastOneExtesion_lineHasOneWordAndStartsWithSpaces) {
  CreateMimeTypeMap create;

  std::string theLine("   foo");
  bool test = create.lineHasAMimetypeAndAtLeastOneExtesion(theLine);
  EXPECT_FALSE(test);
}

TEST(CreateMimeTypeMapTest,
     lineHasAMimetypeAndAtLeastOneExtesion_lineHasTwoWords) {
  CreateMimeTypeMap create;

  std::string theLine("foo bar");
  bool test = create.lineHasAMimetypeAndAtLeastOneExtesion(theLine);
  EXPECT_TRUE(test);
}

TEST(CreateMimeTypeMapTest,
     lineHasAMimetypeAndAtLeastOneExtesion_lineHasTwoWordsBetweenSpaces) {
  CreateMimeTypeMap create;

  std::string theLine("  foo bar  ");
  bool test = create.lineHasAMimetypeAndAtLeastOneExtesion(theLine);
  EXPECT_TRUE(test);
}

TEST(CreateMimeTypeMapTest,
     lineHasAMimetypeAndAtLeastOneExtesion_lineHasTwoWordsAndStartsWithSpaces) {
  CreateMimeTypeMap create;

  std::string theLine("  foo bar");
  bool test = create.lineHasAMimetypeAndAtLeastOneExtesion(theLine);
  EXPECT_TRUE(test);
}

TEST(CreateMimeTypeMapTest,
     lineHasAMimetypeAndAtLeastOneExtesion_lineHasTwoWordsAndEndsWithSpaces) {
  CreateMimeTypeMap create;

  std::string theLine("foo bar  ");
  bool test = create.lineHasAMimetypeAndAtLeastOneExtesion(theLine);
  EXPECT_TRUE(test);
}

TEST(CreateMimeTypeMapTest,
     lineHasAMimetypeAndAtLeastOneExtesion_lineHasThreeWords) {
  CreateMimeTypeMap create;

  std::string theLine("foo bar top");
  bool test = create.lineHasAMimetypeAndAtLeastOneExtesion(theLine);
  EXPECT_TRUE(test);
}

TEST(CreateMimeTypeMapTest,
     lineHasAMimetypeAndAtLeastOneExtesion_lineHasThreeWordsBetweenSpaces) {
  CreateMimeTypeMap create;

  std::string theLine("  foo bar top  ");
  bool test = create.lineHasAMimetypeAndAtLeastOneExtesion(theLine);
  EXPECT_TRUE(test);
}

TEST(
    CreateMimeTypeMapTest,
    lineHasAMimetypeAndAtLeastOneExtesion_lineHasThreeWordsAndStartsWithSpaces) {
  CreateMimeTypeMap create;

  std::string theLine("  foo bar top");
  bool test = create.lineHasAMimetypeAndAtLeastOneExtesion(theLine);
  EXPECT_TRUE(test);
}

TEST(CreateMimeTypeMapTest,
     lineHasAMimetypeAndAtLeastOneExtesion_lineHasThreeWordsAndEndsWithSpaces) {
  CreateMimeTypeMap create;

  std::string theLine("foo bar top  ");
  bool test = create.lineHasAMimetypeAndAtLeastOneExtesion(theLine);
  EXPECT_TRUE(test);
}

//-----------------------------------------------------

TEST(CreateMimeTypeMapTest, areLinesValid_emptyMap) {
  CreateMimeTypeMap create;
  std::map<int, std::string> mapToTest;

  error::Status isValid = create.areLinesValid(mapToTest);

  EXPECT_FALSE(isValid.ok());

  std::string errorMessage = isValid.message();

  EXPECT_EQ("The mimetype file is empty", errorMessage);
}

TEST(CreateMimeTypeMapTest, areLinesValid_mapWithOneLineAndThisLineIsValid) {
  CreateMimeTypeMap create;
  std::map<int, std::string> mapToTest;
  mapToTest.insert(std::make_pair(1, "aaa bbb"));

  error::Status isValid = create.areLinesValid(mapToTest);

  EXPECT_TRUE(isValid.ok());
}

TEST(CreateMimeTypeMapTest, areLinesValid_mapWithOneLineAndThisLineIsInvalid) {
  CreateMimeTypeMap create;
  std::map<int, std::string> mapToTest;
  mapToTest.insert(std::make_pair(1, "zzz"));

  error::Status isValid = create.areLinesValid(mapToTest);

  EXPECT_FALSE(isValid.ok());

  std::string errorMessage = isValid.message();

  EXPECT_EQ(
      "The line: 1 is not valid, if the line isn't a line break, it must have "
      "at least one mime type and one extesion",
      errorMessage);
}

TEST(CreateMimeTypeMapTest, areLinesValid_mapWithTwoLinesAndBothAreValid) {
  CreateMimeTypeMap create;
  std::map<int, std::string> mapToTest;
  mapToTest.insert(std::make_pair(1, "aaa bbb"));
  mapToTest.insert(std::make_pair(2, "zzz    yyy"));

  error::Status isValid = create.areLinesValid(mapToTest);

  EXPECT_TRUE(isValid.ok());
}

TEST(CreateMimeTypeMapTest, areLinesValid_mapWithTwoLinesTheFirstIsInvalid) {
  CreateMimeTypeMap create;
  std::map<int, std::string> mapToTest;
  mapToTest.insert(std::make_pair(1, "zzz"));
  mapToTest.insert(std::make_pair(2, "zzz    yyy"));

  error::Status isValid = create.areLinesValid(mapToTest);

  EXPECT_FALSE(isValid.ok());

  std::string errorMessage = isValid.message();

  EXPECT_EQ(
      "The line: 1 is not valid, if the line isn't a line break, it must have "
      "at least one mime type and one extesion",
      errorMessage);
}

TEST(CreateMimeTypeMapTest, areLinesValid_mapWithTwoLinesTheSecondIsInvalid) {
  CreateMimeTypeMap create;
  std::map<int, std::string> mapToTest;
  mapToTest.insert(std::make_pair(1, "zzz   yyy"));
  mapToTest.insert(std::make_pair(2, "zzz   "));

  error::Status isValid = create.areLinesValid(mapToTest);

  EXPECT_FALSE(isValid.ok());

  std::string errorMessage = isValid.message();

  EXPECT_EQ(
      "The line: 2 is not valid, if the line isn't a line break, it must have "
      "at least one mime type and one extesion",
      errorMessage);
}

//-----------------------------------------------------

TEST(CreateMimeTypeMapTest,
     createAMapOfMimetypeFromAValidLine_lineWithTwoWords) {
  std::map<std::string, std::string> mapToCompare;
  mapToCompare.insert(std::make_pair("extension", "mime"));

  CreateMimeTypeMap create;

  std::map<std::string, std::string> map =
      create.createAMapOfMimetypeFromAValidLine("mime extension");

  EXPECT_EQ(mapToCompare, map);
}

TEST(CreateMimeTypeMapTest, createVectorOfMimeTypesPairs_lineWithThreeWords) {
  std::map<std::string, std::string> mapToCompare;
  mapToCompare.insert(std::make_pair("pdf", "mime"));
  mapToCompare.insert(std::make_pair("jpeg", "mime"));

  CreateMimeTypeMap create;

  std::map<std::string, std::string> map =
      create.createAMapOfMimetypeFromAValidLine("mime pdf jpeg");

  EXPECT_EQ(mapToCompare, map);
}

//-----------------------------------------------------

TEST(CreateMimeTypeMapTest, readLines_emptyInput) {
  CreateMimeTypeMap create;

  std::map<int, std::string> mapToCompare;

  std::stringstream ss("");

  std::map<int, std::string> mapLines = create.readLines(ss);

  EXPECT_EQ(mapToCompare, mapLines);
}

TEST(CreateMimeTypeMapTest, readLines_oneLineButItIsOnlyAnNewLineCharacter) {
  CreateMimeTypeMap create;

  std::map<int, std::string> mapToCompare;

  std::stringstream ss("\n");
  std::map<int, std::string> mapLines = create.readLines(ss);

  EXPECT_EQ(mapToCompare, mapLines);
}

TEST(CreateMimeTypeMapTest, readLines_inputWithOnelineWithoutNewLineCharacter) {
  CreateMimeTypeMap create;

  std::map<int, std::string> mapToCompare;
  mapToCompare.insert(std::make_pair(1, "foo bar"));

  std::stringstream ss("foo bar");

  std::map<int, std::string> mapLines = create.readLines(ss);

  EXPECT_EQ(mapToCompare, mapLines);
}

TEST(CreateMimeTypeMapTest, readLines_inputWithOnelineWithNewLineCharacter) {
  CreateMimeTypeMap create;

  std::map<int, std::string> mapToCompare;
  mapToCompare.insert(std::make_pair(1, "foo bar"));

  std::stringstream ss("foo bar\n");

  std::map<int, std::string> mapLines = create.readLines(ss);

  EXPECT_EQ(mapToCompare, mapLines);
}

TEST(CreateMimeTypeMapTest,
     readLines_inputWithTwoLinesButTheLastWithoutNewLineCharacter) {
  CreateMimeTypeMap create;

  std::map<int, std::string> mapToCompare;
  mapToCompare.insert(std::make_pair(1, "foo bar"));
  mapToCompare.insert(std::make_pair(2, "aaa bbb"));

  std::stringstream ss("foo bar\naaa bbb");

  std::map<int, std::string> mapLines = create.readLines(ss);

  EXPECT_EQ(mapToCompare, mapLines);
}

TEST(CreateMimeTypeMapTest,
     readLines_inputWithTwoLinesButTheLastWithNewLineCharacter) {
  CreateMimeTypeMap create;

  std::map<int, std::string> mapToCompare;
  mapToCompare.insert(std::make_pair(1, "foo bar"));
  mapToCompare.insert(std::make_pair(2, "aaa bbb"));

  std::stringstream ss("foo bar\naaa bbb\n");

  std::map<int, std::string> mapLines = create.readLines(ss);

  EXPECT_EQ(mapToCompare, mapLines);
}

TEST(CreateMimeTypeMapTest, readLines_inputWithTwoLinesButTheFirstIsEmpty) {
  CreateMimeTypeMap create;

  std::map<int, std::string> mapToCompare;
  mapToCompare.insert(std::make_pair(2, "aaa bbb"));

  std::stringstream ss("\naaa bbb\n");

  std::map<int, std::string> mapLines = create.readLines(ss);

  EXPECT_EQ(mapToCompare, mapLines);
}

TEST(CreateMimeTypeMapTest, readLines_inputWithTwoLinesButTheLastIsEmpty) {
  CreateMimeTypeMap create;

  std::map<int, std::string> mapToCompare;
  mapToCompare.insert(std::make_pair(1, "aaa bbb"));

  std::stringstream ss("aaa bbb\n\n");

  std::map<int, std::string> mapLines = create.readLines(ss);

  EXPECT_EQ(mapToCompare, mapLines);
}

TEST(CreateMimeTypeMapTest, readLines_inputWithThreeLinesTheFirstIsEmpty) {
  CreateMimeTypeMap create;

  std::map<int, std::string> mapToCompare;
  mapToCompare.insert(std::make_pair(2, "foo bar"));
  mapToCompare.insert(std::make_pair(3, "aaa bbb"));

  std::stringstream ss("\nfoo bar\naaa bbb\n");

  std::map<int, std::string> mapLines = create.readLines(ss);

  EXPECT_EQ(mapToCompare, mapLines);
}

TEST(CreateMimeTypeMapTest, readLines_inputWithThreeLinesTheMiddleLineIsEmpty) {
  CreateMimeTypeMap create;

  std::map<int, std::string> mapToCompare;
  mapToCompare.insert(std::make_pair(1, "foo bar"));
  mapToCompare.insert(std::make_pair(3, "aaa bbb"));

  std::stringstream ss("foo bar\n\naaa bbb\n");

  std::map<int, std::string> mapLines = create.readLines(ss);

  EXPECT_EQ(mapToCompare, mapLines);
}

TEST(CreateMimeTypeMapTest, readLines_inputWithThreeLinesTheLastIsEmpty) {
  CreateMimeTypeMap create;

  std::map<int, std::string> mapToCompare;
  mapToCompare.insert(std::make_pair(1, "foo bar"));
  mapToCompare.insert(std::make_pair(2, "aaa bbb"));

  std::stringstream ss("foo bar\naaa bbb\n\n");

  std::map<int, std::string> mapLines = create.readLines(ss);

  EXPECT_EQ(mapToCompare, mapLines);
}

//-----------------------------------------------------

TEST(CreateMimeTypeMapTest,
     createAMapOfMimetypeFromAValidLinesMap_mapWithOneLine1) {
  std::map<std::string, std::string> mapToCompare;
  mapToCompare.insert(std::make_pair("aaa", "mime"));

  std::map<int, std::string> mapFakeLines;
  mapFakeLines.insert(std::make_pair(1, "mime aaa"));

  CreateMimeTypeMap create;
  std::map<std::string, std::string> mapMimeType =
      create.createAMapOfMimetypeFromAValidLinesMap(mapFakeLines);

  EXPECT_EQ(mapToCompare, mapMimeType);
}

TEST(CreateMimeTypeMapTest,
     createAMapOfMimetypeFromAValidLinesMap_mapWithOneLine2) {
  std::map<std::string, std::string> mapToCompare;
  mapToCompare.insert(std::make_pair("aaa", "mime"));
  mapToCompare.insert(std::make_pair("bbb", "mime"));

  std::map<int, std::string> mapFakeLines;
  mapFakeLines.insert(std::make_pair(1, "mime aaa bbb"));

  CreateMimeTypeMap create;
  std::map<std::string, std::string> mapMimeType =
      create.createAMapOfMimetypeFromAValidLinesMap(mapFakeLines);

  EXPECT_EQ(mapToCompare, mapMimeType);
}

TEST(CreateMimeTypeMapTest,
     createAMapOfMimetypeFromAValidLinesMap_mapWithTwoLines1) {
  std::map<std::string, std::string> mapToCompare;
  mapToCompare.insert(std::make_pair("aaa", "mime"));
  mapToCompare.insert(std::make_pair("bbb", "mime"));
  mapToCompare.insert(std::make_pair("ccc", "mime2"));
  mapToCompare.insert(std::make_pair("ddd", "mime2"));

  std::map<int, std::string> mapFakeLines;
  mapFakeLines.insert(std::make_pair(1, "mime aaa bbb"));
  mapFakeLines.insert(std::make_pair(2, "mime2 ccc ddd"));

  CreateMimeTypeMap create;
  std::map<std::string, std::string> mapMimeType =
      create.createAMapOfMimetypeFromAValidLinesMap(mapFakeLines);

  EXPECT_EQ(mapToCompare, mapMimeType);
}

TEST(CreateMimeTypeMapTest,
     createAMapOfMimetypeFromAValidLinesMap_mapWithTwoLines2) {
  std::map<std::string, std::string> mapToCompare;
  mapToCompare.insert(std::make_pair("aaa", "mime"));
  mapToCompare.insert(std::make_pair("bbb", "mime"));
  mapToCompare.insert(std::make_pair("ccc", "mime2"));

  std::map<int, std::string> mapFakeLines;
  mapFakeLines.insert(std::make_pair(1, "mime aaa bbb"));
  mapFakeLines.insert(std::make_pair(2, "mime2 ccc"));

  CreateMimeTypeMap create;
  std::map<std::string, std::string> mapMimeType =
      create.createAMapOfMimetypeFromAValidLinesMap(mapFakeLines);

  EXPECT_EQ(mapToCompare, mapMimeType);
}

TEST(CreateMimeTypeMapTest,
     createAMapOfMimetypeFromAValidLinesMap_mapWithTwoLines3) {
  std::map<std::string, std::string> mapToCompare;
  mapToCompare.insert(std::make_pair("aaa", "mime"));
  mapToCompare.insert(std::make_pair("bbb", "mime2"));
  mapToCompare.insert(std::make_pair("ccc", "mime2"));

  std::map<int, std::string> mapFakeLines;
  mapFakeLines.insert(std::make_pair(1, "mime aaa"));
  mapFakeLines.insert(std::make_pair(2, "mime2 bbb ccc"));

  CreateMimeTypeMap create;
  std::map<std::string, std::string> mapMimeType =
      create.createAMapOfMimetypeFromAValidLinesMap(mapFakeLines);

  EXPECT_EQ(mapToCompare, mapMimeType);
}
