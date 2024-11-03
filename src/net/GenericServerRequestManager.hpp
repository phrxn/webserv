#ifndef NET_GENERIC_SERVER_REQUEST_MANAGER_HPP
#define NET_GENERIC_SERVER_REQUEST_MANAGER_HPP

#include <ctime>

#include "../error/Log.hpp"
#include "../io/Poll.hpp"
#include "ProtocolManager.hpp"
#include "ProtocolManagerFactory.hpp"
#include "SocketFileDescriptorImpl.hpp"

class GenericServerRequestManager {
 public:
  /*
    enum Stage { HANDLER_REQUEST_PROCESSING, HANDLER_REQUEST_FINISHED, FINISHED
    }; enum ProtocolStage { REQUEST, PROCESS_SERVLET, TIME_OUT, RESPONSE,
      WRITING_RESPONSE
    };
  */

  enum Stage {
    REQUEST_CREATING,
    PROCESS_SERVLET,
    TIME_OUT,
    RESPONSE,
    WRITING_RESPONSE,
    RESET_TO_NEW_REQUESTS,
    DESTROY
  };

  GenericServerRequestManager(Poll *_poll,
                              SocketFileDescriptorImpl *_socketFileDescriptor,
                              Log *logger);
  ~GenericServerRequestManager();

  bool readInputFromSocket();

  Stage createRequest();

  void doServlet();

  void doTimeout();

  void doResponse();

  Stage doWritingResponse();

  Stage handler();

  void resetForANewRequest();

  void checkTimeOut();

  void setProtocolManager(ProtocolManager *protocolManager);

 private:
  GenericServerRequestManager(const GenericServerRequestManager &src);
  GenericServerRequestManager &operator=(
      const GenericServerRequestManager &src);

  Poll *_poll;
  SocketFileDescriptorImpl *_socketFileDescriptor;
  Log *_logger;
  Stage _managerStage;
  ProtocolManager *_protocolManager;
  std::time_t _timeOfLastInputFromCLient;
};

#endif