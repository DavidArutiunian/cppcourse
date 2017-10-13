#include <SFML/Graphics.hpp>
#include <SFML/System.hpp>
#include <SFML/Window.hpp>
#include <cmath>
#include <vector>
#include <windows.h>

#define WINDOW_TITLE "Moving Balls v2.0"
#define ANTIALIASING_LEVEL 8
#define MAX_FPS 60
#define WINDOW_WIDTH 800
#define WINDOW_HEIGHT 600

struct Ball
{
	sf::CircleShape shape;
	sf::Vector2f position;

	float size;
	unsigned int id;
	sf::Vector2f speed;
	sf::Color color;

	void updatePosition(float deltaTime);

	void updateElement();

	static void init(std::vector<Ball>& balls);

	static void checkCollisions(std::vector<Ball>& balls);

	bool operator==(Ball& toCompare);
};

void init(std::vector<Ball>& balls);

void pollEvents(sf::RenderWindow& window);

void update(std::vector<Ball>& balls, float deltaTime);

void redrawFrame(sf::RenderWindow& window, std::vector<Ball>& balls);