#include "../../../libs/googletest/googlemock/include/gmock/gmock.h"
#include "../../../libs/googletest/googletest/include/gtest/gtest.h"
#include "MimeType.hpp"

TEST(MimeTypeTest, getExtensionFromPath_emptyPath) {
  MimeType mime;

  std::string theExtesion = mime.getExtensionFromPath("");

  EXPECT_EQ("", theExtesion);
}

TEST(MimeTypeTest, getExtensionFromPath_emptyHasOnlyADot) {
  MimeType mime;

  std::string theExtesion = mime.getExtensionFromPath(".");

  EXPECT_EQ("", theExtesion);
}

TEST(MimeTypeTest, getExtensionFromPath_pathWithoutDot) {
  MimeType mime;

  std::string theExtesion = mime.getExtensionFromPath("a");

  EXPECT_EQ("a", theExtesion);
}

TEST(MimeTypeTest, getExtensionFromPath_pathStartWithADot) {
  MimeType mime;

  std::string theExtesion = mime.getExtensionFromPath(".f");

  EXPECT_EQ("f", theExtesion);
}

TEST(MimeTypeTest, getExtensionFromPath_pathEndsWithADot) {
  MimeType mime;

  std::string theExtesion = mime.getExtensionFromPath("f.");

  EXPECT_EQ("", theExtesion);
}

TEST(MimeTypeTest, getExtensionFromPath_pathHasADotInItsMiddel) {
  MimeType mime;

  std::string theExtesion = mime.getExtensionFromPath("a.b");

  EXPECT_EQ("b", theExtesion);
}

// -------------------------------------------------------------

TEST(MimeTypeTest, getMimeTypeByFileExtesion_mimeTypeMapIsEmpty) {
  MimeType mime;
  std::map<std::string, std::string> fakeGlobalMimetypeMap;
  MimeType::setMimetypeMap(fakeGlobalMimetypeMap);

  std::string mimeType = mime.getMimeTypeByFileExtesion("file.pdf");

  EXPECT_EQ("application/octet-stream", mimeType);
}

TEST(MimeTypeTest,
     getMimeTypeByFileExtesion_mimeTypeMapWithOneExtesionAndWithOneMatch) {
  MimeType mime;
  std::map<std::string, std::string> fakeGlobalMimetypeMap;
  fakeGlobalMimetypeMap.insert(std::make_pair("pdf", "application/pdf"));

  MimeType::setMimetypeMap(fakeGlobalMimetypeMap);

  std::string mimeType = mime.getMimeTypeByFileExtesion("file.pdf");

  EXPECT_EQ("application/pdf", mimeType);
}

TEST(MimeTypeTest,
     getMimeTypeByFileExtesion_mimeTypeMapWithOneExtesionButWithoutMatch) {
  MimeType mime;
  std::map<std::string, std::string> fakeGlobalMimetypeMap;
  fakeGlobalMimetypeMap.insert(std::make_pair("pdf", "application/pdf"));

  MimeType::setMimetypeMap(fakeGlobalMimetypeMap);

  std::string mimeType = mime.getMimeTypeByFileExtesion("file.xxx");

  EXPECT_EQ("application/octet-stream", mimeType);
}
