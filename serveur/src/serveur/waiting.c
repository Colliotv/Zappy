#define _GNU_SOURCE
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "get_line.h"
#include "lerror.h"
#include "serveur.h"

static wclients* del_waiting(serveur* this, wclients* node) {
  wclients* pnod;
  wclients* nn;

  nn = (wclients*)node->_.next;
  free(node->team);
  if (this->waiting == node)
    this->waiting = (wclients*)node->_.next;
  else
    {
      pnod = (wclients*)this->waiting;
      while (pnod && pnod->_.next != (clients*)node)
	pnod = (wclients*)pnod->_.next;
      if (pnod)
	pnod->_.next = node->_.next;
    }
  destroyBuffer(node->_.rdBuffer, false);
  free(node);
  return (nn);
}

static int	let_it_know(serveur* this, wclients* waiting) {
  char* sending;
  teams* team;

  if (!waiting)
    return (0);
  if (!waiting->info) {
    if ((team = getTeamById(this, waiting->team)) == NULL)
      return (let_it_know(this, del_waiting(this, waiting)));
    asprintf(&sending, "%d\n", team->unaff_size);
    pushNode(waiting->_.rdBuffer, sending);
    asprintf(&sending, "%d %d\n", this->size.x, this->size.y);
    pushNode(waiting->_.rdBuffer, sending);
  }
  return (let_it_know(this, (wclients*)waiting->_.next));
}

static int	propagate_buffer(serveur* this, wclients* node, fd_set* wr) {
  char* k;

  if (!node)
    return (0);
  if (FD_ISSET(node->_.client, wr))
    {
      if ((k = popNode(node->_.rdBuffer)))
	{
	  if (write(node->_.client, k, strlen(k)) < (int)strlen(k))
	    return (propagate_buffer(this, del_waiting(this, node), wr));
	}
    }
  return (propagate_buffer(this, (wclients*)node->_.next, wr));
}

static int	getcmd(serveur* this, wclients* node, fd_set* rd) {
  char* k;
  if (!node)
    return (0);
  if (FD_ISSET(node->_.client, rd))
    {
      if ((k = _get_socket(node->_.client)))
	return (getcmd(this, del_waiting(this, node), rd));
      pushNode(node->_.rdBuffer, k);
    }
  return (getcmd(this, (wclients*)node->_.next, rd));
}

void	actualize_waiting(serveur* this, fd_set* rd, fd_set* wr) {
  getcmd(this, this->waiting, rd);
  let_it_know(this, this->waiting);
  propagate_buffer(this, this->waiting, wr);
}
