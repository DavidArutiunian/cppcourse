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
	circle.setFillColor(backgroundColor);
	circle.setOutlineColor(outlineColor);
	circle.setOutlineThickness(outlineThickness);
	circle.setOrigin(radius, radius);
	circle.setPosition(WINDOW_WIDTH / 2, WINDOW_HEIGHT - (radius + outlineThickness));
}

void Ball::initText()
{
	sf::Font font;

	assert(initials.length() > 0);
	assert(font.loadFromFile(FONT_PATH));

	text.setFont(font);
	text.setString(initials);
	text.setCharacterSize(fontSize);
	text.setFillColor(sf::Color::Black);
	text.setPosition({ circle.getPosition().x, circle.getPosition().y });
}

void Ball::updatePosition(float deltaTime)
{
}

void Ball::updateText()
{
}

void Ball::updateCircle()
{
}
