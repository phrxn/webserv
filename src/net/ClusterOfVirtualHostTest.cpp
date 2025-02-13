#include "../../libs/googletest/googlemock/include/gmock/gmock.h"
#include "../../libs/googletest/googletest/include/gtest/gtest.h"

#include "VirtualHostDefault.hpp"
#include "ClusterOfVirtualHost.hpp"


class VirtualHostMockToTestCluster : public VirtualHostDefault {
 public:
  VirtualHostMockToTestCluster(int port, const std::string &serverName) : VirtualHostDefault(port, serverName) {}
  VirtualHostMockToTestCluster(const VirtualHostMockToTestCluster &src) : VirtualHostDefault(src) {}

  MOCK_METHOD(bool, isPathValid,(const URL& url), (const, override));
  MOCK_METHOD(std::string, isPathARedirection, (const URL& url), (const, override));
  MOCK_METHOD(bool, isTheMethodAllowedForThisPath, (const URL& url, HTTPMethods::Method method), (const, override));
  MOCK_METHOD(bool, isUrlAPathToCGI, (const URL& url), (const, override));
  MOCK_METHOD(std::string, getThePhysicalPath, (const URL& url), (const, override));
  MOCK_METHOD(bool, isDirectoryListingAllowedForThisPath, (const URL& url), (const, override));
  MOCK_METHOD(std::string, getThePathToCustomPageForHTTPStatus, (HTTPStatus::Status httpStatus), (const, override));

};


bool compareTheTwoMaps(const std::map<int, std::list<const VirtualHostDefault *>> &map, std::map<int, std::list<VirtualHostMockToTestCluster>> &mapToCompare){

	for(auto it = map.begin(); it != map.end(); it++){
		if (mapToCompare.find(it->first) == mapToCompare.end()){
		  return false;
		}

		std::list<const VirtualHostDefault*>::const_iterator itListOfVH = it->second.begin();
		std::list<VirtualHostMockToTestCluster>::const_iterator itListOfVHToCompare = mapToCompare[it->first].begin();

		for(; itListOfVH != it->second.end(); ++itListOfVH, ++itListOfVHToCompare){
		  if ((*itListOfVH)->getPort() != itListOfVHToCompare->getPort() ||
			  (*itListOfVH)->getServerName() != itListOfVHToCompare->getServerName()){
				return false;
			  }
		}
	  }
	  return true;
}

TEST(ClusterOfVirtualHostTest, addVirtualHostToCluster_addOneVirtualHost) {
  VirtualHostMockToTestCluster *v = new VirtualHostMockToTestCluster (100, "foo");

  ClusterOfVirtualHost vCluster;
  bool wasVirtualAdded = vCluster.addVirtualHostToCluster(v);
  EXPECT_TRUE(wasVirtualAdded);

  std::map<int, std::list<VirtualHostMockToTestCluster>> mapToCompare;
  mapToCompare[100] = std::list<VirtualHostMockToTestCluster>({VirtualHostMockToTestCluster(100, "foo")});

  auto &map = vCluster.getMap();
  decltype(map.size()) mapSize = 1;

  EXPECT_EQ(mapSize, map.size());

  EXPECT_TRUE(compareTheTwoMaps(map, mapToCompare));

  vCluster.destroyAllVirtualHosts();
}


TEST(ClusterOfVirtualHostTest, addVirtualHostToCluster_addTwoEqualsVirtualHost) {
  VirtualHostMockToTestCluster *v = new VirtualHostMockToTestCluster(100, "foo");
  VirtualHostMockToTestCluster *v2 = new VirtualHostMockToTestCluster(100, "foo");

  ClusterOfVirtualHost vCluster;
  bool wasVirtualAdded = vCluster.addVirtualHostToCluster(v);
  EXPECT_TRUE(wasVirtualAdded);
  bool wasVirtualAddedV2 = vCluster.addVirtualHostToCluster(v2);
  EXPECT_FALSE(wasVirtualAddedV2);

  std::map<int, std::list<VirtualHostMockToTestCluster>> mapToCompare;
  mapToCompare[100] = std::list<VirtualHostMockToTestCluster>({VirtualHostMockToTestCluster(100, "foo")});

  const std::map<int, std::list<const VirtualHostDefault*>> &map = vCluster.getMap();
  decltype(map.size()) mapSize = 1;

  EXPECT_EQ(mapSize, map.size());

  EXPECT_TRUE(compareTheTwoMaps(map, mapToCompare));

  vCluster.destroyAllVirtualHosts();

  delete v2;
}


