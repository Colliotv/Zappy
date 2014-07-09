#ifndef	_GAME_HH_
#define	_GAME_HH_

#include	<string>
#include	<vector>
#include	<map>
#include <GLFW/glfw3.h>


#define DEAD 0;
#define ALIVE 1;


struct player
{
	int nb;
	int pos_x;
	int pos_y;
	int spawn_x;
	int spawn_y;
	int orientation;
	int niveau; // Niveau du joueur ou de l'incatation
	int food;
	int	linemate;
	int	deraumere;
	int	sibur;
	int	mendiane;
	int	phiras;
	int	thystame;
	int state;
	std::string team;
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

class Game
{
	std::map<std::string, void(Game::*)(std::stringstream&)>    cmd;
	std::vector<square> v_square;
	std::vector<player> v_player;
	int                 sgt;
	int                 size_map_x;
	int                 size_map_y;

public:
	Game();
	~Game();
	void  initMap();
	void	isset_server(int fd);
	void  Rendering(GLFWwindow* window, int fd);
	void	ClientRead(int cs);

	void    cmdMszSizeMap(std::stringstream &);
	void    cmdBctContentCase(std::stringstream &);
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