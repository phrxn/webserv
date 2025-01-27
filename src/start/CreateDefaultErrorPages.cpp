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
  if (_theErrno) {
    delete _theErrno;
  }
  _theErrno = new Errno(*src._theErrno);
  return *this;
}

error::StatusOr<std::map<HTTPStatus::Status, DefaultErrorPage> >
CreateDefaultErrorPages::loadDefaultPageErrorsMap() {
  std::list<HTTPStatus::Status> listStatusWithPage;

  // 400 family
  listStatusWithPage.push_back(HTTPStatus::BAD_REQUEST);
  listStatusWithPage.push_back(HTTPStatus::FORBIDDEN);
  listStatusWithPage.push_back(HTTPStatus::NOT_FOUND);
  listStatusWithPage.push_back(HTTPStatus::NOT_ALLOWED);
  listStatusWithPage.push_back(HTTPStatus::TIMEOUT);
  listStatusWithPage.push_back(HTTPStatus::CONFLICT);
  listStatusWithPage.push_back(HTTPStatus::REQUEST_ENTITY_TOO_LARGE);

  // 500 family
  listStatusWithPage.push_back(HTTPStatus::SERVER_ERROR);
  listStatusWithPage.push_back(HTTPStatus::NOT_IMPLEMENTED);
  listStatusWithPage.push_back(HTTPStatus::SERVICE_UNAVAILABLE);

  std::map<HTTPStatus::Status, DefaultErrorPage> map;

  std::list<HTTPStatus::Status>::const_iterator it = listStatusWithPage.begin();
  std::list<HTTPStatus::Status>::const_iterator end = listStatusWithPage.end();

  for (; it != end; ++it) {
    error::StatusOr<DefaultErrorPage> defaultErroPage =
        loadDefaultDefaultErrorPage(*it);
    if (!defaultErroPage.ok()) {
      return defaultErroPage.status();
    }
    map.insert(std::make_pair(*it, defaultErroPage.value()));
  }
  return map;
}

error::StatusOr<DefaultErrorPage>
CreateDefaultErrorPages::loadDefaultDefaultErrorPage(
    HTTPStatus::Status codeStatus) const {
  std::string fullPathToFile = createFullPathToErroPage(codeStatus);
  return loadDefaultDefaultErrorPage(fullPathToFile);
}

error::StatusOr<DefaultErrorPage>
CreateDefaultErrorPages::loadDefaultDefaultErrorPage(
    std::string fullPathToFile) const {

  std::ifstream pageDateStream(fullPathToFile.c_str());

  if (!pageDateStream.is_open()) {
    std::stringstream ssErrorMessage;
    ssErrorMessage << "Could not open the page error file: " << fullPathToFile
                   << ": " << _theErrno->getErrorMessage();
    return error::Status(error::Status::FileOpen, ssErrorMessage.str());
  }

  std::string allBytes = readAllTheStream(pageDateStream);

  DefaultErrorPage defaultPageError(allBytes);

  return defaultPageError;
}

DefaultErrorPage loadDefaultDefaultErrorPage(HTTPStatus codeStatus) {
  (void)codeStatus;
  return DefaultErrorPage();
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

std::string CreateDefaultErrorPages::readAllTheStream(
    std::istream &inputStream) const {
  std::stringstream buffer;
  buffer << inputStream.rdbuf();

  return buffer.str();
}