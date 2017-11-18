#include "main.h"

int main()
{
#ifdef _WIN32
	ShowWindow(GetConsoleWindow(), SW_HIDE);
#endif

	sf::RenderWindow window;
	sf::Clock clock;
	std::vector<std::shared_ptr<Ball>> balls(BALLS_COUNT, nullptr);

	createWindow(window);
	init(balls);

	while (window.isOpen())
	{
		const float deltaTime = clock.restart().asSeconds();
		pollEvents(window, balls);
		update(balls, deltaTime);
		redrawFrame(window, balls);
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

void update(std::vector<std::shared_ptr<Ball>>& balls, float deltaTime)
{
	const float dtPhysics = deltaTime / MAX_PRECISION_COUNT;
	for (unsigned i = 0; i < MAX_PRECISION_COUNT; ++i)
	{
		Ball::checkCollisions(balls);
		for (auto&& ball : balls)
		{
			ball->updateBallLifetimes(dtPhysics);
			ball->updatePosition(dtPhysics);
			ball->updateElement();
		}
		Ball::removeDeathBalls(balls);
	}
}

void redrawFrame(sf::RenderWindow& window, std::vector<std::shared_ptr<Ball>>& balls)
{
	window.clear();
	for (auto&& ball : balls)
	{
		window.draw(*ball.get());
	}
	window.display();
}

void createWindow(sf::RenderWindow& window)
{
	sf::ContextSettings settings;
	settings.antialiasingLevel = ANTIALIASING_LEVEL;
	window.create(sf::VideoMode(WINDOW_WIDTH, WINDOW_HEIGHT), WINDOW_TITLE.data(), sf::Style::Default, settings);
	window.setFramerateLimit(MAX_FPS);
}
