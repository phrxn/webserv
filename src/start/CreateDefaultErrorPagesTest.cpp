#include "../../libs/googletest/googlemock/include/gmock/gmock.h"
#include "../../libs/googletest/googletest/include/gtest/gtest.h"
#include "CreateDefaultErrorPages.hpp"

TEST(CreateDefaultErrorPages, copyOperator) {
  CreateDefaultErrorPages a;
  CreateDefaultErrorPages b = a;
  CreateDefaultErrorPages c(a);
}

TEST(CreateDefaultErrorPages, createFullPathToErroPage) {
  CreateDefaultErrorPages create;

  std::string fullPath =
      create.createFullPathToErroPage(HTTPStatus::BAD_REQUEST);

  EXPECT_EQ("conf/default_error_pages/400.html", fullPath);
}