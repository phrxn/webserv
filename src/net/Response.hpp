#ifndef NET_RESPONSE_HPP
#define NET_RESPONSE_HPP

class Response {
 public:
  virtual ~Response() = 0;
  virtual void createResponse() = 0;
};

#endif