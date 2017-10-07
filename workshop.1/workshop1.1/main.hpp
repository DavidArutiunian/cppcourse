#include <SFML/Graphics.hpp>
#include <SFML/System.hpp>
#include <SFML/Window.hpp>
#include <cmath>
#include <windows.h>

#define WINDOW_WIDTH 800
#define WINDOW_HEIGHT 600
#define WINDOW_TITLE "Arrow"
#define MAX_FPS 60
#define ANTIALIASING_LEVEL 8
#define BACKGROUND_COLOR sf::Color(255, 255, 255)
#define ARROW_COLOR sf::Color(255, 255, 0)
#define OUTLINE_COLOR sf::Color(0, 0, 0)