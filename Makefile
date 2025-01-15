NAME = webserv

CC = cc
CXX = c++

FLAGS = -Wall -Werror -Wextra

CPP_VERSION = --std=c++98

TEST_BINARY = output/tests/test.out

BUILD_DIR = build/

GTEST_LIBS = build/lib/libgmock.a \
			 build/lib/libgtest.a

GTEST_INCLUDES = libs/googletest/googletest/include/
GMOCK_INCLUDES = libs/googletest/googlemock/include/

SOURCES = src/Main.cpp\
		  src/config/Configuration.cpp\
		  src/error/Log.cpp\
		  src/error/LogDefault.cpp\
		  src/error/Status.cpp\
		  src/io/Epoll.cpp\
		  src/io/FileDescriptor.cpp\
		  src/io/Poll.cpp\
		  src/error/LogWriter.cpp\
		  src/error/LogWriteToConsole.cpp\
		  src/net/http/HTTPMethods.cpp\
		  src/net/http/HTTPRequest.cpp\
		  src/net/http/HTTPRequestFake.cpp\
		  src/net/http/HTTPResponse.cpp\
		  src/net/http/HTTPResponseFake.cpp\
		  src/net/http/HTTPServlet.cpp\
		  src/net/http/HTTPServletCGI.cpp\
		  src/net/http/HTTPServletManager.cpp\
		  src/net/http/HTTPServletStatic.cpp\
		  src/net/http/HTTPStatus.cpp\
		  src/net/http/ProtocolManagerHTTP.cpp\
		  src/net/http/ProtocolManagerHTTPFake.cpp\
		  src/net/FileDescriptorVisitor.cpp\
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
		  src/net/VirtualHostFactory.cpp\
		  src/system/Errno.cpp\
		  src/system/SystemCalls.cpp\
		  src/time/Time.cpp\
		  src/Start.cpp\
		  src/Webserv.cpp

SOURCES_TEST =  tests/Main.cpp\
				src/config/ConfigurationTest.cpp\
                src/error/LogWriterTest.cpp\
				src/io/EpollTest.cpp\
				src/net/http/HTTPMethodsTest.cpp\
				src/net/http/HTTPRequestFakeTest.cpp\
				src/net/http/HTTPStatusTest.cpp\
				src/net/GenericServerTest.cpp\
				src/net/ServerSocketFileDescriptorTest.cpp\
				src/net/SocketFileDescriptorImplTest.cpp\
				src/net/URLTest.cpp\
				src/net/VirtualHostFactoryTest.cpp


OBJECTS = $(SOURCES:.cpp=.o)
DEPENDS = $(SOURCES:.cpp=.d)

OBJECTS_TEST = $(SOURCES_TEST:.cpp=.o)
DEPENDS_TEST = $(SOURCES_TEST:.cpp=.d)

all : $(NAME)
	$(MAKE) -C tests_cli/

$(NAME) : before_compile $(OBJECTS)
	$(CXX) $(OBJECTS) -o $@

clean:
	rm -rf src/Main.d src/Main.o
	rm -rf $(OBJECTS)
	rm -rf $(DEPENDS)
	rm -rf $(OBJECTS_TEST)
	rm -rf $(DEPENDS_TEST)
	$(MAKE) -C tests_cli/ clean

fclean: clean
	rm -rf $(NAME)
	$(MAKE) -C tests_cli/ fclean

%.o : %.cpp
	$(CXX) -I$(GTEST_INCLUDES) -I$(GMOCK_INCLUDES) $(CPP_VERSION) $(FLAGS) -D$(COMPILE_TEST) -MMD -c $< -o $@

$(GTEST_LIBS):
	mkdir -p $(BUILD_DIR)
	cd $(BUILD_DIR) && cmake ../libs/googletest/ -DCMAKE_C_COMPILER=$(CC) -DCMAKE_CXX_COMPILER=$(CXX)
	make -C $(BUILD_DIR)

before_compile: clean
	$(eval COMPILE_TEST := NOTHING_TEST)

before_compile_tests:
	$(eval COMPILE_TEST := COMPILE_TEST)
	$(eval CPP_VERSION := --std=c++14)


tests : before_compile_tests clean $(GTEST_LIBS) $(OBJECTS) $(OBJECTS_TEST)
	mkdir -p output/tests
	$(CXX) $(OBJECTS) $(OBJECTS_TEST) -o $(TEST_BINARY) $(GTEST_LIBS) -lpthread
	./$(TEST_BINARY)

-include $(DEPENDS)

run : all
	./$(NAME)

.PHONY : all clean fclean re before_compile_tests before_compile run

