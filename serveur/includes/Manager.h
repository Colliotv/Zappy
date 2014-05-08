#ifndef __MANAGER_H__
# define __MANAGER_H__

typedef struct sManager Manager;
typedef struct sDialogue Dialogue;

# include "bool.h"
# include "fd.h"
# include "Clients.h"
# include "bufferCirculaire.h"
# include "Ressource.h"

# define NRESSOURCE 3

Manager* ManagerAllocator(void);
struct sManager{
  /* Clients */
  Client*	ClientList;
  Client*	Waiting_ClientList;
  void		(*pushClient)(_fd);
  void		(*acceptClient)(Client*);
  void		(*deleteClient)(_fd);

  /* Ressource Manager */
  RessourceManager*	ressource;

  /* buffer */
  BufferCirculaire*	rdBuffer;
  
  /* traitement de message */
};


struct sDialogue{
  CLient*	client;
  char*		msg;
};

#endif
