#include <SFML/System.hpp>
#include <SFML/Window.hpp>
#include <SFML/Graphics.hpp>
#include <cmath>

int main()
{
  constexpr unsigned WINDOW_WIDTH = 800;
  constexpr unsigned WINDOW_HEIGHT = 600;
  constexpr float BALL_SIZE = 40;
  constexpr float AMPLITUDE = 80.f;
  constexpr float PERIOD = 1.f;

  float speed = 500.f;
  float time = 0;

  sf::RenderWindow window(sf::VideoMode(WINDOW_WIDTH, WINDOW_HEIGHT), "Wave Moving Ball 2");
  sf::Clock clock;

  sf::Vector2f position = {0, window.getSize().y / 2 - AMPLITUDE / 2};

  sf::CircleShape shape(BALL_SIZE);
  shape.setFillColor(sf::Color(0xFF, 0xFF, 0xFF));

  while (window.isOpen())
  {
    sf::Event event{};
    while (window.pollEvent(event))
    {
      if (event.type == sf::Event::Closed)
      {
        window.close();
      }
    }

    const float deltaTime = clock.restart().asSeconds();

    time = time + deltaTime;

    const float wavePhase = time * static_cast<float>(2 * M_PI);
    const float x = x + speed * deltaTime;
    const float y = AMPLITUDE * std::sin(wavePhase / PERIOD);
    const sf::Vector2f offset = {x, y};

    if ((x + 2 * BALL_SIZE >= WINDOW_WIDTH) && (speed > 0))
    {
      speed = -speed;
    }
    if ((x < 0) && (speed < 0))
    {
      speed = -speed;
    }

    shape.setPosition(position + offset);

    window.clear();
    window.draw(shape);
    window.display();
  }
}