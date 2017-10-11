#include <SFML/Graphics.hpp>
#include <SFML/System.hpp>
#include <SFML/Window.hpp>
#include <cmath>
#include <windows.h>

#define WINDOW_WIDTH 800
#define WINDOW_HEIGHT 600
#define WINDOW_TITLE "Kitty++"
#define MAX_FPS 60
#define BACKGROUND_COLOR sf::Color(255, 255, 255)

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