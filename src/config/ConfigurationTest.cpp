#include "../../libs/googletest/googlemock/include/gmock/gmock.h"
#include "../../libs/googletest/googletest/include/gtest/gtest.h"
#include "Configuration.hpp"

TEST(ConfigurationTest, testSingleton) {
  Configuration &c = Configuration::getInstance();
  c.setTimeOutForNewRequestOrToSendAFullRequest(100);

  Configuration &c2 = Configuration::getInstance();
  c2.setTimeOutForNewRequestOrToSendAFullRequest(200);

  EXPECT_EQ(200, c.getTimeOutForNewRequestOrToSendAFullRequest());

  c.setTimeOutForNewRequestOrToSendAFullRequest(300);

  EXPECT_EQ(300, c.getTimeOutForNewRequestOrToSendAFullRequest());
}

TEST(ConfigurationTest, testTheServerSupportsThisHTTPMethod_invalidMethod) {
  Configuration &c = Configuration::getInstance();
  bool b = c.theServerSupportsThisHTTPMethod(HTTPMethods::GET);

  EXPECT_TRUE(b);
}

TEST(ConfigurationTest, testTheServerSupportsThisHTTPMethod_validMethod) {
  Configuration &c = Configuration::getInstance();

  // FAKE_METHOD comes from a define established during compilation, so here it
  // appears as a "wrong value" by IDEs
  bool b = c.theServerSupportsThisHTTPMethod(HTTPMethods::FAKE_METHOD);

  EXPECT_FALSE(b);
}