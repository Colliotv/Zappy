#define _GNU_SOURCE
#include <stdlib.h>
#include <stdio.h>
#include <string.h>

#include "monitor.h"
#include "lerror.h"
#include "serveur.h"

static void	sendNotif(teams* team, position *_p, int lvl) {
  iaClients*	ia;
  char*		s;

  if (!team)
    return ;
  ia = team->list;
  while (ia) {
    if (ia->_p.x == _p->x && ia->_p.y == _p->y && ia->lvl == lvl) {
      asprintf(&s, "niveau actuel %d\n", lvl + 1);
      pushNode(ia->wrBuffer, s);
      ia->lvl += 1;
    }
    ia = ia->next;
  }
  sendNotif(team->next, _p, lvl);
}

static void	depletRessource(char *stash, int *r){
  int	itt;

  itt = 0;
  while (itt < ressourceLength) {
    stash[itt] -= r[itt];
    itt++;
  }
}

static void	avertMonitorForEach(serveur* this, teams* team, position* p, int lvl) {
  iaClients*	ia;

  if (!team)
    return ;
  ia = team->list;
  while (ia)
    {
      if (ia->lvl == lvl && ia->_p.x == p->x && ia->_p.y == p->y)
	avertMonitor(this, mLvlPlayer(ia->num, ia->lvl));
      ia = ia->next;
    }
  avertMonitorForEach(this, team->next, p, lvl);
}

void	iaIncantation	(serveur* this, iaClients* ia, char* i) {
  int	ressource[ressourceLength];

  (void)i;
  if (testForPlayer(this, ia)
      && testForRessource(this, ia, ressource))
    {
      depletRessource(GET_SQUARE(this, ia->_p.x, ia->_p.y), ressource);
      sendNotif(this->teams, &(ia->_p), ia->lvl);
      pushNode(ia->wrBuffer, strdup("elevation en cours\n"));
      avertMonitor(this, mIncantSPlayer(ia->_p.x, ia->_p.y));
      ia->pause = 300;
      avertMonitorForEach(this, this->teams, &(ia->_p), ia->lvl);
      avertMonitor(this, mIncantEPlayer(ia->_p.x, ia->_p.y));
      return ;
    }
  pushNode(ia->wrBuffer, strdup("ko\n"));
}
