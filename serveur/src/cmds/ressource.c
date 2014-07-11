#define _GNU_SOURCE
#include <stdlib.h>
#include <stdio.h>
#include <string.h>

#include "serveur.h"
#include "ressource.h"

static char*	addS(char* r, char* ressource) {
  char* rs;

  asprintf(&rs, "%s %s", r, ressource);
  free(r);
  return (rs);
}

char*	getRessourceOnMap(char* ressource) {
  char* r;

  r = strdup("");
  if (ressource[linemate])
    r = addS(r, " linemate");
  if (ressource[deraumere])
    r = addS(r, " deraumere");
  if (ressource[sibur])
    r = addS(r, " sibur");
  if (ressource[mendiane])
    r = addS(r, " mendiane");
  if (ressource[phiras])
    r = addS(r, " phiras");
  if (ressource[thystane])
    r = addS(r, " thystane");
  if (ressource[nourriture])
    r = addS(r, " nourriture");
  return (r);
}

ressource getRessourceId(char* ressource) {
  if (!strcmp(ressource, "nourriture\n"))
    return (nourriture);
  if (!strcmp(ressource, "linemate\n"))
    return (linemate);
  if (!strcmp(ressource, "sibur\n"))
    return (sibur);
  if (!strcmp(ressource, "mendiane\n"))
    return (mendiane);
  if (!strcmp(ressource, "phiras\n"))
    return (phiras);
  if (!strcmp(ressource, "thystane\n"))
    return (thystane);
  if (!strcmp(ressource, "deraumere\n"))
    return (deraumere);
  return (-1);
}

void	iaInventaire	(serveur* this, iaClients* ia, char* i) {
  char* s;

  (void)this;
  (void)i;
  asprintf(&s, "{nourriture %d, linemate %d, deraumere %d \
, sibur %d, mendiane %d, phiras %d, thystane %d}\n",
	   (ia->stash)[nourriture],
	   (ia->stash)[linemate],
	   (ia->stash)[deraumere],
	   (ia->stash)[sibur],
	   (ia->stash)[mendiane],
	   (ia->stash)[phiras],
	   (ia->stash)[thystane]
	   );
  pushNode(ia->wrBuffer, s);
  ia->pause = 1;
}
