NAME = webserv

CC = cc
CXX = c++

FLAGS = -Wall -Werror -Wextra

CPP_VERSION = --std=c++98

BUILD_DIR = build/

GTEST_LIBS = build/lib/libgmock.a \
			 build/lib/libgtest.a

GTEST_INCLUDES = libs/googletest/googletest/include/
GMOCK_INCLUDES = libs/googletest/googlemock/include/


SOURCES = $(VAR)

SOURCES_TEST = tests/Main.cpp


OBJECTS = $(SOURCES:.cpp=.o)
DEPENDS = $(SOURCES:.cpp=.d)

OBJECTS_TEST = $(SOURCES_TEST:.cpp=.o)
DEPENDS_TEST = $(SOURCES_TEST:.cpp=.d)

all : $(NAME)

$(NAME) : before_compile $(OBJECTS)
	$(CXX) $(OBJECTS) -o $@

clean:
	rm -rf $(OBJECTS)
	rm -rf $(DEPENDS)
	rm -rf $(OBJECTS_TEST)
	rm -rf $(DEPENDS_TEST)

fclean: clean
	rm -rf $(NAME)

%.o : %.cpp
	$(CXX) -I$(GTEST_INCLUDES) -I$(GMOCK_INCLUDES) $(CPP_VERSION) $(FLAGS) -MMD -c $< -o $@

$(GTEST_LIBS):
	mkdir -p $(BUILD_DIR)
	cd $(BUILD_DIR) && cmake ../libs/googletest/ -DCMAKE_C_COMPILER=$(CC) -DCMAKE_CXX_COMPILER=$(CXX)
	make -C $(BUILD_DIR)

before_compile: clean

before_compile_tests:
	$(eval CPP_VERSION := --std=c++14)


tests : before_compile_tests clean $(GTEST_LIBS) $(OBJECTS) $(OBJECTS_TEST)
	mkdir -p output/tests
	$(CXX) $(OBJECTS) $(OBJECTS_TEST) -o output/tests/test.out $(GTEST_LIBS) -lpthread

-include $(DEPENDS)

.PHONY : all clean fclean re before_compile_tests before_compile

