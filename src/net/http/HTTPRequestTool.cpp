
#include "HTTPRequestTool.hpp"
#include "HTTPMethods.hpp"
#include "../URL.hpp"
#include "../../config/ProgramConfiguration.hpp"
#include <sstream>
#include <iostream>
#include <string>
#include <vector>

HTTPRequestTool::HTTPRequestTool(Log *logger) : _logger(logger) {
	pos = 0;
}

HTTPRequestTool::HTTPRequestTool(const HTTPRequestTool &other) {
    (void)other;
}
HTTPRequestTool &HTTPRequestTool::operator=(const HTTPRequestTool &other) {
    (void)other;
    return *this;
}

HTTPRequestTool::~HTTPRequestTool() {}


void HTTPRequestTool::splitFirstLine(const std::string& buffer) {
    std::size_t spacePos1 = buffer.find(' ');
    std::size_t spacePos2 = buffer.find(' ', spacePos1 + 1);
    if (spacePos1 == std::string::npos || spacePos2 == std::string::npos) {
        _status = HTTPStatus::OK;
        return;
    }

    _header["Method"] = buffer.substr(0, spacePos1);
    _header["URL"] = buffer.substr(spacePos1 + 1, spacePos2 - spacePos1 - 1);
    std::string httpVersion = buffer.substr(spacePos2 + 1);
    // Remover caracteres de nova linha (\r e \n)
    _header["HTTP-Version"] = httpVersion.substr(0, httpVersion.size());

    if(!isValidHeader())
    {
        _status = HTTPStatus::NOT_ALLOWED;
    }
    else
    {
        _status = HTTPStatus::OK;
    }
	_logger->log(Log::DEBUG, "HTTPRequestTool", "splitFirstLine", "the status", _status);
	_logger->log(Log::DEBUG, "HTTPRequestTool", "splitFirstLine", "METHOD", _header["Method"]);
	_logger->log(Log::DEBUG, "HTTPRequestTool", "splitFirstLine", "URL", _header["URL"]);
	_logger->log(Log::DEBUG, "HTTPRequestTool", "splitFirstLine", "HTTP", _header["HTTP-Version"]);
}

void HTTPRequestTool::splitOtherLines(const std::string& buffer) {
    while (pos < buffer.size()) {
        std::size_t endPos = buffer.find("\r\n", pos);

        line = buffer.substr(pos, endPos - pos);
        pos = endPos + (buffer[endPos] == '\r' ? 2 : 1); // Skip the line and the \r\n or \n

        if (line.empty()) {
            break; // End of headers
        }

        std::size_t colonPos = line.find(":");
        if (colonPos != std::string::npos) {
            std::string key = line.substr(0, colonPos);
            std::string value = line.substr(colonPos + 2); // Skip ": "
            _header[key] = value;
        }

		if(!isValidContentlength()) {
            _status = HTTPStatus::NOT_ALLOWED;
        }
		else{
		_status = HTTPStatus::OK;
		}
    }
  _logger->log(Log::DEBUG, "HTTPRequestTool", "splitOtherLines", "the status", _status);
 // _logger->log(Log::DEBUG, "HTTPRequestTool", "splitFirstLine", "the status", _header[]);
}

void HTTPRequestTool::parserHeader(const std::string& buffer) {
    pos = 0;
    std::string tmp = buffer.substr(0, buffer.find("\r\n"));
    splitFirstLine(tmp);
    if (_status == HTTPStatus::OK) {
        splitOtherLines(buffer.substr(buffer.find("\r\n") + 2));
    }
	_logger->log(Log::DEBUG, "HTTPRequestTool", "parserHeader", "the status", _status);
}

std::string HTTPRequestTool::getHeader(const std::string method) {
    return _header[method];
}

HTTPStatus::Status HTTPRequestTool::getStatus() {
    return _status;
}

std::string HTTPRequestTool::getBody() {
    return _body;
}

