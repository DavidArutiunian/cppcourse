#include <cassert>

#include "EventLoop.h"

void EventLoop::init()
{
	VertexArray* vertex = line.getVertex();

	assert(vertex != nullptr);

	vertex->front().position = { WINDOW_WIDTH / 2, WINDOW_HEIGHT / 2 };
	vertex->back().position = { WINDOW_WIDTH / 2, WINDOW_HEIGHT / 2 };

	vertex->front().color = sf::Color::Black;
	vertex->back().color = sf::Color::Black;
}

sf::RenderWindow& EventLoop::createWindow()
{
	sf::ContextSettings settings;
	settings.antialiasingLevel = ANTIALIASING_LEVEL;
	window.create(sf::VideoMode(WINDOW_WIDTH, WINDOW_HEIGHT),
		WINDOW_TITLE,
		sf::Style::Default,
		settings);
	window.setFramerateLimit(MAX_FPS);

	return window;
}

EventLoop& EventLoop::redrawFrame()
{
	window.clear(sf::Color::White);
	window.draw(line);
	window.display();

	return *this;
}

EventLoop& EventLoop::pollEvents()
{
	sf::Event event{};
	while (window.pollEvent(event))
	{
		switch (event.type)
		{
		case sf::Event::Closed:
			window.close();
			break;
		case sf::Event::MouseMoved:
		{
			const sf::Vector2i position = sf::Mouse::getPosition(window);
			mousePosition = { static_cast<float>(position.x), static_cast<float>(position.y) };
			printLength();
			break;
		}
		default:
			break;
		}
	}

	return *this;
}

EventLoop& EventLoop::update()
{
	line.setEndPosition({ mousePosition.x, mousePosition.y });

	return *this;
}

EventLoop::EventLoop(Line& line)
	: line(line)
{
}

void EventLoop::printLength()
{
	printf("Line length: %f\n", line.length());
}
