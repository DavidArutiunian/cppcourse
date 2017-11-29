#include "main.h"

#ifdef _WIN32

#include <windows.h>

#endif

int main()
{
#ifdef _WIN32
	ShowWindow(GetConsoleWindow(), SW_HIDE);
#endif

	sf::View view;
	sf::RenderWindow window;
	sf::Clock clock;
	const std::shared_ptr<Overlay> overlay(std::make_shared<Overlay>(Overlay()));
	std::vector<std::shared_ptr<Ball>> balls(BALLS_COUNT, std::make_shared<Ball>(Ball()));

	createWindow(window);
	init(balls, view);

	while (window.isOpen())
	{
		const float deltaTime = clock.restart().asSeconds();
		const float fps = 1.f / deltaTime;
		pollEvents(window, balls, view);
		update(balls, overlay, window, deltaTime, fps);
		redrawFrame(window, balls, overlay, view);
	}
}

void init(std::vector<std::shared_ptr<Ball>>& balls, sf::View& view)
{
	Ball::init(balls);
	view.reset(sf::FloatRect(0, 0, WINDOW_WIDTH, WINDOW_HEIGHT));
	view.setCenter(0.f, 0.f);
}

void onMouseClick(sf::Vector2f& mousePosition, std::vector<std::shared_ptr<Ball>>& balls)
{
	Ball::addBall(balls, mousePosition);
}

void pollEvents(sf::RenderWindow& window, std::vector<std::shared_ptr<Ball>>& balls, sf::View& view)
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
		{
			const sf::Vector2i mousePosition = sf::Mouse::getPosition(window);
			sf::Vector2f relativePosition = window.mapPixelToCoords(mousePosition);
			onMouseClick(relativePosition, balls);
			break;
		}
		case sf::Event::KeyPressed:
			onKeyPress(event.key, view);
			break;
		default:
			break;
		}
	}
}

void update(std::vector<std::shared_ptr<Ball>>& balls, const std::shared_ptr<Overlay>& overlay,
	sf::RenderWindow& window,
	float deltaTime, float frameRate)
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
	overlay->updateOverlay(window, frameRate);
}

void redrawFrame(sf::RenderWindow& window, std::vector<std::shared_ptr<Ball>>& balls,
	const std::shared_ptr<Overlay>& overlay, sf::View& view)
{
	window.clear(sf::Color::White);
	window.setView(view);
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

void onKeyPress(const sf::Event::KeyEvent& event, sf::View& view)
{
	const sf::Vector2f center = view.getCenter();
	switch (event.code)
	{
	case sf::Keyboard::Left:
		if (center.x > -1.f * GAME_FIELD_WIDTH + WINDOW_WIDTH / 2)
		{
			view.move(-1.f * MOVE_SPEED, 0);
		}
		break;
	case sf::Keyboard::Right:
		if (center.x < GAME_FIELD_WIDTH - WINDOW_WIDTH / 2)
		{
			view.move(MOVE_SPEED, 0);
		}
		break;
	case sf::Keyboard::Up:
		if (center.y > -1.f * GAME_FIELD_HEIGHT + WINDOW_HEIGHT / 2)
		{
			view.move(0, -1.f * MOVE_SPEED);
		}
		break;
	case sf::Keyboard::Down:
		if (center.y < GAME_FIELD_HEIGHT - WINDOW_HEIGHT / 2)
		{
			view.move(0, MOVE_SPEED);
		}
		break;
	default:
		break;
	}
}
