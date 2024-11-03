NAME = cli

FLAGS = -Wall -Werror -Wextra

CXX = c++

SOURCES_FILES =  Menu.cpp\
				 ClientConnector.cpp\
				 SimpleConnection.cpp\
				 SocketClient.cpp\
			     ThreadReceiveMessage.cpp

OBJECTS_FILES = $(SOURCES_FILES:.cpp=.o)
DEPENDS_FILES = $(SOURCES_FILES:.cpp=.d)


all : $(NAME)

$(NAME) :$(OBJECTS_FILES)
	$(CXX) $(OBJECTS_FILES) -o $@ -lpthread

%.o : %.cpp
	$(CXX) $(FLAGS) -MMD -c $< -o $@


clean :
	$(RM) $(OBJECTS_FILES)
	$(RM) $(DEPENDS_FILES)

fclean : clean
	$(RM) $(NAME)

re : fclean all

-include $(DEPENDS)

.PHONY : all clean fclean re bonus
