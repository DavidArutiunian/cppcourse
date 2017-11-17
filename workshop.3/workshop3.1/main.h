#ifndef CPPCOURSE_MAIN_H
#define CPPCOURSE_MAIN_H

#include "Ball.h"
#include "consts.h"

/// \brief Create window object
/// \param window
void createWindow(sf::RenderWindow& window);

/// \brief Initialize object
/// \param ball
void init(std::shared_ptr<Ball> ball);

/// \brief Process window events
/// \param window
void pollEvents(sf::RenderWindow& window);

/// \brief Update object position
/// \param ball
/// \param deltaTime
void update(std::shared_ptr<Ball> ball, float deltaTime);

/// \brief Update frame
/// \param window
/// \param ball
void redrawFrame(sf::RenderWindow& window, std::shared_ptr<Ball> ball);

#endif //CPPCOURSE_MAIN_H
