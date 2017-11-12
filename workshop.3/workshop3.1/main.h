#ifndef CPPCOURSE_MAIN_H
#define CPPCOURSE_MAIN_H

#include <cassert>
#include <stdexcept>
#include <utility>

#include "Ball.h"

#ifdef _WIN32

#include <windows.h>

#endif

/// \brief Window object params
static const float WINDOW_WIDTH = 800.f;
static const float WINDOW_HEIGHT = 600.f;
static const unsigned MAX_FPS = 60;
static const unsigned ANTIALIASING_LEVEL = 8;
static const std::string WINDOW_TITLE = "Gravity Ball";

/// \brief Ball object params
static const float BALL_RADIUS = 125.f;
static const float BALL_THICKNESS = 8;
static const unsigned BALL_FONT_SIZE = 24;
static const std::string BALL_TEXT = "ADR";
static const std::string FONT_PATH = "./resources/arial.ttf";
static const sf::Color BACKGROUND_COLOR = sf::Color::White;
static const sf::Color BALL_BACKGROUND_COLOR = sf::Color(255, 192, 0);
static const sf::Color BALL_OUTLINE_COLOR = sf::Color(76, 109, 166);

/// \brief Create window object
/// \param window
void createWindow(sf::RenderWindow& window);

/// \brief Initialize object
/// \param ball
void init(Ball& ball);

/// \brief Process window events
/// \param window
void pollEvents(sf::RenderWindow& window);

/// \brief Update object position
/// \param ball
/// \param deltaTime
void update(Ball& ball, float deltaTime);

/// \brief Update frame
/// \param window
/// \param ball
void redrawFrame(sf::RenderWindow& window, Ball& ball);

#endif //CPPCOURSE_MAIN_H
