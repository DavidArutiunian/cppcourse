#include <SFML/Graphics.hpp>
#include <SFML/System.hpp>
#include <SFML/Window.hpp>
#include <cmath>

static const float OFFSET = 20.f;
static const sf::Color COLOR = sf::Color(0xFF, 0xFF, 0xFF);
static const auto WINDOW_WIDTH = static_cast<unsigned>(270 + 2 * OFFSET);
static const auto WINDOW_HEIGHT = static_cast<unsigned>(170 + 2 * OFFSET);

std::vector<sf::Vector2f> calcCubicBezier(
	const sf::Vector2f& start,
	const sf::Vector2f& end,
	const sf::Vector2f& startControl,
	const sf::Vector2f& endControl,
	const size_t numSegments)
{
	std::vector<sf::Vector2f> ret;
	if (!numSegments)
	{
		return ret;
	}

	ret.push_back(start);
	float p = 1.f / numSegments;
	float q = p;
	for (size_t i = 1; i < numSegments; i++, p += q)
	{
		ret.push_back(p * p * p * (end + 3.f * (startControl - endControl) - start) + 3.f * p * p * (start - 2.f * startControl + endControl) + 3.f * p * (startControl - start) + start);
	}
	ret.push_back(end);
	return ret;
}

float calcToDegrees(float deg)
{
	return static_cast<float>(deg * M_PI / 180);
}

void drawDLetter(sf::RenderWindow* window)
{
	sf::RectangleShape d1;
	d1.setSize({ 1, 150 });
	d1.setFillColor(COLOR);
	d1.setPosition({ OFFSET + 120, OFFSET });

	sf::VertexArray d2(sf::LinesStrip, 0);

	std::vector<sf::Vector2f> points = calcCubicBezier(
		sf::Vector2f(OFFSET + 120, OFFSET),
		sf::Vector2f(OFFSET + 120, OFFSET + 150),
		sf::Vector2f(OFFSET + 200, OFFSET + 20),
		sf::Vector2f(OFFSET + 200, OFFSET + 120),
		25);

	for (auto& point : points)
	{
		d2.append(sf::Vertex(point, sf::Color::White));
	}

	window->draw(d1);
	window->draw(d2);
}

void drawALetter(sf::RenderWindow* window)
{
	sf::RectangleShape a1;
	a1.setSize({ 1, std::abs(150 / std::cos(calcToDegrees(15))) });
	a1.setFillColor(COLOR);
	a1.setPosition({ OFFSET + 50, OFFSET });
	a1.setRotation(15);

	sf::RectangleShape a2;
	a2.setSize({ 1, std::abs(150 / std::cos(calcToDegrees(15))) });
	a2.setFillColor(COLOR);
	a2.setPosition({ OFFSET + 50, OFFSET });
	a2.setRotation(-15);

	sf::RectangleShape a3;
	a3.setSize({ std::abs(150 / std::sin(calcToDegrees(75))) / 4, 1 });
	a3.setFillColor(COLOR);
	a3.setPosition({ OFFSET + 50 - std::abs(75 * std::tan(calcToDegrees(15))) + 1, OFFSET + 75 });

	window->draw(a1);
	window->draw(a2);
	window->draw(a3);
}

void drawRLetter(sf::RenderWindow* window)
{
	sf::RectangleShape r1;
	r1.setSize({ 1, 150 });
	r1.setFillColor(COLOR);
	r1.setPosition({ OFFSET + 220, OFFSET });

	sf::VertexArray r2(sf::LinesStrip, 0);

	std::vector<sf::Vector2f> points = calcCubicBezier(
		sf::Vector2f(OFFSET + 220, OFFSET),
		sf::Vector2f(OFFSET + 220, OFFSET + 60),
		sf::Vector2f(OFFSET + 260, OFFSET + 10),
		sf::Vector2f(OFFSET + 260, OFFSET + 50),
		25);

	for (auto& point : points)
	{
		r2.append(sf::Vertex(point, sf::Color::White));
	}

	sf::RectangleShape r3;
	r3.setSize({ 1, std::abs(90 / std::cos(calcToDegrees(20))) });
	r3.setFillColor(COLOR);
	r3.setPosition({ OFFSET + 220, OFFSET + 60 });
	r3.setRotation(-20);

	window->draw(r1);
	window->draw(r2);
	window->draw(r3);
}

int main()
{
	sf::VideoMode videoMode = sf::VideoMode(WINDOW_WIDTH, WINDOW_HEIGHT);

	sf::RenderWindow window(videoMode, "ADR");

	window.clear();

	drawDLetter(&window);
	drawALetter(&window);
	drawRLetter(&window);

	window.display();

	sf::sleep(sf::seconds(5));
}