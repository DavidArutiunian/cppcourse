#include <SFML/Graphics.hpp>

#include "Line.h"
#include "EventLoop.h"

int main()
{
  sf::Vertex vertex[2];
  Line line(vertex);

  EventLoop eventLoop(line);
  eventLoop.init();

  sf::RenderWindow &window = eventLoop.createWindow();

  while (window.isOpen())
  {
    eventLoop
        .update()
        .pollEvents()
        .redrawFrame();
  }
}