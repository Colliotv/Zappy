#include <time.h>
#include <stdlib.h>
#include <string.h>

#include "lerror.h"
#include "serveur.h"

static iaClients*	addIaClient(struct args* arg, int n, iaClients* prev){
  iaClients	*node;

  if (!n)
    return (NULL);
  if ((node = malloc(sizeof(iaClients))) == NULL)
    lerror(MEMORY_ERROR(sizeof(iaClients)));
  node->next = NULL;
  if (prev)
    prev->next = node;

  node->iaClient = FD_NOSET;
  node->pause = READY;
  node->rdBuffer = createBuffer();
  node->wrBuffer = createBuffer();

  bzero(node->stash, sizeof(node->stash));
  node->_life.time = uLife;
  node->_life.amount = 10;
  node->_o = random() % maxOrientation;
  node->_p.x = random() % arg->X;
  node->_p.y = random() % arg->Y;
  addIaClient(arg, n-1, node);
  return (node);
}

static teams*	addTeam(struct nameNode* teamName, struct args* arg,
			teams *prev){
  teams	*node;

  if (!teamName)
    return (NULL);
  if ((node = malloc(sizeof(teams))) == NULL)
    lerror(MEMORY_ERROR(sizeof(teams)));
  node->next = NULL;
  if (prev)
    prev->next = node;
  node->list = addIaClient(arg, arg->nByTeams, NULL);
  addTeam(teamName->next, arg, node);
  free(teamName);
  return (node);
}

static void	fillMap(serveur* this, int pond) {
  int	i;

  i = 0;
  while (i < this->size.y * this->size.x * ressourceLength) {
    (this->ressources)[i++] = !(random() % pond);
  }
}

static void	enableNetworking(serveur* this, _port port) {
  struct  sockaddr_in	sock_in;
  _fd			_socket;

  if ((_socket = socket(AF_INET, SOCK_STREAM, 0)) == -1)
    lerror(FUNCTION_ERROR("socket()"));
  bzero(&(sock_in), sizeof(sock_in));
  sock_in.sin_addr.s_addr = htonl(INADDR_ANY);
  sock_in.sin_family = AF_INET;
  sock_in.sin_port = htons(port);
  if (bind(_socket, ((struct sockaddr*)(&sock_in)), sizeof(sock_in))
     == -1)
    lerror(FUNCTION_ERROR("bind()"));
  if (listen(_socket, 10) == -1)
    lerror(FUNCTION_ERROR("listen()"));
  this->serv = _socket;
}


serveur* factory(struct args* args){
  serveur* this;

  if ((this = malloc(sizeof(serveur))) == NULL)
    lerror(MEMORY_ERROR(sizeof(serveur)));
  enableNetworking(this, args->port);
  srandom(time(NULL));
  this->unaffecteds = NULL;

  this->monitor = NULL;

  this->waiting = NULL;
  this->teams = addTeam(args->names, args, NULL);

  this->size.x = args->X;
  this->size.y = args->Y;

  if ((this->ressources =
       malloc(sizeof(*(this->ressources)) *
	      (args->X * args->Y * ressourceLength))) == NULL)
    lerror(MEMORY_ERROR(sizeof(*(this->ressources))));
  fillMap(this, BASE_POND);
  return (this);
}
