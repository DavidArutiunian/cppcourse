#include <cassert>
#include <cmath>

#include "Line.h"

void Line::draw(sf::RenderTarget& target, const sf::RenderStates states) const
{
	sf::Vertex buffer[std::size(vertex)] = { vertex.front(), vertex.back() };
	target.draw(buffer, std::size(vertex), sf::Lines, states);
}

Line::Line(VertexArray& line)
	: vertex(line)
{
	assert(std::size(line) == std::size(vertex));
}

float Line::length()
{
	const sf::Vector2f delta = vertex.back().position - vertex.front().position;
	auto length = static_cast<float>(std::pow(std::pow(delta.x, 2) + std::pow(delta.y, 2), 0.5));
	assert(length > 0);
	return length;
}

VertexArray* Line::getVertex()
{
	return &vertex;
}

void Line::setEndPosition(const sf::Vector2f& nextPosition)
{
	vertex.back().position = nextPosition;
}