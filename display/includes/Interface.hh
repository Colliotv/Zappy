
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
		std::string curPlay;

		Interface();
		~Interface();
		void drawInterface(sf::RenderWindow &window, std::vector<player> playerList);
		void eventsInterface(sf::RenderWindow &window);
};

#endif