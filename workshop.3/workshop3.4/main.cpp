#include <SFML/Graphics.hpp>

#include "EventLoop.h"

int main()
{
	sf::Clock clock;
	Ship ship;
	EventLoop eventLoop(ship);
	eventLoop.init();

	sf::RenderWindow& window = eventLoop.createWindow();

	while (window.isOpen())
	{
		const float deltaTime = clock.restart().asSeconds();
		eventLoop
			.update(deltaTime)
			.pollEvents()
			.redrawFrame();
	}
}
