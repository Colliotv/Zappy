#ifndef	_GAME_HH_
#define	_GAME_HH_

#include	<string>
#include	<vector>
#include	<map>
#include <GLFW/glfw3.h>
#include <SFML/Graphics.hpp>
#include <SFML/Window.hpp>
#include <SFML/OpenGL.hpp>
#include <SFML/System/Vector2.hpp>
#include "MD2Loader.h"


#define DEAD 0;
#define ALIVE 1;

enum {
	NORD = 1,
	EST = 2,
	SUD = 3,
	OUEST = 4,
};

struct player
{
	int nb;
	int nb_team;
	float pos_x[2];
	float pos_y[2];
	int spawn_x;
	int spawn_y;
	int orientation;
	int level;
	int food;
	int	linemate;
	int	deraumere;
	int	sibur;
	int	mendiane;
	int	phiras;
	int	thystame;
	int state;
	int cursor;
	std::string team;
};

struct square
{
	float	pos_x;
	float	pos_y;
	int	food;
	int	linemate;
	int	deraumere;
	int	sibur;
	int	mendiane;
	int	phiras;
	int	thystame;
	int egg;
	int incant;
};

class Game
{
	public:
		std::map<std::string, void(Game::*)(std::stringstream&)>    cmd;
		std::vector<square> v_square;
		std::vector<player> v_player;
		int                 sgt;
		int                 fd_server;
		int                 size_map_x;
		int                 size_map_y;
		int                 map_ready = 0;

		Game();
		~Game();
		void initMap();
		void isset_server(int fd);
		void ClientRead(int cs);
		void cmdMszSizeMap(std::stringstream &);
		void cmdBctContentCase(std::stringstream &);
		void cmdTnaNameTeam(std::stringstream &);
		void cmdPnwConnect(std::stringstream &);
		void cmdPpoPosition(std::stringstream &);
		void cmdPlvNiveau(std::stringstream &);
		void cmdPinInventaire(std::stringstream &);
		void cmdPexExpulse(std::stringstream &);
		void cmdPicIncantBegin(std::stringstream &);
		void cmdPieIncantEnd(std::stringstream &);
		void cmdPfkEggsSpawn(std::stringstream &);
		void cmdPdrDepositResource(std::stringstream &);
		void cmdPgtGetResource(std::stringstream &);
		void cmdPdiPlayerDead(std::stringstream &);
		void cmdEnwEggsSpawn(std::stringstream &);
		void cmdEhtEclos(std::stringstream &);
		void cmdEboEggsConnect(std::stringstream &);
		void cmdEdiDead(std::stringstream &);
		void cmdSegVictory(std::stringstream &);
};

int   ConnectClientGraToServer(std::string   ip, std::string hostname);

void	ClientRead(int cs);

int	my_connect(int	*cs, char *ip, char *hostname);

#endif