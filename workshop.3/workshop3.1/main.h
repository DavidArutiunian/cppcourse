#ifndef CPPCOURSE_MAIN_H
#define CPPCOURSE_MAIN_H

#include <SFML/Graphics.hpp>
#include <SFML/System.hpp>
#include <SFML/Window.hpp>
#include <cassert>
#include <stdexcept>
#include <utility>
#include <cmath>

#include "Ball.h"
#include "consts.h"

#ifdef _WIN32

#include <windows.h>

#endif

/// \brief Create window object
/// \param window
void createWindow(sf::RenderWindow &window);

/// \brief Initialize object
/// \param ball
void init(Ball &ball);

/// \brief Process window events
/// \param window
void pollEvents(sf::RenderWindow &window);

/// \brief Update object position
/// \param ball
/// \param deltaTime
void update(Ball &ball, float deltaTime);

/// \brief Update frame
/// \param window
/// \param ball
void redrawFrame(sf::RenderWindow &window, Ball &ball);

#endif //CPPCOURSE_MAIN_H
