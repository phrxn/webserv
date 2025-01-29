#include "../../../../libs/googletest/googlemock/include/gmock/gmock.h"
#include "../../../../libs/googletest/googletest/include/gtest/gtest.h"
#include "DirectoryHTMLDocument.hpp"

class FileMock : public File {
 public:
  FileMock() {}
  FileMock(bool isDirectory, const std::string &path)
      : File(path), _isDirectory(isDirectory) {}
  FileMock(const std::string &path) : File(path) {}
  FileMock(const std::string &path, Log *logger) : File(path, logger) {}
  FileMock(const std::string &path, Log *logger,
           DirectoryListing *directoryListing)
      : File(path, logger, directoryListing) {}

  bool isDirectory() const { return _isDirectory; }

 private:
  bool _isDirectory;
};

// -------------------------------------------------

bool operator==(const std::vector<File *> &list1,
                const std::vector<File *> &list2) {
  if (list1.size() != list2.size()) return false;

  for (size_t i = 0; i < list1.size(); ++i) {
    if (!(*(list1[i]) == *(list2[i]))) {
      return false;
    }
  }
  return true;
}

TEST(DirectoryHTMLDocumentTest, sortDirectoryFiles) {

  std::vector<File *> listToCompare{
      new FileMock(true, "../"),          new FileMock(true, "com_l/"),
      new FileMock(true, "dir49_789/"),   new FileMock(true, "dir50_7890/"),
      new FileMock(true, "dir51_78901/"), new FileMock(true, "sem_l/"),
      new FileMock(false, "file49_89"),   new FileMock(false, "file50_890"),
      new FileMock(false, "file51_8901")};

  std::vector<File *> listToSortDirectory{
      new FileMock(false, "file50_890"), new FileMock(true, "sem_l/"),
      new FileMock(true, "dir50_7890/"), new FileMock(false, "file51_8901"),
      new FileMock(true, "com_l/"),      new FileMock(true, "dir51_78901/"),
      new FileMock(true, "../"),         new FileMock(false, "file49_89"),
      new FileMock(true, "dir49_789/")};

  DirectoryHTMLDocument dhtml("a");

  dhtml.sortDirectoryFiles(listToSortDirectory);

  EXPECT_TRUE(listToCompare == listToSortDirectory);

  //free lists
  for(auto & file: listToCompare){
	delete file;
  }
  for(auto & file: listToSortDirectory){
	delete file;
  }

}

TEST(DirectoryHTMLDocumentTest, removeDotAndDotDotDirectoriesFromDirectoryList_emptyList) {

  std::vector<File> listToCompare;

  std::vector<File> listToRemoveDirectory;

  DirectoryHTMLDocument dhtml("a");

  dhtml.removeDotAndDotDotDirectoriesFromDirectoryList(listToRemoveDirectory);

  EXPECT_EQ(listToCompare, listToRemoveDirectory);

}

TEST(DirectoryHTMLDocumentTest,
     removeDotAndDotDotDirectoriesFromDirectoryList_twoItemsDotAndDotDot) {

  std::vector<File> listToCompare;

  std::vector<File> listToRemoveDirectory{File("."), File("..")};

  DirectoryHTMLDocument dhtml("a");

  dhtml.removeDotAndDotDotDirectoriesFromDirectoryList(listToRemoveDirectory);

  EXPECT_EQ(listToCompare, listToRemoveDirectory);

}

TEST(DirectoryHTMLDocumentTest,
     removeOwnDirectoryFromDirectoryList_listWithThreeItems) {

  std::vector<File> listToCompare{File("foo")};

  std::vector<File> listToRemoveDirectory{File("foo"), File(".."), File(".")};

  DirectoryHTMLDocument dhtml("a");

  dhtml.removeDotAndDotDotDirectoriesFromDirectoryList(listToRemoveDirectory);

  EXPECT_EQ(listToCompare, listToRemoveDirectory);

}

TEST(DirectoryHTMLDocumentTest,
     removeOwnDirectoryFromDirectoryList_listWithThreeItems2) {

  std::vector<File> listToCompare{File("foo")};

  std::vector<File> listToRemoveDirectory{File(".."), File("foo"), File(".")};

  DirectoryHTMLDocument dhtml("a");

  dhtml.removeDotAndDotDotDirectoriesFromDirectoryList(listToRemoveDirectory);

  EXPECT_EQ(listToCompare, listToRemoveDirectory);

}

TEST(DirectoryHTMLDocumentTest,
     removeOwnDirectoryFromDirectoryList_listWithThreeItems3) {

  std::vector<File> listToCompare{File("foo")};

  std::vector<File> listToRemoveDirectory{File(".."), File("."), File("foo")};

  DirectoryHTMLDocument dhtml("a");

  dhtml.removeDotAndDotDotDirectoriesFromDirectoryList(listToRemoveDirectory);

  EXPECT_EQ(listToCompare, listToRemoveDirectory);

}

TEST(DirectoryHTMLDocumentTest,
     removeOwnDirectoryFromDirectoryList_listWithWithoutDotsDirectories) {

  std::vector<File> listToCompare{File("foo"), File("bar"), File("zzz")};

  std::vector<File> listToRemoveDirectory{File("foo"), File("bar"), File("zzz")};

  DirectoryHTMLDocument dhtml("a");

  dhtml.removeDotAndDotDotDirectoriesFromDirectoryList(listToRemoveDirectory);

  EXPECT_EQ(listToCompare, listToRemoveDirectory);

}

// -------------------------------------------------
