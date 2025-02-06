#include <iostream>
#include <map>

#include "../../../../libs/googletest/googlemock/include/gmock/gmock.h"
#include "../../../../libs/googletest/googletest/include/gtest/gtest.h"
#include "EnvironmentVariables.hpp"

TEST(EnvironmentVariablesTest, getEnvironmentVariablesSize) {
  char *fakeEnv[3] = {reinterpret_cast<char *>(1), reinterpret_cast<char *>(2),
                      0};

  EnvironmentVariables env;

  std::size_t sizeOfEnv = env.getEnvironmentVariablesSize(fakeEnv);

  EXPECT_EQ(static_cast<std::size_t>(2), sizeOfEnv);
}

TEST(EnvironmentVariablesTest, addVariable) {
  EnvironmentVariables env;

  env.addVariable("name", "value");
  env.addVariable("name", "value");

  EXPECT_EQ(static_cast<std::size_t>(1), env.getEnvMap().size());
  EXPECT_NE(env.getEnvMap().end(), env.getEnvMap().find("name"));
}

TEST(EnvironmentVariablesTest, addVariables) {
  EnvironmentVariables env;

  std::map<std::string, std::string> mapToAdd;
  mapToAdd["value1"] = "foo1";
  mapToAdd["value2"] = "foo2";

  env.addVariable("value0", "foo0");
  env.addVariables(mapToAdd);

  EXPECT_EQ(static_cast<std::size_t>(3), env.getEnvMap().size());
  EXPECT_NE(env.getEnvMap().end(), env.getEnvMap().find("value0"));
  EXPECT_EQ("foo0", env.getEnvMap().find("value0")->second);
  EXPECT_NE(env.getEnvMap().end(), env.getEnvMap().find("value1"));
  EXPECT_EQ("foo1", env.getEnvMap().find("value1")->second);
  EXPECT_NE(env.getEnvMap().end(), env.getEnvMap().find("value2"));
  EXPECT_EQ("foo2", env.getEnvMap().find("value2")->second);
  EXPECT_EQ(env.getEnvMap().end(), env.getEnvMap().find("xxxxxx"));
}

TEST(EnvironmentVariablesTest, addVariables_fromArrayChar) {
  std::string enva = "a=b";
  std::string envb = "c=d";

  const char *fakeEnv[3] = {const_cast<char *>(enva.c_str()),
                            const_cast<char *>(envb.c_str()), 0};

  EnvironmentVariables env;
  env.addVariables(fakeEnv);

  EXPECT_NE(env.getEnvMap().end(), env.getEnvMap().find("a"));
  EXPECT_NE(env.getEnvMap().end(), env.getEnvMap().find("c"));
  EXPECT_EQ(env.getEnvMap().end(), env.getEnvMap().find("xxxxxx"));
}

TEST(EnvironmentVariablesTest, createParFromStringVariable_emptyString) {
  EnvironmentVariables env;

  std::pair<std::string, std::string> thePair =
      env.createParFromStringVariable("");

  EXPECT_EQ("", thePair.first);
  EXPECT_EQ("", thePair.second);
}

TEST(EnvironmentVariablesTest,
     createParFromStringVariable_stringWithoutSeparator) {
  EnvironmentVariables env;

  std::pair<std::string, std::string> thePair =
      env.createParFromStringVariable("aaa");

  EXPECT_EQ("aaa", thePair.first);
  EXPECT_EQ("", thePair.second);
}

TEST(EnvironmentVariablesTest,
     createParFromStringVariable_stringEndsWithSeparator) {
  EnvironmentVariables env;

  std::pair<std::string, std::string> thePair =
      env.createParFromStringVariable("a=");

  EXPECT_EQ("a", thePair.first);
  EXPECT_EQ("", thePair.second);
}

TEST(EnvironmentVariablesTest,
     createParFromStringVariable_stringStartsWithSeparator) {
  EnvironmentVariables env;

  std::pair<std::string, std::string> thePair =
      env.createParFromStringVariable("=a");

  EXPECT_EQ("", thePair.first);
  EXPECT_EQ("a", thePair.second);
}

TEST(EnvironmentVariablesTest,
     createParFromStringVariable_stringIsOnlySeparator) {
  EnvironmentVariables env;

  std::pair<std::string, std::string> thePair =
      env.createParFromStringVariable("=");

  EXPECT_EQ("", thePair.first);
  EXPECT_EQ("", thePair.second);
}

TEST(EnvironmentVariablesTest,
     createParFromStringVariable_stringWithNameSeparatorValue) {
  EnvironmentVariables env;

  std::pair<std::string, std::string> thePair =
      env.createParFromStringVariable("a=b");

  EXPECT_EQ("a", thePair.first);
  EXPECT_EQ("b", thePair.second);
}

TEST(EnvironmentVariablesTest, createEnvironmentVariables) {
  EnvironmentVariables env;
  env.addVariable("a", "1");
  env.addVariable("b", "2");

  char **envArray = env.createEnvironmentVariables();

  std::size_t size = env.getEnvironmentVariablesSize(envArray);

  EXPECT_EQ(static_cast<std::size_t>(2), size);

  std::string variable1(envArray[0]);
  std::string variable2(envArray[1]);

  EXPECT_EQ("a=1", variable1);
  EXPECT_EQ("b=2", variable2);

  std::cout << std::endl;

  for (std::size_t count = 0; count < size; ++count) {
    delete[] (envArray[count]);
  }
  delete[] envArray;
}