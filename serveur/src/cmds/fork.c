#define _GNU_SOURCE
#include <stdlib.h>
#include <stdio.h>
#include <string.h>

#include "lerror.h"
#include "serveur.h"

static void	addUnaff(serveur* this, iaClients* ia) {
  teams*	team;

  team = getTeam(this->teams, ia);
  team->unaff_size += 1;
  team->size += 1;
}

void	iaFork		(serveur* this, iaClients* ia, char* i) {
  iaClients* node;

  (void)i;
  if ((node = malloc(sizeof(iaClients))) == NULL)
    lerror(MEMORY_ERROR(sizeof(iaClients)));
  node->next = ia->next;
  ia->next = node;
  node->num = this->num;
  this->num += 1;
  node->iaClient = FD_NOSET;
  node->pause = READY;
  node->wrBuffer = createBuffer();
  node->state = egg;
  node->depletingNut = pBirth + uLife;
  node->pause = pBirth;
  node->lvl = 1;
  node->_o = random() % maxOrientation;
  node->_p.x = ia->_p.x;
  node->_p.y = ia->_p.y;
  bzero(node->stash, sizeof(node->stash));
  (node->stash)[nourriture] = 3;
  ia->pause = pFork;
  addUnaff(this, ia);
  pushNode(ia->wrBuffer, strdup("ok\n"));
}
