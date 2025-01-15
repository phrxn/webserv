#include <algorithm>

#include "../../libs/googletest/googlemock/include/gmock/gmock.h"
#include "../../libs/googletest/googletest/include/gtest/gtest.h"
#include "DirectoryListing.hpp"

// ------------------------------------------------------------------------

TEST(DirectoryListingTest, copy_operator) {
  DirectoryListing a("abc");

  DirectoryListing b = a;
}

// ------------------------------------------------------------------------

TEST(DirectoryListingTest, assignment_operator) {
  DirectoryListing a("abc");
  DirectoryListing b("zzz");

  b = a;
}

// -------------------------------------------------------------------------- //
// ------------------------- INTEGRATION TESTS ------------------------------ //
// -------------------------------------------------------------------------- //

TEST(DirectoryListingTest, listFile) {
  DirectoryListing directoryListing(
      "tests/integration/"
      "folder_with_things_to_test_the_class_DirectoryListing-cpp");

  std::vector<std::string> filesInDirectory = directoryListing.listFiles();

  std::vector<std::string> listToCompare;
  listToCompare.push_back(".");
  listToCompare.push_back("..");
  listToCompare.push_back("dir1");
  listToCompare.push_back("dir2");
  listToCompare.push_back("file1");
  listToCompare.push_back("file2");

  std::sort(listToCompare.begin(), listToCompare.end());
  std::sort(filesInDirectory.begin(), filesInDirectory.end());

  EXPECT_EQ(listToCompare, filesInDirectory);
}