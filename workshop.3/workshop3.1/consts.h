#ifndef CPPCOURSE_CONSTS_H
#define CPPCOURSE_CONSTS_H

#include <SFML/Graphics.hpp>
#include <SFML/System.hpp>
#include <SFML/Window.hpp>
#include <cassert>
#include <cmath>
#include <iostream>
#include <memory>
#include <stdexcept>
#include <utility>

/// Window object params
static const float WINDOW_WIDTH = 800.f;
static const float WINDOW_HEIGHT = 600.f;
static const unsigned MAX_FPS = 60;
static const unsigned ANTIALIASING_LEVEL = 8;
static const std::string_view WINDOW_TITLE = "Gravity Ball";

/// Physics params
static const float INITIAL_SPEED = 75.f;
static const float G = 9.8f;
static const float TIME_ACCELERATOR = 7.5f;

/// Ball object params
static const float BALL_RADIUS = 125.f;
static const float BALL_THICKNESS = 8.f;
static const unsigned BALL_FONT_SIZE = 72;
static const size_t POINT_COUNT = 256;
static const std::string_view BALL_TEXT = "ADR";
static const std::string_view FONT_PATH = "./resources/arial.ttf";
static const sf::Color BACKGROUND_COLOR = sf::Color::White;
static const sf::Color BALL_BACKGROUND_COLOR = sf::Color(255, 192, 0);
static const sf::Color BALL_OUTLINE_COLOR = sf::Color(76, 109, 166);

#endif //CPPCOURSE_CONSTS_H
