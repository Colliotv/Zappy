
#include  "Interface.hh"

bool sortByTeam(const player &lhs, const player &rhs) {return lhs.team < rhs.team;}
bool sortByLevel(const player &lhs, const player &rhs) {return lhs.level > rhs.level;}

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

void  Interface::nextPlay(std::vector<player> playerList)
{
  unsigned int n = 0;

  while (n < playerList.size() && playerList[n].nb != curPlay)
    n++;
  if (n < playerList.size() && n + 1 < playerList.size() && playerList[n + 1].team == curTeam)
  {
    curPlay = playerList[n + 1].nb;
    curPos++;
  }
}

void  Interface::prevPlay(std::vector<player> playerList)
{
  unsigned int n = 0;

  while (n < playerList.size() && playerList[n].nb != curPlay)
    n++;
  if (n > 0 && playerList[n - 1].team == curTeam)
  {
    curPlay = playerList[n - 1].nb;
    curPos--;
  }  
}

void  Interface::nextTeam(std::vector<player> playerList)
{
  unsigned int n = 0;

  while (n < playerList.size() && playerList[n].team != curTeam)
    n++;
  while (n < playerList.size() && playerList[n].team == curTeam)
    n++;
  if (n < playerList.size())
  {
    curTeam = playerList[n].team;
    curPlay = playerList[n].nb;
    curPos = 0;
  }
}

void  Interface::prevTeam(std::vector<player> playerList)
{
  unsigned int n = 0;

  while (n < playerList.size() && playerList[n].team != curTeam)
    n++;
  if (n > 0)
  {
    n--;
    curTeam = playerList[n].team;
    while (n > 0 && playerList[n].team == curTeam)
      n--;
    if (n != 0)
      n++;
    curPlay = playerList[n].nb;
    curPos = 0;
  }  
}

void Interface::eventsInterface(sf::RenderWindow &window, std::vector<player> playerList)
{
  sf::Event event;

  while (window.pollEvent(event))
  {
    if (event.type == sf::Event::KeyPressed)
    {
      if (sf::Keyboard::isKeyPressed(sf::Keyboard::Up))
        prevPlay(playerList);
      else if (sf::Keyboard::isKeyPressed(sf::Keyboard::Down))
        nextPlay(playerList);
      else if (sf::Keyboard::isKeyPressed(sf::Keyboard::Right))
        nextTeam(playerList);
      else if (sf::Keyboard::isKeyPressed(sf::Keyboard::Left))
        prevTeam(playerList);
    }
  }
}

void  Interface::initInterface(sf::RenderWindow &window, std::vector<player> playerList)
{
  unsigned int n = 0;

  if (playerList.size() && curPlay == -1)
  {
    curPlay = playerList[0].nb;
    curTeam = playerList[0].team;
    curPos = 0;
  }
  window.clear();
  while (n < 800)
  {
    rect.setPosition(10, n + 10);
    window.draw(rect);
    n+=100;
  }
}

void  Interface::moveCursor(sf::RenderWindow &window)
{
  rect.setFillColor(sf::Color(255, 255, 255, 55));
  rect.setOutlineColor(sf::Color(200, 200, 200, 55));
  rect.setPosition(10, ((curPos + 1) * 100) + 10);
  window.draw(rect);
  rect.setFillColor(sf::Color(200, 200, 200, 128));
  rect.setOutlineColor(sf::Color(120, 120, 120, 128));
}

void  Interface::drawText(sf::RenderWindow &window, std::vector<player> playerList)
{
  unsigned int n = 0, m = 0;

  text.setColor(sf::Color::Red);
  text.setString(curTeam);
  text.setPosition(100, 20);
  window.draw(text);
  text.setString("Fo  Li  De  Si  Me  Ph  Th");
  text.setPosition(20, 55);
  window.draw(text);
  n = 100;
  text.setColor(sf::Color::Green);
  while (m < playerList.size() && playerList[m].team != curTeam)
    m++;
  while (m < playerList.size() && n < 800 && playerList[m].team == curTeam)
  {
    text.setString("Player  " + std::to_string(playerList[m].nb) + "    lvl  " + std::to_string(playerList[m].level));
    text.setPosition(20, n + 20);
    window.draw(text);
    text.setString(std::to_string(playerList[m].food) + "  " + std::to_string(playerList[m].linemate) + "  " + std::to_string(playerList[m].deraumere) + "  " + 
      std::to_string(playerList[m].sibur) + "  " + std::to_string(playerList[m].mendiane) + "  " + std::to_string(playerList[m].phiras) + "  " + std::to_string(playerList[m].thystame));
    text.setPosition(20, n + 55);
    window.draw(text);
    n+=100;
    m++;
  }
}

void  Interface::drawInterface(sf::RenderWindow &window, std::vector<player> playerList)
{
  std::sort(playerList.begin(), playerList.end(), sortByLevel);
  std::sort(playerList.begin(), playerList.end(), sortByTeam);

  initInterface(window, playerList);
  eventsInterface(window, playerList);
  moveCursor(window);
  drawText(window, playerList);
  window.display();
}