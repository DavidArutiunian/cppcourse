#pragma once

#include "Ball.hpp"
#include <cmath>
#include <vector>
#include <windows.h>

#define BALLS_COUNT 4
#define WINDOW_TITLE "Moving Balls v2.0"
#define ANTIALIASING_LEVEL 8
#define MAX_FPS 60
#define WINDOW_WIDTH 800
#define WINDOW_HEIGHT 600

void init(std::vector<Ball>& balls);

void pollEvents(sf::RenderWindow& window);

void update(std::vector<Ball>& balls, float deltaTime);

void redrawFrame(sf::RenderWindow& window, std::vector<Ball>& balls);