#include "../../../../libs/googletest/googlemock/include/gmock/gmock.h"
#include "../../../../libs/googletest/googletest/include/gtest/gtest.h"
#include "CreateDirectoryHTMLPage.hpp"

TEST(CreateDirectoryHTMLPageTest, createAnchorToPath_directoryWithPathShorterThan50Chars){

	 CreateDirectoryHTMLPage create("foo");

	ItemDirectoryHTMLDocument a("dir07__", 0, 0, true);

	std::string archorLink = create.createAnchorToPath(a);

	EXPECT_EQ("<a href=\"dir07__/\">dir07__/</a>                                          ", archorLink);
}

TEST(CreateDirectoryHTMLPageTest, createAnchorToPath_directoryWithPathWith49Chars){

	 CreateDirectoryHTMLPage create("foo");

	ItemDirectoryHTMLDocument a("dir49__890123456789012345678901234567890123456789/", 0, 0, true);

	std::string archorLink = create.createAnchorToPath(a);

	EXPECT_EQ("<a href=\"dir49__890123456789012345678901234567890123456789/\">dir49__890123456789012345678901234567890123456789/</a>", archorLink);
}

TEST(CreateDirectoryHTMLPageTest, createAnchorToPath_directoryWithPathWith50Chars){

	 CreateDirectoryHTMLPage create("foo");

	ItemDirectoryHTMLDocument a("dir50__8901234567890123456789012345678901234567890", 0, 0, true);

	std::string archorLink = create.createAnchorToPath(a);

	EXPECT_EQ("<a href=\"dir50__8901234567890123456789012345678901234567890/\">dir50__8901234567890123456789012345678901234567890</a>", archorLink);
}


TEST(CreateDirectoryHTMLPageTest, createAnchorToPath__directoryWithPathWith51Chars){

	 CreateDirectoryHTMLPage create("foo");

	ItemDirectoryHTMLDocument a("dir51__89012345678901234567890123456789012345678901/", 0, 0, true);

	std::string archorLink = create.createAnchorToPath(a);

	EXPECT_EQ("<a href=\"dir51__89012345678901234567890123456789012345678901/\">dir51__8901234567890123456789012345678901234567..&gt;</a>", archorLink);
}

//------------------------------------------------------------------

TEST(CreateDirectoryHTMLPageTest, createAnchorToPath_fileWithPathShorterThan50Chars){

	 CreateDirectoryHTMLPage create("foo");

	ItemDirectoryHTMLDocument a("file07_", 0, 0, false);

	std::string archorLink = create.createAnchorToPath(a);

	EXPECT_EQ("<a href=\"file07_\">file07_</a>                                           ", archorLink);
}

TEST(CreateDirectoryHTMLPageTest, createAnchorToPath_fileWithPathWith49Char){

	 CreateDirectoryHTMLPage create("foo");

	ItemDirectoryHTMLDocument a("file49_890123456789012345678901234567890123456789", 0, 0, false);

	std::string archorLink = create.createAnchorToPath(a);

	EXPECT_EQ("<a href=\"file49_890123456789012345678901234567890123456789\">file49_890123456789012345678901234567890123456789</a> ", archorLink);
}

TEST(CreateDirectoryHTMLPageTest, createAnchorToPath_fileWithPathWith50Char){

	 CreateDirectoryHTMLPage create("foo");

	ItemDirectoryHTMLDocument a("file50_8901234567890123456789012345678901234567890", 0, 0, false);

	std::string archorLink = create.createAnchorToPath(a);

	EXPECT_EQ("<a href=\"file50_8901234567890123456789012345678901234567890\">file50_8901234567890123456789012345678901234567890</a>", archorLink);
}

