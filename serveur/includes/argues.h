#ifndef __ARGUES_H__
# define __ARGUES_H__

#include "bool.h"

# define ARGSNUM 6
# define ARGS "-p|-x|-y|-n|-c|-t"

# define BASE_PORT 4000
# define BASE_X 100
# define BASE_Y 100
# define BASE_NBY 1
# define BASE_TIME 10

struct nameNode{
  struct nameNode* next;
  char* name;
};

struct args{
  /* parsing parts */
  bool	initialized[ARGSNUM];
  int	ac;
  /* data parts */
  int	port;
  int	X;
  int	Y;
  struct nameNode*	names;
  int	nByTeams;
  int	time;
};

enum argsType {
  port,
  X,
  Y,
  names,
  nByTeams,
  time
};

char* getName(enum argsType);

/*		Factory			*/
struct args*	getArgs(int ac, char** av);
#endif
