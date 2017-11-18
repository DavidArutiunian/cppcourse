#ifndef CPPCOURSE_MAIN_H
#define CPPCOURSE_MAIN_H

#include "Ball.h"
#include "consts.h"

/////////////////////////////////////////////
/// \brief Create window object
///
/// \param window Window object
/////////////////////////////////////////////
void createWindow(sf::RenderWindow &window);

/////////////////////////////////////////////
/// \brief Initialize object
///
/// \param ball Pointer to the ball object
/////////////////////////////////////////////
void init(std::shared_ptr<Ball> ball);

/////////////////////////////////////////////
/// \brief Process window events
///
/// \param window Window object
/////////////////////////////////////////////
void pollEvents(sf::RenderWindow &window);

/////////////////////////////////////////////
/// \brief Update object position
///
/// \param ball Pointer to the ball object
/// \param deltaTime Difference in time between frames
/////////////////////////////////////////////
void update(std::shared_ptr<Ball> ball, float deltaTime);

/////////////////////////////////////////////
/// \brief Update frame
///
/// \param window Window object
/// \param ball Pointer to the ball object
/////////////////////////////////////////////
void redrawFrame(sf::RenderWindow &window, std::shared_ptr<Ball> ball);

#endif //CPPCOURSE_MAIN_H
