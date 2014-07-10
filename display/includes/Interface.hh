
#ifndef	_INTERFACE_HH_
#define	_INTERFACE_HH_

#include  <iostream>
#include  <SFML/Graphics.hpp>
#include  "Game.hh"

class Interface
{
	public:
		sf::RectangleShape rect;
		sf::Font font;
		sf::Text text;
		std::string str;
		std::string curTeam;
		int curPlay;
		int	curPos;

		Interface();
		~Interface();
		void eventsInterface(sf::RenderWindow &window, std::vector<player> playerList);
		void drawInterface(sf::RenderWindow &window, std::vector<player> playerList);
		void nextPlay(std::vector<player> playerList);
		void prevPlay(std::vector<player> playerList);
		void nextTeam(std::vector<player> playerList);
		void prevTeam(std::vector<player> playerList);
		void initInterface(sf::RenderWindow &window, std::vector<player> playerList);
		void moveCursor(sf::RenderWindow &window);
		void drawText(sf::RenderWindow &window, std::vector<player> playerList);
};

#endif