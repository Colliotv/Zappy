
#include	<SFML/Audio.hpp>

class Menu
{
	public:
		sf::RectangleShape rect1;
		sf::RectangleShape rect2;
		sf::RectangleShape rect3;
		sf::Font font;
		sf::Text text1;
		sf::Text text2;
		sf::Text text3;
		sf::Text textIp;
		sf::Text textHost;
		sf::Music music;
		sf::Texture textureBack;
		sf::Sprite	spriteBack;
		int button;
		char	c;
		std::string	ip;
		std::string	port;

		Menu();
		~Menu();
};