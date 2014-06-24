CC = g++

RM = rm -f

CFLAGS += -Wextra -Wall -Werror
CFLAGS += -ansi -pedantic
CFLAGS += -I.

LDFLAGS =

NAME = binaire_sfml

SRCS = main.cpp

JS = $(SRCS:.c=.o)

#all: $(NAME)

all:
		g++ -c main.cpp -I./sfml/branches/sfml2/
		g++ main.o -o $(NAME) -L./sfml/trunk/lib -lsfml-graphics -lsfml-window -lsfml-system

$(NAME): $(OBJS)
	$(CC) $(OBJS) -o $(NAME) $(LDFLAGS)

clean:
	$(RM) $(OBJS)

fclean: clean
	$(RM) $(NAME)

re: fclean all

.PHONY: all clean fclean re