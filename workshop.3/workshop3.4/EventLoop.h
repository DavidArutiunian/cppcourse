#ifndef CPPCOURSE_EVENTLOOP_H
#define CPPCOURSE_EVENTLOOP_H

#include <SFML/Graphics.hpp>

#include "Ship.h"
#include "consts.h"

class EventLoop
{
private:
	Ship ship; // Ship instance
	sf::RenderWindow window; // RenderWindow instance
	sf::Texture backgroundTexture;
	sf::Sprite background;

public:
	////////////////////////////////////////////////////////////
	/// \brief Construct eventloop instance
	///
	/// \param ship Ship instance
	////////////////////////////////////////////////////////////
	explicit EventLoop(Ship& ship);

	~EventLoop() = default;

	////////////////////////////////////////////////////////////
	/// \brief Update event
	///
	/// Updates current state of program
	///
	/// \return Current instance
	////////////////////////////////////////////////////////////
	EventLoop& update();

	////////////////////////////////////////////////////////////
	/// \brief Redraw frame
	///
	/// Draw current program state
	///
	/// \return Current instance
	////////////////////////////////////////////////////////////
	EventLoop& redrawFrame();

	////////////////////////////////////////////////////////////
	/// \brief Poll events
	///
	/// \return Current instance
	////////////////////////////////////////////////////////////
	EventLoop& pollEvents();

	////////////////////////////////////////////////////////////
	/// \brief Create window
	///
	/// \return RenderWindow instance
	////////////////////////////////////////////////////////////
	sf::RenderWindow& createWindow();

	////////////////////////////////////////////////////////////
	/// \brief Initialize new state
	////////////////////////////////////////////////////////////
	EventLoop& init();
};

#endif //CPPCOURSE_EVENTLOOP_H
