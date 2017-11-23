#include <cassert>

#include "Overlay.h"
#include "consts.h"

void Overlay::initFont() const
{
	assert(font->loadFromFile(FONT_PATH));
}

void Overlay::initText() const
{
	text->setFont(*font.get());
	text->setCharacterSize(FONT_SIZE);
	text->setFillColor(sf::Color::White);
	text->setPosition(FPS_MARGIN.x, FPS_MARGIN.y);
}

Overlay::Overlay()
{
	initFont();
	initText();
}

void Overlay::draw(sf::RenderTarget& target, const sf::RenderStates states) const
{
	target.draw(*text.get(), states);
}

void Overlay::updateOverlay(const float value) const
{
	text->setString(std::to_string(static_cast<int>(value)));
}
