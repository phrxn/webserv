#ifndef NET_HTTP_CGI_FILES_TO_CGI
#define NET_HTTP_CGI_FILES_TO_CGI

#include <fstream>
#include <string>

#include "../../../error/Log.hpp"
#include "../../../error/LogDefault.hpp"
#include "../../../system/SystemCalls.hpp"
#include "../HTTPRequest.hpp"

class FilesToCGI {
 public:
  static const std::string inputFileName;
  static const std::string outputFileName;
  static const std::string stderrFileName;

  FilesToCGI();
  FilesToCGI(Log *logger);
  ~FilesToCGI();

  bool createFileDescriptors(HTTPRequest &request);

  bool prepareFileDescriptorsToChildProcess(int fdIn, int fdOut, int fdErr);

  int openAFile(const std::string fileName);

  bool deleteFiles();

  bool closeAFile(int fileDescriptor);

  void setSystemCalls(SystemCalls *_systemCalls);

  int getInputFileDescriptor();
  int getOutputFileDescriptor();
  int getStderrFileDescriptor();

  void setInputFileDescriptor(int inputFileDescriptor);
  void setOutputFileDescriptor(int outputFileDescriptor);
  void setStderrFileDescriptor(int stderrFileDescriptor);

  void setDefaultDirectoryToSaveTheFiles(const std::string &newDirectory);
  std::string getDefaultDirectoryToSaveTheFiles();

  std::ifstream &getOutputFile();
  std::ifstream &getStderrFile();

 private:
  static std::string defaultDirectoryToSaveTheFiles;

  FilesToCGI(const FilesToCGI &src);
  FilesToCGI &operator=(const FilesToCGI &src);

  Log *_logger;
  SystemCalls *_systemCalls;

  int _inputFileDescriptor;
  int _outputFileDescriptor;
  int _stderrFileDescriptor;

  std::ifstream _outputFile;
  std::ifstream _srtErrFile;

};

#endif