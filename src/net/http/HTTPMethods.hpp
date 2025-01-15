#ifndef NET_HTTP_HTTP_METHODS_HPP
#define NET_HTTP_HTTP_METHODS_HPP

#include <map>
#include <string>

//this is a "class enum"!
class HTTPMethods {
 public:
  enum Method{
	INVALID,
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

  static const std::string INVALID_STRING_TEXT;

  HTTPMethods();
  ~HTTPMethods();
  HTTPMethods(const HTTPMethods &src);
  HTTPMethods &operator=(const HTTPMethods &src);

  HTTPMethods::Method getStringToMethod(std::string status);
  std::string getMethodToString(HTTPMethods::Method status);

  private:
	static const std::map<HTTPMethods::Method, std::string> mapMethods;
	static std::map<HTTPMethods::Method, std::string> startMapMethods();
};
#endif