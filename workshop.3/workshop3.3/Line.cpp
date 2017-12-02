#include <cassert>

#include "Line.h"

void Line::draw(sf::RenderTarget &target, sf::RenderStates states) const
{
  target.draw(vertex, 2, sf::LineStrip, states);
}

Line::Line(sf::Vertex line[2])
{
  vertex[0].position = line[0].position;
  vertex[1].position = line[1].position;
}

float Line::length()
{
  const sf::Vector2f delta = vertex[1].position - vertex[0].position;
  return static_cast<float>(std::pow(std::pow(delta.x, 2) + std::pow(delta.y, 2), 0.5));
}

sf::Vertex *Line::getVertex()
{
  return vertex;
}

void Line::setEndPosition(const sf::Vector2f &nextPosition)
{
  vertex[1] = nextPosition;
}