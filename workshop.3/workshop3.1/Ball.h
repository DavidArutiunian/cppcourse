#ifndef CPPCOURSE_BALL_H
#define CPPCOURSE_BALL_H

#include <SFML/Graphics.hpp>
#include <SFML/System.hpp>
#include <SFML/Window.hpp>

class Ball : public sf::Drawable
{
private:
	float radius = 0;
	float thickness = 0;
	unsigned fontSize = 0;
	size_t pointCount = 128;
	sf::Color backgroundColor;
	sf::Color outlineColor;
	std::string string;
	sf::CircleShape* shape;
	sf::Text* text;

	/// \brief Initialize sf::CircleShape object
	void initShape();

	/// \brief Initialize sf::Text object
	void initText();

public:
	Ball();

	/// \brief Draw the object to a render target
	/// \param target
	/// \param states
	void draw(sf::RenderTarget& target, sf::RenderStates states) const override;

	/// \brief Initialize the object
	/// \param radius
	/// \param string
	/// \param backgroundColor
	/// \param outlineColor
	/// \param thickness
	/// \param fontSize
	void init(float radius,
		std::string string,
		sf::Color backgroundColor,
		sf::Color outlineColor,
		float thickness,
		unsigned int fontSize);
};

#endif //CPPCOURSE_BALL_H
