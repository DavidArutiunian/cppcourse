#ifndef CPPCOURSE_SHIP_H
#define CPPCOURSE_SHIP_H

#include <SFML/Graphics.hpp>

#include "consts.h"

class Ship : public sf::Drawable, public sf::Transformable
{
private:
  sf::ConvexShape shipShape;
  sf::ConvexShape burnShape;

  sf::Vector2f position = {0.f, 0.f};
  sf::Vector2f velocity = {0.f, 0.f};

  float rotation = 0.f; // Overall rotation

  ////////////////////////////////////////////////////////////
  /// \brief Draw the object to a render target
  ///
  /// \param target Render target to draw to
  /// \param states Current render states
  ////////////////////////////////////////////////////////////
  void draw(sf::RenderTarget &target, sf::RenderStates states) const override;

  ////////////////////////////////////////////////////////////
  /// \brief Check collision with walls
  ////////////////////////////////////////////////////////////
  void checkCollision();

public:
  float direction = 0.f; // Current direction
  float thrust = 0.f; // Acceleration of ship
  bool showFlame = false; // Indicates whether to show flame or not

  Ship();

  ~Ship() override = default;

  ////////////////////////////////////////////////////////////
  /// \brief Update ship position and rotation
  ////////////////////////////////////////////////////////////
  void update(float deltaTime);

};

#endif //CPPCOURSE_SHIP_H
