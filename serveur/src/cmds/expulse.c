#define _GNU_SOURCE
#include <stdlib.h>
#include <stdio.h>
#include <string.h>

#include "monitor.h"
#include "serveur.h"

static orientation	deductO(orientation o) {
  if (o == gauche)
    return (droite);
  if (o == droite)
    return (gauche);
  if (o == haut)
    return (bas);
  if (o == bas)
    return (haut);
  return (0);
}

static void	deductP(serveur* this, position pp,
			orientation o, position *p) {
  p->x = pp.x;
  p->y = pp.y;
  p->x +=
    (o == gauche) ? (-1) :
    (o == droite) ? (+1) :
    (0);
  p->y +=
    (o == haut) ? (-1) :
    (o == bas) ? (+1) :
    (0);
  if (p->y < 0)
    p->y = this->size.y;
  if (p->x < 0)
    p->x = this->size.x;
  if (p->y >= this->size.y)
    p->y = 0;
  if (p->x >= this->size.x)
    p->x = 0;
}

static void	updatePos(iaClients* node, iaClients* exp,
			  position *p, orientation o) {
  char* d;

  if (node->_p.x != exp->_p.x ||
      node->_p.y != exp->_p.y)
    return ;
  asprintf(&d, "deplacement %d\n", o);
  pushNode(node->wrBuffer, d);
  node->_p.x = p->x;
  node->_p.y = p->y;
}

static bool	dispatchNewPosition(teams* node, iaClients* ignored,
				    position *p, orientation o) {
  iaClients*	c;
  bool		test1;
  bool		test2;

  if (!node)
    return (false);
  test1 = false;
  c = node->list;
  while (c) {
    if (c != ignored && c->iaClient != -1)
      {
	updatePos(c, ignored, p, o);
	test1 = true;
      }
    c = c->next;
  }
  test2 = dispatchNewPosition(node->next, ignored, p, o);
  return (test1 || test2);
}

void	iaExpulse	(serveur* this, iaClients* ia, char* i) {
  position	p;
  orientation	o;

  (void)i;
  o = deductO(ia->_o);
  deductP(this, ia->_p, ia->_o, &p);
  dispatchNewPosition(this->teams, ia, &p, o);
  pushNode(ia->wrBuffer, strdup("ok\n"));
  avertMonitor(this, mExpulsePlayer(ia->num));
  ia->pause = 7;
}
