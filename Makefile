NAME = webserv

CXX = c++

CXXFLAGS = -Wall -Werror -Wextra

PROGRAM_CPP_VERSION = -std=c++98
PROGRAM_OBJDIR = output/binary/objects/

TESTS_CPP_VERSION = -std=c++17
TESTS_OBJDIR = output/tests/objects/
TESTS_BINARY = $(ARG_TESTS_BINARY)

GTEST_LIBS = $(ARG_GTEST_LIBS)

GTEST_INCLUDES = libs/googletest/googletest/include/
GMOCK_INCLUDES = libs/googletest/googlemock/include/


ifeq ($(COMPILE), binary)
  OUTPUT_OBJECTS_DIR = $(PROGRAM_OBJDIR)
else ifeq ($(COMPILE), tests)
  OUTPUT_OBJECTS_DIR = $(TESTS_OBJDIR)
endif

SRC =	src/config/ProgramConfiguration.cpp\
		src/error/Log.cpp\
		src/error/LogDefault.cpp\
		src/error/LogWriter.cpp\
		src/error/LogWriteToConsole.cpp\
		src/error/Status.cpp\
		src/file_configuration/Config.cpp\
		src/file_configuration/ConfigExtract.cpp\
		src/file_configuration/ConfigUtils.cpp\
		src/file_configuration/RouteConfig.cpp\
		src/file_configuration/ServerConfig.cpp\
		src/io/DirectoryListing.cpp\
		src/io/Epoll.cpp\
		src/io/File.cpp\
		src/io/FileDescriptor.cpp\
		src/io/Poll.cpp\
		src/net/http/cgi/ArrayChar.cpp\
		src/net/http/cgi/CGIBinary.cpp\
		src/net/http/cgi/CGIBinaryFactory.cpp\
		src/net/http/cgi/CGICreateEnvironmentVariables.cpp\
		src/net/http/cgi/CGIEnvironmentVariables.cpp\
		src/net/http/cgi/ChildProcessCGI.cpp\
		src/net/http/cgi/EnvironmentVariables.cpp\
		src/net/http/cgi/ExecuteCGIProgram.cpp\
		src/net/http/cgi/FilesToCGI.cpp\
		src/net/http/cgi/ParentProcessCGI.cpp\
		src/net/http/cgi/ProcessCGI.cpp\
		src/net/http/html/CreateCGIHTMLDocument.cpp\
		src/net/http/html/CGIHTMLDocument.cpp\
		src/net/http/html/CreateDirectoryHTMLPage.cpp\
		src/net/http/html/DirectoryHTMLDocument.cpp\
		src/net/http/html/ErrorPageFileHTMLDocument.cpp\
		src/net/http/html/FileHTMLDocument.cpp\
		src/net/http/html/FillHTTPResponse.cpp\
		src/net/http/html/HTMLDocument.cpp\
		src/net/http/html/ItemDirectoryHTMLDocument.cpp\
		src/net/http/CGIPagesPhysicalPathChecker.cpp\
		src/net/http/GetMimeType.cpp\
		src/net/http/HandlerHTTPStatus.cpp\
		src/net/http/HTTPMethods.cpp\
		src/net/http/HTTPRequest.cpp\
		src/net/http/HTTPRequestFake.cpp\
		src/net/http/HTTPRequestTool.cpp\
		src/net/http/HTTPResponse.cpp\
		src/net/http/HTTPResponseFake.cpp\
		src/net/http/HTTPServlet.cpp\
		src/net/http/HTTPServletCGI.cpp\
		src/net/http/HTTPServletManager.cpp\
		src/net/http/HTTPServletStatic.cpp\
		src/net/http/HTTPStatus.cpp\
		src/net/http/HTTPTypeOfPages.cpp\
		src/net/http/PhysicalPathChecker.cpp\
		src/net/http/ProtocolManagerHTTP.cpp\
		src/net/http/ProtocolManagerHTTPFake.cpp\
		src/net/http/StaticPagesPhysicalPathChecker.cpp\
		src/net/FileDescriptorVisitor.cpp\
		src/net/ClusterOfVirtualHost.cpp\
		src/net/GenericServer.cpp\
		src/net/GenericServerRequestManager.cpp\
		src/net/ProtocolManager.cpp\
		src/net/ProtocolManagerEnter.cpp\
		src/net/ProtocolManagerFactory.cpp\
		src/net/Request.cpp\
		src/net/Response.cpp\
		src/net/ServerSocketFileDescriptor.cpp\
		src/net/SocketFileDescriptor.cpp\
		src/net/SocketFileDescriptorImpl.cpp\
		src/net/URL.cpp\
		src/net/VirtualHost.cpp\
		src/net/VirtualHostDefault.cpp\
		src/net/VirtualHostFactory.cpp\
		src/start/CreateDefaultErrorPages.cpp\
		src/start/CreateDefaultErrorPagesFactory.cpp\
		src/start/CreateMimeTypeMap.cpp\
		src/start/LoaderOfProgramFiles.cpp\
		src/system/Errno.cpp\
		src/system/SystemCalls.cpp\
		src/time/Time.cpp\
		src/Start.cpp\
		src/Webserv.cpp

