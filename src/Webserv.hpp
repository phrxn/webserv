#ifndef WEBSERV_HPP
#define WEBSERV_HPP

#include "io/Poll.hpp"
#include "net/GenericServer.hpp"

class Webserv {
 public:
  static bool continueRunningTheServer;

  Webserv(Poll &poll, Log &log, ProgramConfiguration &configuration);
  ~Webserv();

  void start();

 private:
  Webserv(const Webserv &src);
  Webserv &operator=(const Webserv &src);

  Poll &_poll;
  Log &_log;
  ProgramConfiguration &_configuration;
  GenericServer _genericServer;

};

#endif