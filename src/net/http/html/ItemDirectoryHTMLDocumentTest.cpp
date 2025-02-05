#include "../../../../libs/googletest/googlemock/include/gmock/gmock.h"
#include "../../../../libs/googletest/googletest/include/gtest/gtest.h"

#include "ItemDirectoryHTMLDocument.hpp"

// ------------------------------------------------------------------------

TEST(ItemDirectoryHTMLDocumentTest, equals_operator) {
  ItemDirectoryHTMLDocument a("a", 0, 0, false);
  ItemDirectoryHTMLDocument b("a",0, 0, false);
  ItemDirectoryHTMLDocument c("c",0, 0, false);

  EXPECT_TRUE((a == b));
  EXPECT_FALSE((a == c));
}

// ------------------------------------------------------------------------

TEST(ItemDirectoryHTMLDocumentTest, minorOperator_onlyFiles) {
  ItemDirectoryHTMLDocument a("a", 0, 0, false);
  ItemDirectoryHTMLDocument b("a", 0, 0, false);
  ItemDirectoryHTMLDocument c("b", 0, 0, false);

  EXPECT_FALSE((a < b));
  EXPECT_TRUE((a < c));
  EXPECT_FALSE((c < a));
}

TEST(ItemDirectoryHTMLDocumentTest, minorOperator_onlyDirectories) {
  ItemDirectoryHTMLDocument a("a", 0, 0, true);
  ItemDirectoryHTMLDocument b("a", 0, 0, true);
  ItemDirectoryHTMLDocument c("b", 0, 0, true);

  EXPECT_FALSE((a < b));
  EXPECT_TRUE((a < c));
  EXPECT_FALSE((c < a));
}

TEST(
    ItemDirectoryHTMLDocumentTest,
    minorOperator_mixFileAndDirectoryOneOfEach_fileNameIsAandDirectoryNameIsB) {
  ItemDirectoryHTMLDocument a("a", 0, 0, false);
  ItemDirectoryHTMLDocument b("b", 0, 0, true);

  EXPECT_FALSE((a < b));
  EXPECT_TRUE((b < a));
}

TEST(
    ItemDirectoryHTMLDocumentTest,
    minorOperator_mixFileAndDirectoryOneOfEach_fileNameIsBandDirectoryNameIsA) {
  ItemDirectoryHTMLDocument a("b", 0, 0, false);
  ItemDirectoryHTMLDocument b("a", 0, 0, true);

  EXPECT_FALSE((a < b));
  EXPECT_TRUE((b < a));
}

// ------------------------------------------------------------------------

TEST(ItemDirectoryHTMLDocumentTest, getPath_toDirectoryThePathDoesntHasASlash){
	ItemDirectoryHTMLDocument item("a", 0, 0, true);

	EXPECT_EQ("a/", item.getPathFullEncoded());
}

TEST(ItemDirectoryHTMLDocumentTest, getPath_toDirectoryThePathHasASlash){
	ItemDirectoryHTMLDocument item("a/", 0, 0, true);

	EXPECT_EQ("a/", item.getPathFullEncoded());
}

TEST(ItemDirectoryHTMLDocumentTest, getPath_toFile){
	ItemDirectoryHTMLDocument item("a", 0, 0, false);

	EXPECT_EQ("a", item.getPathFullEncoded());
}

// ------------------------------------------------------------------------

TEST(ItemDirectoryHTMLDocumentTest, getSizeInBytes_toDirectory){
	ItemDirectoryHTMLDocument item("a", 0, 10, true);

	EXPECT_EQ("-", item.getSizeInBytes());
}

TEST(ItemDirectoryHTMLDocumentTest, getSizeInBytes_toFile){
	ItemDirectoryHTMLDocument item("a", 0, 10, false);

	EXPECT_EQ("10", item.getSizeInBytes());
}

// ------------------------------------------------------------------------

TEST(ItemDirectoryHTMLDocumentTest, getModificationTime){
	ItemDirectoryHTMLDocument item("a", 1112486462, 10, false);

	EXPECT_EQ("10", item.getSizeInBytes());

	EXPECT_EQ("03-Apr-2005 00:01", item.getModificationTime());
}

