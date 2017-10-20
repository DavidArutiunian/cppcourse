#include "main.hpp"

int main()
{
#ifdef _WIN32
  ShowWindow(GetConsoleWindow(), SW_HIDE);
#endif

  sf::ContextSettings settings;
  settings.antialiasingLevel = ANTIALIASING_LEVEL;
  sf::RenderWindow window(sf::VideoMode(WINDOW_WIDTH, WINDOW_HEIGHT), WINDOW_TITLE, sf::Style::Default, settings);
  window.setFramerateLimit(MAX_FPS);

  sf::Clock clock;

  std::vector<Ball> balls(BALLS_COUNT, Ball());

  Ball::init(balls);

  init(balls);

  while (window.isOpen())
  {
    pollEvents(window);
    float deltaTime = clock.restart().asSeconds();
    update(balls, deltaTime);
    redrawFrame(window, balls);
  }
}

void init(std::vector<Ball> &balls)
{
  for (auto &&ball : balls)
  {
    ball.shape.setRadius(ball.size);
    ball.shape.setFillColor(ball.color);
  }
}

void pollEvents(sf::RenderWindow &window)
{
  sf::Event event{};
  while (window.pollEvent(event))
  {
    switch (event.type)
    {
      case sf::Event::Closed:
        window.close();
        break;
      default:
        break;
    }
  }
}

void update(std::vector<Ball> &balls, float deltaTime)
{
  for (auto &&ball : balls)
  {
    Ball::checkCollisions(balls, deltaTime);
    ball.updatePosition(deltaTime);
    ball.updateElement();
  }
}

void redrawFrame(sf::RenderWindow &window, std::vector<Ball> &balls)
{
  window.clear();
  for (auto &&ball : balls)
  {
    window.draw(ball.shape);
  }
  window.display();
}
