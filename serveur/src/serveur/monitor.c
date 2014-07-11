#define _GNU_SOURCE
#include <stdio.h>
#include <stdarg.h>
#include <stdlib.h>
#include <string.h>

#include "serveur.h"
#include "monitor.h"
#include "get_line.h"

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

static clients*	deleteMonitor(serveur* this, clients* monitor) {
  clients* pre;

  pre = this->monitor;
  while (pre && pre != monitor && pre->next != monitor)
    pre = pre->next;
  if (!pre)
    return (monitor);

}

static bool	getrd(serveur* this, clients* node, fd_set *rd) {
  char*	k;

  if (!FD_ISSET(node->client, rd))
    return (true);
  k = _get_socket(node->client);
  if (k == NULL)
    return (false);
  //  calcCmd(this, node, k);
  free(k);
  return (true);
}

static bool     pushwr(clients* node, fd_set* wr) {
  char* k;

  if (!FD_ISSET(node->client, wr))
    return (true);
  while ((k = popNode(node->rdBuffer)) != NULL)
    if (write(node->client, k, strlen(k)) <= 0)
      return (false);
    else
      free(k);
  return (true);
}

void	push_monitor(serveur* this, clients* node, fd_set* rd, fd_set* wr) {
  bool	oui;

  if (!node)
    return ;
  oui = getrd(this, node, rd);
  if (!oui)
    oui = pushwr(node, wr);
  if (!oui)
    push_monitor(this, deleteMonitor(this, node), rd, wr);
  else
    push_monitor(this, node->next, rd, wr);
}
