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
	text->setFillColor(sf::Color::Black);
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

void Overlay::updateOverlay(sf::RenderWindow& window, const float value) const
{
	text->setString(std::to_string(static_cast<int>(value)));
	sf::Vector2f absolutePosition = window.mapPixelToCoords({ static_cast<int>(FPS_MARGIN.x),
		static_cast<int>(FPS_MARGIN.y) });
	// Prevent rendering overlay in center of viewport of first frame
	if (absolutePosition.x == FPS_MARGIN.x && absolutePosition.y == FPS_MARGIN.y)
	{
		absolutePosition.x -= WINDOW_WIDTH / 2;
		absolutePosition.y -= WINDOW_HEIGHT / 2;
	}
	text->setPosition(absolutePosition);
}
