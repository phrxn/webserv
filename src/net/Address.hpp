#ifndef NET_ADDRESS_NET
#define NET_ADDRESS_NET

#include <netinet/in.h>

class Address {
 public:
  enum Type { LOCAL, REMOTE };

  Address();
  Address(uint16_t port, Type type);
  ~Address();
  Address(const Address &src);

  Address &operator=(const Address &src);

  struct sockaddr_in *getAddress();

 private:
  void createLocalAddress();

  struct sockaddr_in address;
  uint16_t port;
};

#endif
