
#include  <iostream>
#include <string>
#include <iostream>
#include <sstream>
#include <vector>
#include  "client.h"
#include  "Game.hh"

Game::Game()
{
  cmd.insert(std::pair<std::string, void(Game::*)(std::stringstream &)>("msz", &Game::cmdMszSizeMap));
  cmd.insert(std::pair<std::string, void(Game::*)(std::stringstream &)>("bct", &Game::cmdBctContentCase));
  cmd.insert(std::pair<std::string, void(Game::*)(std::stringstream &)>("tna", &Game::cmdTnaNameTeam));
  cmd.insert(std::pair<std::string, void(Game::*)(std::stringstream &)>("pnw", &Game::cmdPnwConnect));
  cmd.insert(std::pair<std::string, void(Game::*)(std::stringstream &)>("ppo", &Game::cmdPpoPosition));
  cmd.insert(std::pair<std::string, void(Game::*)(std::stringstream &)>("plv", &Game::cmdPlvNiveau));
  cmd.insert(std::pair<std::string, void(Game::*)(std::stringstream &)>("pin", &Game::cmdPinInventaire));
  cmd.insert(std::pair<std::string, void(Game::*)(std::stringstream &)>("pex", &Game::cmdPexExpulse));
  cmd.insert(std::pair<std::string, void(Game::*)(std::stringstream &)>("pic", &Game::cmdPicIncantBegin));
  cmd.insert(std::pair<std::string, void(Game::*)(std::stringstream &)>("pie", &Game::cmdPieIncantEnd));
  cmd.insert(std::pair<std::string, void(Game::*)(std::stringstream &)>("pfk", &Game::cmdPfkEggsSpawn));
  cmd.insert(std::pair<std::string, void(Game::*)(std::stringstream &)>("pdr", &Game::cmdPdrDepositResource));
  cmd.insert(std::pair<std::string, void(Game::*)(std::stringstream &)>("pgt", &Game::cmdPgtGetResource));
  cmd.insert(std::pair<std::string, void(Game::*)(std::stringstream &)>("pdi", &Game::cmdPdiPlayerDead));
  cmd.insert(std::pair<std::string, void(Game::*)(std::stringstream &)>("enw", &Game::cmdEnwEggsSpawn));
  cmd.insert(std::pair<std::string, void(Game::*)(std::stringstream &)>("eht", &Game::cmdEhtEclos));
  cmd.insert(std::pair<std::string, void(Game::*)(std::stringstream &)>("edi", &Game::cmdEdiDead));
  cmd.insert(std::pair<std::string, void(Game::*)(std::stringstream &)>("ebo", &Game::cmdEboEggsConnect));
  cmd.insert(std::pair<std::string, void(Game::*)(std::stringstream &)>("seg", &Game::cmdSegVictory));
  player_win = "";
}

Game::~Game(){}

void Game::cmdMszSizeMap(std::stringstream &iss)
{
  iss >> size_map_x;
  iss >> size_map_y;
  square buff;
  float x = 0.0f;
  float y = 0.0f;
  int i = 0;

  while (x < size_map_x)
  {
    y = 0;
    while (y < size_map_y)
    {
      buff.pos_x = x;
      buff.pos_y = y;
      buff.food = -42;
      buff.linemate = 0;
      buff.deraumere = 0;
      buff.sibur = 0;
      buff.mendiane = 0;
      buff.phiras = 0;
      buff.thystame = 0;
      buff.egg = 0;
      buff.incant = 0;
    	v_square.push_back(buff);
    	y++;
    	i++;
    }
    x++;
  }
}

void Game::cmdBctContentCase(std::stringstream &iss)
{
  int   x;
  int   y;

  iss >> x;
  iss >> y;
  v_square[x + (y * this->size_map_x)].pos_x = x;
  v_square[x + (y * this->size_map_x)].pos_y = y;
  iss >> v_square[x + (y * this->size_map_x)].food;
  iss >> v_square[x + (y * this->size_map_x)].linemate;
  iss >> v_square[x + (y * this->size_map_x)].deraumere;
  iss >> v_square[x + (y * this->size_map_x)].sibur;
  iss >> v_square[x + (y * this->size_map_x)].mendiane;
  iss >> v_square[x + (y * this->size_map_x)].phiras;
  iss >> v_square[x + (y * this->size_map_x)].thystame;
}

void Game::cmdTnaNameTeam(std::stringstream &iss)
{
	std::string   name_team;

	iss >> name_team;
}

