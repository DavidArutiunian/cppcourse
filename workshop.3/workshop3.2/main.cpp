#include "main.h"

int main()
{
#ifdef _WIN32
	ShowWindow(GetConsoleWindow(), SW_HIDE);
#endif

	sf::RenderWindow window;
	sf::Clock clock;
	std::shared_ptr<FPS> fps(std::make_shared<FPS>(FPS()));
	std::vector<std::shared_ptr<Ball>> balls(BALLS_COUNT, std::make_shared<Ball>(Ball()));

	createWindow(window);
	init(balls);

	while (window.isOpen())
	{
		const float frameRate = 1.f / clock.getElapsedTime().asSeconds();
		const float deltaTime = clock.restart().asSeconds();
		pollEvents(window, balls);
		update(balls, fps, deltaTime, frameRate);
		redrawFrame(window, balls, fps);
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

void update(std::vector<std::shared_ptr<Ball>>& balls, std::shared_ptr<FPS> FPS, float deltaTime, float frameRate)
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
	FPS->updateFps(frameRate);
}

void redrawFrame(sf::RenderWindow& window, std::vector<std::shared_ptr<Ball>>& balls, const std::shared_ptr<FPS>& fps)
{
	window.clear();
	std::for_each(balls.begin(), balls.end(), [&window](std::shared_ptr<Ball> ball) -> void {
		window.draw(*ball.get());
	});
	window.draw(*fps.get());
	window.display();
}

void createWindow(sf::RenderWindow& window)
{
	sf::ContextSettings settings;
	settings.antialiasingLevel = ANTIALIASING_LEVEL;
	window.create(sf::VideoMode(WINDOW_WIDTH, WINDOW_HEIGHT), WINDOW_TITLE.data(), sf::Style::Default, settings);
	window.setFramerateLimit(MAX_FPS);
}
