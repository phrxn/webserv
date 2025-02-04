#include "../../libs/googletest/googlemock/include/gmock/gmock.h"
#include "../../libs/googletest/googletest/include/gtest/gtest.h"

#include "VirtualHostDefault.hpp"
#include "ClusterOfVirtualHost.hpp"

TEST(ClusterOfVirtualHostTest, addVirtualHostToCluster_addOneVirtualHost) {
  VirtualHostDefault v(100, "foo");

  ClusterOfVirtualHost vCluster;
  bool wasVirtualAdded = vCluster.addVirtualHostToCluster(v);
  EXPECT_TRUE(wasVirtualAdded);

  std::map<int, std::list<VirtualHostDefault>> mapToCompare;
  mapToCompare[100] = std::list<VirtualHostDefault>({VirtualHostDefault(100, "foo")});

  const std::map<int, std::list<VirtualHostDefault>> &map = vCluster.getMap();
  decltype(map.size()) mapSize = 1;
  EXPECT_EQ(mapSize, map.size());

  EXPECT_EQ(mapToCompare, map);
}

TEST(ClusterOfVirtualHostTest, addVirtualHostToCluster_addTwoEqualsVirtualHost) {
  VirtualHostDefault v(100, "foo");
  VirtualHostDefault v2(100, "foo");

  ClusterOfVirtualHost vCluster;
  bool wasVirtualAdded = vCluster.addVirtualHostToCluster(v);
  EXPECT_TRUE(wasVirtualAdded);
  bool wasVirtualAddedV2 = vCluster.addVirtualHostToCluster(v2);
  EXPECT_FALSE(wasVirtualAddedV2);

  std::map<int, std::list<VirtualHostDefault>> mapToCompare;
  mapToCompare[100] = std::list<VirtualHostDefault>({VirtualHostDefault(100, "foo")});

  const std::map<int, std::list<VirtualHostDefault>> &map = vCluster.getMap();
  decltype(map.size()) mapSize = 1;
  EXPECT_EQ(mapSize, map.size());

  EXPECT_EQ(mapToCompare, map);
}

TEST(ClusterOfVirtualHostTest,
     addVirtualHostToCluster_addTwoDifferentVirtualHostsWithSamePort) {
  VirtualHostDefault v(100, "foo");
  VirtualHostDefault v2(100, "bar");

  ClusterOfVirtualHost vCluster;
  bool wasVirtualAdded = vCluster.addVirtualHostToCluster(v);
  EXPECT_TRUE(wasVirtualAdded);
  bool wasVirtualAddedV2 = vCluster.addVirtualHostToCluster(v2);
  EXPECT_TRUE(wasVirtualAddedV2);

  std::map<int, std::list<VirtualHostDefault>> mapToCompare;
  mapToCompare[100] = std::list<VirtualHostDefault>(
      {VirtualHostDefault(100, "foo"), VirtualHostDefault(100, "bar")});

  const std::map<int, std::list<VirtualHostDefault>> &map = vCluster.getMap();
  decltype(map.size()) mapSize = 1;
  EXPECT_EQ(mapSize, map.size());

  EXPECT_EQ(mapToCompare, map);
}

TEST(ClusterOfVirtualHostTest,
     addVirtualHostToCluster_addTwoDifferentVirtualHostsWithDifferentPort) {
  VirtualHostDefault v(100, "foo");
  VirtualHostDefault v2(200, "foo");

  ClusterOfVirtualHost vCluster;
  bool wasVirtualAdded = vCluster.addVirtualHostToCluster(v);
  EXPECT_TRUE(wasVirtualAdded);
  bool wasVirtualAddedV2 = vCluster.addVirtualHostToCluster(v2);
  EXPECT_TRUE(wasVirtualAddedV2);

  std::map<int, std::list<VirtualHostDefault>> mapToCompare;
  mapToCompare[100] = std::list<VirtualHostDefault>({VirtualHostDefault(100, "foo")});
  mapToCompare[200] = std::list<VirtualHostDefault>({VirtualHostDefault(200, "foo")});

  const std::map<int, std::list<VirtualHostDefault>> &map = vCluster.getMap();
  decltype(map.size()) mapSize = 2;
  EXPECT_EQ(mapSize, map.size());

  EXPECT_EQ(mapToCompare, map);
}

TEST(
    ClusterOfVirtualHostTest,
    addVirtualHostToCluster_addTwoDifferentVirtualHostsWithDifferentPortsAndServername) {
  VirtualHostDefault v(100, "foo");
  VirtualHostDefault v2(200, "bar");

  ClusterOfVirtualHost vCluster;
  bool wasVirtualAdded = vCluster.addVirtualHostToCluster(v);
  EXPECT_TRUE(wasVirtualAdded);
  bool wasVirtualAddedV2 = vCluster.addVirtualHostToCluster(v2);
  EXPECT_TRUE(wasVirtualAddedV2);

  std::map<int, std::list<VirtualHostDefault>> mapToCompare;
  mapToCompare[100] = std::list<VirtualHostDefault>({VirtualHostDefault(100, "foo")});
  mapToCompare[200] = std::list<VirtualHostDefault>({VirtualHostDefault(200, "bar")});

  const std::map<int, std::list<VirtualHostDefault>> &map = vCluster.getMap();
  decltype(map.size()) mapSize = 2;
  EXPECT_EQ(mapSize, map.size());

  EXPECT_EQ(mapToCompare, map);
}

