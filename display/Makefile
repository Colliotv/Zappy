
NAME   		= 	zappy

SRCS    	= 	./sources/menu/main.cpp \
				./sources/menu/Menu.cpp \
				./md2_test/Src/GLFWBase.cpp \
				./md2_test/Src/MD2Loader.cpp \
				./md2_test/Src/Render.cpp \
				./md2_test/Src/tga.cpp \
				./md2_test/Src/Obj.cpp \


OBJS    	= 	$(SRCS:.cpp=.o)

CC      	= 	g++

RM      	= 	rm -f

CXXFLAGS  	+=	-Wextra -Wall -I./includes --std=c++11 -g3

LIBSFLAGS	+=	-I./sfml/branches/sfml2
LIBSFLAGS	+=	-L./sfml/trunk/lib -lsfml-graphics -lsfml-window -lsfml-system -lsfml-audio
LIBSFLAGS	+=	-lGL -lGLU  -lglfw
LIBSFLAGS	+=	-L./GLEW/libGLEW.so.1.9.0

all: 		$(NAME)

$(NAME): 	$(OBJS)
			$(CC) -o $(NAME) $(OBJS) $(CXXFLAGS) $(LIBSFLAGS)

clean:
			$(RM) $(OBJS)

fclean: 	clean
			$(RM) $(NAME)


re: 		fclean all

.PHONY: 	all clean fclean re