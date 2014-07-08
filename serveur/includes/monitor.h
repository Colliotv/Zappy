#ifndef __MONITOR_H__
# define __MONITOR_H__

typedef struct s_serveur serveur;
void	avertMonitor(serveur*, char*, ... );

# define mNewPlayer(n, x, y, orientation, lvl, team) "pnw %d %d %d %d %d %s", n, x, y, orientation, lvl, team
# define mBroadcastPlayer(n, m) "pbc %d, %s", n
# define mExpulsePlayer(n) "pex %d\n", n
# define mPosePlayer(n, r) "pdr %d %d\n", n, r
# define mPrendPlayer(n, r) "pgt %d %d\n", n, r
# define mIncantEPlayer(x, y) "pie %d %d 0\n", x, y
# define mIncantSPlayer(x, y) "pie %d %d 1\n", x, y

#endif
