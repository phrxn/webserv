#ifndef NET_REQUEST_HPP
#define NET_REQUEST_HPP

class Request {
 public:
  enum StateOfCreation { REQUEST_CREATED, REQUEST_CREATING };

  virtual ~Request() = 0;

  virtual StateOfCreation createRequest() = 0;
};

#endif