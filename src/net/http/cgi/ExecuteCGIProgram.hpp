#ifndef NET_HTTP_CGI_EXECUTE_CGI_PROGRAM_HPP
#define NET_HTTP_CGI_EXECUTE_CGI_PROGRAM_HPP

#include <string>

#include "../../../system/SystemCalls.hpp"
#include "../HTTPRequest.hpp"
#include "CGIBinary.hpp"
#include "CGIBinaryFactory.hpp"
#include "ChildProcessCGI.hpp"
#include "FilesToCGI.hpp"
#include "ProcessCGI.hpp"

class ExecuteCGIProgram {
 public:
  ExecuteCGIProgram();
  ~ExecuteCGIProgram();
  ExecuteCGIProgram(const ExecuteCGIProgram &src);
  ExecuteCGIProgram &operator=(const ExecuteCGIProgram &src);

  ProcessCGI::ExitStatus execute(const std::string &virtualHostRootPath,
                                 const std::string &physicalPathToResource,
                                 const HTTPRequest &request,
                                 FilesToCGI &FilesToCGI);

  virtual bool cgiBinaryValid(const CGIBinary &cgiBinary) const;

 private:
  SystemCalls *_systemCalls;
  Log *_logger;
};

#endif