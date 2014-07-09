
NAME   		= 	zappy

DIR		=	sources

DIR_CLIENT	=	client_dir

SRCS    	= 	./sources/menu_main.cpp \
				./sources/Menu.cpp \
				./sources/MD2Loader.cpp \
				./sources/Render.cpp \
				./sources/tga.cpp \
				./sources/connect_main.cpp	\
				./sources/tools.cpp \
				./sources/create_socket.cpp \
				./sources/Game.cpp \
				./sources/Interface.cpp



OBJS    	= 	$(SRCS:.cpp=.o)

CC      	= 	g++

RM      	= 	rm -f

CXXFLAGS  	+=	-Wunused-parameter -Wextra -Wall -I./includes --std=c++11 -g3 

LIBSFLAGS	+=	-I./sfml/branches/sfml2
LIBSFLAGS	+=	-L./sfml/trunk/lib -lsfml-graphics -lsfml-window -lsfml-system -lsfml-audio
LIBSFLAGS	+=	-lGL -lGLU  -lglfw
LIBSFLAGS	+=	-L./GLEW/libGLEW.so.1.9.0
LIBSFLAGS	+=	-L./includes/

all: 		$(NAME)

$(NAME): 	$(OBJS)
			$(CC) -o $(NAME) $(OBJS) $(CXXFLAGS) $(LIBSFLAGS)

clean:
			$(RM) $(OBJS)

fclean: 	clean
			$(RM) $(NAME)


re: 		fclean all

.PHONY: 	all clean fclean re