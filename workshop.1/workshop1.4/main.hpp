#include <SFML/Graphics.hpp>
#include <SFML/System.hpp>
#include <SFML/Window.hpp>
#include <cmath>
#include <string>

#ifdef _WIN32

#include <windows.h>

#endif

static const unsigned WINDOW_WIDTH = 800;
static const unsigned WINDOW_HEIGHT = 600;
static const std::string WINDOW_TITLE = "Kitty++";
static const unsigned MAX_FPS = 60;
static const sf::Color BACKGROUND_COLOR = sf::Color(255, 255, 255);

struct Pointer
{
	const std::string SPRITE_PATH = "./img/pointer.png";

	sf::Texture texture;
	sf::Sprite sprite;

	sf::Vector2f position;
	sf::Vector2f scale;

	void updatePosition(sf::Vector2f& mousePosition);

	void updateElement();
};

struct Kitty
{
	const std::string SPRITE_PATH = "./img/kitty.png";

	sf::Texture texture;
	sf::Sprite sprite;

	sf::Vector2f position;
	sf::Vector2f scale;

	void updatePosition(sf::Vector2f delta, float deltaTime);

	void updateElement();
};

void init(Kitty& kitty, Pointer& pointer);

void onMouseClick(const sf::Event::MouseButtonEvent& event, sf::Vector2f& mousePosition, Pointer& pointer);

void pollEvents(sf::RenderWindow& window, sf::Vector2f& mousePosition, Pointer& pointer);

void update(sf::Vector2f& mousePosition, Kitty& kitty, Pointer& pointer, float deltaTime);

void redrawFrame(sf::RenderWindow& window, Kitty& kitty, Pointer& pointer);

float toDegrees(float radians);