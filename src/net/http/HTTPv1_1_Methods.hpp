#ifndef NET_HTTP_HTTP_METHODS_HPP
#define NET_HTTP_HTTP_METHODS_HPP

enum HTTPv1_1_Methods {
  GET,
  POST,
  PUT,
  DELETE,
  HEAD,
  OPTIONS,
  TRACE,
  CONNECT,
  PATCH,
  LINK,
  UNLINK
#ifdef COMPILE_TEST
  ,
  // value used only in the tests
  FAKE_METHOD
#endif
};

#endif