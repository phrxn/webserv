#ifndef START_CREATE_DEFAULT_ERRO_PAGES_FACTORY_HPP
#define START_CREATE_DEFAULT_ERRO_PAGES_FACTORY_HPP

#include <map>

#include "../error/Log.hpp"
#include "../net/http/DefaultErrorPage.hpp"
#include "../net/http/HTTPStatus.hpp"

class CreateDefaultErrorPagesFactory {
 public:
  static void fillTheFactory(
      const std::map<HTTPStatus::Status, DefaultErrorPage>
          &mapWithDefaultPagesErrors);

  CreateDefaultErrorPagesFactory();
  ~CreateDefaultErrorPagesFactory();
  CreateDefaultErrorPagesFactory(const CreateDefaultErrorPagesFactory &src);
  CreateDefaultErrorPagesFactory &operator=(
      const CreateDefaultErrorPagesFactory &src);

  DefaultErrorPage getDefaultErrorPages(HTTPStatus::Status codeStatus);

  void setLogger(Log *logger);

 private:
  static std::map<HTTPStatus::Status, DefaultErrorPage>
      mapWithDefaultPagesErrors;
  Log *_logger;
};

#endif