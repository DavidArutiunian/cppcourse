#ifndef CPPCOURSE_LINE_H
#define CPPCOURSE_LINE_H

#include <SFML/Graphics.hpp>
#include <cmath>

class Line : public sf::Drawable
{
private:
  sf::Vertex vertex[2];

public:
  ////////////////////////////////////////////////////////////
  /// \brief Construct new line
  ///
  /// \param vertex sf::Vertex object
  ////////////////////////////////////////////////////////////
  explicit Line(sf::Vertex vertex[2]);

  ////////////////////////////////////////////////////////////
  /// \brief Default constructor
  ////////////////////////////////////////////////////////////
  ~Line() override = default;

  void draw(sf::RenderTarget &target, sf::RenderStates states) const override;

  sf::Vertex *getVertex();

  void setEndPosition(const sf::Vector2f &nextPosition);

  float length();

};


#endif //CPPCOURSE_LINE_H
