#include "Ball.h"
#include "main.h"

void Ball::draw(sf::RenderTarget& target, sf::RenderStates states) const
{
	target.draw(circle, states);
	target.draw(text, states);
}

void Ball::init(float radius,
	float outlineThickness,
	unsigned fontSize,
	std::string initials,
	sf::Color backgroundColor,
	sf::Color outlineColor)
{
	this->radius = radius;
	this->initials = std::move(initials);
	this->backgroundColor = backgroundColor;
	this->outlineColor = outlineColor;
	this->outlineThickness = outlineThickness;
	this->fontSize = fontSize;

	initCircle();
	initText();
}

void Ball::initCircle()
{
	assert(radius > 0);

	circle.setRadius(radius);
	circle.setPointCount(pointCount);
	circle.setFillColor(backgroundColor);
	circle.setOutlineColor(outlineColor);
	circle.setOutlineThickness(outlineThickness);
	circle.setOrigin(radius, radius);
	circle.setPosition(WINDOW_WIDTH / 2, WINDOW_HEIGHT - (radius + outlineThickness));
}

void Ball::initText()
{
	assert(initials.length() > 0);
	assert(font.loadFromFile(FONT_PATH));

	text.setFont(font);
	text.setString(initials);
	text.setCharacterSize(fontSize);
	text.setFillColor(sf::Color::Black);
	const sf::FloatRect textLocalBounds = text.getLocalBounds();
	text.setOrigin({ textLocalBounds.width / 2, textLocalBounds.height - outlineThickness });
	const sf::Vector2f circlePosition = circle.getPosition();
	text.setPosition({ circlePosition.x, circlePosition.y });
	initialPosition = circlePosition.y;
}

void Ball::updatePosition(float deltaTime)
{
	time += deltaTime * timeAccelerator;
	checkCollision();
	auto nextY = static_cast<float>(initialPosition - initialSpeed * time + 0.5 * G * std::pow(time, 2));
	const sf::Vector2f nextPosition = { circle.getPosition().x, nextY };
	updateCirclePosition(nextPosition);
	updateTextPosition(nextPosition);
}

void Ball::updateTextPosition(const sf::Vector2f& nextPosition)
{
	text.setPosition(nextPosition);
}

void Ball::updateCirclePosition(const sf::Vector2f& nextPosition)
{
	circle.setPosition(nextPosition);
}

void Ball::checkCollision()
{
	const float currentBottomPosition = circle.getPosition().y + radius + outlineThickness;
	const bool isAtZeroLevel = currentBottomPosition > WINDOW_HEIGHT;
	if (isAtZeroLevel)
	{
		time = 0;
	}
}
