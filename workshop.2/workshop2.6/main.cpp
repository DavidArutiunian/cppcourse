#include "main.hpp"

int main()
{
#ifdef _WIN32
	ShowWindow(GetConsoleWindow(), SW_HIDE);
#endif

	sf::ContextSettings settings;
	settings.antialiasingLevel = ANTIALIASING_LEVEL;
	sf::RenderWindow window(sf::VideoMode(WINDOW_WIDTH, WINDOW_HEIGHT), WINDOW_TITLE, sf::Style::Default, settings);
	window.setFramerateLimit(MAX_FPS);

	sf::Clock clock;

	std::vector<Ball> balls(BALLS_COUNT, Ball());

	init(balls);

	while (window.isOpen())
	{
		pollEvents(window, balls);
		float deltaTime = clock.restart().asSeconds();
		update(balls, deltaTime);
		redrawFrame(window, balls);
	}
}

void init(std::vector<Ball>& balls)
{
	Ball::init(balls);
}

void onMouseClick(const sf::Event::MouseButtonEvent& event, std::vector<Ball>& balls)
{
	sf::Vector2f mousePosition = { static_cast<float>(event.x), static_cast<float>(event.y) };
	Ball::addBall(balls, mousePosition);
}

void pollEvents(sf::RenderWindow& window, std::vector<Ball>& balls)
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

void update(std::vector<Ball>& balls, float deltaTime)
{
	Ball::checkCollisions(balls);
	for (auto&& ball : balls)
	{
		ball.updateBallLifetimes(deltaTime);
		ball.updatePosition(deltaTime);
		ball.updateElement();
	}
	Ball::removeDeathBalls(balls);
}

void redrawFrame(sf::RenderWindow& window, std::vector<Ball>& balls)
{
	window.clear();
	for (auto&& ball : balls)
	{
		window.draw(ball.shape);
	}
	window.display();
}
