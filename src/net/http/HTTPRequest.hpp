#ifndef NET_HTTP_HTTP_REQUEST_HPP
#define NET_HTTP_HTTP_REQUEST_HPP

#include <string>
#include <map>

#include "../Request.hpp"
#include "../../error/Log.hpp"
#include "../SocketFileDescriptor.hpp"
#include "HTTPStatus.hpp"
#include "HTTPMethods.hpp"
#include "URL.hpp"

class HTTPRequest : public Request {
	private:
		HTTPRequest(const HTTPRequest &src);
		HTTPRequest &operator=(const HTTPRequest &src);
		HTTPRequest();
		map<std::string, std::string> parserHeader();
		void headerValidation();
		StateOfCreation headerRequest();

		SocketFileDescriptor *_socketFD;
		map<std::string, std::string> _header;
		std::string _body;
		std::string _buffer;
		HTTPStatus::Status _status;
		log *_logger

	public:

		HTTPRequest(SocketFileDescriptor *socketFD, log *logger);
		~HTTPRequest();

		StateOfCreation createRequest();

		std::string getHost();

		HTTPMethods::Method getMethod();

		std::string getURL();

		HTTPStatus::Status getStatus();

		bool isTheHTTPHeaderComplete(std::string _buffer);

};

	#endif