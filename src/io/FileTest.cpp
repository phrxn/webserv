#include <string>
#include <vector>

#include "../../libs/googletest/googlemock/include/gmock/gmock.h"
#include "../../libs/googletest/googletest/include/gtest/gtest.h"
#include "File.hpp"

class SystemCallsMock : public SystemCalls {
 public:
  MOCK_METHOD(error::StatusOr<int>, stat,
              (const char *_file, struct stat *_buf), (const override));
};

class LogMock : public Log {
 public:
  MOCK_METHOD(void, log,
              (LogLevel level, const std::string &clazzName,
               const std::string &methodName, const std::string &message,
               const std::string &details),
              (override));

  MOCK_METHOD(void, log,
              (LogLevel level, const std::string &clazzName,
               const std::string &methodName, const std::string &message,
               int details),
              (override));
};

class DirectoryListingMock : public DirectoryListing {
 public:
  DirectoryListingMock() : DirectoryListing("/") {}
  MOCK_METHOD(std::vector<std::string>, listFiles, (), (const override));
};

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

// ------------------------------------------------------------------------

TEST(FileTest, copy_operator) {
  File a("abc");

  File b = a;

  EXPECT_EQ("abc", b.getPath());
}

// ------------------------------------------------------------------------

TEST(FileTest, assignment_operator) {
  File a("abc");
  File b("zzz");

  b = a;

  EXPECT_EQ("abc", b.getPath());
}

// ------------------------------------------------------------------------

TEST(FileTest, equals_operator) {
  File a("a");
  File b("a");
  File c("c");

  EXPECT_TRUE((a == b));
  EXPECT_FALSE((a == c));
}

// ------------------------------------------------------------------------

TEST(FileTest, minorOperator_onlyFiles) {
  FileMock a(false, "a");
  FileMock b(false, "a");
  FileMock c(false, "b");

  EXPECT_FALSE((a < b));
  EXPECT_TRUE((a < c));
  EXPECT_FALSE((c < a));
}

TEST(FileTest, minorOperator_onlyDirectories) {
  FileMock a(true, "a");
  FileMock b(true, "a");
  FileMock c(true, "b");

  EXPECT_FALSE((a < b));
  EXPECT_TRUE((a < c));
  EXPECT_FALSE((c < a));
}

TEST(
    FileTest,
    minorOperator_mixFileAndDirectoryOneOfEach_fileNameIsAandDirectoryNameIsB) {
  FileMock a(false, "a");
  FileMock b(true, "b");

  EXPECT_FALSE((a < b));
  EXPECT_TRUE((b < a));
}

TEST(
    FileTest,
    minorOperator_mixFileAndDirectoryOneOfEach_fileNameIsBandDirectoryNameIsA) {
  FileMock a(false, "b");
  FileMock b(true, "a");

  EXPECT_FALSE((a < b));
  EXPECT_TRUE((b < a));
}


// ------------------------------------------------------------------------

TEST(FileTest, isFile_systemCallError) {
  SystemCallsMock *systemCallMock = new SystemCallsMock;

  EXPECT_CALL(*systemCallMock,
              stat(::testing::A<const char *>(), ::testing::A<struct stat *>()))
      .WillOnce(::testing::Invoke(
          []() { return error::Status(error::Status::SystemCall, "error"); }));

  File file;
  file.setSystemCalls(systemCallMock);

  bool isFile = file.isFile();

  EXPECT_FALSE(isFile);
}

TEST(FileTest, isFile_statReturnDirectory) {
  SystemCallsMock *systemCallMock = new SystemCallsMock;

  EXPECT_CALL(*systemCallMock,
              stat(::testing::A<const char *>(), ::testing::A<struct stat *>()))
      .WillOnce(::testing::Invoke([](const char *_file, struct stat *_buf) {
        (void)_file;
        _buf->st_mode = 16877;
        return 0;
      }));

  File file;
  file.setSystemCalls(systemCallMock);

  bool isFile = file.isFile();

  EXPECT_FALSE(isFile);
}

