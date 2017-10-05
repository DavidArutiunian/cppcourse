#include <SFML/Graphics.hpp>
#include <SFML/System.hpp>
#include <SFML/Window.hpp>
#include <cmath>
#include <windows.h>

#define WINDOW_WIDTH 800
#define WINDOW_HEIGHT 600
#define WINDOW_TITLE "Looking Eyes v2.0"
#define MAX_FPS 60
#define ANTIALIASING_LEVEL 8
#define BACKGROUND_COLOR sf::Color(255, 255, 255)

struct Arrow
{
	sf::ConvexShape shape;

	const unsigned pointCount = 7;
	const unsigned int outlineThickness = 2;
	sf::Color outlineColor = sf::Color(0, 0, 0);
	sf::Color arrowColor = sf::Color(255, 255, 0);

	float rotation = 0;
	sf::Vector2f position;

	void setPoints();

	void updateElement();
};

void init(Arrow& arrow);

float toDegrees(float radians);

double checkElipseIntersection(const sf::Vector2f& mousePosition, const sf::Vector2f& position, float a, float b);

sf::Vector2f toEuclidian(float a, float b, float angle);

void onMouseMove(const sf::Event::MouseMoveEvent& event, sf::Vector2f& mousePosition);

void pollEvents(sf::RenderWindow& window, sf::Vector2f& mousePosition);

void update(const sf::Vector2f& mousePosition, Arrow& arrow);

void redrawFrame(sf::RenderWindow& window, Arrow& arrow);