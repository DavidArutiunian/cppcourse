#include <SFML/System.hpp>
#include <SFML/Window.hpp>
#include <SFML/Graphics.hpp>
#include <cmath>
#include <iostream>

#define MAX_ANGULAR_VELOCITY 15.f
#define WINDOW_WIDTH 800
#define WINDOW_HEIGHT 600
#define WINDOW_TITLE "Pointer follows mouse with limited speed (15 deg/sec)"
#define POINTER_COLOR sf::Color(255, 152, 0)
#define BACKGROUND_COLOR sf::Color(33, 33, 33)

void init(sf::ConvexShape &pointer, sf::RectangleShape &background);

float toDegrees(float radians);

void onMouseMove(const sf::Event::MouseMoveEvent &event, sf::Vector2f &mousePosition);

void pollEvents(sf::RenderWindow &window, sf::Vector2f &mousePosition);

void update(const sf::Vector2f &mousePosition, sf::ConvexShape &pointer, float deltaTime);

void redrawFrame(sf::RenderWindow &window, sf::ConvexShape &pointer, sf::RectangleShape &background);