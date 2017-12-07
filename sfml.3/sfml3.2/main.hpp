#include <SFML/Graphics.hpp>
#include <SFML/System.hpp>
#include <SFML/Window.hpp>
#include <cmath>
#include <string>

static const unsigned WINDOW_WIDTH = 800;
static const unsigned WINDOW_HEIGHT = 600;
static const std::string WINDOW_TITLE = "Looking Eyes";
static const unsigned MAX_FPS = 60;
static const unsigned ANTIALIASING_LEVEL = 8;

struct Eye
{
	sf::ConvexShape back;
	sf::ConvexShape orb;

	const size_t pointCount = 200;
	const sf::Vector2f radius = { 50.f, 80.f };
	const sf::Color eyeColor = sf::Color(255, 255, 255);
	const sf::Color orbColor = sf::Color(0, 0, 0);
	float rotation = 0.f;
	sf::Vector2f position;

	void setPoints();

	void updateElement();
};

void init(Eye& leftEye, Eye& rightEye);

sf::Vector2f toEuclidian(float a, float b, float angle);

void onMouseMove(const sf::Event::MouseMoveEvent& event, sf::Vector2f& mousePosition);

void pollEvents(sf::RenderWindow& window, sf::Vector2f& mousePosition);

void update(const sf::Vector2f& mousePosition, Eye& leftEye, Eye& rightEye);

void redrawFrame(sf::RenderWindow& window, Eye& leftEye, Eye& rightEye);