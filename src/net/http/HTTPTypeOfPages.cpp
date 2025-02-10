#include "HTTPTypeOfPages.hpp"

const std::map<HTTPTypeOfPages::TypeOfPage, std::string> HTTPTypeOfPages::mapTypeOfPage = HTTPTypeOfPages::startMapTypeOfPage();

std::map<HTTPTypeOfPages::TypeOfPage, std::string> HTTPTypeOfPages::startMapTypeOfPage(){

	std::map<HTTPTypeOfPages::TypeOfPage, std::string> theMapToReturn;

	theMapToReturn.insert(std::pair<HTTPTypeOfPages::TypeOfPage, std::string>(HTTPTypeOfPages::STATIC, ""));
	theMapToReturn.insert(std::pair<HTTPTypeOfPages::TypeOfPage, std::string>(HTTPTypeOfPages::PHP, ".php"));
	theMapToReturn.insert(std::pair<HTTPTypeOfPages::TypeOfPage, std::string>(HTTPTypeOfPages::PYTHON, ".py"));

	return theMapToReturn;
}

HTTPTypeOfPages::HTTPTypeOfPages(){}

HTTPTypeOfPages::~HTTPTypeOfPages(){}

HTTPTypeOfPages::HTTPTypeOfPages(const HTTPTypeOfPages &src){
	*this =  src;
}

HTTPTypeOfPages &HTTPTypeOfPages::operator=(const HTTPTypeOfPages &src){
	(void)src;
	return *this;
}

HTTPTypeOfPages::TypeOfPage HTTPTypeOfPages::getStringToTypeOfPageFromPath(const std::string &path) const {

	std::map<HTTPTypeOfPages::TypeOfPage, std::string>::const_iterator start = mapTypeOfPage.begin();
	std::map<HTTPTypeOfPages::TypeOfPage, std::string>::const_iterator end = mapTypeOfPage.end();

	while(start != end){
		const std::string &extesionWithDot = start->second;
		if (extesionWithDot != "" && path.find(extesionWithDot) != std::string::npos){
				return start->first;
		}
		start++;
	}
	return HTTPTypeOfPages::STATIC;
}

HTTPTypeOfPages::TypeOfPage HTTPTypeOfPages::getStringToTypeOfPage(const std::string &typeOfPage) const {
	std::map<HTTPTypeOfPages::TypeOfPage, std::string>::const_iterator start = mapTypeOfPage.begin();
	std::map<HTTPTypeOfPages::TypeOfPage, std::string>::const_iterator end = mapTypeOfPage.end();

	while(start != end){
		if (start->second == typeOfPage)
			return start->first;
		start++;
	}
	return HTTPTypeOfPages::STATIC;
}

std::string HTTPTypeOfPages::getTypeOfPageToString(HTTPTypeOfPages::TypeOfPage typeOfPage) const {
	std::map<HTTPTypeOfPages::TypeOfPage, std::string>::const_iterator start = mapTypeOfPage.begin();
	std::map<HTTPTypeOfPages::TypeOfPage, std::string>::const_iterator end = mapTypeOfPage.end();

	while(start != end){
		if (start->first == typeOfPage)
			return start->second;
		start++;
	}
	return "STATIC";
}

HTTPTypeOfPages::TypeOfPage HTTPTypeOfPages::getTypeOfPathFromPath(const std::string &path) const {
	if (path.find(".php") != std::string::npos){
		return PHP;
	}
	if (path.find(".py") != std::string::npos){
		return PYTHON;
	}
	return STATIC;
}