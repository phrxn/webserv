#include "../../libs/googletest/googlemock/include/gmock/gmock.h"
#include "../../libs/googletest/googletest/include/gtest/gtest.h"
#include "File.hpp"

#include <string>
#include <vector>

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

class DirectoryListingMock : public DirectoryListing{
  public:
    DirectoryListingMock() : DirectoryListing("/"){}
    MOCK_METHOD(std::vector<std::string>, listFiles, (), (const override));

};

// ------------------------------------------------------------------------

TEST(FileTest, copy_operator){

	File a("abc");

	File b = a;

	EXPECT_EQ("abc", b.getPath());
}

// ------------------------------------------------------------------------

TEST(FileTest, assignment_operator){

	File a("abc");
	File b("zzz");

	b = a;

	EXPECT_EQ("abc", b.getPath());
}

// ------------------------------------------------------------------------

TEST(FileTest, equals_operator){

	File a("a");
	File b("a");
	File c("c");

	EXPECT_TRUE((a == b));
	EXPECT_FALSE((a == c));
}

// ------------------------------------------------------------------------

TEST(FileTest, minor_operator){

	File a("a");
	File b("a");
	File c("b");

	EXPECT_FALSE((a < b));
	EXPECT_TRUE((a < c));
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
      .WillOnce(::testing::Invoke(
          [](const char *_file, struct stat *_buf) {
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
      .WillOnce(::testing::Invoke(
          [](const char *_file, struct stat *_buf) {
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
      .WillOnce(::testing::Invoke(
          [](const char *_file, struct stat *_buf) {
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
      .WillOnce(::testing::Invoke(
          [](const char *_file, struct stat *_buf) {
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
      .WillOnce(::testing::Invoke(
          [](const char *_file, struct stat *_buf) {
			(void)_file;
			_buf->st_size = 42;
			return 1; }));
  EXPECT_CALL(*loggerMock,
              log(Log::ERROR, "", "", "", ""))
      .Times(0);

  File file;
  file.setSystemCalls(systemCallMock);

  ssize_t theSize = file.size();

  EXPECT_EQ(42, theSize);

  delete loggerMock;
}

// ------------------------------------------------------------------------

TEST(FileTest, listFiles) {

  DirectoryListingMock *directoryListingMock = new DirectoryListingMock;

  EXPECT_CALL(*directoryListingMock, listFiles()).WillOnce(::testing::Invoke([](void){
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

	File file("tests/integration/folder_with_things_to_test_the_class_File-cpp/file");

	bool isAFile = file.isFile();

	EXPECT_TRUE(isAFile);
}

TEST(FileTest, isFile_testWithDirectory) {

	File file("tests/integration/folder_with_things_to_test_the_class_File-cpp/directory");

	bool isAFile = file.isFile();

	EXPECT_FALSE(isAFile);
}

// ----------

TEST(FileTest, isDirectory_testWithFile) {

	File file("tests/integration/folder_with_things_to_test_the_class_File-cpp/file");

	bool isADirectory = file.isDirectory();

	EXPECT_FALSE(isADirectory);
}

TEST(FileTest, isDirectory_testWithDirectory) {

	File file("tests/integration/folder_with_things_to_test_the_class_File-cpp/directory");

	bool isADirectory = file.isDirectory();

	EXPECT_TRUE(isADirectory);
}

// ----------

TEST(FileTest, isReadable){

	File directory  ("tests/integration/folder_with_things_to_test_the_class_File-cpp/directory");
	File directory_r("tests/integration/folder_with_things_to_test_the_class_File-cpp/directory_r");
	File directory_rw("tests/integration/folder_with_things_to_test_the_class_File-cpp/directory_rw");
	File directory_rwx("tests/integration/folder_with_things_to_test_the_class_File-cpp/directory_rwx");
	File directory_rx("tests/integration/folder_with_things_to_test_the_class_File-cpp/directory_rx");
	File directory_w("tests/integration/folder_with_things_to_test_the_class_File-cpp/directory_w");
	File directory_wx("tests/integration/folder_with_things_to_test_the_class_File-cpp/directory_wx");
	File directory_x("tests/integration/folder_with_things_to_test_the_class_File-cpp/directory_x");

	File file  ("tests/integration/folder_with_things_to_test_the_class_File-cpp/file");
	File file_r("tests/integration/folder_with_things_to_test_the_class_File-cpp/file_r");
	File file_rw("tests/integration/folder_with_things_to_test_the_class_File-cpp/file_rw");
	File file_rwx("tests/integration/folder_with_things_to_test_the_class_File-cpp/file_rwx");
	File file_rx("tests/integration/folder_with_things_to_test_the_class_File-cpp/file_rx");
	File file_w("tests/integration/folder_with_things_to_test_the_class_File-cpp/file_w");
	File file_wx("tests/integration/folder_with_things_to_test_the_class_File-cpp/file_wx");
	File file_x("tests/integration/folder_with_things_to_test_the_class_File-cpp/file_x");

	EXPECT_TRUE(directory_r.isReadable());
	EXPECT_TRUE(directory_rw.isReadable());
	EXPECT_TRUE(directory_rwx.isReadable());
	EXPECT_TRUE(directory_rx.isReadable());
	EXPECT_TRUE(file_r.isReadable());
	EXPECT_TRUE(file_rw.isReadable());
	EXPECT_TRUE(file_rwx.isReadable());
	EXPECT_TRUE(file_rx.isReadable());

	EXPECT_FALSE(directory.isReadable());
	EXPECT_FALSE(directory_w.isReadable());
	EXPECT_FALSE(directory_wx.isReadable());
	EXPECT_FALSE(directory_x.isReadable());
	EXPECT_FALSE(file.isReadable());
	EXPECT_FALSE(file_w.isReadable());
	EXPECT_FALSE(file_wx.isReadable());
	EXPECT_FALSE(file_x.isReadable());
}

// ----------

TEST(FileTest, isWritable){

	File directory  ("tests/integration/folder_with_things_to_test_the_class_File-cpp/directory");
	File directory_r("tests/integration/folder_with_things_to_test_the_class_File-cpp/directory_r");
	File directory_rw("tests/integration/folder_with_things_to_test_the_class_File-cpp/directory_rw");
	File directory_rwx("tests/integration/folder_with_things_to_test_the_class_File-cpp/directory_rwx");
	File directory_rx("tests/integration/folder_with_things_to_test_the_class_File-cpp/directory_rx");
	File directory_w("tests/integration/folder_with_things_to_test_the_class_File-cpp/directory_w");
	File directory_wx("tests/integration/folder_with_things_to_test_the_class_File-cpp/directory_wx");
	File directory_x("tests/integration/folder_with_things_to_test_the_class_File-cpp/directory_x");

	File file  ("tests/integration/folder_with_things_to_test_the_class_File-cpp/file");
	File file_r("tests/integration/folder_with_things_to_test_the_class_File-cpp/file_r");
	File file_rw("tests/integration/folder_with_things_to_test_the_class_File-cpp/file_rw");
	File file_rwx("tests/integration/folder_with_things_to_test_the_class_File-cpp/file_rwx");
	File file_rx("tests/integration/folder_with_things_to_test_the_class_File-cpp/file_rx");
	File file_w("tests/integration/folder_with_things_to_test_the_class_File-cpp/file_w");
	File file_wx("tests/integration/folder_with_things_to_test_the_class_File-cpp/file_wx");
	File file_x("tests/integration/folder_with_things_to_test_the_class_File-cpp/file_x");

	EXPECT_TRUE(directory_rw.isWritable());
	EXPECT_TRUE(directory_rwx.isWritable());
	EXPECT_TRUE(directory_w.isWritable());
	EXPECT_TRUE(directory_wx.isWritable());
	EXPECT_TRUE(file_rw.isWritable());
	EXPECT_TRUE(file_rwx.isWritable());
	EXPECT_TRUE(file_w.isWritable());
	EXPECT_TRUE(file_wx.isWritable());

	EXPECT_FALSE(directory.isWritable());
	EXPECT_FALSE(directory_r.isWritable());
	EXPECT_FALSE(directory_rx.isWritable());
	EXPECT_FALSE(directory_x.isWritable());
	EXPECT_FALSE(file.isWritable());
	EXPECT_FALSE(file_r.isWritable());
	EXPECT_FALSE(file_rx.isWritable());
	EXPECT_FALSE(file_x.isWritable());
}

// ----------

TEST(FileTest, isExecutable){

	File directory  ("tests/integration/folder_with_things_to_test_the_class_File-cpp/directory");
	File directory_r("tests/integration/folder_with_things_to_test_the_class_File-cpp/directory_r");
	File directory_rw("tests/integration/folder_with_things_to_test_the_class_File-cpp/directory_rw");
	File directory_rwx("tests/integration/folder_with_things_to_test_the_class_File-cpp/directory_rwx");
	File directory_rx("tests/integration/folder_with_things_to_test_the_class_File-cpp/directory_rx");
	File directory_w("tests/integration/folder_with_things_to_test_the_class_File-cpp/directory_w");
	File directory_wx("tests/integration/folder_with_things_to_test_the_class_File-cpp/directory_wx");
	File directory_x("tests/integration/folder_with_things_to_test_the_class_File-cpp/directory_x");

	File file  ("tests/integration/folder_with_things_to_test_the_class_File-cpp/file");
	File file_r("tests/integration/folder_with_things_to_test_the_class_File-cpp/file_r");
	File file_rw("tests/integration/folder_with_things_to_test_the_class_File-cpp/file_rw");
	File file_rwx("tests/integration/folder_with_things_to_test_the_class_File-cpp/file_rwx");
	File file_rx("tests/integration/folder_with_things_to_test_the_class_File-cpp/file_rx");
	File file_w("tests/integration/folder_with_things_to_test_the_class_File-cpp/file_w");
	File file_wx("tests/integration/folder_with_things_to_test_the_class_File-cpp/file_wx");
	File file_x("tests/integration/folder_with_things_to_test_the_class_File-cpp/file_x");

	EXPECT_TRUE(directory_rwx.isExecutable());
	EXPECT_TRUE(directory_rx.isExecutable());
	EXPECT_TRUE(directory_wx.isExecutable());
	EXPECT_TRUE(directory_x.isExecutable());
	EXPECT_TRUE(file_rwx.isExecutable());
	EXPECT_TRUE(file_rx.isExecutable());
	EXPECT_TRUE(file_wx.isExecutable());
	EXPECT_TRUE(file_x.isExecutable());

	EXPECT_FALSE(directory.isExecutable());
	EXPECT_FALSE(directory_r.isExecutable());
	EXPECT_FALSE(directory_rw.isExecutable());
	EXPECT_FALSE(directory_w.isExecutable());
	EXPECT_FALSE(file.isExecutable());
	EXPECT_FALSE(file_r.isExecutable());
	EXPECT_FALSE(file_rw.isExecutable());
	EXPECT_FALSE(file_w.isExecutable());
}

// ----------

TEST(FileTest, exist_directory) {

	File file("tests/integration/folder_with_things_to_test_the_class_File-cpp/directory");

    bool exist = file.exist();

	EXPECT_TRUE(exist);
}

TEST(FileTest, exist_file) {

	File file("tests/integration/folder_with_things_to_test_the_class_File-cpp/file");

    bool exist = file.exist();

	EXPECT_TRUE(exist);
}

// ----------

TEST(FileTest, size_z_file_10_bytes) {

	File file("tests/integration/folder_with_things_to_test_the_class_File-cpp/z_file_10_bytes");

    ssize_t theSize = file.size();

	EXPECT_EQ(10, theSize);
}

TEST(FileTest, size_z_file_empty) {

	File file("tests/integration/folder_with_things_to_test_the_class_File-cpp/z_file_empty");

    ssize_t theSize = file.size();

	EXPECT_EQ(0, theSize);
}

TEST(FileTest, size_z_dir_10_bytes) {

	File file("tests/integration/folder_with_things_to_test_the_class_File-cpp/z_dir_10_bytes");

    ssize_t theSize = file.size();

	EXPECT_EQ(4096, theSize);
}

TEST(FileTest, size_z_dir_empty) {

	File file("tests/integration/folder_with_things_to_test_the_class_File-cpp/z_dir_empty");

    ssize_t theSize = file.size();

	EXPECT_EQ(4096, theSize);
}