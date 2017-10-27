#pragma once

#include "Ball.hpp"
#include "Random.hpp"
#include <cmath>
#include <functional>
#include <numeric>
#include <vector>
#include <windows.h>

static const unsigned MAX_LIFETIME = 10;
static const unsigned MIN_SIZE = 40;
static const unsigned MAX_SIZE = 70;
static const float MIN_SPEED = -500.f;
static const float MAX_SPEED = 500.f;
static const unsigned BALLS_COUNT = 4;
static const std::string WINDOW_TITLE = "Moving Balls v2.4";
static const unsigned ANTIALIASING_LEVEL = 8;
static const unsigned MAX_FPS = 60;
static const unsigned WINDOW_WIDTH = 800;
static const unsigned WINDOW_HEIGHT = 600;
static PRNG generator;

void init(std::vector<Ball>& balls);

void pollEvents(sf::RenderWindow& window, std::vector<Ball>& balls);

void update(std::vector<Ball>& balls, float deltaTime);

void redrawFrame(sf::RenderWindow& window, std::vector<Ball>& balls);

void onMouseClick(const sf::Event::MouseButtonEvent& event, std::vector<Ball>& balls);