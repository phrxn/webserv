#ifndef START_CREATE_DEFAULT_ERRO_PAGES_FACTORY_HPP
#define START_CREATE_DEFAULT_ERRO_PAGES_FACTORY_HPP

#include <map>

#include "../error/Log.hpp"
#include "../net/http/html/ErrorPageFileHTMLDocument.hpp"
#include "../net/http/HTTPStatus.hpp"

class CreateDefaultErrorPagesFactory {
 public:
  static void fillTheFactory(
      const std::map<HTTPStatus::Status, ErrorPageFileHTMLDocument*>
          &mapWithDefaultPagesErrors);
  static void destroyFactory();

  CreateDefaultErrorPagesFactory();
  ~CreateDefaultErrorPagesFactory();
  CreateDefaultErrorPagesFactory(const CreateDefaultErrorPagesFactory &src);
  CreateDefaultErrorPagesFactory &operator=(
      const CreateDefaultErrorPagesFactory &src);

  ErrorPageFileHTMLDocument* getDefaultErrorPages(HTTPStatus::Status codeStatus);

  void setLogger(Log *logger);

 private:
  static std::map<HTTPStatus::Status, ErrorPageFileHTMLDocument*>
      mapWithDefaultPagesErrors;
  Log *_logger;
};

#endif