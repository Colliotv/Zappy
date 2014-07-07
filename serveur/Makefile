NAME	= zappy_serveur

CC	= gcc
RM	= rm -f

SRC	=
INC	= -I ./includes
###############
#### SOCKRD ####
SOCKRD	= src/getline/getline.c

#### ARGUES ####
ARGUES	= src/args/parse.c

#### ERRROR ####
ERROR	= src/err/lerror.c

#### BUFFER ####
BUFFER	= src/circularBuffer/factory.c

#### IA CMD ####
CMDS	= src/cmds/movement.c src/cmds/voir.c src/cmds/ressource.c src/cmds/take.c src/cmds/expulse.c src/cmds/broadcast.c

#### SERVER ####
SERVER	= src/serveur/factory.c src/serveur/destroy.c src/serveur/actualize.c src/serveur/unaff.c src/serveur/client.c src/serveur/waiting.c src/serveur/manageTeam.c src/serveur/iaManagement.c src/serveur/monitor.c src/serveur/iaBuffering.c src/serveur/treating.c

####  MAIN  ####
MAIN	= src/main/main.c
###############
SRC = $(ARGUES) $(SOCKRD) $(ERROR) $(BUFFER) $(CMDS) $(SERVER) $(MAIN)

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
