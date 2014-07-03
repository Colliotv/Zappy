#include <string.h>
#include <stdlib.h>

#include "lerror.h"
#include "serveur.h"
#include "get_line.h"

static bool	treat_node(serveur* this,
			   clients* node, char* msg, clients* prev)
{
  clients* next;

  next = node->next;
  if (!strcmp(msg, "GRAPHIC\n"))
    {
      node->next = this->monitor;
      this->monitor = node;
      free(msg);
    }
  else
    {
      if ((node = realloc(node, sizeof(wclients))) == NULL)
	lerror(MEMORY_ERROR(sizeof(wclients)));
      ((wclients*)node) ->team = msg;
      node->next = (clients*)(this->waiting);
      this->waiting = (wclients*)node;
      ((wclients*)node) ->info = false;
    }
  if (!prev)
    this->unaffecteds = next;
  else
    prev->next = next;
  return (true);
}

static void	_change(serveur* this,
			clients* prev, clients* _node,
			fd_set *rd) {
  clients*	node;
  clients*	next;

  if (!_node)
    return ;
  next = _node->next;
  node = _node;
  if (FD_ISSET(_node->client, rd) && treat_node(this, _node, _get_socket(_node->client), prev))
    node = (prev) ? (prev) : (NULL);
  _change(this, node, next, rd);
}

static	void	welcome(clients* node, fd_set* wr) {
  if (!node)
    return ;
  if (FD_ISSET(node->client, wr) && node->welcome == false) {
    write(node->client, "BIENVENUE\n", sizeof(char) * strlen("BIENVENUE\n"));
    node->welcome = true;
  }
  welcome(node->next, wr);
}

void	actualize_unaff(serveur* this, fd_set* rd, fd_set* wr) {
  welcome(this->unaffecteds, wr);
  _change(this, NULL, this->unaffecteds, rd);
}

