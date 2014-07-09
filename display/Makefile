
NAME   		= 	zappy

DIR		=	sources

DIR_CLIENT	=	client_dir

SRCS    	= 	./sources/menu/main.cpp \
				./sources/menu/Menu.cpp \
				./md2_test/Src/MD2Loader.cpp \
				./md2_test/Src/Render.cpp \
				./md2_test/Src/tga.cpp \
				./$(DIR)/$(DIR_CLIENT)/main.cpp	\
				./$(DIR)/$(DIR_CLIENT)/tools.cpp \
				./$(DIR)/$(DIR_CLIENT)/create_socket.cpp \
				./$(DIR)/$(DIR_CLIENT)/Game.cpp \
				./$(DIR)/$(DIR_CLIENT)/cmd.cpp


OBJS    	= 	$(SRCS:.cpp=.o)

CC      	= 	g++ 

RM      	= 	rm -f

CXXFLAGS  	+=	-Wunused-parameter -Wextra -Wall -I./includes --std=c++11 -g3 

LIBSFLAGS	+=	-I./sfml/branches/sfml2
LIBSFLAGS	+=	-L./sfml/trunk/lib -lsfml-graphics -lsfml-window -lsfml-system -lsfml-audio
LIBSFLAGS	+=	-lGL -lGLU  -lglfw
LIBSFLAGS	+=	-L./GLEW/libGLEW.so.1.9.0
LIBSFLAGS	+=	-L./includes

all: 		$(NAME)

$(NAME): 	$(OBJS)
			$(CC) -o $(NAME) $(OBJS) $(CXXFLAGS) $(LIBSFLAGS)

clean:
			$(RM) $(OBJS)

fclean: 	clean
			$(RM) $(NAME)


re: 		fclean all

.PHONY: 	all clean fclean re