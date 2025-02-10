#ifndef NET_HTTP_HTML_CREATE_CGI_HTML_DOCUMENT_HPP
#define NET_HTTP_HTML_CREATE_CGI_HTML_DOCUMENT_HPP

#include "HTMLDocument.hpp"
#include "../HTTPResponse.hpp"
#include "../../../error/LogDefault.hpp"

class CreateCGIHTMLDocument : public HTMLDocument {
 public:
  CreateCGIHTMLDocument(HTTPResponse &response);
  CreateCGIHTMLDocument(HTTPResponse &response, Log *logger);
  ~CreateCGIHTMLDocument();
  CreateCGIHTMLDocument(const CreateCGIHTMLDocument &src);
  CreateCGIHTMLDocument &operator=(const CreateCGIHTMLDocument &src);

  std::string getData() const;
  std::size_t getSize() const;
  std::string getMimeType() const;
  std::string getLastModified() const;
  HTTPStatus::Status getStatus() const;

  HTMLDocument* clone() const;

  HTTPStatus::Status createTheCGIResponse(const std::string &outputCGIFullStream);

  std::map<std::string, std::vector<std::string> > getHeaders(const std::string &headers_part) const;

  HTTPStatus::Status checkByStatusHeader(std::map<std::string, std::vector<std::string> > &headers);

  private:
    HTTPResponse &_response;
	HTTPStatus::Status _status;
	Log *_logger;
	std::string _body;
};

#endif  // NET_HTTP_HTML_CREATECGIHTMLDOCUMENT_HPP