#ifndef CPPCOURSE_BALL_H
#define CPPCOURSE_BALL_H

#include <SFML/Graphics.hpp>

class Ball : public sf::Drawable
{
private:
  sf::CircleShape shape{}; /// Object shape

  sf::Vector2f position{}; /// Object current position

  sf::Vector2f speed{}; /// Speed of object

  sf::Color color{}; /// Color ob object

  float lifeTime = 0.f; /// Object current lifetime

  float size = 0.f; /// Object size

public:
  Ball() = default;

  ////////////////////////////////////////////////////////////
  /// \brief Construct a new ball
  ///
  /// \param position Initial ball position
  /// \param speed Initial ball speed
  /// \param color Ball color
  /// \param size Ball size
  ////////////////////////////////////////////////////////////
  Ball(sf::Vector2f position, sf::Vector2f speed, sf::Color color, float size);

  ////////////////////////////////////////////////////////////
  /// \brief Default constructor
  ////////////////////////////////////////////////////////////
  ~Ball() override = default;

  ////////////////////////////////////////////////////////////
  /// \brief Draw the object to a render target
  ///
  /// \param target Render target to draw to
  /// \param states Current render states
  ////////////////////////////////////////////////////////////
  void draw(sf::RenderTarget &target, sf::RenderStates states) const override;

  ////////////////////////////////////////////////////////////
  /// \brief Update ball object position
  ///
  /// \param deltaTime Difference between previous and next frames
  ////////////////////////////////////////////////////////////
  void updatePosition(float deltaTime);

  ////////////////////////////////////////////////////////////
  /// \brief Update element position
  ////////////////////////////////////////////////////////////
  void updateElement();

  ////////////////////////////////////////////////////////////
  /// \brief Initialize balls
  ///
  /// \param balls Vector of nullptr of unsigned length
  ////////////////////////////////////////////////////////////
  static void init(std::vector<std::shared_ptr<Ball>> &balls);

  ////////////////////////////////////////////////////////////
  /// \brief Check collision of balls
  ///
  /// \param balls Vector of balls
  ////////////////////////////////////////////////////////////
  static void checkCollisions(std::vector<std::shared_ptr<Ball>> &balls);

  ////////////////////////////////////////////////////////////
  /// \brief Add new ball
  ///
  /// \param balls Vector of balls
  /// \param mousePosition Current position of new ball
  ////////////////////////////////////////////////////////////
  static void addBall(std::vector<std::shared_ptr<Ball>> &balls, sf::Vector2f &mousePosition);

  ////////////////////////////////////////////////////////////
  /// \brief Check intersection of new ball with existing ones
  ///
  /// \param balls Vector of balls
  /// \param ball New ball
  ////////////////////////////////////////////////////////////
  static void checkIntersection(std::vector<std::shared_ptr<Ball>> &balls, const std::shared_ptr<Ball> &ball);

  ////////////////////////////////////////////////////////////
  /// \brief Update ball lifetime
  ///
  /// \param deltaTime Difference between previous and next frames
  ////////////////////////////////////////////////////////////
  void updateBallLifetimes(float deltaTime);

  ////////////////////////////////////////////////////////////
  /// \brief Remove balls (lifetime > MAX_LIFETIME)
  ///
  /// \param balls Vector of balls
  ////////////////////////////////////////////////////////////
  static void removeDeathBalls(std::vector<std::shared_ptr<Ball>> &balls);

  ////////////////////////////////////////////////////////////
  /// \param toCompare Ball to compare with
  /// \return True of false
  ////////////////////////////////////////////////////////////
  bool operator==(Ball &toCompare) const;

  ////////////////////////////////////////////////////////////
  /// \brief Get the length of given vector
  ///
  /// \param vector Vector to get the length of
  /// \return Length of vector
  ////////////////////////////////////////////////////////////
  static float length(const sf::Vector2f &vector);

  ////////////////////////////////////////////////////////////
  /// \brief Speed getter
  ///
  /// \param nextSpeed Next ball speed
  ////////////////////////////////////////////////////////////
  void setSpeed(const sf::Vector2f &nextSpeed);
};

#endif //CPPCOURSE_BALL_H
