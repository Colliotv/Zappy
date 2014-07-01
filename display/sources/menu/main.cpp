
#include    <iostream>
#include    <string>
#include    <SFML/Graphics.hpp>
#include    "Menu.hh"

void    buttonSwitcher(int dir, Menu &menu)
{
    if (dir == 0)
    {
        if (menu.button == 2)
        {
            menu.rect1.setOutlineColor(sf::Color(120, 120, 120, 128));
            menu.rect2.setOutlineColor(sf::Color(245, 245, 245, 128));
            menu.button = 1;
        }
        else if (menu.button == 3)
        {
            menu.rect2.setOutlineColor(sf::Color(120, 120, 120, 128));
            menu.rect3.setOutlineColor(sf::Color(245, 245, 245, 128));
            menu.button = 2;
        }
    }
    else if (dir == 1)
    {
        if (menu.button == 1)
        {
            menu.rect1.setOutlineColor(sf::Color(245, 245, 245, 128));
            menu.rect2.setOutlineColor(sf::Color(120, 120, 120, 128));
            menu.button = 2;
        }
        else if (menu.button == 2)
        {
            menu.rect2.setOutlineColor(sf::Color(245, 245, 245, 128));
            menu.rect3.setOutlineColor(sf::Color(120, 120, 120, 128));
            menu.button = 3;
        }
    }
}

void    exec_game(sf::RenderWindow window)
{
    
}

void    exec_menu()
{
    sf::RenderWindow window(sf::VideoMode(1200, 800), "Zappy");
    Menu    menu;

    menu.music.play();
    while (window.isOpen())
    {
        sf::Event event;

        while (window.pollEvent(event))
        {
            if (event.type == sf::Event::Closed)
                window.close();
            if (event.type == sf::Event::KeyPressed)
            {
                if (sf::Keyboard::isKeyPressed(sf::Keyboard::Escape))
                    window.close();
                else if (sf::Keyboard::isKeyPressed(sf::Keyboard::Up))
                    buttonSwitcher(0, menu);
                else if (sf::Keyboard::isKeyPressed(sf::Keyboard::Down))
                    buttonSwitcher(1, menu);
                // else if (sf::Keyboard::isKeyPressed(sf::Keyboard::Return) && button == 3)
                //     exec_game(window);
            }
            if (event.type == sf::Event::TextEntered)
            {
                std::cout << event.text.unicode << std::endl;
                if (event.text.unicode >= 46 && event.text.unicode <= 58 && menu.button == 1 && menu.ip.size() < 16)
                    menu.ip.push_back(static_cast<char>(event.text.unicode));
                else if (event.text.unicode >= 33 && event.text.unicode < 127 && menu.button == 2 && menu.hostname.size() < 12)
                    menu.hostname.push_back(static_cast<char>(event.text.unicode));
                else if (event.text.unicode == 8 && menu.button == 1 && menu.ip.size() > 0)
                    menu.ip.pop_back();
                else if (event.text.unicode == 8 && menu.button == 2  && menu.hostname.size() > 0)
                    menu.hostname.pop_back();
            }
        }
        menu.textIp.setString(menu.ip);
        menu.textHost.setString(menu.hostname);
        window.clear();
        window.draw(menu.spriteBack);
        window.draw(menu.rect1);
        window.draw(menu.rect2);
        window.draw(menu.rect3);
        window.draw(menu.text1);
        window.draw(menu.text2);
        window.draw(menu.text3);
        window.draw(menu.textIp);
        window.draw(menu.textHost);
        window.display();
    }
}

int main()
{
    exec_menu();
    return (0);
}