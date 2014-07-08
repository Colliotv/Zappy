
#ifndef	_OBJ_HH_
#define	_OBJ_HH_

#include	<string>

struct player
{
	int	pos_x;
	int	pos_y;
	int nb;
	std::string team;
	int food;
	int	linemate;
	int	deraumere;
	int	sibur;
	int	mendiane;
	int	phiras;
	int	thystame;
};

struct square
{
	int	pos_x;
	int	pos_y;
	int	food;
	int	linemate;
	int	deraumere;
	int	sibur;
	int	mendiane;
	int	phiras;
	int	thystame;
};

#endif