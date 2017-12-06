#include <cmath>

#include "Ship.h"

void Ship::update()
{
	if (showFlame)
	{
		burnShape.setScale(1.f, 1.f);
	}
	else
	{
		burnShape.setScale(0.f, 0.f);
	}

	rotation += direction;
	shipShape.setRotation(rotation);
	burnShape.setRotation(rotation);

	const auto angle = static_cast<float>(rotation * M_PI / 180);
	const sf::Vector2f deltaVelocity = { std::cos(angle) * thrust, std::sin(angle) * thrust };
	velocity += deltaVelocity;
	position += velocity;

	checkCollision();

	shipShape.setPosition(position);
	burnShape.setPosition(position);
}

void Ship::draw(sf::RenderTarget& target, sf::RenderStates states) const
{
	states.transform *= getTransform();
	target.draw(burnShape, states);
	target.draw(shipShape, states);
}

Ship::Ship()
{
	shipShape.setPointCount(SHIP_POINT_COUNT);
	shipShape.setFillColor(sf::Color::Black);
	shipShape.setOutlineThickness(OUTLINE_THICKNESS);
	shipShape.setOutlineColor(sf::Color::White);
	shipShape.setOrigin(position);

	shipShape.setPoint(0, position + sf::Vector2f(-20.f, -20.f));
	shipShape.setPoint(1, position + sf::Vector2f(20.f, 0.f));
	shipShape.setPoint(2, position + sf::Vector2f(-20.f, 20.f));
	shipShape.setPoint(3, position + sf::Vector2f(-10.f, 0.f));

	burnShape.setPointCount(SHIP_POINT_COUNT);
	burnShape.setFillColor(sf::Color::Red);
	burnShape.setOutlineThickness(OUTLINE_THICKNESS);
	burnShape.setOutlineColor(sf::Color::Yellow);
	burnShape.setOrigin(position);

	burnShape.setPoint(0, position + sf::Vector2f(-25.f, 0.f));
	burnShape.setPoint(1, position + sf::Vector2f(-7.5f, -7.5f));
	burnShape.setPoint(3, position + sf::Vector2f(-7.5f, 7.5f));
	burnShape.setPoint(4, position);
}

void Ship::checkCollision()
{
	if ((position.x >= WINDOW_WIDTH / 2) && (velocity.x > 0))
	{
		position.x = -1 * static_cast<float>(WINDOW_WIDTH) / 2;
	}
	if ((position.x < -1 * static_cast<float>(WINDOW_WIDTH) / 2) && (velocity.x < 0.f))
	{
		position.x = WINDOW_WIDTH / 2;
	}
	if ((position.y >= WINDOW_HEIGHT / 2) && (velocity.y > 0))
	{
		position.y = -1 * static_cast<float>(WINDOW_HEIGHT) / 2;
	}
	if ((position.y < -1 * static_cast<float>(WINDOW_WIDTH) / 2) && (velocity.y < 0))
	{
		position.y = WINDOW_HEIGHT / 2;
	}
}
