#include "consts.h"

void FPS::initFont()
{
	assert(font->loadFromFile(FONT_PATH.data()));
}

void FPS::initText()
{
	text->setFont(*font.get());
	text->setCharacterSize(FONT_SIZE);
	text->setFillColor(sf::Color::White);
	text->setPosition(FPS_MARGIN.x, FPS_MARGIN.y);
}

FPS::FPS()
{
	initFont();
	initText();
}

void FPS::draw(sf::RenderTarget& target, const sf::RenderStates states) const
{
	target.draw(*text.get(), states);
}

void FPS::updateFps(const float nextFps)
{
	text->setString(std::to_string(static_cast<int>(nextFps)));
}
