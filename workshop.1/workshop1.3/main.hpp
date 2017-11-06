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
static const std::string WINDOW_TITLE = "Kitty";
static const unsigned MAX_FPS = 60;
static const sf::Color BACKGROUND_COLOR = sf::Color(255, 255, 255);
static const std::string SPRITE_PATH = "./img/kitty.png";