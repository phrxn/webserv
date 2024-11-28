#include "../../libs/googletest/googlemock/include/gmock/gmock.h"
#include "../../libs/googletest/googletest/include/gtest/gtest.h"

#include "ServerSocketFileDescriptor.hpp"

TEST(ServerSocketFileDescriptorTest, getSocketClientIPv4){

                 //[4]     [3]       [2]      [1]
 uint32_t ipv4 = 0b00000100000000110000001000000001;

 ServerSocketFileDescriptor ssfd(NULL);

 EXPECT_EQ("1.2.3.4", ssfd.getSocketClientIPv4(ipv4));
}