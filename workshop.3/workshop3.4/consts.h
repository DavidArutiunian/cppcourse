#ifndef CPPCOURSE_CONSTS_H
#define CPPCOURSE_CONSTS_H

#include <string>

/// Ship params
static const unsigned SHIP_POINT_COUNT = 4;
static const unsigned OUTLINE_THICKNESS = 1;
static const float ANGULAR_VELOCITY = 150.f;
static const float THRUST = 500.f;

/// Window params
static const std::string WINDOW_TITLE = "Space Ship";
static const unsigned ANTIALIASING_LEVEL = 8;
static const unsigned MAX_FPS = 60;
static const unsigned WINDOW_WIDTH = 800;
static const unsigned WINDOW_HEIGHT = 600;
static const std::string BACKGOUND_PATH = "./resources/background.png";

#endif //CPPCOURSE_CONSTS_H
