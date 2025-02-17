#include "CreateDefaultErrorPages.hpp"

#include <fstream>
#include <list>
#include <sstream>

const std::string
    CreateDefaultErrorPages::DEFAULT_PATH_TO_FOLDER_WITH_ERROR_PAGES =
        "conf/default_error_pages/";

CreateDefaultErrorPages::CreateDefaultErrorPages() : _theErrno(new Errno) {}

CreateDefaultErrorPages::~CreateDefaultErrorPages() {
  if (_theErrno) {
    delete _theErrno;
  }
}

CreateDefaultErrorPages::CreateDefaultErrorPages(
    const CreateDefaultErrorPages &src) : _theErrno(new Errno(*src._theErrno)) {
}

CreateDefaultErrorPages &CreateDefaultErrorPages::operator=(
    const CreateDefaultErrorPages &src) {
  if (this == &src) return *this;
  if (_theErrno) {
    delete _theErrno;
  }
  _theErrno = new Errno(*src._theErrno);
  return *this;
}

error::StatusOr<std::map<HTTPStatus::Status, ErrorPageFileHTMLDocument*> >
CreateDefaultErrorPages::loadDefaultPageErrorsMap() {
  std::list<HTTPStatus::Status> listStatusWithPage;

  // 300 family
  listStatusWithPage.push_back(HTTPStatus::MOVED_PERMANENTLY);
  listStatusWithPage.push_back(HTTPStatus::FOUND);

  // 400 family
  listStatusWithPage.push_back(HTTPStatus::BAD_REQUEST);
  listStatusWithPage.push_back(HTTPStatus::FORBIDDEN);
  listStatusWithPage.push_back(HTTPStatus::NOT_FOUND);
  listStatusWithPage.push_back(HTTPStatus::NOT_ALLOWED);
  listStatusWithPage.push_back(HTTPStatus::TIMEOUT);
  listStatusWithPage.push_back(HTTPStatus::CONFLICT);
  listStatusWithPage.push_back(HTTPStatus::REQUEST_ENTITY_TOO_LARGE);

  // 500 family
  listStatusWithPage.push_back(HTTPStatus::INTERNAL_SERVER_ERROR);
  listStatusWithPage.push_back(HTTPStatus::NOT_IMPLEMENTED);
  listStatusWithPage.push_back(HTTPStatus::SERVICE_UNAVAILABLE);

  std::map<HTTPStatus::Status, ErrorPageFileHTMLDocument*> map;

  std::list<HTTPStatus::Status>::const_iterator it = listStatusWithPage.begin();
  std::list<HTTPStatus::Status>::const_iterator end = listStatusWithPage.end();

  for (; it != end; ++it) {
    error::StatusOr<ErrorPageFileHTMLDocument*> defaultErroPage = loadDefaultDefaultErrorPage(*it);
    if (!defaultErroPage.ok()) {
      return defaultErroPage.status();
    }
    map.insert(std::make_pair(*it, defaultErroPage.value()));
  }
  return map;
}

error::StatusOr<ErrorPageFileHTMLDocument*>
CreateDefaultErrorPages::loadDefaultDefaultErrorPage(
    HTTPStatus::Status codeStatus) const {
  std::string fullPathToFile = createFullPathToErroPage(codeStatus);
  return loadDefaultDefaultErrorPage(fullPathToFile);
}

error::StatusOr<ErrorPageFileHTMLDocument*>
CreateDefaultErrorPages::loadDefaultDefaultErrorPage(
    std::string fullPathToFile) const {

  std::ifstream pageDateStream(fullPathToFile.c_str());

  if (!pageDateStream.is_open()) {
    std::stringstream ssErrorMessage;
    ssErrorMessage << "Could not open the page error file: " << fullPathToFile
                   << ": " << _theErrno->getErrorMessage();
    return error::Status(error::Status::FileOpen, ssErrorMessage.str());
  }

 ErrorPageFileHTMLDocument* epf = new ErrorPageFileHTMLDocument(fullPathToFile, pageDateStream);

  return epf;
}

std::string CreateDefaultErrorPages::createFullPathToErroPage(
    HTTPStatus::Status codeStatus) const {
  std::stringstream ss;
  ss << DEFAULT_PATH_TO_FOLDER_WITH_ERROR_PAGES << codeStatus << ".html";
  return ss.str();
}

void CreateDefaultErrorPages::setErrno(Errno *newErrno) {
  if (_theErrno) {
    delete _theErrno;
  }
  _theErrno = newErrno;
}
