#include <sys/select.h>
#include <sys/time.h>
#include <sys/types.h>
#include <unistd.h>

#include "serveur.h"

static int	fetchClient(clients* node, fd_set *rd, bool doWr, fd_set *wr) {
  int	max;
  int	tmax;

  if (!node)
    return (0);
  FD_SET(node->client, rd);
  max = node->client + 1;
  if (doWr)
    FD_SET(node->client, wr);
  tmax = fetchClient(node->next, rd, doWr, wr);
  if (tmax > max)
    max = tmax;
  return (max);
}

static int	fetchFDS(serveur* this, fd_set *rd, fd_set *wr) {
  int max;
  int tmax;

  FD_SET(this->serv, rd);
  max = this->serv + 1;
  if ((tmax = fetchClient(this->unaffecteds, rd, false, NULL)) > max)
    max = tmax;
  if ((tmax = fetchClient(this->monitor, rd, true, wr)) > max)
    max = tmax;
  if (this->waiting)
    if ((tmax = fetchClient(&(this->waiting->_), rd, false, NULL)) > max)
      max = tmax;
  return (max);
}

#include <stdio.h>

void	actualize(serveur* this) {
  fd_set rd;
  fd_set wr;
  int	mx;
  struct timeval tv;

  FD_ZERO(&rd);
  FD_ZERO(&wr);
  mx = fetchFDS(this, &rd, &wr);
  tv.tv_sec = 0;
  tv.tv_usec = 0;
  select(mx, &rd, &wr, NULL, &tv);
  if (this->time)
    usleep(1.f/this->time * 1000000.f);
  else
    usleep(100000.f);
}
