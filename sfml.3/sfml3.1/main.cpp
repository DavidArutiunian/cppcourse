#include "main.hpp"

int main()
{
  sf::ContextSettings settings;
  settings.antialiasingLevel = 8;
  sf::RenderWindow window(sf::VideoMode(WINDOW_WIDTH, WINDOW_HEIGHT), WINDOW_TITLE, sf::Style::Default, settings);
  window.setFramerateLimit(60);

  sf::Clock clock;
  sf::ConvexShape pointer;
  sf::RectangleShape background;
  sf::Vector2f mousePosition;

  init(pointer, background);

  while (window.isOpen())
  {
    const float deltaTime = clock.restart().asMilliseconds();
    pollEvents(window, mousePosition);
    update(mousePosition, pointer, deltaTime);
    redrawFrame(window, pointer, background);
  }
}

void update(const sf::Vector2f &mousePosition, sf::ConvexShape &pointer, float deltaTime)
{
  const sf::Vector2f delta = mousePosition - pointer.getPosition();
  auto angle = static_cast<float>(atan2(delta.y, delta.x));
  if (angle < 0.f) // TODO: fix 0 degree intersection bug
  {
    angle += 2 * M_PI;
  }
  angle = toDegrees(angle);
  const float maxDegreesPerFrame = MAX_ANGULAR_VELOCITY / 1000.f * deltaTime;
  const float degreesPerFrame = std::abs((angle - pointer.getRotation()) / 1000.f * deltaTime);
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

void redrawFrame(sf::RenderWindow &window, sf::ConvexShape &pointer, sf::RectangleShape &background)
{
  window.clear();
  window.draw(background);
  window.draw(pointer);
  window.display();
}

void init(sf::ConvexShape &pointer, sf::RectangleShape &background)
{
  pointer.setPointCount(3);
  pointer.setPoint(0, {40, 0});
  pointer.setPoint(1, {-20, -20});
  pointer.setPoint(2, {-20, 20});
  pointer.setPosition(WINDOW_WIDTH / 2, WINDOW_HEIGHT / 2);
  pointer.setFillColor(POINTER_COLOR);

  background.setSize({WINDOW_WIDTH, WINDOW_HEIGHT});
  background.setPosition(0, 0);
  background.setFillColor(BACKGROUND_COLOR);
}

float toDegrees(float radians)
{
  return static_cast<float>(static_cast<double>(radians) * 180 / M_PI);
}
