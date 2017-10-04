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

struct Eye
{
	sf::ConvexShape back;
	sf::ConvexShape orb;

	const unsigned int pointCount = 200;
	const sf::Vector2f radius = { 50.f, 80.f };
	const sf::Color eyeColor = sf::Color(255, 255, 255);
	const sf::Color orbColor = sf::Color(0, 0, 0);

	float rotation = 0;
	sf::Vector2f position;

	void setPoints();

	void updateElement();
};

void init(Eye& leftEye, Eye& rightEye);

float toDegrees(float radians);

double checkElipseIntersection(const sf::Vector2f& mousePosition, const sf::Vector2f& position, float a, float b);

sf::Vector2f toEuclidian(float a, float b, float angle);

void onMouseMove(const sf::Event::MouseMoveEvent& event, sf::Vector2f& mousePosition);

void pollEvents(sf::RenderWindow& window, sf::Vector2f& mousePosition);

void update(const sf::Vector2f& mousePosition, Eye& leftEye, Eye& rightEye);

void redrawFrame(sf::RenderWindow& window, Eye& leftEye, Eye& rightEye);