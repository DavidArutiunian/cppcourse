#include <SFML/Graphics.hpp>
#include <SFML/Window.hpp>
#include <cmath>

int main()
{
  constexpr int pointCount = 200;
  const sf::Vector2f elipseRadius = {200.f, 80.f};

  sf::ContextSettings settings;
  settings.antialiasingLevel = 8;

  sf::RenderWindow window(sf::VideoMode({800, 600}), "Elipse", sf::Style::Default, settings);

  sf::ConvexShape elipse;
  elipse.setPosition({400, 300});
  elipse.setFillColor(sf::Color(0xFF, 0xFF, 0xFF));

  elipse.setPointCount(pointCount);
  for (int pointNo = 0; pointNo < pointCount; ++pointNo)
  {
    float angle = float(2 * M_PI * pointNo) / float(pointCount);
    sf::Vector2f point = sf::Vector2f{
        elipseRadius.x * std::sin(angle),
        elipseRadius.y * std::cos(angle)};
    elipse.setPoint(pointNo, point);
  }

  while (window.isOpen())
  {
    sf::Event event;
    while (window.pollEvent(event))
    {
      if (event.type == sf::Event::Closed)
      {
        window.close();
      }
    }

    window.clear();
    window.draw(elipse);
    window.display();
  }
}