void Game::cmdPnwConnect(std::stringstream &iss) 
{
  player  buff;

  iss >> buff.nb;
  iss >> buff.pos_x[0];
  iss >> buff.pos_y[0];
  iss >> buff.orientation;
  iss >> buff.level;
  iss >> buff.team;
  buff.state = ALIVE;
  buff.cursor = 0;
  buff.pos_x[1] = buff.pos_x[0];
  buff.pos_y[1] = buff.pos_y[0];
  if (buff.orientation == 1)
    buff.orientation = 3;
  else if (buff.orientation == 3)
    buff.orientation = 1;
  v_player.push_back(buff);

  unsigned int i = 0;  
  std::vector<std::string> teamList;
  unsigned int n = 0, m = 0;
  while (n < v_player.size())
  {
    i++;
    m = 0;
    while (m < teamList.size())
    {
      if (v_player[n].team == teamList[m])
        v_player[n].nb_team = m;
      m++;
    }
    if (v_player[n].nb_team == -1)
    {
      teamList.push_back(v_player[n].team);
      v_player[n].nb_team = m;
    }
    n++;
  }
}

void Game::cmdPpoPosition(std::stringstream &iss)
{
  int nb_player;
  float pos_x;
  float pos_y;
  int orientation;
  unsigned int i = 0;

  iss >> nb_player;
  iss >> pos_x;
  iss >> pos_y;
  iss >> orientation;
  while (i <v_player.size())
  {
    if (v_player[i].nb == nb_player)
    {
      v_player[i].pos_x[0] = v_player[i].pos_x[1];
      v_player[i].pos_y[0] = v_player[i].pos_y[1];

      v_player[i].pos_x[1] = pos_x;
      v_player[i].pos_y[1] = pos_y;
      v_player[i].orientation = orientation;
      if (v_player[i].orientation == 1)
        v_player[i].orientation = 3;
      else if (v_player[i].orientation == 3)
        v_player[i].orientation = 1;
    }
    i++;
  }
}

void Game::cmdPlvNiveau(std::stringstream &iss)
{
  unsigned int i;
  int nb;
  int buff_niv;

  i = 0;
  iss >> nb;
  iss >> buff_niv;
  while (i < v_player.size())
  {
    if (nb == v_player[i].nb)
      v_player[i].level = buff_niv;
    i++;
  }
}

void Game::cmdPinInventaire(std::stringstream &iss)
{
  int nb_player;
  unsigned int i = 0;

  iss >> nb_player;
  while (i < v_player.size())
  {
    if (nb_player == v_player[i].nb)
    {
        iss >> v_player[i].pos_x[0];
        iss >> v_player[i].pos_y[0];
        iss >> v_player[i].food;
        iss >> v_player[i].linemate;
        iss >> v_player[i].deraumere;
        iss >> v_player[i].sibur;
        iss >> v_player[i].mendiane;
        iss >> v_player[i].phiras;
        iss >> v_player[i].thystame;
    }
    i++;
  }
}

void Game::cmdPexExpulse(std::stringstream &iss)
{
  int  nb_player;
  int x;
  int y;
  std::vector<player>::iterator it = v_player.begin();

  iss >> nb_player;
  while (it != v_player.end())
  {
    if (it->nb == nb_player)
    {
      x = it->pos_x[1];
      y = it->pos_y[1];
      break;
    }
    else
      it++;
  }
  it = v_player.begin();
  while (it != v_player.end())
  {
    if (it->pos_x[1] == x && it->pos_y[1] == y)
    {
      // std::cout << "*** \n";
      char *str;
      asprintf(&str, "ppo %d\n", it->nb);
      write(fd_server, str, strlen(str));
    }
    else
      it++;
  }
}

void Game::cmdPicIncantBegin(std::stringstream &iss)
{
  int pos_x;
  int pos_y;
  int current_niv;

  iss >> pos_x;
  iss >> pos_y;
  iss >> current_niv;
  v_square[pos_x + (pos_y * this->size_map_x)].incant = 1;
}

void Game::cmdPieIncantEnd(std::stringstream &iss)
{
  int    x;
  int    y;
  int    result;
  iss >> x;
  iss >> y;
  iss >> result;
  v_square[x + (y * this->size_map_x)].incant = 0;
}

void Game::cmdPfkEggsSpawn(std::stringstream &iss)
{
	int   num_player;

	iss >> num_player;
}

