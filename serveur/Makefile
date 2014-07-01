NAME	= zappy_serveur

CC	= gcc
RM	= rm -f

SRC	=
INC	= -I ./includes
###############
#### ARGUES ####
ARGUES	= src/args/parse.c
#### ERRROR ####
ERROR	= src/err/lerror.c
#### BUFFER ####
BUFFER	= src/circularBuffer/factory.c
#### SERVER ####
SERVER	= src/serveur/factory.c src/serveur/destroy.c src/serveur/actualize.c
####  MAIN  ####
MAIN	= src/main/main.c
###############
SRC = $(ARGUES) $(ERROR) $(BUFFER) $(SERVER) $(MAIN)

FLAGS	= -W -Wall -Wextra $(INC)              -g3
CFLAGS	= $(FLAGS)
LDFLAGS	=

OBJ		= $(SRC:.c=.o)

all: $(NAME)

$(NAME): $(OBJ)
	$(CC) -o $(NAME) $(OBJ) $(LDFLAGS)

clean:
	$(RM) $(OBJ)

fclean: clean
	$(RM) $(NAME)

re: fclean all
