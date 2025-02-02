#ifndef HTTPREQUESTTOOL_HPP
#define HTTPREQUESTTOOL_HPP

#include <map>
#include <string>
#include "HTTPStatus.hpp"



class HTTPRequestTool : public HTTPStatus {
public:
    // Default constructor
    HTTPRequestTool();

    // Destructor
    ~HTTPRequestTool();

    // Getters
    std::map<std::string, std::string> getHeaders();
    std::string getBody();
    // Split the first line of the HTTP request
    void splitFirstLine(const std::string& buffer);
    void splitOtherLines(const std::string& buffer);
    //parse the HTTP request
    void parserHeader (const std::string& buffer);
    //set body
    void setBody(const std::string& body);


private:

    HTTPRequestTool& operator=(const HTTPRequestTool& other);
    HTTPRequestTool(const HTTPRequestTool& other);

    long int stringParaLongInt(const std::string& str);

    std::map<std::string, std::string> _header;
    int _status;
    std::string line;
    std::size_t pos;
    std::string _body;
};

#endif // HTTPREQUESTTOOL_HPP