#ifndef CPPCOURSE_MAIN_H
#define CPPCOURSE_MAIN_H

#include <SFML/Graphics.hpp>
#include <memory>

#include "Ball.h"
#include "Overlay.h"

////////////////////////////////////////////////////////////
/// \brief Run initializing of balls
///
/// \param balls Vector of nullptr of unsigned length
////////////////////////////////////////////////////////////
void init(std::vector<std::shared_ptr<Ball>>& balls);

////////////////////////////////////////////////////////////
/// \brief Create window object
///
/// \param window
////////////////////////////////////////////////////////////
void createWindow(sf::RenderWindow& window);

////////////////////////////////////////////////////////////
/// \brief Process window events
///
/// \param window Window object
/// \param balls Vector of balls to dispatch an event on
////////////////////////////////////////////////////////////
void pollEvents(sf::RenderWindow& window, std::vector<std::shared_ptr<Ball>>& balls);

////////////////////////////////////////////////////////////
/// \brief Update object position
///
/// \param balls Vector of balls
/// \param deltaTime Difference in time between frames
////////////////////////////////////////////////////////////
void update(std::vector<std::shared_ptr<Ball>>& balls,
            std::shared_ptr<Overlay> fps,
            float deltaTime,
            float frameRate);

////////////////////////////////////////////////////////////
/// \brief Update frame
///
/// \param window Window object
/// \param ball Pointer to the ball object
////////////////////////////////////////////////////////////
void redrawFrame(sf::RenderWindow& window,
                 std::vector<std::shared_ptr<Ball>>& balls,
                 const std::shared_ptr<Overlay>& fps);

////////////////////////////////////////////////////////////
/// \brief Dispatch event to vector of balls
///
/// \param event Event object
/// \param balls Vector of balls
////////////////////////////////////////////////////////////
void onMouseClick(const sf::Event::MouseButtonEvent& event, std::vector<std::shared_ptr<Ball>>& balls);

#endif //CPPCOURSE_MAIN_H
