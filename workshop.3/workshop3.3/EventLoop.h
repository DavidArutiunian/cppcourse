#ifndef CPPCOURSE_EVENTLOOP_H
#define CPPCOURSE_EVENTLOOP_H

#include <SFML/Graphics.hpp>
#include <cassert>

#include "Line.h"
#include "consts.h"

class EventLoop
{
private:
  Line line;
  sf::RenderWindow window;
  sf::Vector2f mousePosition;

public:

  explicit EventLoop(Line &line);

  EventLoop &update();

  EventLoop &pollEvents();

  EventLoop &redrawFrame();

  sf::RenderWindow &createWindow();

  void printLength();

  void init();

};


#endif //CPPCOURSE_EVENTLOOP_H
