#ifndef CPPCOURSE_BALL_H
#define CPPCOURSE_BALL_H

#include <SFML/Graphics.hpp>
#include <SFML/System.hpp>
#include <SFML/Window.hpp>

class Ball : public sf::Drawable
{
private:
	/// \brief Shape object params
	sf::CircleShape circle;
	float radius = 0;
	float outlineThickness = 0;
	sf::Color backgroundColor;
	sf::Color outlineColor;

	/// \brief Text object params
	sf::Text text;
	unsigned fontSize = 0;
	std::string initials;

	/// \brief Physics params
	float deltaTime = 0;

	/// \brief Initialize sf::CircleShape object
	void initCircle();

	/// \brief Initialize sf::Text object
	void initText();

	/// \brief Update circle position
	void updateCircle();

	/// \brief Update text position
	void updateText();

public:
	Ball() = default;

	~Ball() override = default;

	/// \brief Draw the object to a render target
	/// \param target
	/// \param states
	void draw(sf::RenderTarget& target, sf::RenderStates states) const override;

	/// \brief Initialize update of components
	/// \param deltaTime
	void updatePosition(float deltaTime);

	/// \brief Initialize the object
	/// \param radius
	/// \param outlineThickness
	/// \param fontSize
	/// \param initials
	/// \param backgroundColor
	/// \param outlineColor
	void init(float radius,
		float outlineThickness,
		unsigned fontSize,
		std::string initials,
		sf::Color backgroundColor,
		sf::Color outlineColor);
};

#endif //CPPCOURSE_BALL_H
