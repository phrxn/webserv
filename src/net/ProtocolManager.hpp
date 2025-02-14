#ifndef NET_PROTOCOL_MANAGER_HPP
#define NET_PROTOCOL_MANAGER_HPP


//interface ProtocolManager
class ProtocolManager {
 public:
  enum RequestCreationStatus { REQUEST_CREATED, REQUEST_CREATING };

  virtual ~ProtocolManager();
  virtual RequestCreationStatus createRequest() = 0;
  virtual void servlet() = 0;
  virtual void createResponse() = 0;
  virtual void connectionHitTheTimeout() = 0;
};

#endif