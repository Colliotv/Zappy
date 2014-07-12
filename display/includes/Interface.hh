
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
		int curCircle;
		float move_X;
		float move_Y;
		float move_Z;
		int  mouseX;
		int  mouseY;

		Interface();
		~Interface();
		void drawInterface(sf::RenderWindow &mainWindow, sf::RenderWindow &window, std::vector<player> &playerList);
		void eventsInterface(sf::RenderWindow &mainWindow, std::vector<player> &playerList);
		void nextPlay(std::vector<player> &playerList);
		void prevPlay(std::vector<player> &playerList);
		void nextTeam(std::vector<player> &playerList);
		void prevTeam(std::vector<player> &playerList);
		void initInterface(sf::RenderWindow &window, std::vector<player> &playerList);
		void moveCursor(sf::RenderWindow &window);
		void drawText(sf::RenderWindow &window, std::vector<player> &playerList);
};

#endif