TEST(ClusterOfVirtualHostTest,
     addVirtualHostToCluster_addTwoDifferentVirtualHostsWithSamePort) {
  VirtualHostMockToTestCluster *v = new VirtualHostMockToTestCluster(100, "foo");
  VirtualHostMockToTestCluster *v2 = new VirtualHostMockToTestCluster(100, "bar");

  ClusterOfVirtualHost vCluster;
  bool wasVirtualAdded = vCluster.addVirtualHostToCluster(v);
  EXPECT_TRUE(wasVirtualAdded);
  bool wasVirtualAddedV2 = vCluster.addVirtualHostToCluster(v2);
  EXPECT_TRUE(wasVirtualAddedV2);

  std::map<int, std::list<VirtualHostMockToTestCluster>> mapToCompare;
  mapToCompare[100] = std::list<VirtualHostMockToTestCluster>({VirtualHostMockToTestCluster(100, "foo"), VirtualHostMockToTestCluster(100, "bar")});

  const std::map<int, std::list<const VirtualHostDefault*>> &map = vCluster.getMap();
  decltype(map.size()) mapSize = 1;
  EXPECT_EQ(mapSize, map.size());

  EXPECT_TRUE(compareTheTwoMaps(map, mapToCompare));

  vCluster.destroyAllVirtualHosts();
}



TEST(ClusterOfVirtualHostTest,
     addVirtualHostToCluster_addTwoDifferentVirtualHostsWithDifferentPort) {
  VirtualHostMockToTestCluster *v = new VirtualHostMockToTestCluster(100, "foo");
  VirtualHostMockToTestCluster *v2 = new VirtualHostMockToTestCluster(200, "foo");

  ClusterOfVirtualHost vCluster;
  bool wasVirtualAdded = vCluster.addVirtualHostToCluster(v);
  EXPECT_TRUE(wasVirtualAdded);
  bool wasVirtualAddedV2 = vCluster.addVirtualHostToCluster(v2);
  EXPECT_TRUE(wasVirtualAddedV2);

  std::map<int, std::list<VirtualHostMockToTestCluster>> mapToCompare;
  mapToCompare[100] = std::list<VirtualHostMockToTestCluster>({VirtualHostMockToTestCluster(100, "foo")});
  mapToCompare[200] = std::list<VirtualHostMockToTestCluster>({VirtualHostMockToTestCluster(200, "foo")});

  const std::map<int, std::list<const VirtualHostDefault*>> &map = vCluster.getMap();
  decltype(map.size()) mapSize = 2;
  EXPECT_EQ(mapSize, map.size());

  EXPECT_TRUE(compareTheTwoMaps(map, mapToCompare));

  vCluster.destroyAllVirtualHosts();
}


TEST(
    ClusterOfVirtualHostTest,
    addVirtualHostToCluster_addTwoDifferentVirtualHostsWithDifferentPortsAndServername) {
  VirtualHostMockToTestCluster *v = new VirtualHostMockToTestCluster(100, "foo");
  VirtualHostMockToTestCluster *v2 = new VirtualHostMockToTestCluster(200, "bar");

  ClusterOfVirtualHost vCluster;
  bool wasVirtualAdded = vCluster.addVirtualHostToCluster(v);
  EXPECT_TRUE(wasVirtualAdded);
  bool wasVirtualAddedV2 = vCluster.addVirtualHostToCluster(v2);
  EXPECT_TRUE(wasVirtualAddedV2);

  std::map<int, std::list<VirtualHostMockToTestCluster>> mapToCompare;
  mapToCompare[100] = std::list<VirtualHostMockToTestCluster>({VirtualHostMockToTestCluster(100, "foo")});
  mapToCompare[200] = std::list<VirtualHostMockToTestCluster>({VirtualHostMockToTestCluster(200, "bar")});

  const std::map<int, std::list<const VirtualHostDefault*>> &map = vCluster.getMap();
  decltype(map.size()) mapSize = 2;
  EXPECT_EQ(mapSize, map.size());

  EXPECT_TRUE(compareTheTwoMaps(map, mapToCompare));

  vCluster.destroyAllVirtualHosts();
}

// ---------------------------------------------------------


TEST(ClusterOfVirtualHostTest, getVirtualHost_invalidPort) {

  ClusterOfVirtualHost vCluster;

  error::StatusOr<const VirtualHostDefault*> vhExist = vCluster.getVirtualHost(100, "foo");

  EXPECT_FALSE(vhExist.ok());
  EXPECT_EQ("there is no host using port: 100", vhExist.status().message());

  vCluster.destroyAllVirtualHosts();
}


TEST(ClusterOfVirtualHostTest, getVirtualHost_validPort) {

  VirtualHostMockToTestCluster *v = new VirtualHostMockToTestCluster(100, "bar");

  ClusterOfVirtualHost vCluster;
  bool wasVirtualAdded = vCluster.addVirtualHostToCluster(v);
  EXPECT_TRUE(wasVirtualAdded);

  error::StatusOr<const VirtualHostDefault*> vhExist = vCluster.getVirtualHost(100, "foo");

  EXPECT_TRUE(vhExist.ok());

  EXPECT_EQ(v, vhExist.value());

  vCluster.destroyAllVirtualHosts();
}


