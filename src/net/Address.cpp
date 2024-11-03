#include "Address.hpp"

#include <cstring>

Address::Address() {}

Address::Address(uint16_t port, Type type) : port(port) {
  if (type == LOCAL) createLocalAddress();
}

Address::~Address() {}

Address::Address(const Address &src) { *this = src; }

Address &Address::operator=(const Address &src) {
  this->address = src.address;
  return *this;
}

struct sockaddr_in *Address::getAddress() {
  return &(this->address);
}

void Address::createLocalAddress() {
  memset(&address, 0, sizeof address);

  address.sin_family = AF_INET;
  address.sin_port = htons(port);
  address.sin_addr.s_addr = INADDR_ANY;
}
