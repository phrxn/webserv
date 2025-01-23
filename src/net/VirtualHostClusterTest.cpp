#include "../../libs/googletest/googlemock/include/gmock/gmock.h"
#include "../../libs/googletest/googletest/include/gtest/gtest.h"

#include "VirtualHost.hpp"
#include "VirtualHostCluster.hpp"

TEST(VirtualHostClusterTest, addVirtualHostToCluster_addOneVirtualHost) {
  VirtualHost v(100, "foo");

  VirtualHostCluster vCluster;
  bool wasVirtualAdded = vCluster.addVirtualHostToCluster(v);
  EXPECT_TRUE(wasVirtualAdded);

  std::map<int, std::list<VirtualHost>> mapToCompare;
  mapToCompare[100] = std::list<VirtualHost>({VirtualHost(100, "foo")});

  const std::map<int, std::list<VirtualHost>> &map = vCluster.getMap();
  decltype(map.size()) mapSize = 1;
  EXPECT_EQ(mapSize, map.size());

  EXPECT_EQ(mapToCompare, map);
}

TEST(VirtualHostClusterTest, addVirtualHostToCluster_addTwoEqualsVirtualHost) {
  VirtualHost v(100, "foo");
  VirtualHost v2(100, "foo");

  VirtualHostCluster vCluster;
  bool wasVirtualAdded = vCluster.addVirtualHostToCluster(v);
  EXPECT_TRUE(wasVirtualAdded);
  bool wasVirtualAddedV2 = vCluster.addVirtualHostToCluster(v2);
  EXPECT_FALSE(wasVirtualAddedV2);

  std::map<int, std::list<VirtualHost>> mapToCompare;
  mapToCompare[100] = std::list<VirtualHost>({VirtualHost(100, "foo")});

  const std::map<int, std::list<VirtualHost>> &map = vCluster.getMap();
  decltype(map.size()) mapSize = 1;
  EXPECT_EQ(mapSize, map.size());

  EXPECT_EQ(mapToCompare, map);
}

TEST(VirtualHostClusterTest,
     addVirtualHostToCluster_addTwoDifferentVirtualHostsWithSamePort) {
  VirtualHost v(100, "foo");
  VirtualHost v2(100, "bar");

  VirtualHostCluster vCluster;
  bool wasVirtualAdded = vCluster.addVirtualHostToCluster(v);
  EXPECT_TRUE(wasVirtualAdded);
  bool wasVirtualAddedV2 = vCluster.addVirtualHostToCluster(v2);
  EXPECT_TRUE(wasVirtualAddedV2);

  std::map<int, std::list<VirtualHost>> mapToCompare;
  mapToCompare[100] = std::list<VirtualHost>(
      {VirtualHost(100, "foo"), VirtualHost(100, "bar")});

  const std::map<int, std::list<VirtualHost>> &map = vCluster.getMap();
  decltype(map.size()) mapSize = 1;
  EXPECT_EQ(mapSize, map.size());

  EXPECT_EQ(mapToCompare, map);
}

TEST(VirtualHostClusterTest,
     addVirtualHostToCluster_addTwoDifferentVirtualHostsWithDifferentPort) {
  VirtualHost v(100, "foo");
  VirtualHost v2(200, "foo");

  VirtualHostCluster vCluster;
  bool wasVirtualAdded = vCluster.addVirtualHostToCluster(v);
  EXPECT_TRUE(wasVirtualAdded);
  bool wasVirtualAddedV2 = vCluster.addVirtualHostToCluster(v2);
  EXPECT_TRUE(wasVirtualAddedV2);

  std::map<int, std::list<VirtualHost>> mapToCompare;
  mapToCompare[100] = std::list<VirtualHost>({VirtualHost(100, "foo")});
  mapToCompare[200] = std::list<VirtualHost>({VirtualHost(200, "foo")});

  const std::map<int, std::list<VirtualHost>> &map = vCluster.getMap();
  decltype(map.size()) mapSize = 2;
  EXPECT_EQ(mapSize, map.size());

  EXPECT_EQ(mapToCompare, map);
}

