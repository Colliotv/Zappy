
#include  "Interface.hh"

bool sortByTeam(const player &lhs, const player &rhs) {return lhs.team < rhs.team;}
bool sortByLevel(const player &lhs, const player &rhs) {return lhs.level < rhs.level;}

Interface::Interface()
{
  if (!font.loadFromFile("resources/LCD.otf"))
    std::cout << "Error : failed to load font" << std::endl;
  rect.setSize(sf::Vector2f(280, 80));
  rect.setFillColor(sf::Color(200, 200, 200, 128));
  rect.setOutlineThickness(10);
  rect.setOutlineColor(sf::Color(120, 120, 120, 128));
  text.setFont(font);
  text.setCharacterSize(24);
  curPlay = -1;
  curTeam = -1;
}

Interface::~Interface()
{

}

// std::string  nextPlay(int curPlay, std::vector<player> playerList)
// {
//   if ()
// }

// std::string  prevPlay(int curPlay, std::vector<player> playerList)
// {
  
// }

// std::string  nextTeam(std::string curTeam, std::vector<player> playerList)
// {
  
// }

// std::string  prevTeam(std::string curTeam, std::vector<player> playerList)
// {
  
// }

// void Interface::eventsInterface(sf::RenderWindow &window, std::vector<player> playerList)
// {
//   sf::Event event;

//   while (window.pollEvent(event))
//   {
//     if (event.type == sf::Event::KeyPressed)
//     {
//       if (sf::Keyboard::isKeyPressed(sf::Keyboard::Up))
//         curPlay = prevPlay(curPlay, playerList);
//       else if (sf::Keyboard::isKeyPressed(sf::Keyboard::Down))
//         curPlay = nextPlay(curPlay, playerList);
//       else if (sf::Keyboard::isKeyPressed(sf::Keyboard::Right))
//         curTeam = nextTeam(curTeam, playerList);
//       else if (sf::Keyboard::isKeyPressed(sf::Keyboard::Left))
//         curTeam = prevTeam(curTeam, playerList);
//     }
//   }
// }

void  Interface::drawInterface(sf::RenderWindow &window, std::vector<player> playerList)
{
  std::sort(playerList.begin(), playerList.end(), sortByLevel);
  std::sort(playerList.begin(), playerList.end(), sortByTeam);

  int n = 0;
  window.clear();
  // eventsInterface(window, playerList);
  while (n < 800)
  {
    rect.setPosition(10, n + 10);
    window.draw(rect);
    n+=100;
  }
  text.setColor(sf::Color::Red);
  text.setString("Team Zappy");
  text.setPosition(90, 20);
  window.draw(text);
  n = 100;
  text.setColor(sf::Color::Green);
  while (n < 800)
  {
    text.setString("Player name");
    text.setPosition(20, n + 20);
    window.draw(text);
    n+=100;
  }
  window.display();
}