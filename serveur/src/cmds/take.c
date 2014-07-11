#define _GNU_SOURCE
#include <stdlib.h>
#include <stdio.h>
#include <string.h>

#include "serveur.h"
#include "ressource.h"
#include "monitor.h"

void	iaPrend		(serveur* this, iaClients* ia, char* i) {
  ressource n;

  n = getRessourceId(i + strlen("voir "));
  if (n != -1 && (GET_SQUARE(this, ia->_p.x, ia->_p.y))[n])
    {
      (GET_SQUARE(this, ia->_p.x, ia->_p.y))[n] -= 1;
      ia->stash[n] += 1;
      pushNode(ia->wrBuffer, strdup("ok\n"));
      avertMonitor(this, mPrendPlayer(ia->num, n));
      avertMonitor(this, mStashPlayer(ia->num, ia->_p.x, ia->_p.y,
				      (ia->stash)[nourriture], (ia->stash)[linemate],
				      (ia->stash)[deraumere], (ia->stash)[sibur],
				      (ia->stash)[mendiane], (ia->stash)[phiras],
				      (ia->stash)[thystane]));
      
    }
  else
    pushNode(ia->wrBuffer, strdup("ko\n"));
}

void	iaPose		(serveur* this, iaClients* ia, char* i) {
  ressource n;

  n = getRessourceId(i + strlen("voir "));
  if (n != -1 && (ia->stash)[n])
    {
      (GET_SQUARE(this, ia->_p.x, ia->_p.y))[n] += 1;
      ia->stash[n] -= 1;
      pushNode(ia->wrBuffer, strdup("ok\n"));
      avertMonitor(this, mPosePlayer(ia->num, n));
      avertMonitor(this, mStashPlayer(ia->num, ia->_p.x, ia->_p.y,
				      (ia->stash)[nourriture], (ia->stash)[linemate],
				      (ia->stash)[deraumere], (ia->stash)[sibur],
				      (ia->stash)[mendiane], (ia->stash)[phiras],
				      (ia->stash)[thystane]));
    }
  else
    pushNode(ia->wrBuffer, strdup("ko\n"));
}
