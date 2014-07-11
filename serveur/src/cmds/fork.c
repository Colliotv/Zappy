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

static void	iaForkInit(serveur* this, iaClients* _egg, iaClients* ia) {
  (void)this;
  _egg->iaClient = FD_NOSET;
  _egg->pause = READY;
  _egg->wrBuffer = createBuffer();
  _egg->state = egg;
  _egg->depletingNut = pBirth + uLife;
  _egg->pause = pBirth;
  _egg->lvl = 1;
  _egg->_o = random() % maxOrientation;
  _egg->_p.x = ia->_p.x;
  _egg->_p.y = ia->_p.y;
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
  iaForkInit(this, node, ia);
  bzero(node->stash, sizeof(node->stash));
  (node->stash)[nourriture] = 3;
  ia->pause = pFork;
  addUnaff(this, ia);
  pushNode(ia->wrBuffer, strdup("ok\n"));
}
