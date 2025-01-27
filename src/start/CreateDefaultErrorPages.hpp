#ifndef START_CREATE_DEFAULT_ERRO_PAGES_HPP
#define START_CREATE_DEFAULT_ERRO_PAGES_HPP

#include <map>
#include <string>

#include "../error/StatusOr.hpp"
#include "../net/http/DefaultErrorPage.hpp"
#include "../net/http/HTTPStatus.hpp"
#include "../system/Errno.hpp"

class CreateDefaultErrorPages {
 public:
  const static std::string DEFAULT_PATH_TO_FOLDER_WITH_ERROR_PAGES;
  CreateDefaultErrorPages();
  ~CreateDefaultErrorPages();
  CreateDefaultErrorPages(const CreateDefaultErrorPages &src);
  CreateDefaultErrorPages &operator=(const CreateDefaultErrorPages &src);

  error::StatusOr<std::map<HTTPStatus::Status, DefaultErrorPage> >
  loadDefaultPageErrorsMap();
  error::StatusOr<DefaultErrorPage> loadDefaultDefaultErrorPage(
      HTTPStatus::Status codeStatus) const;

  error::StatusOr<DefaultErrorPage> loadDefaultDefaultErrorPage(
      std::string codeStatus) const;

  std::string createFullPathToErroPage(HTTPStatus::Status codeStatus) const;
  void setErrno(Errno *newErrno);

  std::string readAllTheStream(std::istream &inputStream) const;

 private:
  Errno *_theErrno;
};

#endif