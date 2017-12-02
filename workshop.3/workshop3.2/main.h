#ifndef CPPCOURSE_MAIN_H
#define CPPCOURSE_MAIN_H

#include <SFML/Graphics.hpp>
#include <memory>
#include <map>

#include "Ball.h"
#include "Overlay.h"
#include "consts.h"

using KeysMap = std::map<sf::Keyboard::Key, bool>;

////////////////////////////////////////////////////////////
/// \brief Run initializing of balls
///
/// \param balls Vector of nullptr of unsigned length
////////////////////////////////////////////////////////////
void init(std::vector<std::shared_ptr<Ball>>& balls, sf::View& view);

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
void pollEvents(sf::RenderWindow& window, KeysMap& pressedKeys, std::vector<std::shared_ptr<Ball>>& balls);

////////////////////////////////////////////////////////////
/// \brief Update object position
///
/// \param balls Vector of balls
/// \param deltaTime Difference in time between frames
////////////////////////////////////////////////////////////
void update(std::vector<std::shared_ptr<Ball>>& balls,
	const std::shared_ptr<Overlay>& overlay,
	const KeysMap& pressedKeys,
	sf::RenderWindow& window,
	sf::View& view,
	float deltaTime, float frameRate);

////////////////////////////////////////////////////////////
/// \brief Update frame
///
/// \param window Window object
/// \param ball Pointer to the ball object
////////////////////////////////////////////////////////////
void redrawFrame(sf::RenderWindow& window,
	std::vector<std::shared_ptr<Ball>>& balls,
	const std::shared_ptr<Overlay>& fps,
	sf::View& view);

////////////////////////////////////////////////////////////
/// \brief Dispatch event to vector of balls
///
/// \param mousePosition Event object
/// \param balls Vector of balls
////////////////////////////////////////////////////////////
void onMouseClick(sf::Vector2f& mousePosition, std::vector<std::shared_ptr<Ball>>& balls);

////////////////////////////////////////////////////////////
/// \brief Dispatch press key event
///
/// \param event Key event
/// \param view Window view
////////////////////////////////////////////////////////////
void onKeyPress(const sf::Event::KeyEvent& event, KeysMap& pressedKeys);

////////////////////////////////////////////////////////////
/// \brief Dispatch release key event
///
/// \param event Key event
/// \param view Window view
////////////////////////////////////////////////////////////
void onKeyRelease(const sf::Event::KeyEvent& event, KeysMap& pressedKeys);

#endif //CPPCOURSE_MAIN_H
