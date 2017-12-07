#include <cassert>

#include "EventLoop.h"

EventLoop& EventLoop::redrawFrame()
{
	window.clear();
	window.draw(background);
	window.draw(ship);
	window.display();

	return *this;
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
		case sf::Event::KeyPressed:
		{
			switch (event.key.code)
			{
			case sf::Keyboard::Left:
				ship.direction = -1 * ANGULAR_VELOCITY;
				break;
			case sf::Keyboard::Right:
				ship.direction = ANGULAR_VELOCITY;
				break;
			case sf::Keyboard::Up:
				ship.thrust = THRUST;
				ship.showFlame = true;
				break;
			default:
				break;
			}
			break;
		}
		case sf::Event::KeyReleased:
			switch (event.key.code)
			{
			case sf::Keyboard::Up:
				ship.thrust = 0.f;
				ship.showFlame = false;
				break;
			case sf::Keyboard::Left:
			case sf::Keyboard::Right:
				ship.direction = 0.f;
				break;
			default:
				break;
			}
			break;
		default:
			break;
		}
	}

	return *this;
}

EventLoop& EventLoop::update(const float deltaTime)
{
	ship.update(deltaTime);
	return *this;
}

EventLoop& EventLoop::init()
{
	ship.setPosition(WINDOW_WIDTH / 2, WINDOW_HEIGHT / 2);
	assert(backgroundTexture.loadFromFile(BACKGOUND_PATH));
	backgroundTexture.setSmooth(true);
	background.setTexture(backgroundTexture);
	background.setScale(WINDOW_WIDTH / background.getLocalBounds().width,
		WINDOW_HEIGHT / background.getLocalBounds().height);
	return *this;
}

EventLoop::EventLoop(Ship& ship)
	: ship(ship)
{
}
