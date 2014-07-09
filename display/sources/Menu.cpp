
#include	<SFML/Graphics.hpp>
#include	<SFML/Audio.hpp>
#include    <iostream>
#include	"Menu.hh"

Menu::Menu()
{
	button = 1;
    c = 0;
    ip = "";
    hostname = "";
	if (!font.loadFromFile("images/LCD.otf"))
		std::cout << "Error : failed to load font" << std::endl;
    if (!music.openFromFile("images/StarCraft.wav"))
        std::cout << "Error : failed to load music" << std::endl;
    if (!textureBack.loadFromFile("images/Space.jpg"))
        std::cout << "Error : failed to load texture" << std::endl;
    spriteBack.setTexture(textureBack);
    text1.setFont(font);
    text2.setFont(font);
    text3.setFont(font);
    textIp.setFont(font);
    textHost.setFont(font);
    text1.setString("IP :");
    text2.setString("HostName :");
    text3.setString("Start");
    textIp.setString(ip);
    textHost.setString(hostname);
    text1.setCharacterSize(24);
    text2.setCharacterSize(24);
    text3.setCharacterSize(24);
    textIp.setCharacterSize(24);
    textHost.setCharacterSize(24);
    text1.setColor(sf::Color::Green);
    text2.setColor(sf::Color::Green);
    text3.setColor(sf::Color::Green);
    textIp.setColor(sf::Color::Green);
    textHost.setColor(sf::Color::Green);
    text1.setPosition(120, 120);
    text2.setPosition(120, 320);
    text3.setPosition(120, 520);
    textIp.setPosition(165, 120);
    textHost.setPosition(245, 320);
    rect1.setSize(sf::Vector2f(400, 80));
    rect2.setSize(sf::Vector2f(400, 80));
    rect3.setSize(sf::Vector2f(400, 80));
    rect1.setFillColor(sf::Color(200, 200, 200, 128));
    rect2.setFillColor(sf::Color(200, 200, 200, 128));
    rect3.setFillColor(sf::Color(200, 200, 200, 128));
    rect1.setOutlineThickness(10);
    rect2.setOutlineThickness(10);
    rect3.setOutlineThickness(10);
    rect1.setOutlineColor(sf::Color(120, 120, 120, 128));
    rect2.setOutlineColor(sf::Color(245, 245, 245, 128));
    rect3.setOutlineColor(sf::Color(245, 245, 245, 128));
    rect1.setPosition(100, 100);
    rect2.setPosition(100, 300);
    rect3.setPosition(100, 500);
}

Menu::~Menu()
{

}