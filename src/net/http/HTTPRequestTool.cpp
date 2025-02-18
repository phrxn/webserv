
#include "HTTPRequestTool.hpp"
#include <iostream>
#include <string>
#include <sstream>
#include <vector>
#include <iomanip>

HTTPRequestTool::HTTPRequestTool() {}

HTTPRequestTool::HTTPRequestTool(const HTTPRequestTool &other) : HTTPStatus(other) {
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
        _status = 0;
        return;
    }

    _header["Method"] = buffer.substr(0, spacePos1);
    _header["URL"] = buffer.substr(spacePos1 + 1, spacePos2 - spacePos1 - 1);
    std::string httpVersion = buffer.substr(spacePos2 + 1);
    // Remover caracteres de nova linha (\r e \n)
    _header["HTTP-Version"] = httpVersion.substr(0, httpVersion.size());
}

void HTTPRequestTool::splitOtherLines(const std::string& buffer) {
    while (pos < buffer.size()) {
        std::size_t endPos = buffer.find("\r\n", pos);
        if (endPos == std::string::npos) {
            endPos = buffer.find('\n', pos);
            if (endPos == std::string::npos) {
                endPos = buffer.size();
            }
        }
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
        } else {
            _status = 0;
        }
    }
}

void HTTPRequestTool::parserHeader(const std::string& buffer) {
    pos = 0;
    std::string tmp = buffer.substr(0, buffer.find("\r\n"));
    splitFirstLine(tmp);
    if (_status != 0) {
        splitOtherLines(buffer.substr(buffer.find("\r\n") + 2));
    }
}

std::map<std::string, std::string> HTTPRequestTool::getHeaders() {
    return _header;
}

std::string HTTPRequestTool::getBody() {
    return _body;
}

void HTTPRequestTool::setBody(const std::string& body) {
    if (_header["Content-Length"].empty()) {
        _body = body;
    } else {
       long int len = stringParaLongInt(_header["Content-Length"]);
        _body = body.substr(0, len);
    }
}

long int HTTPRequestTool::stringParaLongInt(const std::string& str) {
    std::istringstream iss(str);
    long int resultado = 0;

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

void HTTPRequestTool::parserChunked(const std::string& buffer) {
    std::string body;
    std::string line;
    std::istringstream stream(buffer);

    while (std::getline(stream, line)) {
        if (line.empty()) continue;

        int chunkSize = hexStringToInt(line);
        if (chunkSize == 0) break; // Final chunk - DO NOT include this in the body

        std::vector<char> _buffer(chunkSize + 1);
        if (stream.read(&_buffer[0], chunkSize)) {
            _buffer[chunkSize] = '\0';
            body.append(&_buffer[0], chunkSize);  // Append ONLY the chunk data
        } else {
            std::cerr << "Error: Could not read chunk data." << std::endl;
            return;
        }

        std::getline(stream, line); // Read the trailing \r\n - DO NOT include this
        if (line != "\r") {
          std::cerr << "Warning: Expected \\r\\n, but got: " << line << std::endl;
        }
    }

    _body = body;
}