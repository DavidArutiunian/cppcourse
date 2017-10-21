#include <SFML/Graphics.hpp>
#include <SFML/System.hpp>
#include <SFML/Window.hpp>
#include <cmath>
#include <string>
#include <windows.h>

static const unsigned WINDOW_WIDTH = 800;
static const unsigned WINDOW_HEIGHT = 600;
static const std::string WINDOW_TITLE = "Arrow";
static const unsigned MAX_FPS = 60;
static const unsigned ANTIALIASING_LEVEL = 8;
static const sf::Color BACKGROUND_COLOR = sf::Color(255, 255, 255);
static const sf::Color ARROW_COLOR = sf::Color(255, 255, 0);
static const sf::Color OUTLINE_COLOR = sf::Color(0, 0, 0);