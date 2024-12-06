#ifndef NET_HTTP_HTTP_METHODS_HPP
#define NET_HTTP_HTTP_METHODS_HPP

//this is a "class enum"!
class HTTPMethods {
 public:
  enum Method{
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

  private:
	HTTPMethods();
	~HTTPMethods();
	HTTPMethods(const HTTPMethods &src);
	HTTPMethods &operator=(HTTPMethods &src);
};
#endif