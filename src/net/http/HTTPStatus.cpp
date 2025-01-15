#include "HTTPStatus.hpp"

const std::string HTTPStatus::INVALID_STRING_TEXT = "INVALID";

const std::map<HTTPStatus::Status, std::string> HTTPStatus::mapStatus = HTTPStatus::startMapStatus();

std::map<HTTPStatus::Status, std::string> HTTPStatus::startMapStatus(){

	std::map<HTTPStatus::Status, std::string> theMapToReturn;

	theMapToReturn.insert(std::pair<HTTPStatus::Status, std::string>(HTTPStatus::INVALID, INVALID_STRING_TEXT));

    // --- 200 family
	theMapToReturn.insert(std::pair<HTTPStatus::Status, std::string>(HTTPStatus::OK, "OK"));
	theMapToReturn.insert(std::pair<HTTPStatus::Status, std::string>(HTTPStatus::CREATED, "Created"));
	theMapToReturn.insert(std::pair<HTTPStatus::Status, std::string>(HTTPStatus::NO_CONTENT, "No Content"));

    // --- 301 family
	theMapToReturn.insert(std::pair<HTTPStatus::Status, std::string>(HTTPStatus::MOVED_PERMANENTLY, "Moved Permanently"));

    // --- 400 family
	theMapToReturn.insert(std::pair<HTTPStatus::Status, std::string>(HTTPStatus::BAD_REQUEST, "Bad Request"));
	theMapToReturn.insert(std::pair<HTTPStatus::Status, std::string>(HTTPStatus::FORBIDDEN, "Forbidden"));
	theMapToReturn.insert(std::pair<HTTPStatus::Status, std::string>(HTTPStatus::NOT_FOUND, "Not Found"));
	theMapToReturn.insert(std::pair<HTTPStatus::Status, std::string>(HTTPStatus::NOT_ALLOWED, "Method Not Allowed"));
	theMapToReturn.insert(std::pair<HTTPStatus::Status, std::string>(HTTPStatus::TIMEOUT, "Request Timeout"));
	theMapToReturn.insert(std::pair<HTTPStatus::Status, std::string>(HTTPStatus::CONFLICT, "Conflict"));
	theMapToReturn.insert(std::pair<HTTPStatus::Status, std::string>(HTTPStatus::REQUEST_ENTITY_TOO_LARGE, "Payload Too Large"));

    // --- 500 family
	theMapToReturn.insert(std::pair<HTTPStatus::Status, std::string>(HTTPStatus::SERVER_ERROR, "Internal Server Error"));
	theMapToReturn.insert(std::pair<HTTPStatus::Status, std::string>(HTTPStatus::NOT_IMPLEMENTED, "Not Implemented"));
	theMapToReturn.insert(std::pair<HTTPStatus::Status, std::string>(HTTPStatus::SERVICE_UNAVAILABLE, "Service Unavailable"));

	return theMapToReturn;
}

HTTPStatus::HTTPStatus(){}

HTTPStatus::~HTTPStatus(){}

HTTPStatus::HTTPStatus(const HTTPStatus &src){
	*this =  src;
}

HTTPStatus &HTTPStatus::operator=(const HTTPStatus &src){
	(void)src;
	return *this;
}

HTTPStatus::Status HTTPStatus::getStringToStatus(std::string status){
	std::map<HTTPStatus::Status, std::string>::const_iterator start = mapStatus.begin();
	std::map<HTTPStatus::Status, std::string>::const_iterator end = mapStatus.end();

	while(start != end){
		if (start->second == status)
			return start->first;
		start++;
	}
	return HTTPStatus::INVALID;
}

std::string HTTPStatus::getStatusToString(HTTPStatus::Status status){
	std::map<HTTPStatus::Status, std::string>::const_iterator start = mapStatus.begin();
	std::map<HTTPStatus::Status, std::string>::const_iterator end = mapStatus.end();

	while(start != end){
		if (start->first == status)
			return start->second;
		start++;
	}
	return INVALID_STRING_TEXT;
}