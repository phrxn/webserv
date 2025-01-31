#ifndef HTTPREQUESTTOOL_HPP
#define HTTPREQUESTTOOL_HPP

#include <map>
#include <string>



class HTTPRequestTool {
public:
    // Default constructor
    HTTPRequestTool();

    // Destructor
    ~HTTPRequestTool();

    // Split the first line of the HTTP request
    void splitFirstLine(const std::string& buffer);
    void splitOtherLines(const std::string& buffer);
    void parseRequest(const std::string& buffer);
    std::map<std::string, std::string> getHeaders();

private:

    HTTPRequestTool& operator=(const HTTPRequestTool& other);
    HTTPRequestTool(const HTTPRequestTool& other);

    std::map<std::string, std::string> _header;
    int _status;
    std::string line;
    std::size_t pos;
};

#endif // HTTPREQUESTTOOL_HPP