void HTTPRequestTool::setBody(const std::string& body) {
    if (_header["Content-Length"].empty()) {
        _body = body;
    } else {
       long int len = stringParaLongInt(_header["Content-Length"]);
        // long int start = body.find("\r\n\r\n") + 4;
        _logger->log(Log::DEBUG, "HTTPRequestTool", "setBody", "the body", body);
        _body = body.substr(0, len);
        _logger->log(Log::DEBUG, "HTTPRequestTool", "setBody", "the _body", _body);
        _logger->log(Log::DEBUG, "HTTPRequestTool", "setBody", "the Content-Length", _header["Content-Length"]);
        _logger->log(Log::DEBUG, "HTTPRequestTool", "setBody", "the _body size", _body.size());
        
    }
}

std::size_t HTTPRequestTool::stringParaLongInt(const std::string& str) {
    std::istringstream iss(str);
    std::size_t resultado = 0;

    if (iss >> resultado)
        return resultado;
    else
        throw ("Erro na conversão: string inválida para long int.");

}

int HTTPRequestTool::hexStringToInt(const std::string& hex) {
    int value;
    std::istringstream hexStream(hex);
    hexStream >> std::hex >> value;
    return value;
}

bool HTTPRequestTool::isChunked() {
    return _header["Transfer-Encoding"] == "chunked";
}

bool HTTPRequestTool::isChunkedEnd(const std::string& buffer) {
    return buffer.find("0\r\n\r\n") != std::string::npos;
}

bool HTTPRequestTool::isBodyComplete(const std::string& buffer) {
    if (_header["Content-Length"].empty()) {
        return isChunkedEnd(buffer);
    } else {
        return buffer.size() >= stringParaLongInt(_header["Content-Length"]);
    }
}

bool HTTPRequestTool::isTheHTTPHeaderComplete(std::string _buffer){
	if (_buffer.find("\r\n\r\n") != std::string::npos)
		return true;
	return false;
}

bool HTTPRequestTool::isParsed(){
    if(_header.empty())
        return false;
    return true;
}

bool HTTPRequestTool::isValidHeader(){
    if(_method.getStringToMethod (_header["Method"]) &&  _header["HTTP-Version"] == "HTTP/1.1")
        return true;
	else{
		return false;
	}
}

bool HTTPRequestTool::isValidContentlength(){
	if(_header["Content-Length"] != "" && stringParaLongInt(_header["Content-Length"]) > ProgramConfiguration::getInstance().getMaxRequestSizeInBytes())
		return false;
	return true;
}

bool HTTPRequestTool::HasBody(){
	if(_header["Content-Length"] != "" )
		return true;
	return false;
}

void HTTPRequestTool::parseChunkedBody(const std::string& input) {
    //variavel que armazena o tamanho do chunk
    std::size_t chunkSize = 0;
    //variavel que concatena os chunks
    std::string output;
    //variavel que armazena o tamanho do chunk em hexadecimal
    std::string hexSize;
    // Create a copy of input to modify
    std::string remainingInput = input;
    _logger->log(Log::DEBUG, "HTTPRequest", "createRequest", "the input", input);
    _logger->log(Log::DEBUG, "HTTPRequest", "createRequest", "the remainingInput", remainingInput);
    
    //enquanto houver chunks
    while (true) {
        std::size_t endPos = remainingInput.find("\r\n");
        hexSize = remainingInput.substr(0, endPos);
        chunkSize = hexStringToInt(hexSize);
        _logger->log(Log::DEBUG, "HTTPRequest", "createRequest", "the chunkSize", chunkSize);
        if (chunkSize == 0) {
            break;
        }
        output += remainingInput.substr(endPos + 2, chunkSize);
        remainingInput = remainingInput.substr(endPos + 2 + chunkSize + 2);
        _logger->log(Log::DEBUG, "HTTPRequest", "createRequest", "the remainingInput", remainingInput);
    }
    _logger->log(Log::DEBUG, "HTTPRequest", "createRequest", "the output", output);
    _body = output;
    
    // Converte o tamanho do corpo para string usando stringstream
    std::stringstream ss;
    ss << _body.size();
    _header["Content-Length"] = ss.str();
}
