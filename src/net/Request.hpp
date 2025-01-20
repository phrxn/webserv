#ifndef NET_REQUEST_HPP
#define NET_REQUEST_HPP

class Request {
 public:
  enum StateOfCreation { REQUEST_CREATED, REQUEST_CREATING, HEADER_CREATED, HEADER_CREATING, BODY_CREATED, BODY_CREATING };

  virtual ~Request() = 0;

  virtual StateOfCreation createRequest() = 0;
};

#endif