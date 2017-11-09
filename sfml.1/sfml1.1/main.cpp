#include <SFML/Graphics.hpp>
#include <SFML/System.hpp>
#include <SFML/Window.hpp>

int main()
{
	float offset = 20.f;
	float circleRadius = 80.f;

	float width = (2 * circleRadius + 2 * offset);
	float height = (6 * circleRadius + 4 * offset);

	auto videoWidth = static_cast<unsigned>(width + offset);
	auto videoHeight = static_cast<unsigned>(height + offset);

	sf::RectangleShape backgroundRect;
	sf::CircleShape greenCircle(circleRadius);
	sf::CircleShape yellowCircle(circleRadius);
	sf::CircleShape redCircle(circleRadius);

	backgroundRect.setPosition({ offset / 2, offset / 2 });
	backgroundRect.setSize({ width, height });
	backgroundRect.setFillColor(sf::Color(0x67, 0x67, 0x67));

	greenCircle.setPosition({ offset + offset / 2, offset + offset / 2 });
	greenCircle.setFillColor(sf::Color(0, 0xE1, 0xF));

	yellowCircle.setPosition({ offset + offset / 2, 2 * offset + 2 * circleRadius + offset / 2 });
	yellowCircle.setFillColor(sf::Color(0xFF, 0xCC, 0x26));

	redCircle.setPosition({ offset + offset / 2, 3 * offset + 4 * circleRadius + offset / 2 });
	redCircle.setFillColor(sf::Color(0xF2, 0, 0));

	sf::VideoMode videoMode = sf::VideoMode({ videoWidth, videoHeight });

	sf::RenderWindow window(videoMode, "Traffic Light");

	window.clear();

	window.draw(backgroundRect);
	window.draw(greenCircle);
	window.draw(yellowCircle);
	window.draw(redCircle);

	window.display();

	sf::sleep(sf::seconds(5));
}