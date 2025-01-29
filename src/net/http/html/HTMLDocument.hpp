#ifndef SRC_HTTP_HTML_HTML_DOCUMENT_HPP
#define SRC_HTTP_HTML_HTML_DOCUMENT_HPP

#include <string>
#include "../HTTPStatus.hpp"

class HTMLDocument {
 public:
  virtual ~HTMLDocument();

  virtual std::string getData() const = 0;
  virtual std::size_t getSize() const = 0;
  virtual std::string getMimeType() const = 0;
  virtual std::string getLastModified() const = 0;
  virtual HTTPStatus::Status getStatus() const = 0;


};

#endif