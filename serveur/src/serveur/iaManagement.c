#define _GNU_SOURCE
#include <stdio.h>
#include "serveur.h"
#include "monitor.h"

static void	sendingIAData(serveur *this, iaClients* ia, teams* team) {
  char*		sending;
  asprintf(&sending, "%d\n", team->unaff_size);
  pushNode(ia->wrBuffer, sending);
  asprintf(&sending, "%d %d\n", this->size.x, this->size.y);
  pushNode(ia->wrBuffer, sending);
}

static void	push_in_waiting(serveur* this, wclients* node) {
  teams*	team;
  iaClients*	ia;

  while (node)
    {
      team = getTeamById(this, node->team);
      ia = team->list;
      while (ia && ia->iaClient != -1 && (ia = ia->next) != NULL);
      if (!ia)
	node = (wclients*)node->_.next;
      else
	{
	  ia->iaClient = node->_.client;
	  ia->rdBuffer = node->_.rdBuffer;
	  ia->state = (ia->state == unaffected) ? (alive) : (ia->state);
	  team->unaff_size -= 1;
	  sendingIAData(this, ia, team);
	  if (ia->state == egg)
	    avertMonitor(this, mConnectEgg(ia->num));
	  avertMonitor(this, mNewPlayer(ia->num, ia->_p.x, ia->_p.y, ia->_o,
					ia->lvl, node->team));
	  node = del_waiting(this, node, false);
	}
    }
}

void	actualize_IA(serveur* this, fd_set* rd, fd_set* wr, bool buffered) {
  if (this->waiting)
    push_in_waiting(this, this->waiting);
  actualizeBuffering(this->teams, rd, wr);
  if (buffered)
    iaProcess(this, this->teams);
}
