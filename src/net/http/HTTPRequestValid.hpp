#ifndef HTTPREQUESTVALID_HPP
#define HTTPREQUESTVALID_HPP

#include <map>
#include "HTTPRequest.hpp"
#include "HTTPRequestTool.hpp"

class HTTPRequestValid
{
private:
    HTTPRequestValid(const HTTPRequestValid &src);
    HTTPRequestValid &operator=(const HTTPRequestValid &src);
    HTTPRequestValid();

    HTTPRequestTool _header;
public:
    HTTPRequestValid(const HTTPRequestTool &header);
    ~HTTPRequestValid();

    bool isValidHeader(const HTTPRequestTool &header);
    bool isValidBody(const std::string &body);
    
};

