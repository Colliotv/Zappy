#ifndef __SERVEUR_H__
# define __SERVEUR_H__

#include <sys/select.h>
#include <sys/time.h>
#include <sys/types.h>
#include <unistd.h>

# include "teams.h"
# include "argues.h"

typedef struct s_clients{
  struct s_clients	*next;
  _fd			client;
  circularBuffer	*rdBuffer;
  bool			welcome;
}clients;

typedef struct s_wclients{
  struct s_clients	_;
  char*			team;
  bool			info;
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
  char*		ressources;
}serveur;

serveur* factory(struct args*);
void	destroy(serveur*);

void	actualize(serveur*);
/* refresh */
void	addClient(serveur*, fd_set*);
void	actualize_unaff(serveur*, fd_set*, fd_set*);
void	actualize_waiting(serveur*, fd_set*, fd_set*);
void	actualize_IA(serveur*, fd_set*, fd_set*);
void	push_monitor(clients*, fd_set*, fd_set*);

/* teams */
teams*	getTeamById(serveur*, char*);

#endif
