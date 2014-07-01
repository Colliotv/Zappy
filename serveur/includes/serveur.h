#ifndef __SERVEUR_H__
# define __SERVEUR_H__

# include "teams.h"
# include "argues.h"

typedef struct s_clients{
  struct s_clients	*next;
  _fd			client;
  circularBuffer	*rdBuffer;
}clients;

typedef struct s_wclients{
  struct s_clients	_;
  char*			team;
}wclients;

# define GET_SQUARE(this, x, y) (&(((this)->ressources)[x * (this)->size.y + y]))

typedef struct s_serveur{
  /*	time		*/
  gtime		time;
  _fd		serv;

  /*	unaffected Clients	*/
  clients*	unaffecteds;

  /*	Monitors		*/
  clients*	monitor;

  /*	Clients		*/
  wclients*		waiting;		
  teams*		teams;

  /*	map		*/
  position		size;
  bool*		ressources;
}serveur;

serveur* factory(struct args*);
void	destroy(serveur*);

void	actualize(serveur*);

#endif
