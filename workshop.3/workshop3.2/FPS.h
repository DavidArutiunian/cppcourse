#ifndef CPPCOURSE_FPS_H
#define CPPCOURSE_FPS_H

#include "consts.h"

class FPS : public sf::Drawable
{
private:
  std::shared_ptr<sf::Font> font = std::make_shared<sf::Font>(sf::Font());

  std::shared_ptr<sf::Text> text = std::make_shared<sf::Text>(sf::Text());

  ////////////////////////////////////////////////////////////
  /// \brief Load fonts from FONT_PATH
  ////////////////////////////////////////////////////////////
  void initFont();

  ////////////////////////////////////////////////////////////
  /// \brief Set text properties
  ////////////////////////////////////////////////////////////
  void initText();

public:
  FPS();

  ~FPS() override = default;

  ////////////////////////////////////////////////////////////
  /// \brief Draw the object to a render target
  ///
  /// \param target Render target to draw to
  /// \param states Current render states
  ////////////////////////////////////////////////////////////
  void draw(sf::RenderTarget &target, sf::RenderStates states) const override;

  ////////////////////////////////////////////////////////////
  /// \brief Update FPS counter
  ///
  /// \param nextFps Next FPS counter
  ////////////////////////////////////////////////////////////
  void updateFps(float nextFps);
};

#endif //CPPCOURSE_FPS_H