TEST(CreateDirectoryHTMLPageTest, createAnchorToPath_fileWithPathWith51Char){

	 CreateDirectoryHTMLPage create("foo");

	ItemDirectoryHTMLDocument a("file51_89012345678901234567890123456789012345678901", 0, 0, false);

	std::string archorLink = create.createAnchorToPath(a);

	EXPECT_EQ("<a href=\"file51_89012345678901234567890123456789012345678901\">file51_8901234567890123456789012345678901234567..&gt;</a>", archorLink);
}

//------------------------------------------------------------------

TEST(CreateDirectoryHTMLPageTest, formatPath_fileWithPathShorterThan50Chars) {
  CreateDirectoryHTMLPage create("foo");

  ItemDirectoryHTMLDocument a("aaaaaaaaaa", 0, 0, false);

  std::string pathFormatted = create.formatPath(a);

  EXPECT_EQ("aaaaaaaaaa", pathFormatted);
}

TEST(CreateDirectoryHTMLPageTest, formatPath_fileWithPathWith49Char) {
  CreateDirectoryHTMLPage create("foo");

  ItemDirectoryHTMLDocument a(
      "1234567890123456789012345678901234567890123456789", 0, 0, false);

  std::string pathFormatted = create.formatPath(a);

  EXPECT_EQ("1234567890123456789012345678901234567890123456789", pathFormatted);
}

TEST(CreateDirectoryHTMLPageTest, formatPath_fileWithPathWith50Char) {
  CreateDirectoryHTMLPage create("foo");

  ItemDirectoryHTMLDocument a(
      "file50_8901234567890123456789012345678901234567890", 0, 0, false);

  std::string pathFormatted = create.formatPath(a);

  EXPECT_EQ("file50_8901234567890123456789012345678901234567890",
            pathFormatted);
}

TEST(CreateDirectoryHTMLPageTest, formatPath_fileWithPathWith51Char) {
  CreateDirectoryHTMLPage create("foo");

  ItemDirectoryHTMLDocument a(
      "file51_89012345678901234567890123456789012345678901", 0, 0, false);

  std::string pathFormatted = create.formatPath(a);

  EXPECT_EQ("file51_8901234567890123456789012345678901234567..&gt;",
            pathFormatted);
}

TEST(CreateDirectoryHTMLPageTest,
     formatPath_directoryWithPathShorterThan50Chars) {
  CreateDirectoryHTMLPage create("foo");

  ItemDirectoryHTMLDocument a("aaaaaaaaa", 0, 0, true);

  std::string pathFormatted = create.formatPath(a);

  EXPECT_EQ("aaaaaaaaa/", pathFormatted);
}

TEST(CreateDirectoryHTMLPageTest, formatPath_directoryWithPathWith49Chars) {
  CreateDirectoryHTMLPage create("foo");

  ItemDirectoryHTMLDocument a(
      "123456789012345678901234567890123456789012345678", 0, 0, true);

  std::string pathFormatted = create.formatPath(a);

  EXPECT_EQ("123456789012345678901234567890123456789012345678/", pathFormatted);
}

TEST(CreateDirectoryHTMLPageTest, formatPath_directoryWithPathWith50Chars) {
  CreateDirectoryHTMLPage create("foo");

  ItemDirectoryHTMLDocument a(
      "dir50_7890123456789012345678901234567890123456789/", 0, 0, true);

  std::string pathFormatted = create.formatPath(a);

  EXPECT_EQ("dir50_7890123456789012345678901234567890123456789/",
            pathFormatted);
}

TEST(CreateDirectoryHTMLPageTest, formatPath_directoryWithPathWith51Chars) {
  CreateDirectoryHTMLPage create("foo");

  ItemDirectoryHTMLDocument a(
      "dir51_78901234567890123456789012345678901234567890/", 0, 0, true);

  std::string pathFormatted = create.formatPath(a);

  EXPECT_EQ("dir51_78901234567890123456789012345678901234567890",
            pathFormatted);
}

