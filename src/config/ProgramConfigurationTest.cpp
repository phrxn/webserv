#include "../../libs/googletest/googlemock/include/gmock/gmock.h"
#include "../../libs/googletest/googletest/include/gtest/gtest.h"
#include "ProgramConfiguration.hpp"

TEST(ProgramConfigurationTest, testSingleton) {
  ProgramConfiguration &c = ProgramConfiguration::getInstance();
  c.setTimeOutForNewRequestOrToSendAFullRequest(100);

  ProgramConfiguration &c2 = ProgramConfiguration::getInstance();
  c2.setTimeOutForNewRequestOrToSendAFullRequest(200);

  EXPECT_EQ(200, c.getTimeOutForNewRequestOrToSendAFullRequest());

  c.setTimeOutForNewRequestOrToSendAFullRequest(300);

  EXPECT_EQ(300, c.getTimeOutForNewRequestOrToSendAFullRequest());
}

TEST(ProgramConfigurationTest,
     testTheServerSupportsThisHTTPMethod_invalidMethod) {
  ProgramConfiguration &c = ProgramConfiguration::getInstance();
  bool b = c.theServerSupportsThisHTTPMethod(HTTPMethods::GET);

  EXPECT_TRUE(b);
}

TEST(ProgramConfigurationTest,
     testTheServerSupportsThisHTTPMethod_validMethod) {
  ProgramConfiguration &c = ProgramConfiguration::getInstance();

  // FAKE_METHOD comes from a define established during compilation, so here it
  // appears as a "wrong value" by IDEs
  bool b = c.theServerSupportsThisHTTPMethod(HTTPMethods::FAKE_METHOD);

  EXPECT_FALSE(b);
}