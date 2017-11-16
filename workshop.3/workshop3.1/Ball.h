#ifndef CPPCOURSE_BALL_H
#define CPPCOURSE_BALL_H

#include <SFML/Graphics.hpp>
#include <SFML/System.hpp>
#include <SFML/Window.hpp>

#include "consts.h"

class Ball : public sf::Drawable
{
private:
  /// \brief Shape object params
  sf::CircleShape circle;
  float radius = 0;
  float outlineThickness = 0;
  const size_t pointCount = POINT_COUNT;
  sf::Color backgroundColor;
  sf::Color outlineColor;

  /// \brief Text object params
  sf::Text text;
  sf::Font font;
  unsigned fontSize = 0;
  std::string initials;

  /// \brief Physics params
  float time = 0;
  float initialPosition = 0;
  float initialSpeed = INITIAL_SPEED;
  const float timeAccelerator = TIME_ACCELERATOR;

  /// \brief Initialize sf::CircleShape object
  void initCircle();

  /// \brief Initialize sf::Text object
  void initText();

  /// \brief Update circle position
  void updateCirclePosition(const sf::Vector2f &nextPosition);

  /// \brief Update text position
  void updateTextPosition(const sf::Vector2f &nextPosition);

  /// \brief Check object collision
  void checkCollision();

public:
  Ball() = default;

  ~Ball() override = default;

  /// \brief Draw the object to a render target
  /// \param target
  /// \param states
  void draw(sf::RenderTarget &target, sf::RenderStates states) const override;

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
