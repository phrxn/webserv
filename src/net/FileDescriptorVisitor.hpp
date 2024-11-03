#ifndef NET_FILE_DESCRIPTOR_VISITOR_HPP
#define NET_FILE_DESCRIPTOR_VISITOR_HPP

class ServerSocketFileDescriptor;
class SocketFileDescriptorImpl;

class FileDescriptorVisitor {
 public:
  virtual ~FileDescriptorVisitor();

  virtual void doForServerSocketFileDescriptor(
      ServerSocketFileDescriptor *) = 0;

  virtual void doForSocketFileDescriptorImp(SocketFileDescriptorImpl *) = 0;
};

#endif