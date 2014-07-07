#define _GNU_SOURCE
#include <stdio.h>
#include <stdarg.h>
#include "serveur.h"

void	avertMonitor(serveur* this, char* s, ... ) {
  clients* monitor;
  va_list ap;
  char*	si;

  monitor = this->monitor;
  va_start(ap, s);
  while (monitor)
    {
      asprintf(&si, s, ap);
      pushNode(monitor->rdBuffer, si);
      monitor = monitor->next;
    }
  va_end(ap);
}

void	push_monitor(serveur* this, clients* node, fd_set* rd, fd_set* wr) {}
