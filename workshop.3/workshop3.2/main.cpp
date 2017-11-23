#include "main.h"
#include "consts.h"

#ifdef _WIN32

#include <windows.h>

#endif

int main()
{
#ifdef _WIN32
	ShowWindow(GetConsoleWindow(), SW_HIDE);
#endif

	sf::RenderWindow window;
	sf::Clock clock;
	const std::shared_ptr<Overlay> overlay(std::make_shared<Overlay>(Overlay()));
	std::vector<std::shared_ptr<Ball>> balls(BALLS_COUNT, std::make_shared<Ball>(Ball()));

	createWindow(window);
	init(balls);

	while (window.isOpen())
	{
		const float deltaTime = clock.restart().asSeconds();
		const float fps = 1.f / deltaTime;
		pollEvents(window, balls);
		update(balls, overlay, deltaTime, fps);
		redrawFrame(window, balls, overlay);
	}
}

void init(std::vector<std::shared_ptr<Ball>>& balls)
{
	Ball::init(balls);
}

void onMouseClick(const sf::Event::MouseButtonEvent& event, std::vector<std::shared_ptr<Ball>>& balls)
{
	sf::Vector2f mousePosition = { static_cast<float>(event.x), static_cast<float>(event.y) };
	Ball::addBall(balls, mousePosition);
}

void pollEvents(sf::RenderWindow& window, std::vector<std::shared_ptr<Ball>>& balls)
{
	sf::Event event{};
	while (window.pollEvent(event))
	{
		switch (event.type)
		{
		case sf::Event::Closed:
			window.close();
			break;
		case sf::Event::MouseButtonPressed:
			onMouseClick(event.mouseButton, balls);
			break;
		default:
			break;
		}
	}
}

void update(std::vector<std::shared_ptr<Ball>>& balls,
	const std::shared_ptr<Overlay> overlay,
	const float deltaTime,
	const float frameRate)
{
	const float dtPhysics = deltaTime / MAX_PRECISION_COUNT;
	for (unsigned i = 0; i < MAX_PRECISION_COUNT; ++i)
	{
		Ball::checkCollisions(balls);
		std::for_each(balls.begin(), balls.end(), [&dtPhysics](std::shared_ptr<Ball> ball) -> void {
			ball->updateBallLifetimes(dtPhysics);
			ball->updatePosition(dtPhysics);
			ball->updateElement();
		});
		Ball::removeDeathBalls(balls);
	}
	overlay->updateOverlay(frameRate);
}

void redrawFrame(sf::RenderWindow& window,
	std::vector<std::shared_ptr<Ball>>& balls,
	const std::shared_ptr<Overlay>& overlay)
{
	window.clear();
	std::for_each(balls.begin(), balls.end(), [&window](std::shared_ptr<Ball> ball) -> void {
		window.draw(*ball.get());
	});
	window.draw(*overlay.get());
	window.display();
}

void createWindow(sf::RenderWindow& window)
{
	sf::ContextSettings settings;
	settings.antialiasingLevel = ANTIALIASING_LEVEL;
	window.create(sf::VideoMode(WINDOW_WIDTH, WINDOW_HEIGHT),
		WINDOW_TITLE,
		sf::Style::Default,
		settings);
	window.setFramerateLimit(MAX_FPS);
}
