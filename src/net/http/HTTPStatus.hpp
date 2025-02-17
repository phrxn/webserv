#ifndef NET_HTTP_HTTP_STATUS_HPP
#define NET_HTTP_HTTP_STATUS_HPP

#include <map>
#include <string>

//this is a "class enum"!
class HTTPStatus {
 public:
  enum Status{

    INVALID = 0,

    // --- 200 family
    OK = 200,
    CREATED = 201,
    NO_CONTENT = 204,

    // --- 300 family
    MOVED_PERMANENTLY = 301,
	FOUND = 302,

    // --- 400 family
    BAD_REQUEST = 400,
    FORBIDDEN = 403,
    NOT_FOUND = 404,
    NOT_ALLOWED = 405,
    TIMEOUT = 408,
    CONFLICT = 409,
    REQUEST_ENTITY_TOO_LARGE = 413,

    // --- 500 family
    INTERNAL_SERVER_ERROR = 500,
    NOT_IMPLEMENTED = 501,
    SERVICE_UNAVAILABLE = 503,
  };

  static const std::string INVALID_STRING_TEXT;

  HTTPStatus();
  ~HTTPStatus();
  HTTPStatus(const HTTPStatus &src);
  HTTPStatus &operator=(const HTTPStatus &src);

  HTTPStatus::Status getStringToStatus(const std::string &status);
  HTTPStatus::Status getIntToStatus(int status);
  std::string getStatusToString(HTTPStatus::Status status);
  std::string getStatusCodeToString(HTTPStatus::Status status);

  private:
	static const std::map<HTTPStatus::Status, std::string> mapStatus;
	static std::map<HTTPStatus::Status, std::string> startMapStatus();
};

#endif