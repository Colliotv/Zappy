#ifndef __MONITOR_H__
# define __MONITOR_H__

typedef struct s_serveur serveur;
void	avertMonitor(serveur*, char*, ... );

# define mSizeMap(x, y) "msz %d %d\n", x, y
# define mCaseMap(x, y, nourriture, i1, i2, i3, i4, i5, i6) "bct %d %d %d %d %d %d %d %d %d\n", x, y, nourriture, i1, i2, i3, i4, i5, i6
# define mNameTeam(s) "tna %s\n", s
# define mNewPlayer(n, x, y, orientation, lvl, team) "pnw %d %d %d %d %d %s", n, x, y, orientation, lvl, team
# define mPopEgg(n) "eht %d\n", n
# define mLvlPlayer(n, lvl) "pvl %d %d\n", n, lvl
# define mStashPlayer(n, x, y, nourriture, i1, i2, i3, i4, i5, i6) "pin %d %d %d %d %d %d %d %d %d\n", n, x, y, nourriture, i1, i2, i3, i4, i5, i6
# define mBroadcastPlayer(n, m) "pbc %d, %s", n
# define mExpulsePlayer(n) "pex %d\n", n
# define mPosePlayer(n, r) "pdr %d %d\n", n, r
# define mPrendPlayer(n, r) "pgt %d %d\n", n, r
# define mIncantEPlayer(x, y) "pie %d %d 0\n", x, y
# define mIncantSPlayer(x, y) "pie %d %d 1\n", x, y
# define mPositionPlayer(n ,x, y, o) "ppo %d %d %d %d\n", n, x, y, o

#endif
