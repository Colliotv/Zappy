
#ifndef	_OBJ_HH_
#define	_OBJ_HH_

enum {GROUND, STONE, PLAYER};
enum {LINEMATE, DERAUMERE, SIBUR, MENDIANE, PHIRAS, THYSTAME};

class object
{
	public:
		int		type;
		int		sort;
		float		pos_x;
		float		pos_y;

		object();
		~object();
};

#endif