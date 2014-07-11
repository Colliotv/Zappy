
#include  <iostream>
#include <string>
#include <iostream>
#include <sstream>
#include <vector>
#include  "client.h"
#include  "Game.hh"

Game::Game(){}

Game::~Game(){}

void   Game::initMap()
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
}

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
//    	std::cout << "msz x[" << x << "] y{" << y << "}" << i << std::endl;
      buff.pos_x = x;
      buff.pos_y = y;
      buff.food = -1;
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
  std::cout << "cmdMszSizeMap size_map_x[" << size_map_x << "] size_map_y[" << size_map_y << "]\n";
}

void Game::cmdBctContentCase(std::stringstream &iss)
{
  int   x;
  int   y;
  // x +(y*xmax)
  iss >> x;
  iss >> y;
//  std::cout << "bct x[" << x << "] y{" << y << "}" << x + (y * this->size_map_x) << std::endl;
  v_square[x + (y * this->size_map_x)].pos_x = x;
  v_square[x + (y * this->size_map_x)].pos_y = y;
//  std::cout << "size vector " << v_square.size() << std::endl;
  iss >> v_square[x + (y * this->size_map_x)].food;
  iss >> v_square[x + (y * this->size_map_x)].linemate;
  iss >> v_square[x + (y * this->size_map_x)].deraumere;
  iss >> v_square[x + (y * this->size_map_x)].sibur;
  iss >> v_square[x + (y * this->size_map_x)].mendiane;
  iss >> v_square[x + (y * this->size_map_x)].phiras;
  iss >> v_square[x + (y * this->size_map_x)].thystame;
  if (x == size_map_x - 1 && y == size_map_y - 1)
    map_ready = 1;
}

void Game::cmdTnaNameTeam(std::stringstream &iss)
{
	std::string   name_team;

	iss >> name_team;
	std::cout << "cmdTnaNameTeam\n";
//	unsigned int  i = 0;

  // while (i < v_square.size())
  // {
  //   std::cout << v_square[i].pos_x << " " << v_square[i].pos_y << " food " << v_square[i].food << " thystame " << v_square[i].thystame << std::endl;
  //   i++;
  // }
}

