
NAME   		= 	zappy

SRCS    	= 	./sources/main.cpp \

OBJS    	= 	$(SRCS:.cpp=.o)

CC      	= 	g++

RM      	= 	rm -f

CXXFLAGS  	+=	-Wextra -Wall -I./includes

LIBSFLAGS	+=	-I./sfml/branches/sfml2
LIBSFLAGS	+=	-L./sfml/trunk/lib -lsfml-graphics -lsfml-window -lsfml-system

all: 		$(NAME)

$(NAME): 	$(OBJS)
			$(CC) -o $(NAME) $(OBJS) $(CXXFLAGS) $(LIBSFLAGS)

clean:
			$(RM) $(OBJS)


fclean: 	clean
			$(RM) $(NAME)


re: 		fclean all

.PHONY: 	all clean fclean re