// ---------------------------------------------------------


TEST(ClusterOfVirtualHostTest, getVirtualHost_invalidPort) {

  ClusterOfVirtualHost vCluster;

  error::StatusOr<VirtualHostDefault> vhExist = vCluster.getVirtualHost(100, "foo");

  EXPECT_FALSE(vhExist.ok());
  EXPECT_EQ("there is no host using port: 100", vhExist.status().message());
}

TEST(ClusterOfVirtualHostTest, getVirtualHost_validPort) {

  VirtualHostDefault v(100, "bar");

  ClusterOfVirtualHost vCluster;
  bool wasVirtualAdded = vCluster.addVirtualHostToCluster(v);
  EXPECT_TRUE(wasVirtualAdded);

  error::StatusOr<VirtualHostDefault> vhExist = vCluster.getVirtualHost(100, "foo");

  EXPECT_TRUE(vhExist.ok());

  EXPECT_EQ(v, vhExist.value());
}


TEST(ClusterOfVirtualHostTest, getVirtualHost_validPortButTheServernameIsAtTheEndOfItsCluster) {

  //must return the last virtualHost

  VirtualHostDefault v(100, "foo");
  VirtualHostDefault v2(100, "bar");

  ClusterOfVirtualHost vCluster;
  bool wasVirtualAdded = vCluster.addVirtualHostToCluster(v);
  EXPECT_TRUE(wasVirtualAdded);
  bool wasVirtualAddedV2 = vCluster.addVirtualHostToCluster(v2);
  EXPECT_TRUE(wasVirtualAddedV2);

  error::StatusOr<VirtualHostDefault> vhExist = vCluster.getVirtualHost(100, "bar");

  EXPECT_TRUE(vhExist.ok());

  EXPECT_EQ(v2, vhExist.value());
}

TEST(ClusterOfVirtualHostTest, getVirtualHost_validPortButTheServernameIsAtTheBeginningOfItsCluster) {

  //must return the last virtualHost

  VirtualHostDefault v(100, "foo");
  VirtualHostDefault v2(100, "bar");

  ClusterOfVirtualHost vCluster;
  bool wasVirtualAdded = vCluster.addVirtualHostToCluster(v);
  EXPECT_TRUE(wasVirtualAdded);
  bool wasVirtualAddedV2 = vCluster.addVirtualHostToCluster(v2);
  EXPECT_TRUE(wasVirtualAddedV2);

  error::StatusOr<VirtualHostDefault> vhExist = vCluster.getVirtualHost(100, "foo");

  EXPECT_TRUE(vhExist.ok());

  EXPECT_EQ(v, vhExist.value());
}


TEST(ClusterOfVirtualHostTest, getVirtualHost_validPortButHostNameDoesntExists) {

  //must return the first virtualHost

  VirtualHostDefault v(100, "foo");
  VirtualHostDefault v2(100, "bar");

  ClusterOfVirtualHost vCluster;
  bool wasVirtualAdded = vCluster.addVirtualHostToCluster(v);
  EXPECT_TRUE(wasVirtualAdded);
  bool wasVirtualAddedV2 = vCluster.addVirtualHostToCluster(v2);
  EXPECT_TRUE(wasVirtualAddedV2);

  error::StatusOr<VirtualHostDefault> vhExist = vCluster.getVirtualHost(100, "zzzzz");

  EXPECT_TRUE(vhExist.ok());

  EXPECT_EQ(v, vhExist.value());
}

// ---------------------------------------------------------

TEST(ClusterOfVirtualHostTest, getAllPorts_emptyCluster){

	ClusterOfVirtualHost cluster;

	std::list<int> listToCompare;

	EXPECT_EQ(listToCompare, cluster.getAllPorts());

}

TEST(ClusterOfVirtualHostTest, getAllPorts_cluterWithOneVirtualHost){

	ClusterOfVirtualHost cluster;
	cluster.addVirtualHostToCluster(VirtualHostDefault(80, "a"));

	std::list<int> listToCompare{80};

	EXPECT_EQ(listToCompare, cluster.getAllPorts());

}

TEST(ClusterOfVirtualHostTest, getAllPorts_cluterWithTwoVirtualHostButSamePort){

	ClusterOfVirtualHost cluster;
	cluster.addVirtualHostToCluster(VirtualHostDefault(80, "bar"));
	cluster.addVirtualHostToCluster(VirtualHostDefault(80, "xxx"));

	std::list<int> listToCompare{80};

	EXPECT_EQ(listToCompare, cluster.getAllPorts());

}

TEST(ClusterOfVirtualHostTest, getAllPorts_cluterWithTwoVirtualHostWithDifferentPorts){

	ClusterOfVirtualHost cluster;
	cluster.addVirtualHostToCluster(VirtualHostDefault(80, "bar"));
	cluster.addVirtualHostToCluster(VirtualHostDefault(8080, "xxx"));

	std::list<int> listToCompare{80,8080};

	EXPECT_EQ(listToCompare, cluster.getAllPorts());

}