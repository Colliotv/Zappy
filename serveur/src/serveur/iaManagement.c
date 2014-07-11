#define _GNU_SOURCE
#include <stdio.h>
#include "serveur.h"
#include "monitor.h"

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
  while (ia && ia->iaClient != -1 && (ia = ia->next) != NULL);
  if (!ia)
    return (push_in_waiting(this, node));
  ia->iaClient = node->_.client;
  ia->rdBuffer = node->_.rdBuffer;
  ia->state = (ia->state == unaffected) ? (alive) : (ia->state);
  team->unaff_size -= 1;
  asprintf(&sending, "%d\n%d %d\n", team->unaff_size,
	   this->size.x, this->size.y);
  pushNode(ia->wrBuffer, sending);
  if (ia->state == egg)
    avertMonitor(this, mConnectEgg(ia->num));
  avertMonitor(this, mNewPlayer(ia->num, ia->_p.x, ia->_p.y, ia->_o,
				ia->lvl, node->team));
  return (push_in_waiting(this, del_waiting(this, node, false)));
}

void	actualize_IA(serveur* this, fd_set* rd, fd_set* wr) {
  if (this->waiting)
    push_in_waiting(this, this->waiting);
  actualizeBuffering(this->teams, rd, wr);
  iaProcess(this, this->teams);
}
