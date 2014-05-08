#ifndef __CLIENTS_H__
# define __CLIENTS_H__

# include "bufferCirculaire.h"

typedef struct sClient Client;

Client*	ClientAllocator(_fd fd, Client* prev, CLient* next);
struct sClient{
  /* list */
  Client*	next;
  Client*	prev;

  /* wait time */
  int		wait;

  /* Fd */
  _fd		dialogue;

  /* On Read Get Line */
  void		(*get_next_line)();
  Dialogue*	(*get_msg)();

  /* BufferCirculaire */
  BufferCirculaire*	recv;
  BufferCirculaire*	wrte;

  /* info */
  int		posx;
  int		posy;
  int		direction;
  int		inventaire[NRESSOURCE];
  int		lvl;
};

#endif