TEST(
    VirtualHostClusterTest,
    addVirtualHostToCluster_addTwoDifferentVirtualHostsWithDifferentPortsAndServername) {
  VirtualHost v(100, "foo");
  VirtualHost v2(200, "bar");

  VirtualHostCluster vCluster;
  bool wasVirtualAdded = vCluster.addVirtualHostToCluster(v);
  EXPECT_TRUE(wasVirtualAdded);
  bool wasVirtualAddedV2 = vCluster.addVirtualHostToCluster(v2);
  EXPECT_TRUE(wasVirtualAddedV2);

  std::map<int, std::list<VirtualHost>> mapToCompare;
  mapToCompare[100] = std::list<VirtualHost>({VirtualHost(100, "foo")});
  mapToCompare[200] = std::list<VirtualHost>({VirtualHost(200, "bar")});

  const std::map<int, std::list<VirtualHost>> &map = vCluster.getMap();
  decltype(map.size()) mapSize = 2;
  EXPECT_EQ(mapSize, map.size());

  EXPECT_EQ(mapToCompare, map);
}

// ---------------------------------------------------------


TEST(VirtualHostClusterTest, getVirtualHost_invalidPort) {

  VirtualHostCluster vCluster;

  error::StatusOr<VirtualHost> vhExist = vCluster.getVirtualHost(100, "foo");

  EXPECT_FALSE(vhExist.ok());
  EXPECT_EQ("there is no host using port: 100", vhExist.status().message());
}

TEST(VirtualHostClusterTest, getVirtualHost_validPort) {

  VirtualHost v(100, "bar");

  VirtualHostCluster vCluster;
  bool wasVirtualAdded = vCluster.addVirtualHostToCluster(v);
  EXPECT_TRUE(wasVirtualAdded);

  error::StatusOr<VirtualHost> vhExist = vCluster.getVirtualHost(100, "foo");

  EXPECT_TRUE(vhExist.ok());

  EXPECT_EQ(v, vhExist.value());
}


TEST(VirtualHostClusterTest, getVirtualHost_validPortButTheServernameIsAtTheEndOfItsCluster) {

  //must return the last virtualHost

  VirtualHost v(100, "foo");
  VirtualHost v2(100, "bar");

  VirtualHostCluster vCluster;
  bool wasVirtualAdded = vCluster.addVirtualHostToCluster(v);
  EXPECT_TRUE(wasVirtualAdded);
  bool wasVirtualAddedV2 = vCluster.addVirtualHostToCluster(v2);
  EXPECT_TRUE(wasVirtualAddedV2);

  error::StatusOr<VirtualHost> vhExist = vCluster.getVirtualHost(100, "bar");

  EXPECT_TRUE(vhExist.ok());

  EXPECT_EQ(v2, vhExist.value());
}

TEST(VirtualHostClusterTest, getVirtualHost_validPortButTheServernameIsAtTheBeginningOfItsCluster) {

  //must return the last virtualHost

  VirtualHost v(100, "foo");
  VirtualHost v2(100, "bar");

  VirtualHostCluster vCluster;
  bool wasVirtualAdded = vCluster.addVirtualHostToCluster(v);
  EXPECT_TRUE(wasVirtualAdded);
  bool wasVirtualAddedV2 = vCluster.addVirtualHostToCluster(v2);
  EXPECT_TRUE(wasVirtualAddedV2);

  error::StatusOr<VirtualHost> vhExist = vCluster.getVirtualHost(100, "foo");

  EXPECT_TRUE(vhExist.ok());

  EXPECT_EQ(v, vhExist.value());
}


TEST(VirtualHostClusterTest, getVirtualHost_validPortButHostNameDoesntExists) {

  //must return the first virtualHost

  VirtualHost v(100, "foo");
  VirtualHost v2(100, "bar");

  VirtualHostCluster vCluster;
  bool wasVirtualAdded = vCluster.addVirtualHostToCluster(v);
  EXPECT_TRUE(wasVirtualAdded);
  bool wasVirtualAddedV2 = vCluster.addVirtualHostToCluster(v2);
  EXPECT_TRUE(wasVirtualAddedV2);

  error::StatusOr<VirtualHost> vhExist = vCluster.getVirtualHost(100, "zzzzz");

  EXPECT_TRUE(vhExist.ok());

  EXPECT_EQ(v, vhExist.value());
}