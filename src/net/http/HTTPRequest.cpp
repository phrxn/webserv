#include "HTTPRequest.hpp"

#include <iostream>
#include <vector>

HTTPRequest::HTTPRequest(SocketFileDescriptor *socketFD, Log *logger)
{
_socketFD = socketFD;
(void)_header;
(void)_body;
_logger = logger;
}

HTTPRequest::~HTTPRequest() {}

// deleted (this class MUST BE UNIQUE!)
HTTPRequest::HTTPRequest(const HTTPRequest &src) { (void)src; }

// deleted (this class MUST BE UNIQUE!)
HTTPRequest &HTTPRequest::operator=(const HTTPRequest &src) {
(void)src;
return *this;
}

HTTPRequest::StateOfCreation HTTPRequest::createRequest() {

if(headerRequest() == REQUEST_CREATING){
return REQUEST_CREATING;
}

return REQUEST_CREATED;
}

void HTTPRequest::parserHeader()
{
std::map<std::string, std::string> headers;
std::size_t pos = 0;
std::string line;

// Parse the first line (request line)
line = _buffer.substr(pos, _buffer.find("\r\n", pos) - pos);
pos += line.size() + 2;

// implementação para extrair método, URL e versão HTTP da requisição
std::size_t spacePos1 = line.find(' ');
std::size_t spacePos2 = line.find(' ', spacePos1 + 1);
if (spacePos1 == std::string::npos || spacePos2 == std::string::npos) {
_status = HTTPStatus::BAD_REQUEST;
_logger->log(Log::ERROR, "HTTPRequest", "parserHeader", "Invalid request line", line);
}

headers["Method"] = line.substr(0, spacePos1);
headers["URL"] = line.substr(spacePos1 + 1, spacePos2 - spacePos1 - 1);
headers["HTTP-Version"] = line.substr(spacePos2 + 1);

while (pos < _buffer.size()) {
line = _buffer.substr(pos, _buffer.find("\r\n", pos) - pos);
pos += line.size() + 2; // Skip the line and the \r\n

if (line.empty()) {
break; // End of headers
}

std::size_t colonPos = line.find(":");
if (colonPos != std::string::npos) {
std::string key = line.substr(0, colonPos);
std::string value = line.substr(colonPos + 2); // Skip ": "
headers[key] = value;
}
else {
_status = HTTPStatus::BAD_REQUEST;
_logger->log(Log::ERROR, "HTTPRequest", "parserHeader", "Invalid header format", line);
}
}
headerValidation();
_header = headers;
}

HTTPRequest::StateOfCreation HTTPRequest::headerRequest() {
std::vector<char> &data = _socketFD->getInputStream();
std::string strTmp(data.begin(), data.begin() + data.size());
data.clear();
_buffer += strTmp;

if (!isTheHTTPHeaderComplete(_buffer)) {
return REQUEST_CREATING;
}
parserHeader();

_logger->log(Log::DEBUG, "HTTPRequest", "createRequest", _buffer, "");
return REQUEST_CREATED;
}

void HTTPRequest::headerValidation()
{
HTTPMethods httpMethods;

if (_header.find("Host") == _header.end() || _header.find("Method") == _header.end()
|| _header.find("URL") == _header.end() || _header.find("HTTP-Version") == _header.end()) {
_status = HTTPStatus::BAD_REQUEST;
}
else if (httpMethods.getStringToMethod(_header["Method"]) == HTTPMethods::INVALID) {
_status = HTTPStatus::BAD_REQUEST;
}
else if (_header["HTTP-Version"] != "HTTP/1.1") {
_status = HTTPStatus::BAD_REQUEST;
}
else
_status = HTTPStatus::OK;
}

HTTPMethods::Method HTTPRequest::getAnythingFromHeader(const std::string &key){
HTTPMethods httpMethods;

return httpMethods.getStringToMethod(_header[key]);
}

HTTPStatus::Status HTTPRequest::getStatus(){
return _status;
}

bool HTTPRequest::isTheHTTPHeaderComplete(std::string _buffer){
if (_buffer.find("\r\n\r\n") != std::string::npos)
return true;
return false;
}

HTTPStatus::Status  HTTPRequest::body(){
return HTTPStatus::OK;
}

std::string HTTPRequest::getHost(){
	return "";
}

HTTPMethods::Method HTTPRequest::getMethod(){
	return HTTPMethods::GET;
}

std::string HTTPRequest::getURL(){
    return "";
}