void Game::cmdPnwConnect(std::stringstream &iss) 
{
//  std::map<std::string,  void(Game::*)(std::stringstream& iss)>::iterator    it;
//  std::vector<square>::iterator i_square;

  // for (int unsigned i = 0 ; i < v_square.size(); i++)
  // {
  //   std::cout << "{" << v_square[i].pos_x << ", " << v_square[i].pos_y << "} ";
  //   std::cout << " " <<  v_square[i].food << " " << v_square[i].linemate << " " << v_square[i].deraumere << std::endl;
  // } 
  player  buff;

  iss >> buff.nb;
  iss >> buff.pos_x;
  iss >> buff.pos_y;
  iss >> buff.orientation;
  iss >> buff.level;
  iss >> buff.team;
  buff.state = ALIVE;
  v_player.push_back(buff);
  std::cout << "cmdPnwConnect ";
  unsigned int i = 0;  
  std::vector<std::string> teamList;
  unsigned int n = 0, m = 0;


  while (n < v_player.size())
  {
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
  std::cout << "cmdPpoPosition nb_player " << nb_player << " .size()" << v_player.size() << std::endl;
  while (i <v_player.size())
  {
    if (v_player[i].nb == nb_player)
    {
      std::cout << v_player[i].pos_x << " y---------" << v_player[i].pos_y << std::endl;
      v_player[i].pos_x = pos_x;
      v_player[i].pos_y = pos_y;
      v_player[i].orientation = orientation;
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
  std::cout << "cmdPlvNiveau nb_player : " << nb;
  while (i < v_player.size())
  {
    if (nb == v_player[i].nb)
    {
      v_player[i].level = buff_niv;
      std::cout << " i : " << i << " level : " << v_player[i].level << std::endl;
    }
    i++;
  }
}

void Game::cmdPinInventaire(std::stringstream &iss)
{
  int nb_player;
  unsigned int i = 0;

  std::cout << "cmdPinInventaire\n";
  iss >> nb_player;
  while (i < v_player.size())
  {
    std::cout << "nb_player : " << nb_player << " i " << i;
    if (nb_player == v_player[i].nb)
    {
        iss >> v_player[i].pos_x;
        iss >> v_player[i].pos_y;
        iss >> v_player[i].food;
        iss >> v_player[i].linemate;
        iss >> v_player[i].deraumere;
        iss >> v_player[i].sibur;
        iss >> v_player[i].mendiane;
        iss >> v_player[i].phiras;
        iss >> v_player[i].thystame;
        std::cout << "*** x : " << v_player[i].pos_x << " y :" << v_player[i].pos_y << std::endl;
    }
    i++;
  }
}

void Game::cmdPexExpulse(std::stringstream &iss)
{
  std::cout << "cmdPexExpulse\n";
  int  nb_player;
  int x;
  int y;
  std::vector<player>::iterator it = v_player.begin();

  iss >> nb_player;
  while (it != v_player.end())
  {
    if (it->nb == nb_player)
    {
      x = it->pos_x;
      y = it->pos_y;
      break;
    }
    else
      it++;
  }
  it = v_player.begin();
  while (it != v_player.end())
  {
    if (it->pos_x == x && it->pos_y == y)
    {
      std::cout << "*** \n";
      char *str;
      asprintf(&str, "ppo %d\n", it->nb);
      write(fd_server, str, strlen(str));
    }
    else
      it++;
  }
}

void Game::cmdPicIncantBegin(std::stringstream &iss) // animation Début 
{
  int pos_x;
  int pos_y;
  int current_niv;
  int tmp;
  std::vector<int> player_buff;

  iss >> pos_x;
  iss >> pos_y;
  iss >> current_niv;
  std::cout << "cmdPicIncantBegin x " << pos_x << " y " << pos_y << " current_niv : " << current_niv;
  
  v_square[pos_x + (pos_y * this->size_map_x)].incant = 1;
  // while (iss >> tmp)
  // {
  //   std::cout << " joueur n " << tmp; 
  //   player_buff.push_back(tmp);
  // }
  // unsigned int i = 0;
  // unsigned int j = 0;
  // while (i < v_player.size())
  // {
  //   while (j < player_buff.size())
  //   {
  //     if (v_player[i].nb == player_buff[j])
  //     {
  //       std::cout << "*** JOUEUR n : " << v_player[i].nb << " begin incant\n";
  //     }
  //     j++;
  //   }
  //   j = 0;
  //   i++;
  // }
}

void Game::cmdPieIncantEnd(std::stringstream &iss)
{
  int    x;
  int    y;
  int    result;
  unsigned int    i;

  iss >> x;
  iss >> y;
  iss >> result;
  i = 0;
  std::cout << "cmdPieIncantEnd ";
  v_square[x + (y * this->size_map_x)].incant = 0;
  // while (i < v_player.size())
  // {
  //   if (x == v_player[i].pos_x && y == v_player[i].pos_y && result == 1)
  //   {
  //     std::cout << "player n : " << v_player[i].nb << " level++ :" <<
  //     v_player[i].level++;
  //   }
  //   i++;
  // }
}

void Game::cmdPfkEggsSpawn(std::stringstream &iss)
{
	int   num_player;

	iss >> num_player;
	std::cout << "cmdPfkEggsSpawn num_player : " << num_player << std::endl;
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
	std::cout << "cmdPdrDepositResource num_player : " << num_player << " num_resource : " << num_resource << std::endl;
  while (i < v_player.size())
  {
    if (v_player[i].nb == num_player)
    {
      x = v_player[i].pos_x;
      y = v_player[i].pos_y;
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
      std::cout << "*** bouffe déposé\n";
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

	iss >> num_player;
	iss >> num_resource;
  unsigned int i = 0;
  std::cout << "cmdPgtGetResource num_player :" << num_player << " num_resource : " << num_resource << " ";
  while (i < v_player.size())
  {
    if (v_player[i].nb == num_player)
    {
      x = v_player[i].pos_x;
      y = v_player[i].pos_y;
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
      std::cout << "*** bouffe prise\n";
    }
    i++;
  }
}

void Game::cmdPdiPlayerDead(std::stringstream &iss)
{
  int nb_player;
  unsigned int i;

  iss >> nb_player;
  i = 0;
  std::cout << "cmdPdiPlayerDead  ";
  std::vector<player>::iterator it = v_player.begin();
  while ( it != v_player.end() )
  {
    if ( it->nb == nb_player )
    {
      std::cout << "***player delete\n";
      it = v_player.erase(it); // Will return next valid iterator
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
	std::cout << "cmdEnwEggsSpawn\n";

}

void Game::cmdEhtEclos(std::stringstream &iss)
{
	int num_eggs;

	iss >> num_eggs;
	std::cout << "cmdEhtEclos\n";
}

void Game::cmdEboEggsConnect(std::stringstream &iss)
{
	int num_eggs;

	iss >> num_eggs;
	std::cout << "cmdEboEggsConnect\n";
}

void Game::cmdEdiDead(std::stringstream &iss)
{
	int num_eggs;

	iss >> num_eggs;	
	std::cout << "cmdEdiDead\n";
}

void Game::cmdSegVictory(std::stringstream &iss)
{
	std::string   name_team;
	iss >> name_team;
  std::cout << "cmdSegVictory equipe " << name_team << " gagne\n";
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

    std::map<std::string, int/*void(class::*)(stringstream&)*/>::iterator    it;
    std::stringstream iss(data);   
    std::string n;

    iss >> n;
    std::cout << "\ncommand[" << data << "]~>";
    if (cmd.find(n) != cmd.end())
    {
      std::cout << "EXIST\t: ";
      (this->*(cmd[n]))(iss);
    }
    else
      std::cout << "DONT exist\t: ";
    iss.clear();
}