TEST(FileTest, isFile_statReturnRegularFile) {
  SystemCallsMock *systemCallMock = new SystemCallsMock;

  EXPECT_CALL(*systemCallMock,
              stat(::testing::A<const char *>(), ::testing::A<struct stat *>()))
      .WillOnce(::testing::Invoke([](const char *_file, struct stat *_buf) {
        (void)_file;
        _buf->st_mode = 33188;
        return 0;
      }));

  File file;
  file.setSystemCalls(systemCallMock);

  bool isFile = file.isFile();

  EXPECT_TRUE(isFile);
}
// ------------------------------------------------------------------------

TEST(FileTest, isDirectory_systemCallError) {
  SystemCallsMock *systemCallMock = new SystemCallsMock;

  EXPECT_CALL(*systemCallMock,
              stat(::testing::A<const char *>(), ::testing::A<struct stat *>()))
      .WillOnce(::testing::Invoke(
          []() { return error::Status(error::Status::SystemCall, "error"); }));

  File file;
  file.setSystemCalls(systemCallMock);

  bool isDirectory = file.isDirectory();

  EXPECT_FALSE(isDirectory);
}

TEST(FileTest, isDirectory_statReturnFile) {
  SystemCallsMock *systemCallMock = new SystemCallsMock;

  EXPECT_CALL(*systemCallMock,
              stat(::testing::A<const char *>(), ::testing::A<struct stat *>()))
      .WillOnce(::testing::Invoke([](const char *_file, struct stat *_buf) {
        (void)_file;
        _buf->st_mode = 33188;
        return 0;
      }));

  File file;
  file.setSystemCalls(systemCallMock);

  bool isDirectory = file.isDirectory();

  EXPECT_FALSE(isDirectory);
}

TEST(FileTest, isDirectory_statReturnRegularFile) {
  SystemCallsMock *systemCallMock = new SystemCallsMock;

  EXPECT_CALL(*systemCallMock,
              stat(::testing::A<const char *>(), ::testing::A<struct stat *>()))
      .WillOnce(::testing::Invoke([](const char *_file, struct stat *_buf) {
        (void)_file;
        _buf->st_mode = 16877;
        return 0;
      }));

  File file;
  file.setSystemCalls(systemCallMock);

  bool isDirectory = file.isDirectory();

  EXPECT_TRUE(isDirectory);
}

// ------------------------------------------------------------------------

TEST(FileTest, getPath) {
  File file("abc");

  std::string thePath = file.getPath();

  EXPECT_EQ("abc", thePath);
}

// ------------------------------------------------------------------------

TEST(FileTest, size_systemCallError) {
  SystemCallsMock *systemCallMock = new SystemCallsMock;
  LogMock *loggerMock = new LogMock;

  EXPECT_CALL(*systemCallMock,
              stat(::testing::A<const char *>(), ::testing::A<struct stat *>()))
      .WillOnce(::testing::Invoke(
          []() { return error::Status(error::Status::SystemCall, "error"); }));
  EXPECT_CALL(*loggerMock,
              log(Log::ERROR, "File", "size", "get file size", "error"))
      .Times(1);

  File file("/", loggerMock);
  file.setSystemCalls(systemCallMock);

  ssize_t theSize = file.size();

  EXPECT_EQ(-1, theSize);

  delete loggerMock;
}

TEST(FileTest, size_systemCallOk) {
  SystemCallsMock *systemCallMock = new SystemCallsMock;
  LogMock *loggerMock = new LogMock;

  EXPECT_CALL(*systemCallMock,
              stat(::testing::A<const char *>(), ::testing::A<struct stat *>()))
      .WillOnce(::testing::Invoke([](const char *_file, struct stat *_buf) {
        (void)_file;
        _buf->st_size = 42;
        return 1;
      }));
  EXPECT_CALL(*loggerMock, log(Log::ERROR, "", "", "", "")).Times(0);

  File file;
  file.setSystemCalls(systemCallMock);

  ssize_t theSize = file.size();

  EXPECT_EQ(42, theSize);

  delete loggerMock;
}