void Game::cmdPdrDepositResource(std::stringstream &iss)
{
	int   num_player;
	int   num_resource;
  unsigned int i;
  int x;
  int y;

	iss >> num_player;
	iss >> num_resource;
  while (i < v_player.size())
  {
    if (v_player[i].nb == num_player)
    {
      x = v_player[i].pos_x[0];
      y = v_player[i].pos_y[0];
      if (i == 0)
      {
        v_player[i].food--;
        v_square[x + (y * this->size_map_x)].food++;
      }
      if (i == 1)
      {
        v_player[i].linemate--;
        v_square[x + (y * this->size_map_x)].linemate++;
      }
      if (i == 2)
      {
        v_player[i].deraumere--;
        v_square[x + (y * this->size_map_x)].deraumere++;
      }
      if (i == 3)
      {
        v_player[i].sibur--;
        v_square[x + (y * this->size_map_x)].sibur++;
      }
      if (i == 4)
      {
        v_player[i].mendiane--;
        v_square[x + (y * this->size_map_x)].mendiane++;
      }
      if (i == 5)
      {
        v_player[i].phiras--;
        v_square[x + (y * this->size_map_x)].phiras++;
      }
      if (i == 6)
      {
        v_player[i].thystame--;
        v_square[x + (y * this->size_map_x)].thystame++;
      }
    }
    i++;
  }
}

void Game::cmdPgtGetResource(std::stringstream &iss)
{
  int   num_player;
	int   num_resource;
  int   x;
  int   y;
  unsigned int i = 0;

	iss >> num_player;
	iss >> num_resource;
  while (i < v_player.size())
  {
    if (v_player[i].nb == num_player)
    {
      x = v_player[i].pos_x[0];
      y = v_player[i].pos_y[0];
      if (i == 0)
      {
        v_player[i].food++;
        v_square[x + (y * this->size_map_x)].food--;
      }
      if (i == 1)
      {
        v_player[i].linemate++;
        v_square[x + (y * this->size_map_x)].linemate--;
      }
      if (i == 2)
      {
        v_player[i].deraumere++;
        v_square[x + (y * this->size_map_x)].deraumere--;
      }
      if (i == 3)
      {
        v_player[i].sibur++;
        v_square[x + (y * this->size_map_x)].sibur--;
      }
      if (i == 4)
      {
        v_player[i].mendiane++;
        v_square[x + (y * this->size_map_x)].mendiane--;
      }
      if (i == 5)
      {
        v_player[i].phiras++;
        v_square[x + (y * this->size_map_x)].phiras--;
      }
      if (i == 6)
      {
        v_player[i].thystame++;
        v_square[x + (y * this->size_map_x)].thystame--;
      }
    }
    i++;
  }
}

void Game::cmdPdiPlayerDead(std::stringstream &iss)
{
  int nb_player;

  iss >> nb_player;
  std::vector<player>::iterator it = v_player.begin();
  while ( it != v_player.end() )
  {
    if ( it->nb == nb_player )
    {
      it = v_player.erase(it);
      break;
    }
    else
      it++;
  }
}

void Game::cmdEnwEggsSpawn(std::stringstream &iss)
{
	int num_eggs;
	int num_player;
	int x;
	int y;

	iss >> num_eggs;
	iss >> num_player;
	iss >> x;
	iss >> y;
  v_square[x + (y * this->size_map_x)].egg++;
}

void Game::cmdEhtEclos(std::stringstream &iss)
{
	int num_eggs;

	iss >> num_eggs;
}

void Game::cmdEboEggsConnect(std::stringstream &iss)
{
	int num_eggs;

	iss >> num_eggs;
}

void Game::cmdEdiDead(std::stringstream &iss)
{
	int num_eggs;

	iss >> num_eggs;
}

void Game::cmdSegVictory(std::stringstream &iss)
{
	std::string   name_team;
	iss >> name_team;
}

void	Game::isset_server(int fd)
{
    char *buffer;
    int itt;
    char  c;
    
    itt = 0;
    buffer = NULL;
    while (read(fd, &c, 1) > 0)
    {
      buffer = (char *)realloc(buffer, itt + 1);
      if (c == '\n')
        break;
      buffer[itt] = c;
      itt += 1;
    }
    std::string    data(buffer, itt);
    std::stringstream iss(data);   
    std::string n;
    iss >> n;
    if (cmd.find(n) != cmd.end())
      (this->*(cmd[n]))(iss);
    // else
      // std::cout << "DONT exist\t: ";
    iss.clear();
}
