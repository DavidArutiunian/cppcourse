#include <SFML/Graphics.hpp>
#include <SFML/System.hpp>
#include <SFML/Window.hpp>
#include <algorithm>
#include <cmath>
#include <string>
#include <vector>

static const float MAX_ANGULAR_VELOCITY = 15.f;
static const unsigned WINDOW_WIDTH = 800;
static const unsigned WINDOW_HEIGHT = 600;
static const std::string WINDOW_TITLE = "Pointer follows mouse with limited speed (15 deg/sec)";
static const sf::Color POINTER_COLOR = sf::Color(255, 152, 0);
static const unsigned MAX_FPS = 60;
static const unsigned ANTIALIASING_LEVEL = 8;
static const std::vector<sf::Vector2f> POINTS_SET = { { 40, 0 },
	{ -20, -20 },
	{ -20, 20 } };

void init(sf::ConvexShape& pointer);

float toDegrees(float radians);

void onMouseMove(const sf::Event::MouseMoveEvent& event, sf::Vector2f& mousePosition);

void pollEvents(sf::RenderWindow& window, sf::Vector2f& mousePosition);

void update(const sf::Vector2f& mousePosition, sf::ConvexShape& pointer, float deltaTime);

void redrawFrame(sf::RenderWindow& window, sf::ConvexShape& pointer);