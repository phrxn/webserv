#include "HandlerHTTPStatus.hpp"

#include "../../config/ProgramConfiguration.hpp"

HandlerHTTPStatus::HandlerHTTPStatus(const VirtualHostDefault *virtualHost)
    : _virtualHost(virtualHost), _httpDocument(NULL) {}

HandlerHTTPStatus::~HandlerHTTPStatus() {
  if (_httpDocument) {
    delete _httpDocument;
  }
}

HandlerHTTPStatus::HandlerHTTPStatus(const HandlerHTTPStatus &src)
    : _virtualHost(src._virtualHost),
      _fillHTTPResponse(src._fillHTTPResponse),
      _time(src._time) {
	 _httpDocument = src._httpDocument->clone();
}

HandlerHTTPStatus &HandlerHTTPStatus::operator=(const HandlerHTTPStatus &src) {
  if (this == &src) return *this;
  if (_httpDocument){
	delete _httpDocument;
  }
  _virtualHost = src._virtualHost;
  _createDefaultErrorPagesFactory = src._createDefaultErrorPagesFactory;
  _httpDocument = src._httpDocument->clone();
  _fillHTTPResponse = src._fillHTTPResponse;
  _time = src._time;
  return *this;
}

void HandlerHTTPStatus::doStatusError(HTTPResponse &response,
                                      HTTPStatus::Status status) {
  createErrorHTTPResponse(response, status);
  stampTheResponse(response, status);
}

void HandlerHTTPStatus::doStatusFamily200(HTTPRequest &request,
                                          HTTPResponse &response,
                                          HTTPStatus::Status status) {
  response.setConnection(request.isToKeepTheConnection());
  stampTheResponse(response, status);
}

void HandlerHTTPStatus::doStatusFamily300(
    HTTPResponse &response, HTTPStatus::Status status,
    const std::string &thePathToRedirect) {
  response.addHeader("Location", thePathToRedirect);
  createErrorHTTPResponse(response, status);
  stampTheResponse(response, status);
}

void HandlerHTTPStatus::createErrorHTTPResponse(HTTPResponse &response,
                                                HTTPStatus::Status status) {
  loadPageErrorPage(status);
  _fillHTTPResponse.makeFill(response, *_httpDocument);
  response.setConnection("close");
}

void HandlerHTTPStatus::stampTheResponse(HTTPResponse &response, HTTPStatus::Status status) {
  if (status == HTTPStatus::INVALID){
	status = HTTPStatus::INTERNAL_SERVER_ERROR;
  }
  response.setHTTPVersion(ProgramConfiguration::getInstance().getHTTPVersion());
  response.setStatus(status);
  response.setServer(ProgramConfiguration::getInstance().getServerName());
  response.setDate(_time.getCurrentTimeToStampAHTTPHeader());
}

void HandlerHTTPStatus::loadPageErrorPage(HTTPStatus::Status status) {

  _httpDocument = _createDefaultErrorPagesFactory.getDefaultErrorPages(status);

  std::string virtualHostErroPagePath;

  if (_virtualHost){
	virtualHostErroPagePath = _virtualHost->getThePathToCustomPageForHTTPStatus(status);
  }

  if (!virtualHostErroPagePath.empty()) {
    HTMLDocument *_httpDocumentFromVirtualHost =
        new ErrorPageFileHTMLDocument(virtualHostErroPagePath);
    if (_httpDocumentFromVirtualHost->getStatus() == 200) {
      delete _httpDocument;
      _httpDocument = _httpDocumentFromVirtualHost;
    }
  }
}
