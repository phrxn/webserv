#ifndef HTTPREQUESTTOOL_HPP
#define HTTPREQUESTTOOL_HPP

#include <map>
#include <string>
#include "HTTPStatus.hpp"
#include "HTTPMethods.hpp"
#include "../../error/LogDefault.hpp"


class HTTPRequestTool : public HTTPStatus {
public:
    // Default constructor
    HTTPRequestTool(Log *logger);

    // Destructor
    ~HTTPRequestTool();

    // Getters
    std::string getHeader(const std::string method);
    std::string getBody();
    HTTPStatus::Status getStatus();

    // Split the first line of the HTTP request
    void splitFirstLine(const std::string& buffer);
    void splitOtherLines(const std::string& buffer);

    //parse the HTTP request
    void parserHeader (const std::string& buffer);

    //set body
    void setBody(const std::string& body);

    //parser chunked
    std::string parseChunkedBody(const std::string& input) ;
    int hexStringToInt(const std::string& hex);

    //check
    bool isBodyComplete(const std::string& buffer) ;
    bool isChunkedEnd(const std::string& buffer);
    bool isChunked();
    bool isTheHTTPHeaderComplete(std::string _buffer);
    bool isParsed();
	bool isValidContentlength();

    //validate
    bool isValidHeader();
	bool HasBody();

private:

    HTTPRequestTool& operator=(const HTTPRequestTool& other);
    HTTPRequestTool(const HTTPRequestTool& other);

    std::size_t stringParaLongInt(const std::string& str);

    HTTPMethods _method;
    std::map<std::string, std::string> _header;
    HTTPStatus::Status _status;
    std::string line;
    std::size_t pos;
    std::string _body;
	Log *_logger;

};

#endif // HTTPREQUESTTOOL_HPP