#include <SFML/Graphics.hpp>
#include <SFML/System.hpp>
#include <SFML/Window.hpp>
#include <cmath>

int main()
{
	constexpr unsigned pointCount = 200;
	const sf::Vector2f elipseRadius = { 200.f, 80.f };

	sf::ContextSettings settings;
	settings.antialiasingLevel = 8;

	sf::RenderWindow window(sf::VideoMode(800, 600), "Elipse", sf::Style::Default, settings);

	sf::ConvexShape elipse;
	elipse.setPosition({ 400, 300 });
	elipse.setFillColor(sf::Color(0xFF, 0xFF, 0xFF));

	elipse.setPointCount(pointCount);
	for (unsigned pointNo = 0; pointNo < pointCount; ++pointNo)
	{
		float angle = static_cast<float>(2 * M_PI * pointNo) / static_cast<float>(pointCount);
		sf::Vector2f point = sf::Vector2f{
			elipseRadius.x * std::sin(angle),
			elipseRadius.y * std::cos(angle)
		};
		elipse.setPoint(static_cast<size_t>(pointNo), point);
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

		window.clear();
		window.draw(elipse);
		window.display();
	}
}