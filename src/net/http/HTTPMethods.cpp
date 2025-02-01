#include "HTTPMethods.hpp"

const std::string HTTPMethods::INVALID_STRING_TEXT = "INVALID";

const std::map<HTTPMethods::Method, std::string> HTTPMethods::mapMethods = HTTPMethods::startMapMethods();

std::map<HTTPMethods::Method, std::string> HTTPMethods::startMapMethods(){

	std::map<HTTPMethods::Method, std::string> theMapToReturn;

	theMapToReturn.insert(std::pair<HTTPMethods::Method, std::string>(HTTPMethods::INVALID, INVALID_STRING_TEXT));
    theMapToReturn.insert(std::pair<HTTPMethods::Method, std::string>(HTTPMethods::GET, "GET"));
    theMapToReturn.insert(std::pair<HTTPMethods::Method, std::string>(HTTPMethods::POST, "POST"));
    theMapToReturn.insert(std::pair<HTTPMethods::Method, std::string>(HTTPMethods::PUT, "PUT"));
    theMapToReturn.insert(std::pair<HTTPMethods::Method, std::string>(HTTPMethods::DELETE, "DELETE"));
    theMapToReturn.insert(std::pair<HTTPMethods::Method, std::string>(HTTPMethods::HEAD, "HEAD"));
    theMapToReturn.insert(std::pair<HTTPMethods::Method, std::string>(HTTPMethods::OPTIONS, "OPTIONS"));
    theMapToReturn.insert(std::pair<HTTPMethods::Method, std::string>(HTTPMethods::TRACE, "TRACE"));
    theMapToReturn.insert(std::pair<HTTPMethods::Method, std::string>(HTTPMethods::CONNECT, "CONNECT"));
    theMapToReturn.insert(std::pair<HTTPMethods::Method, std::string>(HTTPMethods::PATCH, "PATCH"));
    theMapToReturn.insert(std::pair<HTTPMethods::Method, std::string>(HTTPMethods::LINK, "LINK"));
    theMapToReturn.insert(std::pair<HTTPMethods::Method, std::string>(HTTPMethods::UNLINK, "UNLINK"));

	return theMapToReturn;
}

HTTPMethods::HTTPMethods(){}

HTTPMethods::~HTTPMethods(){}

HTTPMethods::HTTPMethods(const HTTPMethods &src){
	*this = src;
}

HTTPMethods &HTTPMethods::operator=(const HTTPMethods &src){
	(void)src;
	return *this;
}

HTTPMethods::Method HTTPMethods::getStringToMethod(const std::string &status){
	std::map<HTTPMethods::Method, std::string>::const_iterator start = mapMethods.begin();
	std::map<HTTPMethods::Method, std::string>::const_iterator end = mapMethods.end();

	while(start != end){
		if (start->second == status)
			return start->first;
		start++;
	}
	return HTTPMethods::INVALID;
}

std::string HTTPMethods::getMethodToString(HTTPMethods::Method status){
	std::map<HTTPMethods::Method, std::string>::const_iterator start = mapMethods.begin();
	std::map<HTTPMethods::Method, std::string>::const_iterator end = mapMethods.end();

	while(start != end){
		if (start->first == status)
			return start->second;
		start++;
	}
	return INVALID_STRING_TEXT;
}