// ------------------------------------------------------------------------

TEST(FileTest, listFiles) {
  DirectoryListingMock *directoryListingMock = new DirectoryListingMock;

  EXPECT_CALL(*directoryListingMock, listFiles())
      .WillOnce(::testing::Invoke([](void) {
        std::vector<std::string> listOfFiles;

        listOfFiles.push_back("file1");
        listOfFiles.push_back("dir1");

        return listOfFiles;
      }));
  File file("/", NULL, directoryListingMock);

  std::vector<File> listToCompare;
  listToCompare.push_back(File("file1"));
  listToCompare.push_back(File("dir1"));

  std::vector<File> listFromDirectory = file.listFiles();

  std::sort(listToCompare.begin(), listToCompare.end());
  std::sort(listFromDirectory.begin(), listFromDirectory.end());

  EXPECT_EQ(listToCompare, listFromDirectory);
}

// -------------------------------------------------------------------------- //
// ------------------------- INTEGRATION TESTS ------------------------------ //
// -------------------------------------------------------------------------- //

TEST(FileTest, isFile_testWithFile) {
  File file(
      "tests/integration/folder_with_things_to_test_the_class_File-cpp/file");

  bool isAFile = file.isFile();

  EXPECT_TRUE(isAFile);
}

TEST(FileTest, isFile_testWithDirectory) {
  File file(
      "tests/integration/folder_with_things_to_test_the_class_File-cpp/"
      "directory");

  bool isAFile = file.isFile();

  EXPECT_FALSE(isAFile);
}

// ----------

TEST(FileTest, isDirectory_testWithFile) {
  File file(
      "tests/integration/folder_with_things_to_test_the_class_File-cpp/file");

  bool isADirectory = file.isDirectory();

  EXPECT_FALSE(isADirectory);
}

TEST(FileTest, isDirectory_testWithDirectory) {
  File file(
      "tests/integration/folder_with_things_to_test_the_class_File-cpp/"
      "directory");

  bool isADirectory = file.isDirectory();

  EXPECT_TRUE(isADirectory);
}

// ----------

TEST(FileTest, getModificationTime) {
  File file("tests/integration/modification_time.txt");

  time_t modificationTime = file.getModificationTime();

  EXPECT_EQ(1738379045, modificationTime);
}

// ----------

TEST(FileTest, exist_directory) {
  File file(
      "tests/integration/folder_with_things_to_test_the_class_File-cpp/"
      "directory");

  bool exist = file.exist();

  EXPECT_TRUE(exist);
}

TEST(FileTest, exist_file) {
  File file(
      "tests/integration/folder_with_things_to_test_the_class_File-cpp/file");

  bool exist = file.exist();

  EXPECT_TRUE(exist);
}

// ----------

TEST(FileTest, size_z_file_10_bytes) {
  File file(
      "tests/integration/folder_with_things_to_test_the_class_File-cpp/"
      "z_file_10_bytes");

  ssize_t theSize = file.size();

  EXPECT_EQ(10, theSize);
}

TEST(FileTest, size_z_file_empty) {
  File file(
      "tests/integration/folder_with_things_to_test_the_class_File-cpp/"
      "z_file_empty");

  ssize_t theSize = file.size();

  EXPECT_EQ(0, theSize);
}

TEST(FileTest, size_z_dir_10_bytes) {
  File file(
      "tests/integration/folder_with_things_to_test_the_class_File-cpp/"
      "z_dir_10_bytes");

  ssize_t theSize = file.size();

  EXPECT_EQ(4096, theSize);
}

TEST(FileTest, size_z_dir_empty) {
  File file(
      "tests/integration/folder_with_things_to_test_the_class_File-cpp/"
      "z_dir_empty");

  ssize_t theSize = file.size();

  EXPECT_EQ(4096, theSize);
}