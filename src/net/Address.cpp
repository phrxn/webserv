#include "Address.hpp"

#include <cstring>

Address::Address() {}

Address::Address(uint16_t port, Type type) : _port(port) {
  if (type == LOCAL) createLocalAddress();
}

Address::~Address() {}

Address::Address(const Address &src) { *this = src; }

Address &Address::operator=(const Address &src) {
  if (this == &src) return *this;
  _address = src._address;
  _port = src._port;
  return *this;
}

struct sockaddr_in *Address::getAddress() {
  return &(_address);
}

void Address::createLocalAddress() {
  memset(&_address, 0, sizeof _address);

  _address.sin_family = AF_INET;
  _address.sin_port = htons(_port);
  _address.sin_addr.s_addr = INADDR_ANY;
}
