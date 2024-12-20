#ifndef NET_HTTP_HTTP_STATUS_HPP
#define NET_HTTP_HTTP_STATUS_HPP

//this is a "class enum"!
class HTTPStatus {
 public:
  enum Status{

    // --- 200 family
    OK = 200,
    CREATED = 201,
    NO_CONTENT = 204,

    // --- 300 family
    MOVED_PERMANENTLY = 301,

    // --- 400 family
    BAD_REQUEST = 400,
    FORBIDDEN = 403,
    NOT_FOUND = 404,
    NOT_ALLOWED = 405,
    TIMEOUT = 408,
    CONFLICT = 409,
    REQUEST_ENTITY_TOO_LARGE = 413,

    // --- 500 family
    SERVER_ERR = 500,
    NOT_IMPLEMENTED = 501,
    SERVICE_UNAVAILABLE = 503,
  };

  private:
	HTTPStatus();
	~HTTPStatus();
	HTTPStatus(const HTTPStatus &src);
	HTTPStatus &operator=(const HTTPStatus &src);
};

#endif