#include "HTTPResponseFake.hpp"

#include <string>

HTTPResponseFake::HTTPResponseFake(SocketFileDescriptor *socketFD, Log *logger)
    : _socketFD(socketFD), _logger(logger) {}

HTTPResponseFake::~HTTPResponseFake() {}

// deleted (this class MUST BE UNIQUE!)
HTTPResponseFake::HTTPResponseFake(const HTTPResponseFake &src)
    : _logger(src._logger) {
  (void)src;
}

// deleted (this class MUST BE UNIQUE!)
HTTPResponseFake &HTTPResponseFake::operator=(const HTTPResponseFake &src) {
  (void)src;
  return *this;
}

void HTTPResponseFake::createResponse() {
  std::string theResponse;

  theResponse +=
      "HTTP/1.1 200 OK\r\n"
      "Content-Type: text/html; charset=UTF-8\r\n"
      "Content-Length: 290\r\n"
      "Connection: keep-alive\r\n"
      "\r\n"
      "<!DOCTYPE html>\n"
      "<html lang=\"en-us\">\n"
      "<head>\n"
      "<meta charset=\"UTF-8\">\n"
      "<meta name=\"viewport\" content=\"width=device-width, "
      "initial-scale=1.0\">\n"
      "<title>My Simple page</title>\n"
      "</head>\n"
      "<body>\n"
      "<h1>The test page</h1>\n"
      "<p>This is a basic example of an HTTP response with an HTML body.</p>\n"
      "</body>\n"
      "</html>";

  _socketFD->getOutputStream().assign(theResponse.begin(),
                                      theResponse.begin() + theResponse.size());
  _socketFD->setCloseSocketAfterProcessingResponse(false);
}