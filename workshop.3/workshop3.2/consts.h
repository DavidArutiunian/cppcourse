#ifndef CPPCOURSE_CONSTS_H
#define CPPCOURSE_CONSTS_H

#include <SFML/Graphics.hpp>

#include "Random.h"

/// Precision of collisions (deltaTime / MAX_PRECISION_COUNT in one frame)
static const unsigned MAX_PRECISION_COUNT = 1024;

/// Ball object params
static const unsigned MAX_LIFETIME = 10;
static const unsigned MIN_SIZE = 25;
static const unsigned MAX_SIZE = 50;
static const float MAX_SPEED = 500.f;
static const float MIN_SPEED = -500.f;
static const unsigned BALLS_COUNT = 4;

/// Window object params
static const std::string WINDOW_TITLE = "Moving Balls v2.7";
static const unsigned ANTIALIASING_LEVEL = 8;
static const unsigned MAX_FPS = 60;
static const unsigned WINDOW_WIDTH = 800;
static const unsigned WINDOW_HEIGHT = 600;
static const int GAME_FIELD_WIDTH = WINDOW_WIDTH * 3;
static const int GAME_FIELD_HEIGHT = WINDOW_HEIGHT * 3;

/// Overlay pbject params
static const std::string FONT_PATH = "./resources/arial.ttf";
static const sf::Vector2f FPS_MARGIN = {5, 5};
static const unsigned FONT_SIZE = 24;

/// Random generator object
static PRNG generator;

#endif //CPPCOURSE_CONSTS_H
