NAME	= zappy_serveur

CC	= gcc
RM	= rm -f

SRC	=
INC	= -I ./includes

###############

###############
SRC = 

FLAGS	= -W -Wall -Wextra $(INC)
CFLAGS	= $(FLAGS)
LDFLAGS	=

OBJ		= $(SRC:.cpp=.o)

all: $(NAME)

$(NAME): $(OBJ)
	$(CC) -o $(NAME) $(OBJ) $(LDFLAGS)

clean:
	$(RM) $(OBJ)

fclean: clean
	$(RM) $(NAME)

re: fclean all