SOURCES_TEST =  src/config/ProgramConfigurationTest.cpp\
                src/error/LogWriterTest.cpp\
				src/file_configuration/ConfigTest.cpp\
				src/io/DirectoryListingTest.cpp\
				src/io/EpollTest.cpp\
				src/io/FileTest.cpp\
				src/net/http/cgi/ArrayCharTest.cpp\
				src/net/http/cgi/CGICreateEnvironmentVariablesTest.cpp\
				src/net/http/cgi/CGIEnvironmentVariablesTest.cpp\
				src/net/http/cgi/ChildProcessCGITest.cpp\
				src/net/http/cgi/EnvironmentVariablesTest.cpp\
				src/net/http/cgi/FilesToCGITest.cpp\
				src/net/http/cgi/ParentProcessCGITest.cpp\
				src/net/http/html/CreateCGIHTMLDocumentTest.cpp\
				src/net/http/html/CreateDirectoryHTMLPageTest.cpp\
				src/net/http/html/DirectoryHTMLDocumentTest.cpp\
				src/net/http/html/ItemDirectoryHTMLDocumentTest.cpp\
				src/net/http/GetMimeTypeTest.cpp\
				src/net/http/HTTPMethodsTest.cpp\
				src/net/http/HTTPRequestFakeTest.cpp\
				src/net/http/HTTPRequestToolTest.cpp\
				src/net/http/HTTPResponseTest.cpp\
				src/net/http/HTTPStatusTest.cpp\
				src/net/http/HTTPTypeOfPagesTest.cpp\
				src/net/http/StaticPagesPhysicalPathCheckerTest.cpp\
				src/net/ClusterOfVirtualHostTest.cpp\
				src/net/GenericServerTest.cpp\
				src/net/ServerSocketFileDescriptorTest.cpp\
				src/net/SocketFileDescriptorImplTest.cpp\
				src/net/URLTest.cpp\
				src/net/VirtualHostFactoryTest.cpp\
				src/net/VirtualHostDefaultTest.cpp\
				src/start/CreateDefaultErrorPagesFactoryTest.cpp\
				src/start/CreateDefaultErrorPagesTest.cpp\
				src/start/CreateMimeTypeMapTest.cpp\
				src/time/TimeTest.cpp

ifeq ($(COMPILE), binary)
  SRC += src/Main.cpp
else ifeq ($(COMPILE), tests)
  SRC += tests/Main.cpp
  SRC += $(SOURCES_TEST)
endif

OBJ = $(SRC:%.cpp=$(OUTPUT_OBJECTS_DIR)%.o)
DEPENDS = $(SRC:%.cpp=$(OUTPUT_OBJECTS_DIR)%.d)

ifeq ($(COMPILE), binary)

  all: $(NAME)

  $(NAME): $(OBJ)
	$(CXX) $(OBJ) -o $(NAME)

  $(PROGRAM_OBJDIR)%.o: %.cpp
	@mkdir -p $(dir $@)
	$(CXX) $(CXXFLAGS) $(PROGRAM_CPP_VERSION) -MMD -c $< -o $@

else ifeq ($(COMPILE), tests)

  all: $(TESTS_BINARY)

  $(TESTS_BINARY): $(GTEST_LIBS) $(OBJ)
	$(CXX) $(OBJ) -o $(TESTS_BINARY) $(GTEST_LIBS) -lpthread -lrt

  $(TESTS_OBJDIR)%.o: %.cpp
	@mkdir -p $(dir $@)
	$(CXX) -I$(GTEST_INCLUDES) -I$(GMOCK_INCLUDES) $(CXXFLAGS) $(TESTS_CPP_VERSION) -MMD -DCOMPILE_TEST=COMPILE_TEST -c $< -o $@

endif









clean:
	rm -rf output

fclean: clean
	rm -rf $(NAME)

re: clean all

-include $(DEPENDS)