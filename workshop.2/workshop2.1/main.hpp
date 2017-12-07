#include <SFML/Graphics.hpp>
#include <SFML/System.hpp>
#include <SFML/Window.hpp>

#include <vector>

static const unsigned BALLS_COUNT = 4;
static const std::string WINDOW_TITLE = "Moving Balls";
static const unsigned ANTIALIASING_LEVEL = 8;
static const unsigned MAX_FPS = 60;
static const unsigned WINDOW_WIDTH = 800;
static const unsigned WINDOW_HEIGHT = 600;

struct Ball
{
	sf::CircleShape shape;
	sf::Vector2f position;

	float size;
	sf::Vector2f speed;
	sf::Color color;

	void updatePosition(float deltaTime);

	void updateElement();

	static void init(std::vector<Ball>& balls);
};

void init(std::vector<Ball>& balls);

void pollEvents(sf::RenderWindow& window);

void update(std::vector<Ball>& balls, float deltaTime);

void redrawFrame(sf::RenderWindow& window, std::vector<Ball>& balls);