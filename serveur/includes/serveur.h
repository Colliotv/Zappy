#ifndef __SERVEUR_H__
# define __SERVEUR_H__

# include "argues.h"

typedef struct s_serveur{ bool oui; }serveur;
serveur* factory(struct args*);

#endif
