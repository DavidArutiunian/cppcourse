#pragma once

#include "Ball.hpp"
#include <cmath>
#include <functional>
#include <numeric>
#include <vector>
#include <windows.h>

static const unsigned BALLS_COUNT = 4;
static const char* WINDOW_TITLE = "Moving Balls v2.0";
static const unsigned ANTIALIASING_LEVEL = 8;
static const unsigned MAX_FPS = 60;
static const unsigned WINDOW_WIDTH = 800;
static const unsigned WINDOW_HEIGHT = 600;

void init(std::vector<Ball>& balls);

void pollEvents(sf::RenderWindow& window);

void update(std::vector<Ball>& balls, float deltaTime);

void redrawFrame(sf::RenderWindow& window, std::vector<Ball>& balls);