#ifndef CPPCOURSE_FPS_H
#define CPPCOURSE_FPS_H

#include <SFML/Graphics.hpp>
#include <memory>

class Overlay : public sf::Drawable
{
private:
	std::shared_ptr<sf::Font> font = std::make_shared<sf::Font>(sf::Font());

	std::shared_ptr<sf::Text> text = std::make_shared<sf::Text>(sf::Text());

	////////////////////////////////////////////////////////////
	/// \brief Load fonts from FONT_PATH
	////////////////////////////////////////////////////////////
	void initFont() const;

	////////////////////////////////////////////////////////////
	/// \brief Set text properties
	////////////////////////////////////////////////////////////
	void initText() const;

public:
	Overlay();

	~Overlay() override = default;

	////////////////////////////////////////////////////////////
	/// \brief Draw the object to a render target
	///
	/// \param target Render target to draw to
	/// \param states Current render states
	////////////////////////////////////////////////////////////
	void draw(sf::RenderTarget& target, sf::RenderStates states) const override;

	////////////////////////////////////////////////////////////
	/// \brief Update Overlay counter
	///
	/// \param value Next Overlay counter
	////////////////////////////////////////////////////////////
	void updateOverlay(float value) const;
};

#endif //CPPCOURSE_FPS_H
