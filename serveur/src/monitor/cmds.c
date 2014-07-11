#define _GNU_SOURCE
#include <stdlib.h>
#include <stdarg.h>
#include <stdio.h>
#include <string.h>

#include "monitor.h"
#include "serveur.h"

void	avertThisMonitor(clients* monitor, char* s, ... ) {
  va_list ap;
  char*	si;

  va_start(ap, s);
  vasprintf(&si, s, ap);
  pushNode(monitor->rdBuffer, si);
  va_end(ap);
}


void	calcCmd(serveur* this, clients* monitor, char* k) {
  if (!strncmp(cmdMapSize, k, strlen(cmdMapSize)))
    avertThisMonitor(monitor, mSizeMap(this->size.x, this->size.y));
  if (!strncmp("bct ", k, strlen("bct ")))
    avertCase(this, monitor, k);
  if (!strncmp(cmdMap, k, strlen(cmdMap)))
    avertMap(this, monitor);
  if (!strncmp(cmdTeam, k, strlen(cmdTeam)))
    avertTeam(this, monitor);
  if (!strncmp("ppo ", k, strlen("ppo ")))
    avertPlayerPosition(this, monitor, k);
  if (!strncmp("plv ", k, strlen("plv ")))
    avertPlayerLevel(this, monitor, k);
  if (!strncmp("pin ", k, strlen("pin ")))
    avertPlayerInventaire();
}

void	avertMonitorByCmd(serveur* this, char* k) {
  clients* monitor;

  monitor = this->monitor;
  while (monitor)
    {
      calcCmd(this, monitor, k);
      monitor = monitor->next;
    }
}
