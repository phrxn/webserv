#ifndef NET_HTTP_CGI_PROCESS_CGI_HPP
#define NET_HTTP_CGI_PROCESS_CGI_HPP

class ProcessCGI {
 public:
  enum ExitStatus {CHILD_EXIT_OK = 0, CHILD_EXIT_WITH_ERROR = 1, CHILD_FINISHED_BY_SIGNAL = 2, PARENT_ERROR = 3};

  virtual ~ProcessCGI();
  virtual ExitStatus execute() = 0;
};

#endif