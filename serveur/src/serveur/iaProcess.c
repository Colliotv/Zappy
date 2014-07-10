#define _GNU_SOURCE
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "serveur.h"

static void	_cmd(serveur* this, iaClients* ia, char* cmd) {
  int itt;

  if (!cmd)
    return ;
  itt = 0;
  while (itt < NTREAT)
    {
      if (!strncmp((this->cmds)[itt], cmd, strlen((this->cmds)[itt])))
	{
	  (this->treat)[itt](this, ia, cmd);
	  free(cmd);
	  return ;
	}
      itt++;
    }
  free(cmd);
}

static bool	depletNut(iaClients* ia) {
  ia->depletingNut = uLife;
  (ia->stash)[nourriture] -= 1;
  if ((ia->stash)[nourriture] == 0)
    return (true);
  return (false);
}

static int	_proc(serveur* this, iaClients* ia, teams* team) {
  bool	supress;

  supress = false;
  if (!ia)
    return (0);
  if (ia->state == unaffected)
    return (_proc(this, ia->next, team));
  ia->pause -= (ia->pause > 0);
  if (ia->pause)
    return (_proc(this, ia->next, team));
  ia->depletingNut -= 1;
  if (!ia->depletingNut)
    supress = depletNut(ia);
  if (supress)
    return (_proc(this, delete_iaClient(team, ia), team));
  _cmd(this, ia, popNode(ia->rdBuffer));
  return (_proc(this, ia->next, team));
}

void	iaProcess(serveur* this, teams* team) {
  if (!team)
    return ;
  _proc(this, team->list, team);
  iaProcess(this, team->next);
}
