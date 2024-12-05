#include "../../libs/googletest/googlemock/include/gmock/gmock.h"
#include "../../libs/googletest/googletest/include/gtest/gtest.h"
#include "VirtualHost.hpp"
#include "VirtualHostFactory.hpp"

class VirtualHostMock : public VirtualHost {
 public:
  VirtualHostMock() {}
  ~VirtualHostMock() {}
};

TEST(VirtualHostFactory, memoryLeak){

	VirtualHostMock *vhm = new VirtualHostMock;
	VirtualHostMock *vhm2 = new VirtualHostMock;

	std::map<std::string, const VirtualHost *> map;
	map["a"] = vhm;
	map["b"] = vhm2;

	VirtualHostFactory::fillTheFactory(map);
	VirtualHostFactory::destroyFactory();
}

// ---------------------------------------------------------

TEST(VirtualHostFactory, createVirtualHost_hostDoesntExist){

	VirtualHostMock *vhm = new VirtualHostMock;
	VirtualHostMock *vhm2 = new VirtualHostMock;

	std::map<std::string, const VirtualHost *> map;
	map["a"] = vhm;
	map["b"] = vhm2;

	VirtualHostFactory::fillTheFactory(map);

	VirtualHostFactory vhf;
	const VirtualHost *vhNull = vhf.createVirtualHost("c");

	EXPECT_EQ(NULL, vhNull);

	VirtualHostFactory::destroyFactory();
}

TEST(VirtualHostFactory, createVirtualHost_hostExist){

	VirtualHostMock *vhm = new VirtualHostMock;
	VirtualHostMock *vhm2 = new VirtualHostMock;

	std::map<std::string, const VirtualHost *> map;
	map["a"] = vhm;
	map["b"] = vhm2;

	VirtualHostFactory::fillTheFactory(map);

	VirtualHostFactory vhf;
	const VirtualHost *vh = vhf.createVirtualHost("b");

	EXPECT_EQ(vhm2, vh);

	VirtualHostFactory::destroyFactory();
}

TEST(VirtualHostFactory, createVirtualHost_checkIfPointersAreDifferent){

	VirtualHostMock *vhm = new VirtualHostMock;
	VirtualHostMock *vhm2 = new VirtualHostMock;

	std::map<std::string, const VirtualHost *> map;
	map["a"] = vhm;
	map["b"] = vhm2;

	VirtualHostFactory::fillTheFactory(map);

	VirtualHostFactory vhf;
	const VirtualHost *vh = vhf.createVirtualHost("a");

	EXPECT_NE(vhm2, vh);

	VirtualHostFactory::destroyFactory();
}