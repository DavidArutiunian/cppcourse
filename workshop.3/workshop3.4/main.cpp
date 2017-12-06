#include <SFML/Graphics.hpp>

#include "EventLoop.h"

int main()
{
	Ship ship;
	EventLoop eventLoop(ship);
	eventLoop.init();

	sf::RenderWindow& window = eventLoop.createWindow();

	while (window.isOpen())
	{
		eventLoop
			.update()
			.pollEvents()
			.redrawFrame();
	}
}
