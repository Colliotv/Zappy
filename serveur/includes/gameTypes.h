#ifndef __GAMETYPES_H__
# define __GAMETYPES_H__

# include <netdb.h>
# include <sys/types.h>
# include <sys/socket.h>
# include <netinet/in.h>

typedef int _port;

typedef enum eOrientation{
  haut = 0,
  bas,
  gauche,
  droite,
  maxOrientation
}	orientation;

typedef struct s_position{
  int	x;
  int	y;
} position;

typedef enum etime{
  READY,
  pAvance = 7,
  pRotation = 7,
  pVoir = 7,
  pInventaire = 1,
  pPrendre = 7,
  pExpulse = 7,
  pBroadcast = 7,
  pIncatation = 300,
  pFork = 42,
  uLife = 1260,
}		gtime;

typedef struct sLife{
  gtime	time;
  int	amount;
} life;

#endif
