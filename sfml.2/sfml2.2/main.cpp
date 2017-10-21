#include <SFML/Graphics.hpp>
#include <SFML/System.hpp>
#include <SFML/Window.hpp>
#include <cmath>

int main()
{
	constexpr unsigned WINDOW_WIDTH = 800;
	constexpr unsigned WINDOW_HEIGHT = 600;
	constexpr unsigned DEFAULT_RADIUS = 150;
	constexpr unsigned POINT_COUNT = 200;
	constexpr float AMPLITUDE = 80.f;
	constexpr float PERIOD = 2.f;

	float time = 0;

	sf::ContextSettings settings;
	settings.antialiasingLevel = 8;

	sf::RenderWindow window(sf::VideoMode(WINDOW_WIDTH, WINDOW_HEIGHT), "Polar Rose", sf::Style::Default, settings);
	sf::Clock clock;

	sf::Vector2f position = { static_cast<float>(WINDOW_WIDTH / 2), static_cast<float>(WINDOW_HEIGHT / 2) };

	sf::ConvexShape shape;
	shape.setFillColor(sf::Color(0xFF, 0x9, 0x80));

	shape.setPointCount(POINT_COUNT);
	for (int i = 0; i < POINT_COUNT; ++i)
	{
		float angle = static_cast<float>(2 * M_PI * i) / static_cast<float>(POINT_COUNT);
		float RADIUS = DEFAULT_RADIUS * std::sin(6 * angle);
		sf::Vector2f point = sf::Vector2f{ RADIUS * std::sin(angle), RADIUS * std::cos(angle) };
		shape.setPoint(static_cast<size_t>(i), point);
	}

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

		const float deltaTime = clock.restart().asSeconds();

		time = time + deltaTime;

		const float wavePhase = time * static_cast<float>(2 * M_PI);
		const float x = DEFAULT_RADIUS * std::cos(wavePhase / PERIOD);
		const float y = DEFAULT_RADIUS * std::sin(wavePhase / PERIOD);
		const sf::Vector2f offset = { x, y };

		shape.setPosition(position + offset);

		window.clear();
		window.draw(shape);
		window.display();
	}
}