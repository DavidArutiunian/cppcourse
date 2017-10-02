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
  if (angle < 0) // TODO: fix 0 degree intersection bug
  {
    angle += 2 * M_PI;
  }
  angle = toDegrees(angle);
  const float maxDegreesPerFrame = MAX_ANGULAR_VELOCITY / 1000 * deltaTime;
  const float degreesPerFrame = std::abs((angle - pointer.getRotation()) / 1000 * deltaTime);
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
  pointer.setPointCount(POINTS_SET.size());
  for (auto iterator = POINTS_SET.begin(); iterator != POINTS_SET.end(); ++iterator)
  {
    const auto index = static_cast<const int>(std::distance(POINTS_SET.begin(), iterator));
    if (index < POINTS_SET.size())
    {
      pointer.setPoint((size_t) index, POINTS_SET.at((unsigned long long int) index));
    }
  }
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