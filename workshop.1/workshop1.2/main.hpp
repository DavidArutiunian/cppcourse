#include <SFML/Graphics.hpp>
#include <SFML/System.hpp>
#include <SFML/Window.hpp>
#include <cmath>
#include <string>
#include <windows.h>

static const unsigned WINDOW_WIDTH = 800;
static const unsigned WINDOW_HEIGHT = 600;
static const std::string WINDOW_TITLE = "Arrow++";
static const unsigned MAX_FPS = 60;
static const unsigned ANTIALIASING_LEVEL = 8;
static const sf::Color BACKGROUND_COLOR = sf::Color(255, 255, 255);

struct Arrow
{
	sf::ConvexShape shape;

	const unsigned pointCount = 7;
	const unsigned outlineThickness = 2;
	sf::Color outlineColor = sf::Color(0, 0, 0);
	sf::Color arrowColor = sf::Color(255, 255, 0);

	float rotation = 0;
	sf::Vector2f position;

	void updateRotation(Arrow& arrow, sf::Vector2f delta, float deltaTime);

	void updatePosition(Arrow& arrow, sf::Vector2f delta, float deltaTime);

	void setPoints();

	void updateElement();
};

void init(Arrow& arrow);

float toDegrees(float radians);

void onMouseMove(const sf::Event::MouseMoveEvent& event, sf::Vector2f& mousePosition);

void pollEvents(sf::RenderWindow& window, sf::Vector2f& mousePosition);

void update(sf::Vector2f& mousePosition, Arrow& arrow, float deltaTime);

void redrawFrame(sf::RenderWindow& window, Arrow& arrow);