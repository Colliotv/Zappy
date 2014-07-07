#define _GNU_SOURCE
#include <stdio.h>
#include "serveur.h"

static int	push_in_waiting(serveur* this, wclients* node) {
  teams*	team;
  iaClients*	ia;
  char*		sending;

  if (!node)
    return (0);
  team = getTeamById(this, node->team);
  if (!team->unaff_size)
    return (push_in_waiting(this, (wclients*)node->_.next));
  ia = team->list;
  while (ia && ia->iaClient != -1)
    ia = ia->next;
  if (!ia)
    return (push_in_waiting(this, node));
  ia->iaClient = node->_.client;
  ia->rdBuffer = node->_.rdBuffer;
  team->unaff_size -= 1;
  asprintf(&sending, "%d\n", team->unaff_size);
  pushNode(ia->wrBuffer, sending);
  asprintf(&sending, "%d %d\n", this->size.x, this->size.y);
  pushNode(ia->wrBuffer, sending);
  return (push_in_waiting(this, del_waiting(this, node)));
}

void	actualize_IA(serveur* this, fd_set* rd, fd_set* wr) {
  if (this->waiting)
    push_in_waiting(this, this->waiting);
  actualizeBuffering(this->teams, rd, wr);
}
