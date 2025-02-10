#ifndef NET_HTTP_HTML_CGI_HTML_DOCUMENT_HPP
#define NET_HTTP_HTML_CGI_HTML_DOCUMENT_HPP

#include "../../../error/LogDefault.hpp"
#include "../HTTPRequest.hpp"
#include "../cgi/FilesToCGI.hpp"
#include "CreateCGIHTMLDocument.hpp"
#include "HTMLDocument.hpp"

class CGIHTMLDocument : public HTMLDocument {
 public:
  CGIHTMLDocument(HTTPResponse &response);
  ~CGIHTMLDocument();
  CGIHTMLDocument(const CGIHTMLDocument &src);
  CGIHTMLDocument &operator=(const CGIHTMLDocument &src);

  std::string getData() const;
  std::size_t getSize() const;
  std::string getMimeType() const;
  std::string getLastModified() const;
  HTTPStatus::Status getStatus() const;

  HTTPStatus::Status createPage(const std::string &virtualHostRootPath,
                                const std::string &physicalPathToResource,
                                const HTTPRequest &request);

  HTMLDocument *clone() const;

 private:
  Log *_logger;
  CreateCGIHTMLDocument _createCGIHTMLDocument;
};

#endif