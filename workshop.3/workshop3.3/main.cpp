#include <SFML/Graphics.hpp>

#include "EventLoop.h"

int main()
{
	VertexArray vertex;
	Line line(vertex);

	EventLoop eventLoop(line);
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