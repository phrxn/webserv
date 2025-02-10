#include "CreateCGIHTMLDocument.hpp"

#include <sstream>

CreateCGIHTMLDocument::CreateCGIHTMLDocument(HTTPResponse &response)
    : _response(response),
      _status(HTTPStatus::OK),
      _logger(LogDefault::loggerGlobal) {}

CreateCGIHTMLDocument::CreateCGIHTMLDocument(HTTPResponse &response,
                                             Log *logger)
    : _response(response), _status(HTTPStatus::OK), _logger(logger) {}

CreateCGIHTMLDocument::~CreateCGIHTMLDocument() {}

CreateCGIHTMLDocument::CreateCGIHTMLDocument(const CreateCGIHTMLDocument &src)
    : _response(src._response),
      _status(src._status),
      _logger(src._logger),
      _body(src._body) {
  (void)src;
}

CreateCGIHTMLDocument &CreateCGIHTMLDocument::operator=(
    const CreateCGIHTMLDocument &src) {
  if (this == &src) return *this;
  _status = src._status;
  _logger = src._logger;
  _body = src._body;
  return *this;
}

std::string CreateCGIHTMLDocument::getData() const { return _body; }

std::size_t CreateCGIHTMLDocument::getSize() const { return _body.size(); }

std::string CreateCGIHTMLDocument::getMimeType() const { return "text/html"; }

std::string CreateCGIHTMLDocument::getLastModified() const { return ""; }

HTTPStatus::Status CreateCGIHTMLDocument::getStatus() const { return _status; }

HTMLDocument *CreateCGIHTMLDocument::clone() const {
  return new CreateCGIHTMLDocument(*this);
}

HTTPStatus::Status CreateCGIHTMLDocument::createTheCGIResponse(const std::string &outputCGIFullStream) {
  std::stringstream ssStream(outputCGIFullStream);

  size_t pos = outputCGIFullStream.find("\r\n\r\n");
  if (pos == std::string::npos) {
    _logger->log(Log::ERROR, "CreateCGIHTMLDocument", "createTheCGIResponse", "the outputCGIFullStream malformed", "the file doesn't have an \r\n\r\n");
    return HTTPStatus::INTERNAL_SERVER_ERROR;
  }

  _body = outputCGIFullStream.substr(pos + 4);

  std::string headers_part = outputCGIFullStream.substr(0, pos);

  std::map<std::string, std::vector<std::string> > headers = getHeaders(headers_part);

  //before we set the headers we need to check if the status is in the headers
  //to remove it and set the status of the response
  _status = checkByStatusHeader(headers);

  _response.setHeaders(headers);

  // we will set it to true to prevent changes to headers that were created
  // by CGI in other parts of the program
  _response.setItACGIResponse(true);

  return _status;
}

std::map<std::string, std::vector<std::string> >
CreateCGIHTMLDocument::getHeaders(const std::string &headers_part) const {
  std::map<std::string, std::vector<std::string> > headers;
  std::istringstream stream(headers_part);
  std::string line;

  while (std::getline(stream, line)) {
    if (line.empty()) {
      continue;
    }
	if (line[line.size() - 1] == '\r') {
		line = line.substr(0, line.size() - 1);
	}

    size_t separator = line.find(": ");
    if (separator == std::string::npos){
		continue;
	}
      std::string key = line.substr(0, separator);
      std::string value = line.substr(separator + 2);
      headers[key].push_back(value);
  }
  return headers;
}

// remove the Status and convert the status to the HTTPStatus::Status
HTTPStatus::Status CreateCGIHTMLDocument::checkByStatusHeader(
    std::map<std::string, std::vector<std::string> > &headers) {

  HTTPStatus status;

  std::map<std::string, std::vector<std::string> >::iterator it = headers.find("Status");
  if (it == headers.end()) {
	return HTTPStatus::OK;
  }
  std::stringstream ss(it->second[0]);
  int statusInt;
  ss >> statusInt;
  headers.erase(it);
  return status.getIntToStatus(statusInt);
}
