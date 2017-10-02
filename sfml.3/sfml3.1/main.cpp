#include <SFML/System.hpp>
#include <SFML/Window.hpp>
#include <SFML/Graphics.hpp>
#include <cmath>
#include <iostream>
#include "main.hpp"

int main()
{
  constexpr unsigned int WINDOW_WIDTH = 800;
  constexpr unsigned int WINDOW_HEIGHT = 600;

  sf::ContextSettings settings;
  settings.antialiasingLevel = 8;
  sf::RenderWindow window(sf::VideoMode(WINDOW_WIDTH, WINDOW_WIDTH),
                          "Pointer follows mouse",
                          sf::Style::Default,
                          settings);
  window.setFramerateLimit(60);

  sf::ConvexShape pointer;
  sf::Vector2f mousePosition;

  init(pointer);

  while (window.isOpen())
  {
    pollEvents(window, mousePosition);
    update(mousePosition, pointer);
    redrawFrame(window, pointer);
  }
}

void update(const sf::Vector2f &mousePosition, sf::ConvexShape &pointer)
{
  const sf::Vector2f delta = mousePosition - pointer.getPosition();
  auto angle = static_cast<float>(atan2(delta.y, delta.x));
  if (angle < 0.f) // TODO: fix 0 degree intersection bug
  {
    angle += 2 * M_PI;
  }
  angle = toDegrees(angle);
  const float maxDegreesPerFrame = 15.f / 1000.f * 16.f;
  const float degreesPerFrame = std::abs((angle - pointer.getRotation()) / 1000.f * 16.f);
  if (std::ceil(angle) != std::ceil(pointer.getRotation()))
  {
    if (std::ceil(angle) > std::ceil(pointer.getRotation()))
    {
      pointer.setRotation(pointer.getRotation() + std::min(degreesPerFrame, maxDegreesPerFrame));
    }
    else
    {
      pointer.setRotation(pointer.getRotation() - std::min(degreesPerFrame, maxDegreesPerFrame));
    }
  }

  std::cout << "pointer angle=" << pointer.getRotation() << std::endl;
}

void pollEvents(sf::RenderWindow &window, sf::Vector2f &mousePosition)
{
  sf::Event event{};
  while (window.pollEvent(event))
  {
    switch (event.type)
    {
      case sf::Event::Closed:
        window.close();
        break;
      case sf::Event::MouseMoved:
        onMouseMove(event.mouseMove, mousePosition);
        break;
      default:
        break;
    }
  }
}

void onMouseMove(const sf::Event::MouseMoveEvent &event, sf::Vector2f &mousePosition)
{
  mousePosition = {static_cast<float>(event.x), static_cast<float>(event.y)};
}

void redrawFrame(sf::RenderWindow &window, sf::ConvexShape &pointer)
{
  window.clear();
  window.draw(pointer);
  window.display();
}

void init(sf::ConvexShape &pointer)
{
  pointer.setPointCount(3);
  pointer.setPoint(0, {40, 0});
  pointer.setPoint(1, {-20, -20});
  pointer.setPoint(2, {-20, 20});
  pointer.setPosition({400, 300});
  pointer.setFillColor(sf::Color(0xFF, 0x80, 0x00));
}

float toDegrees(float radians)
{
  return static_cast<float>(static_cast<double>(radians) * 180 / M_PI);
}

float toRadians(float degrees)
{
  return static_cast<float>(static_cast<double>(degrees) * M_PI / 180);
}
