#include "../../../libs/googletest/googlemock/include/gmock/gmock.h"
#include "../../../libs/googletest/googletest/include/gtest/gtest.h"
#include "StaticPagesPhysicalPathChecker.hpp"

class SystemCallsMock : public SystemCalls {
 public:
  MOCK_METHOD(error::StatusOr<int>, access, (const char *name, int type),
              (const override));

  MOCK_METHOD(error::StatusOr<int>, stat,
              (const char *_file, struct stat *_buf), (const override));
};

TEST(StaticPagesPhysicalPathCheckerTest,
     isThePathValidForTheGetMethod_notADirectoryError) {
  SystemCallsMock *systemCallMock = new SystemCallsMock;

  EXPECT_CALL(*systemCallMock,
              stat(::testing::A<const char *>(), ::testing::A<struct stat *>()))
      .WillOnce(::testing::Return(
          error::Status(error::Status::SystemCall, "Not a directory")));

  StaticPagesPhysicalPathChecker checker;
  checker.setSystemCalls(systemCallMock);

  HTTPStatus::Status theReturn =
      checker.isThePathValidForTheGetMethod("foo/", false);

  EXPECT_EQ(HTTPStatus::NOT_FOUND, theReturn);
}

TEST(StaticPagesPhysicalPathCheckerTest,
     isThePathValidForTheGetMethod_NoSuchFileOrDirectoryError) {
  SystemCallsMock *systemCallMock = new SystemCallsMock;

  EXPECT_CALL(*systemCallMock,
              stat(::testing::A<const char *>(), ::testing::A<struct stat *>()))
      .WillOnce(::testing::Return(error::Status(error::Status::SystemCall,
                                                "No such file or directory")));

  StaticPagesPhysicalPathChecker checker;
  checker.setSystemCalls(systemCallMock);

  HTTPStatus::Status theReturn =
      checker.isThePathValidForTheGetMethod("foo/", false);

  EXPECT_EQ(HTTPStatus::NOT_FOUND, theReturn);
}

TEST(StaticPagesPhysicalPathCheckerTest,
     isThePathValidForTheGetMethod_PermissionDeniedError) {
  SystemCallsMock *systemCallMock = new SystemCallsMock;

  EXPECT_CALL(*systemCallMock,
              stat(::testing::A<const char *>(), ::testing::A<struct stat *>()))
      .WillOnce(::testing::Return(
          error::Status(error::Status::SystemCall, "PermissionDenied")));

  StaticPagesPhysicalPathChecker checker;
  checker.setSystemCalls(systemCallMock);

  HTTPStatus::Status theReturn =
      checker.isThePathValidForTheGetMethod("foo/", false);

  EXPECT_EQ(HTTPStatus::FORBIDDEN, theReturn);
}

TEST(StaticPagesPhysicalPathCheckerTest,
     isThePathValidForTheGetMethod_notReadableError) {
  SystemCallsMock *systemCallMock = new SystemCallsMock;

  EXPECT_CALL(*systemCallMock,
              access(::testing::A<const char *>(), ::testing::A<int>()))
      .WillOnce(::testing::Return(
          error::Status(error::Status::SystemCall, "access")));

  StaticPagesPhysicalPathChecker checker;
  checker.setSystemCalls(systemCallMock);

  HTTPStatus::Status theReturn =
      checker.isThePathValidForTheGetMethod("foo/", false);

  EXPECT_EQ(HTTPStatus::FORBIDDEN, theReturn);
}
