#include "CreateDefaultErrorPagesFactory.hpp"

#include <sstream>

#include "../Start.hpp"

std::map<HTTPStatus::Status, ErrorPageFileHTMLDocument *>
    CreateDefaultErrorPagesFactory::mapWithDefaultPagesErrors;

void CreateDefaultErrorPagesFactory::fillTheFactory(
    const std::map<HTTPStatus::Status, ErrorPageFileHTMLDocument *>
        &mapWithDefaultPagesErrors) {
  CreateDefaultErrorPagesFactory::mapWithDefaultPagesErrors =
      mapWithDefaultPagesErrors;
}

void CreateDefaultErrorPagesFactory::destroyFactory() {
  std::map<HTTPStatus::Status, ErrorPageFileHTMLDocument *>::const_iterator it =
      mapWithDefaultPagesErrors.begin();
  std::map<HTTPStatus::Status, ErrorPageFileHTMLDocument *>::const_iterator
      end = mapWithDefaultPagesErrors.end();

  for (; it != end; ++it) {
    if (it->second) {
      delete it->second;
    }
  }
}

CreateDefaultErrorPagesFactory::CreateDefaultErrorPagesFactory()
    : _logger(LogDefault::loggerGlobal) {}

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

ErrorPageFileHTMLDocument *CreateDefaultErrorPagesFactory::getDefaultErrorPages(
    HTTPStatus::Status codeStatus) {
  std::map<HTTPStatus::Status, ErrorPageFileHTMLDocument *>::const_iterator
      end = mapWithDefaultPagesErrors.end();

  std::map<HTTPStatus::Status, ErrorPageFileHTMLDocument *>::const_iterator it =
      mapWithDefaultPagesErrors.find(codeStatus);

  if (it != end) {
    return dynamic_cast<ErrorPageFileHTMLDocument *>(it->second->clone());
  }

  if (_logger) {
    _logger->log(
        Log::FATAL, "CreateDefaultErrorPagesFactory", "getDefaultErrorPages",
        "An HTML error page was requested, but its status does not exist! "
        "Therefore, the page with code 500 was returned. Code",
        codeStatus);
  }

  ErrorPageFileHTMLDocument *pageErro =
      mapWithDefaultPagesErrors[HTTPStatus::INTERNAL_SERVER_ERROR];

  return dynamic_cast<ErrorPageFileHTMLDocument *>(pageErro->clone());
}

void CreateDefaultErrorPagesFactory::setLogger(Log *logger) {
  _logger = logger;
}