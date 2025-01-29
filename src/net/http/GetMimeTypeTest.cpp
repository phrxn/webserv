#include "../../../libs/googletest/googlemock/include/gmock/gmock.h"
#include "../../../libs/googletest/googletest/include/gtest/gtest.h"
#include "GetMimeType.hpp"

TEST(GetMimeTypeTest, getExtensionFromPath_emptyPath) {
  GetMimeType mime;

  std::string theExtesion = mime.getExtensionFromPath("");

  EXPECT_EQ("", theExtesion);
}

TEST(GetMimeTypeTest, getExtensionFromPath_emptyHasOnlyADot) {
  GetMimeType mime;

  std::string theExtesion = mime.getExtensionFromPath(".");

  EXPECT_EQ("", theExtesion);
}

TEST(GetMimeTypeTest, getExtensionFromPath_pathWithoutDot) {
  GetMimeType mime;

  std::string theExtesion = mime.getExtensionFromPath("a");

  EXPECT_EQ("a", theExtesion);
}

TEST(GetMimeTypeTest, getExtensionFromPath_pathStartWithADot) {
  GetMimeType mime;

  std::string theExtesion = mime.getExtensionFromPath(".f");

  EXPECT_EQ("f", theExtesion);
}

TEST(GetMimeTypeTest, getExtensionFromPath_pathEndsWithADot) {
  GetMimeType mime;

  std::string theExtesion = mime.getExtensionFromPath("f.");

  EXPECT_EQ("", theExtesion);
}

TEST(GetMimeTypeTest, getExtensionFromPath_pathHasADotInItsMiddel) {
  GetMimeType mime;

  std::string theExtesion = mime.getExtensionFromPath("a.b");

  EXPECT_EQ("b", theExtesion);
}

// -------------------------------------------------------------

TEST(GetMimeTypeTest, getMimeTypeByFileExtesion_mimeTypeMapIsEmpty) {
  GetMimeType mime;
  std::map<std::string, std::string> fakeGlobalMimetypeMap;
  GetMimeType::setMimetypeMap(fakeGlobalMimetypeMap);

  std::string mimeType = mime.getMimeTypeByFileExtesion("file.pdf");

  EXPECT_EQ("application/octet-stream", mimeType);
}

TEST(GetMimeTypeTest,
     getMimeTypeByFileExtesion_mimeTypeMapWithOneExtesionAndWithOneMatch) {
  GetMimeType mime;
  std::map<std::string, std::string> fakeGlobalMimetypeMap;
  fakeGlobalMimetypeMap.insert(std::make_pair("pdf", "application/pdf"));

  GetMimeType::setMimetypeMap(fakeGlobalMimetypeMap);

  std::string mimeType = mime.getMimeTypeByFileExtesion("file.pdf");

  EXPECT_EQ("application/pdf", mimeType);
}

TEST(GetMimeTypeTest,
     getMimeTypeByFileExtesion_mimeTypeMapWithOneExtesionButWithoutMatch) {
  GetMimeType mime;
  std::map<std::string, std::string> fakeGlobalMimetypeMap;
  fakeGlobalMimetypeMap.insert(std::make_pair("pdf", "application/pdf"));

  GetMimeType::setMimetypeMap(fakeGlobalMimetypeMap);

  std::string mimeType = mime.getMimeTypeByFileExtesion("file.xxx");

  EXPECT_EQ("application/octet-stream", mimeType);
}
