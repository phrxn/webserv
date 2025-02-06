#include <fcntl.h>

#include "../../../../libs/googletest/googlemock/include/gmock/gmock.h"
#include "../../../../libs/googletest/googletest/include/gtest/gtest.h"
#include "../../../error/Log.hpp"
#include "../../../system/SystemCalls.hpp"
#include "FilesToCGI.hpp"

#include <iostream>
#include <filesystem>
#include <fstream>
#include <sstream>


class SystemCallsMockFilesToCGI : public SystemCalls {
 public:
  MOCK_METHOD(error::StatusOr<int>, close, (int), (const override));
  MOCK_METHOD(error::StatusOr<int>, open,
              (const char *name, int flags, mode_t mode), (const override));
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

class MockHTTPRequestToWriteBody : public HTTPRequest{
	public:
	    MOCK_METHOD(std::string, getBody, (), (const override));
		MockHTTPRequestToWriteBody() : HTTPRequest(NULL, NULL){}
};


//--------------------------------------------------------------------

TEST(FilesToCGITest, testDestructor) {
  SystemCallsMockFilesToCGI *systemCallsMock = new SystemCallsMockFilesToCGI;
  EXPECT_CALL(*systemCallsMock, close(1)).WillOnce(::testing::Return(1));
  EXPECT_CALL(*systemCallsMock, close(2)).WillOnce(::testing::Return(1));
  EXPECT_CALL(*systemCallsMock, close(3)).WillOnce(::testing::Return(1));

  FilesToCGI filesToCGI;
  filesToCGI.setInputFileDescriptor(1);
  filesToCGI.setOutputFileDescriptor(2);
  filesToCGI.setStderrFileDescriptor(3);
  filesToCGI.setSystemCalls(systemCallsMock);
}

//-----------------------  openFile -----------------------

TEST(FilesToCGITest, openFile_systeCallIsNull) {
  FilesToCGI filesToCGI(NULL);
  filesToCGI.setSystemCalls(NULL);

  int isFileDescritor = filesToCGI.openAFile("");

  EXPECT_EQ(-1, isFileDescritor);
}

TEST(FilesToCGITest, openFile_openSystemCallFailed) {
  SystemCallsMockFilesToCGI *systemCallsMock = new SystemCallsMockFilesToCGI;
  EXPECT_CALL(*systemCallsMock,
              open(::testing::A<const char *>(), (O_CREAT | O_TRUNC | O_RDWR),
                   (S_IRUSR | S_IWUSR)))
      .WillOnce(
          ::testing::Return(error::Status(error::Status::SystemCall, "xxx")));
  // to destructor
  EXPECT_CALL(*systemCallsMock, close(-1)).WillRepeatedly(::testing::Return(1));

  LogMock *logMock = new LogMock;
  EXPECT_CALL(*logMock, log(Log::ERROR, "FilesToCGI", "openFile", "xxx", ""))
      .Times(1);

  FilesToCGI filesToCGI(logMock);
  filesToCGI.setSystemCalls(systemCallsMock);

  int fileDescriptor = filesToCGI.openAFile("");

  EXPECT_EQ(-1, fileDescriptor);

  // free object allocated
  delete logMock;
}

TEST(FilesToCGITest, openFile_openSystemCallWork) {

  SystemCallsMockFilesToCGI *systemCallsMock = new SystemCallsMockFilesToCGI;
  EXPECT_CALL(*systemCallsMock,
              open(::testing::A<const char *>(), (O_CREAT | O_TRUNC | O_RDWR),
                   (S_IRUSR | S_IWUSR)))
      .WillOnce(
          ::testing::Return(42));
  //to destructor
  EXPECT_CALL(*systemCallsMock, close(-1)).WillRepeatedly(::testing::Return(1));

  FilesToCGI filesToCGI(NULL);
  filesToCGI.setSystemCalls(systemCallsMock);

  int fileDescriptor = filesToCGI.openAFile("");

  EXPECT_EQ(42, fileDescriptor);
}

//-----------------------  deleteFiles -----------------------

TEST(FilesToCGITest, deleteFiles_closeInputFileDescriptorFailed) {
  SystemCallsMockFilesToCGI *systemCallsMock = new SystemCallsMockFilesToCGI;
  EXPECT_CALL(*systemCallsMock, close(1))
      .WillOnce(
          ::testing::Return(error::Status(error::Status::SystemCall, "")));
  EXPECT_CALL(*systemCallsMock, close(2)).WillOnce(::testing::Return(1));
  EXPECT_CALL(*systemCallsMock, close(3)).WillOnce(::testing::Return(1));

  FilesToCGI filesToCGI(NULL);
  filesToCGI.setSystemCalls(systemCallsMock);

  filesToCGI.setInputFileDescriptor(1);
  filesToCGI.setOutputFileDescriptor(2);
  filesToCGI.setStderrFileDescriptor(3);

  bool wasFilesDeleted = filesToCGI.deleteFiles();

  EXPECT_FALSE(wasFilesDeleted);
}

TEST(FilesToCGITest, deleteFiles_closeOutputFileDescriptorFailed) {
  SystemCallsMockFilesToCGI *systemCallsMock = new SystemCallsMockFilesToCGI;
  EXPECT_CALL(*systemCallsMock, close(1)).WillOnce(::testing::Return(1));
  EXPECT_CALL(*systemCallsMock, close(2))
      .WillOnce(
          ::testing::Return(error::Status(error::Status::SystemCall, "")));
  EXPECT_CALL(*systemCallsMock, close(3)).WillOnce(::testing::Return(1));

  FilesToCGI filesToCGI(NULL);
  filesToCGI.setSystemCalls(systemCallsMock);

  filesToCGI.setInputFileDescriptor(1);
  filesToCGI.setOutputFileDescriptor(2);
  filesToCGI.setStderrFileDescriptor(3);

  bool wasFilesDeleted = filesToCGI.deleteFiles();

  EXPECT_FALSE(wasFilesDeleted);
}

TEST(FilesToCGITest, deleteFiles_closeStderrFileDescriptorFailed) {
  SystemCallsMockFilesToCGI *systemCallsMock = new SystemCallsMockFilesToCGI;
  EXPECT_CALL(*systemCallsMock, close(1)).WillOnce(::testing::Return(1));
  EXPECT_CALL(*systemCallsMock, close(2)).WillOnce(::testing::Return(1));
  EXPECT_CALL(*systemCallsMock, close(3))
      .WillOnce(
          ::testing::Return(error::Status(error::Status::SystemCall, "")));

  FilesToCGI filesToCGI(NULL);
  filesToCGI.setSystemCalls(systemCallsMock);

  filesToCGI.setInputFileDescriptor(1);
  filesToCGI.setOutputFileDescriptor(2);
  filesToCGI.setStderrFileDescriptor(3);

  bool wasFilesDeleted = filesToCGI.deleteFiles();

  EXPECT_FALSE(wasFilesDeleted);
}

TEST(FilesToCGITest, deleteFiles_closeAllFileDescriptors) {
  SystemCallsMockFilesToCGI *systemCallsMock = new SystemCallsMockFilesToCGI;
  EXPECT_CALL(*systemCallsMock, close(1)).WillOnce(::testing::Return(1));
  EXPECT_CALL(*systemCallsMock, close(2)).WillOnce(::testing::Return(1));
  EXPECT_CALL(*systemCallsMock, close(3)).WillOnce(::testing::Return(1));

  FilesToCGI filesToCGI(NULL);
  filesToCGI.setSystemCalls(systemCallsMock);

  filesToCGI.setInputFileDescriptor(1);
  filesToCGI.setOutputFileDescriptor(2);
  filesToCGI.setStderrFileDescriptor(3);

  bool wasFilesDeleted = filesToCGI.deleteFiles();

  EXPECT_TRUE(wasFilesDeleted);
}

TEST(FilesToCGITest, deleteFiles_systemCallIsNull) {
  FilesToCGI filesToCGI(NULL);
  filesToCGI.setSystemCalls(NULL);

  //only to skip the first 'if' inside the function
  filesToCGI.setInputFileDescriptor(42);

  bool wasFilesDeleted = filesToCGI.deleteFiles();

  EXPECT_FALSE(wasFilesDeleted);
}

TEST(FilesToCGITest, deleteFiles_AllFileDescritorsAreNegativeOne) {
  FilesToCGI filesToCGI(NULL);
  filesToCGI.setSystemCalls(NULL);
  filesToCGI.setInputFileDescriptor(-1);
  filesToCGI.setOutputFileDescriptor(-1);
  filesToCGI.setStderrFileDescriptor(-1);

  bool wasFilesDeleted = filesToCGI.deleteFiles();

  EXPECT_TRUE(wasFilesDeleted);
}


//-----------------------  closeFile -----------------------

TEST(FilesToCGITest, closeFile_systeCallIsNull) {
  FilesToCGI filesToCGI(NULL);
  filesToCGI.setSystemCalls(NULL);

  bool isFileDescriptoClosed = filesToCGI.closeAFile(1);

  EXPECT_TRUE(isFileDescriptoClosed);
}

TEST(FilesToCGITest, closeFile_closeSystemCallFailed) {
  SystemCallsMockFilesToCGI *systemCallsMock = new SystemCallsMockFilesToCGI;
  EXPECT_CALL(*systemCallsMock, close(1))
      .WillOnce(
          ::testing::Return(error::Status(error::Status::SystemCall, "xxx")));
  // to destructor
  EXPECT_CALL(*systemCallsMock, close(-1)).WillRepeatedly(::testing::Return(1));

  LogMock *logMock = new LogMock;
  EXPECT_CALL(*logMock, log(Log::ERROR, "FilesToCGI", "closeFile", "xxx", 1))
      .Times(1);

  FilesToCGI filesToCGI(logMock);
  filesToCGI.setSystemCalls(systemCallsMock);

  bool isFileDescriptoClosed = filesToCGI.closeAFile(1);

  EXPECT_FALSE(isFileDescriptoClosed);

  // free object allocated
  delete logMock;
}

TEST(FilesToCGITest, closeFile_closeSystemCallWork) {
  SystemCallsMockFilesToCGI *systemCallsMock = new SystemCallsMockFilesToCGI;
  EXPECT_CALL(*systemCallsMock, close(-1)).WillRepeatedly(::testing::Return(1));
  EXPECT_CALL(*systemCallsMock, close(1)).WillOnce(::testing::Return(1));

  FilesToCGI filesToCGI(NULL);
  filesToCGI.setSystemCalls(systemCallsMock);

  bool isFileDescriptoClosed = filesToCGI.closeAFile(1);

  EXPECT_TRUE(isFileDescriptoClosed);
}

// -------------------------------------------------------------------------- //
// ------------------------- INTEGRATION TESTS ------------------------------ //
// -------------------------------------------------------------------------- //

/**
 * This test must create the files (input, output, stderr). These files will
 * be used by cgi program
 */
TEST(FilesToCGITest, createFileDescriptors){

	std::string pathToTestFilesToCGI = "tests/integration/folder_to_test_FilesToCGI/";

	std::string inputFilePath = pathToTestFilesToCGI + FilesToCGI::inputFileName;
	std::string outputFilePath = pathToTestFilesToCGI + FilesToCGI::outputFileName;
	std::string stderrFilePath = pathToTestFilesToCGI + FilesToCGI::stderrFileName;


    //remove old files before tests
	std::filesystem::remove(inputFilePath);
	std::filesystem::remove(outputFilePath);
	std::filesystem::remove(stderrFilePath);

	LogMock *logger = new LogMock;
	EXPECT_CALL(*logger, log(::testing::_, ::testing::_, ::testing::_, ::testing::_, ::testing::A<int>())).Times(0);
	EXPECT_CALL(*logger, log(::testing::_, ::testing::_, ::testing::_, ::testing::_, ::testing::A<const std::string &>())).Times(0);

	MockHTTPRequestToWriteBody *httpReq = new MockHTTPRequestToWriteBody;
	EXPECT_CALL(*httpReq, getBody()).WillOnce(::testing::Return("my input!\nfoo"));

	FilesToCGI fdToCGI = FilesToCGI(logger);

	fdToCGI.setDefaultDirectoryToSaveTheFiles(pathToTestFilesToCGI);
	bool filesCreated = fdToCGI.createFileDescriptors(*httpReq);

	delete httpReq;
	delete logger;

	ASSERT_TRUE(filesCreated);

    //verify if the three files was created
	ASSERT_TRUE(std::filesystem::exists(inputFilePath));
	ASSERT_TRUE(std::filesystem::exists(outputFilePath));
	ASSERT_TRUE(std::filesystem::exists(stderrFilePath));

	//read the inputFile to check if httpRequest body was writed
	std::ifstream file(inputFilePath);
	ASSERT_TRUE(file.is_open());

    std::stringstream ssBody;
	ssBody << file.rdbuf();

    ASSERT_EQ("my input!\nfoo", ssBody.str());
}