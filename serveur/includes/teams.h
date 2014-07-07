#ifndef __TEAMS_H__
# define __TEAMS_H__

# include "bool.h"
# include "fd.h"
# include "ressource.h"
# include "gameTypes.h"
# include "circularBuffer.h"

typedef struct s_iaClients{
  struct s_iaClients*	next;
  /* cmds */
  _fd			iaClient;
  circularBuffer*	rdBuffer;
  circularBuffer*	wrBuffer;
  gtime			pause;

  /* vars */
  int			num;
  int			stash[ressourceLength];
  int			lvl;
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