TEST(ClusterOfVirtualHostTest, getVirtualHost_validPortButTheServernameIsAtTheEndOfItsCluster) {

  //must return the last virtualHost

  VirtualHostMockToTestCluster *v = new VirtualHostMockToTestCluster(100, "foo");
  VirtualHostMockToTestCluster *v2 = new VirtualHostMockToTestCluster(100, "bar");

  ClusterOfVirtualHost vCluster;
  bool wasVirtualAdded = vCluster.addVirtualHostToCluster(v);
  EXPECT_TRUE(wasVirtualAdded);
  bool wasVirtualAddedV2 = vCluster.addVirtualHostToCluster(v2);
  EXPECT_TRUE(wasVirtualAddedV2);

  error::StatusOr<const VirtualHostDefault*> vhExist = vCluster.getVirtualHost(100, "bar");

  EXPECT_TRUE(vhExist.ok());

  EXPECT_EQ(v2, vhExist.value());

  vCluster.destroyAllVirtualHosts();
}


TEST(ClusterOfVirtualHostTest, getVirtualHost_validPortButTheServernameIsAtTheBeginningOfItsCluster) {

  //must return the last virtualHost

  VirtualHostMockToTestCluster *v = new VirtualHostMockToTestCluster(100, "foo");
  VirtualHostMockToTestCluster *v2 = new VirtualHostMockToTestCluster(100, "bar");

  ClusterOfVirtualHost vCluster;
  bool wasVirtualAdded = vCluster.addVirtualHostToCluster(v);
  EXPECT_TRUE(wasVirtualAdded);
  bool wasVirtualAddedV2 = vCluster.addVirtualHostToCluster(v2);
  EXPECT_TRUE(wasVirtualAddedV2);

  error::StatusOr<const VirtualHostDefault*> vhExist = vCluster.getVirtualHost(100, "foo");

  EXPECT_TRUE(vhExist.ok());

  EXPECT_EQ(v, vhExist.value());

  vCluster.destroyAllVirtualHosts();
}


TEST(ClusterOfVirtualHostTest, getVirtualHost_validPortButHostNameDoesntExists) {

  //must return the first virtualHost

  VirtualHostMockToTestCluster *v = new VirtualHostMockToTestCluster(100, "foo");
  VirtualHostMockToTestCluster *v2 = new VirtualHostMockToTestCluster(100, "bar");

  ClusterOfVirtualHost vCluster;
  bool wasVirtualAdded = vCluster.addVirtualHostToCluster(v);
  EXPECT_TRUE(wasVirtualAdded);
  bool wasVirtualAddedV2 = vCluster.addVirtualHostToCluster(v2);
  EXPECT_TRUE(wasVirtualAddedV2);

  error::StatusOr<const VirtualHostDefault*> vhExist = vCluster.getVirtualHost(100, "zzzzz");

  EXPECT_TRUE(vhExist.ok());

  EXPECT_EQ(v, vhExist.value());

  vCluster.destroyAllVirtualHosts();
}


// ---------------------------------------------------------

TEST(ClusterOfVirtualHostTest, getAllPorts_emptyCluster){

	ClusterOfVirtualHost vCluster;

	std::list<int> listToCompare;

	EXPECT_EQ(listToCompare, vCluster.getAllPorts());

	vCluster.destroyAllVirtualHosts();

}


TEST(ClusterOfVirtualHostTest, getAllPorts_cluterWithOneVirtualHost){

	VirtualHostMockToTestCluster *v = new VirtualHostMockToTestCluster(80, "a");

	ClusterOfVirtualHost cluster;
	cluster.addVirtualHostToCluster(v);

	std::list<int> listToCompare{80};

	EXPECT_EQ(listToCompare, cluster.getAllPorts());

	cluster.destroyAllVirtualHosts();
}


TEST(ClusterOfVirtualHostTest, getAllPorts_cluterWithTwoVirtualHostButSamePort){

	VirtualHostMockToTestCluster *v1 = new VirtualHostMockToTestCluster(80, "bar");
	VirtualHostMockToTestCluster *v2 = new VirtualHostMockToTestCluster(80, "xxx");

	ClusterOfVirtualHost cluster;
	cluster.addVirtualHostToCluster(v1);
	cluster.addVirtualHostToCluster(v2);

	std::list<int> listToCompare{80};

	EXPECT_EQ(listToCompare, cluster.getAllPorts());

	cluster.destroyAllVirtualHosts();
}

TEST(ClusterOfVirtualHostTest, getAllPorts_cluterWithTwoVirtualHostWithDifferentPorts){

	VirtualHostMockToTestCluster *v1 = new VirtualHostMockToTestCluster(80, "bar");
	VirtualHostMockToTestCluster *v2 = new VirtualHostMockToTestCluster(8080, "xxx");

	ClusterOfVirtualHost cluster;
	cluster.addVirtualHostToCluster(v1);
	cluster.addVirtualHostToCluster(v2);

	std::list<int> listToCompare{80,8080};

	EXPECT_EQ(listToCompare, cluster.getAllPorts());

	cluster.destroyAllVirtualHosts();
}
