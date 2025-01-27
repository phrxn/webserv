#include "CreateDefaultErrorPagesFactory.hpp"

#include <sstream>

#include "../Start.hpp"

std::map<HTTPStatus::Status, DefaultErrorPage>
      CreateDefaultErrorPagesFactory::mapWithDefaultPagesErrors;

void CreateDefaultErrorPagesFactory::fillTheFactory(
    const std::map<HTTPStatus::Status, DefaultErrorPage>
        &mapWithDefaultPagesErrors) {
  CreateDefaultErrorPagesFactory::mapWithDefaultPagesErrors =
      mapWithDefaultPagesErrors;
}

CreateDefaultErrorPagesFactory::CreateDefaultErrorPagesFactory() : _logger(Start::loggerGlobal) {}

CreateDefaultErrorPagesFactory::~CreateDefaultErrorPagesFactory() {}

CreateDefaultErrorPagesFactory::CreateDefaultErrorPagesFactory(
    const CreateDefaultErrorPagesFactory &src) {
  *this = src;
}

CreateDefaultErrorPagesFactory &CreateDefaultErrorPagesFactory::operator=(
    const CreateDefaultErrorPagesFactory &src) {
  _logger = src._logger;
  return *this;
}

DefaultErrorPage CreateDefaultErrorPagesFactory::getDefaultErrorPages(
    HTTPStatus::Status codeStatus) {
  std::map<HTTPStatus::Status, DefaultErrorPage>::const_iterator end =
      mapWithDefaultPagesErrors.end();

  std::map<HTTPStatus::Status, DefaultErrorPage>::const_iterator it =
      mapWithDefaultPagesErrors.find(codeStatus);
  if (it != end) {
    return it->second;
  }

  if (_logger) {
    _logger->log(
        Log::FATAL, "CreateDefaultErrorPagesFactory", "getDefaultErrorPages",
        "An HTML error page was requested, but its status does not exist! "
        "Therefore, the page with code 500 was returned. Code",
        codeStatus);
  }

  return mapWithDefaultPagesErrors[HTTPStatus::SERVER_ERROR];
}

void CreateDefaultErrorPagesFactory::setLogger(Log *logger){
	_logger = logger;
}