
#include    <iostream>
#include    <string>
#include    <unistd.h>
#include    <SFML/Graphics.hpp>
#include    "Menu.hh"
#include    "../../md2_test/Src/Render.h"
#include    "../../md2_test/Src/Framework.h"

GLFWwindow* InitWindow(int ScrX, int ScrY);
void    Rendering(GLFWwindow* window);

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

void    exec_game()
{
    // window.close();
    Rendering(InitWindow(1200, 800));
    _exit(0);
}

void    exec_menu()
{
<<<<<<< HEAD
    sf::RenderWindow window(sf::VideoMode(1200, 800), "Zappy");
    Menu    menu;
=======
     // sf::RenderWindow window(sf::VideoMode(1200, 800), "Zappy");
    // Menu    menu;
>>>>>>> a97ab559803ea7a49e7619517db3a206b2f38313

    menu.music.play();
    while (window.isOpen())
    {
        sf::Event event;

<<<<<<< HEAD
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
                else if (sf::Keyboard::isKeyPressed(sf::Keyboard::Return) && menu.button == 3)
                    exec_game(window);
            }
            if (event.type == sf::Event::TextEntered)
            {
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
=======
    //     while (window.pollEvent(event))
    //     {
    //         if (event.type == sf::Event::Closed)
    //             window.close();
    //         if (event.type == sf::Event::KeyPressed)
    //         {
    //             if (sf::Keyboard::isKeyPressed(sf::Keyboard::Escape))
    //                 window.close();
    //             else if (sf::Keyboard::isKeyPressed(sf::Keyboard::Up))
    //                 buttonSwitcher(0, menu);
    //             else if (sf::Keyboard::isKeyPressed(sf::Keyboard::Down))
    //                 buttonSwitcher(1, menu);
    //             else if (sf::Keyboard::isKeyPressed(sf::Keyboard::Return) && menu.button == 3)
    exec_game();
    //         }
    //         if (event.type == sf::Event::TextEntered)
    //         {
    //             if (event.text.unicode >= 46 && event.text.unicode <= 58 && menu.button == 1 && menu.ip.size() < 16)
    //                 menu.ip.push_back(static_cast<char>(event.text.unicode));
    //             else if (event.text.unicode >= 33 && event.text.unicode < 127 && menu.button == 2 && menu.hostname.size() < 12)
    //                 menu.hostname.push_back(static_cast<char>(event.text.unicode));
    //             else if (event.text.unicode == 8 && menu.button == 1 && menu.ip.size() > 0)
    //                 menu.ip.pop_back();
    //             else if (event.text.unicode == 8 && menu.button == 2  && menu.hostname.size() > 0)
    //                 menu.hostname.pop_back();
    //         }
    //     }
    //     menu.textIp.setString(menu.ip);
    //     menu.textHost.setString(menu.hostname);
    //     window.clear();
    //     window.draw(menu.spriteBack);
    //     window.draw(menu.rect1);
    //     window.draw(menu.rect2);
    //     window.draw(menu.rect3);
    //     window.draw(menu.text1);
    //     window.draw(menu.text2);
    //     window.draw(menu.text3);
    //     window.draw(menu.textIp);
    //     window.draw(menu.textHost);
    //     window.display();
    // }
>>>>>>> a97ab559803ea7a49e7619517db3a206b2f38313
}

int main()
{
    exec_menu();
    return (0);
}