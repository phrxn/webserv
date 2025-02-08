#ifndef NET_HTTP_HTTP_REQUEST_HPP
#define NET_HTTP_HTTP_REQUEST_HPP

#include <map>
#include <string>

#include "../../error/Log.hpp"
#include "../Request.hpp"
#include "../SocketFileDescriptor.hpp"
#include "../URL.hpp"
#include "HTTPMethods.hpp"
#include "HTTPStatus.hpp"
#include "HTTPRequestTool.hpp"

class HTTPRequest : public Request {
 private:
  HTTPRequest(const HTTPRequest &src);
  HTTPRequest &operator=(const HTTPRequest &src);
  HTTPRequest();
  
  StateOfCreation headerRequest();

  SocketFileDescriptor *_socketFD;
  std::string _buffer;
  HTTPStatus::Status _status;
  HTTPRequestTool _HTTPTool;
  Log *_logger;

 public:
  HTTPRequest(SocketFileDescriptor *socketFD, Log *logger);
  ~HTTPRequest();

  StateOfCreation createRequest();

  std::string getHost();

  virtual HTTPMethods::Method getMethod();

  virtual std::string getURL();

  virtual HTTPStatus::Status getStatus();

  int getPort();

  std::string isToKeepTheConnection();
};

#endif

//IMPLEMENTAR VALIDADEÇÃO PROGRAM CONFIG. METODO É SUPORTADO? SE O REQUEST PASSOU O TAMANHO PERMITIDO?? VALIDAR DURANTE A LEITURA DO BODY!