TEST(CreateDirectoryHTMLPageTest, formatPath_directoryWithPathWith52Chars) {
  CreateDirectoryHTMLPage create("foo");

  ItemDirectoryHTMLDocument a(
      "dir52_789012345678901234567890123456789012345678901/", 0, 0, true);

  std::string pathFormatted = create.formatPath(a);

  EXPECT_EQ("dir52_78901234567890123456789012345678901234567..&gt;",
            pathFormatted);
}

//------------------------------------------------------------------

TEST(CreateDirectoryHTMLPageTest, formatData) {

  CreateDirectoryHTMLPage create("foo");

  ItemDirectoryHTMLDocument a(
      "dir52_789012345678901234567890123456789012345678901/", 1112486462, 0, true);

  std::string dataFormatted = create.formatData(a);

  EXPECT_EQ(static_cast<std::size_t>(35), dataFormatted.size());
  EXPECT_EQ("03-Apr-2005 00:01                  ", dataFormatted);

}



//------------------------------------------------------------------


TEST(CreateDirectoryHTMLPageTest, operatorShiftLeft) {

  CreateDirectoryHTMLPage create("/");

  std::list<ItemDirectoryHTMLDocument> items {
	ItemDirectoryHTMLDocument("dir07__/",    1112486462, 4098, true),
	ItemDirectoryHTMLDocument("dir49__890123456789012345678901234567890123456789",    1112486462, 4098, true),
	ItemDirectoryHTMLDocument("dir50__8901234567890123456789012345678901234567890",   1112486462, 4098, true),
	ItemDirectoryHTMLDocument("dir51__89012345678901234567890123456789012345678901/", 1112486462, 4098, true),

	ItemDirectoryHTMLDocument("file07_",    1112486462, 1, false),
	ItemDirectoryHTMLDocument("file49_890123456789012345678901234567890123456789",   1112486462, 2, false),
	ItemDirectoryHTMLDocument("file50_8901234567890123456789012345678901234567890", 1112486462, 3, false),
	ItemDirectoryHTMLDocument("file51_89012345678901234567890123456789012345678901", 1112486462, 4, false)
  };

  for (auto& item : items) {
	create << item;
  }

  std::string html = create.str();

  std::string expected = "<html>\n" \
						 "<head><title>Index of /</title></head>\n" \
						 "<body>\n" \
						 "<h1>Index of /</h1>\n" \
						 "<hr>\n" \
						 "<pre>\n" \
						 "<a href=\"../\">../</a>\n" \
						 "<a href=\"dir07__/\">dir07__/</a>                                           03-Apr-2005 00:01                   -\n" \
						 "<a href=\"dir49__890123456789012345678901234567890123456789/\">dir49__890123456789012345678901234567890123456789/</a> 03-Apr-2005 00:01                   -\n" \
						 "<a href=\"dir50__8901234567890123456789012345678901234567890/\">dir50__8901234567890123456789012345678901234567890</a> 03-Apr-2005 00:01                   -\n" \
						 "<a href=\"dir51__89012345678901234567890123456789012345678901/\">dir51__8901234567890123456789012345678901234567..&gt;</a> 03-Apr-2005 00:01                   -\n" \
						 "<a href=\"file07_\">file07_</a>                                            03-Apr-2005 00:01                   1\n" \
						 "<a href=\"file49_890123456789012345678901234567890123456789\">file49_890123456789012345678901234567890123456789</a>  03-Apr-2005 00:01                   2\n" \
						 "<a href=\"file50_8901234567890123456789012345678901234567890\">file50_8901234567890123456789012345678901234567890</a> 03-Apr-2005 00:01                   3\n" \
						 "<a href=\"file51_89012345678901234567890123456789012345678901\">file51_8901234567890123456789012345678901234567..&gt;</a> 03-Apr-2005 00:01                   4\n" \
						 "</pre>\n" \
						 "<hr>\n" \
						 "</body>\n" \
						 "</html>\n";

	EXPECT_EQ(expected, html);
}