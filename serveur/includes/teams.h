#ifndef __TEAMS_H__
# define __TEAMS_H__

# include "bool.h"
# include "fd.h"
# include "ressource.h"
# include "gameTypes.h"
# include "circularBuffer.h"

# define REQUEST "avance|droite|gauche|voir|inventaire|prend|pose|inventaire|expulse|broadcast|incantation|fork|connect_nbr"

typedef struct s_iaClients{
  struct s_iaClients*	next;
  /* cmds */
  _fd			iaClient;
  circularBuffer*	rdBuffer;
  circularBuffer*	wrBuffer;
  gtime			pause;

  /* vars */
  bool			stash[ressourceLength];
  life			_life;
  orientation		_o;
  position		_p;
} iaClients;

typedef struct s_teams{
  struct s_teams*	next;
  iaClients*		list;
  int			size;
  int			unaff_size;
  char* name;
} teams;

#endif
