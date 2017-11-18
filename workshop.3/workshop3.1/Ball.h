#ifndef CPPCOURSE_BALL_H
#define CPPCOURSE_BALL_H

#include "consts.h"

class Ball : public sf::Drawable
{
private:
	/// Shape object params
	sf::CircleShape circle;
	float radius = 0;
	float outlineThickness = 0;
	const size_t pointCount = POINT_COUNT;
	sf::Color backgroundColor;
	sf::Color outlineColor;

	/// Text object params
	sf::Text text;
	sf::Font font;
	unsigned fontSize = 0;
	std::string_view initials;

	/// Physics params
	float time = 0;
	float initialPosition = 0;
	float initialSpeed = INITIAL_SPEED;
	const float timeAccelerator = TIME_ACCELERATOR;

	////////////////////////////////////////////////////////////
	/// \brief Initialize sf::CircleShape object
	////////////////////////////////////////////////////////////
	void initCircle();

	////////////////////////////////////////////////////////////
	/// \brief Initialize sf::Text object
	////////////////////////////////////////////////////////////
	void initText();

	////////////////////////////////////////////////////////////
	/// \brief Update circle position
	////////////////////////////////////////////////////////////
	void updateCirclePosition(const sf::Vector2f& nextPosition);

	////////////////////////////////////////////////////////////
	/// \brief Update text position
	////////////////////////////////////////////////////////////
	void updateTextPosition(const sf::Vector2f& nextPosition);

	////////////////////////////////////////////////////////////
	/// \brief Check object collision
	////////////////////////////////////////////////////////////
	void checkCollision();

public:
	Ball() = default;

	~Ball() override = default;

	////////////////////////////////////////////////////////////
	/// \brief Draw the object to a render target
	///
	/// \param target Render target to draw to
	/// \param states states Current render states
	////////////////////////////////////////////////////////////
	void draw(sf::RenderTarget& target, sf::RenderStates states) const override;

	////////////////////////////////////////////////////////////
	/// \brief Initialize update of components
	///
	/// \param deltaTime Time difference between frames
	////////////////////////////////////////////////////////////
	void updatePosition(float deltaTime);

	////////////////////////////////////////////////////////////
	/// \brief Initialize the object
	///
	/// \param radius Radius of the ball
	/// \param outlineThickness Outline thickness of the ball
	/// \param fontSize Font size of initials
	/// \param initials Text of initials
	/// \param backgroundColor Color of the ball
	/// \param outlineColor Color of outline
	////////////////////////////////////////////////////////////
	void init(float radius,
		float outlineThickness,
		unsigned fontSize,
		std::string_view initials,
		sf::Color backgroundColor,
		sf::Color outlineColor);
};

#endif //CPPCOURSE_BALL_H
