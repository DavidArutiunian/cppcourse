#include "Ball.h"

#include "main.h"

void Ball::draw(sf::RenderTarget& target, sf::RenderStates states) const
{
	target.draw(*shape, states);
	target.draw(*text, states);
}

void Ball::init(float radius,
	std::string string,
	sf::Color backgroundColor,
	sf::Color outlineColor,
	float thickness,
	unsigned int fontSize)
{
	assert(radius > 0);
	assert(string.length() > 0);

	this->radius = radius;
	this->string = std::move(string);
	this->backgroundColor = backgroundColor;
	this->outlineColor = outlineColor;
	this->thickness = thickness;
	this->fontSize = fontSize;

	initShape();
	initText();
}

void Ball::initShape()
{
	assert(WINDOW_WIDTH > 0);
	assert(WINDOW_HEIGHT > 0);

	shape = new sf::CircleShape(radius, pointCount);
	shape->setFillColor(backgroundColor);
	shape->setOutlineColor(outlineColor);
	shape->setOutlineThickness(thickness);
	shape->setOrigin(radius, radius);
	shape->setPosition(WINDOW_WIDTH / 2, WINDOW_HEIGHT - (radius + thickness));
}

void Ball::initText()
{
	sf::Font font;
	font.loadFromFile(FONT_PATH);
	if (!font.loadFromFile(FONT_PATH))
	{
		throw std::runtime_error("Error while loading fonts in path " + FONT_PATH);
	}

	text->setFont(font);
	text->setString(string);
	text->setCharacterSize(fontSize);
	text->setFillColor(sf::Color::Black);
	sf::Vector2f textPosition = { shape->getPosition().x, shape->getPosition().y };
	text->setPosition(textPosition);
}

Ball::Ball()
	= default;
