#include "../../../libs/googletest/googlemock/include/gmock/gmock.h"
#include "../../../libs/googletest/googletest/include/gtest/gtest.h"

#include <vector>
#include "../Request.hpp"
#include "../SocketFileDescriptor.hpp"
#include "../URL.hpp"
#include "HTTPMethods.hpp"
#include "HTTPStatus.hpp"
#include "HTTPRequestTool.hpp"

class HTTPRequestTest : public Request 
{
private:
    std::vector<char> _socketFD;
    std::string _buffer;
    HTTPStatus::Status _status;
    HTTPRequestTool _HTTPTool;
public:
    HTTPRequestTest(/* args */);
    ~HTTPRequestTest();
    StateOfCreation createRequest();
    void setSocketFD(std::stirng c) { _socketFD.push_back(c); }


};

HTTPRequestTest::HTTPRequestTest(){}
HTTPRequestTest::~HTTPRequestTest(){}

HTTPRequestTest::StateOfCreation HTTPRequestTest::createRequest() {
	std::vector<char> &data = _socketFD->getInputStream();
	std::string strTmp(data.begin(), data.begin() + data.size());
	data.clear();
	_buffer += strTmp;

	if (_HTTPTool.isTheHTTPHeaderComplete(_buffer) || _HTTPTool.isBodyComplete(_buffer) || _HTTPTool.isChunked()) {
		//FAZER  IF PARA O HEADER 
		if(_HTTPTool.isTheHTTPHeaderComplete(_buffer) && !_HTTPTool.isParsed()){
			_HTTPTool.parserHeader(_buffer);
			_buffer = _buffer.substr(_buffer.find("\r\n\r\n") + 4);
		}
		if(_HTTPTool.isChunked()){
			_buffer = _HTTPTool.parseChunkedBody(_buffer);
			if(_HTTPTool.isChunkedEnd(_buffer)){
				return REQUEST_CREATED;
			}
			else
				return REQUEST_CREATING;
		}
		_HTTPTool.setBody(_buffer);
		return REQUEST_CREATED;
	}
	_logger->log(Log::DEBUG, "HTTPRequest", "createRequest", _buffer, "");
	return REQUEST_CREATING;
}


TEST(HTTPRequestTest, createRequest-leitura-cahrporchar) 
{
    HTTPRequestTest request;

    //leitura de file descriptor
    fd = open("test.txt", O_RDONLY);

    
    //while com leito char a char
    while (read(fd, &c, 1) == 1)
    {
        request.setSocketFD(c);
        response.createRequest();
    }
    close(fd);

    EXPECT_EQ(REQUEST_CREATING, request.createRequest());
}