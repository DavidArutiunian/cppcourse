#include "main.hpp"

int main()
{
	sf::ContextSettings settings;
	settings.antialiasingLevel = ANTIALIASING_LEVEL;
	sf::RenderWindow window(sf::VideoMode(WINDOW_WIDTH, WINDOW_HEIGHT), WINDOW_TITLE, sf::Style::Default, settings);
	window.setFramerateLimit(MAX_FPS);

	sf::ConvexShape arrow;
	arrow.setPosition(WINDOW_WIDTH / 2, WINDOW_HEIGHT / 2);
	arrow.setFillColor(ARROW_COLOR);
	arrow.setPointCount(7);
	arrow.setPoint(0, { 0, -40 });
	arrow.setPoint(1, { 40, 0 });
	arrow.setPoint(2, { 20, 0 });
	arrow.setPoint(3, { 20, 40 });
	arrow.setPoint(4, { -20, 40 });
	arrow.setPoint(5, { -20, 0 });
	arrow.setPoint(6, { -40, 0 });
	arrow.setOutlineColor(OUTLINE_COLOR);
	arrow.setOutlineThickness(2);
	arrow.setRotation(10);

	while (window.isOpen())
	{
		sf::Event event{};
		while (window.pollEvent(event))
		{
			if (event.type == sf::Event::Closed)
			{
				window.close();
			}
		}

		window.clear(BACKGROUND_COLOR);
		window.draw(arrow);
		window.display();
	}
}