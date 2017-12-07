#include "main.h"

int main()
{
	KeysMap pressedKeys;
	pressedKeys[sf::Keyboard::Key::Left] = false;
	pressedKeys[sf::Keyboard::Key::Right] = false;
	pressedKeys[sf::Keyboard::Key::Up] = false;
	pressedKeys[sf::Keyboard::Key::Down] = false;

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
		pollEvents(window, pressedKeys, balls);
		update(balls, overlay, pressedKeys, window, view, deltaTime, fps);
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

void pollEvents(sf::RenderWindow& window, KeysMap& pressedKeys, std::vector<std::shared_ptr<Ball>>& balls)
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
			onKeyPress(event.key, pressedKeys);
			break;
		case sf::Event::KeyReleased:
			onKeyRelease(event.key, pressedKeys);
			break;
		default:
			break;
		}
	}
}

void update(
	std::vector<std::shared_ptr<Ball>>& balls,
	const std::shared_ptr<Overlay>& overlay,
	const KeysMap& pressedKeys,
	sf::RenderWindow& window,
	sf::View& view,
	const float deltaTime,
	const float frameRate)
{
	const sf::Vector2f center = view.getCenter();

	if (pressedKeys.at(sf::Keyboard::Left))
	{
		if (center.x > -1.f * GAME_FIELD_WIDTH + WINDOW_WIDTH / 2)
		{
			view.move(-1.f * MOVE_SPEED * deltaTime, 0);
		}
	}
	if (pressedKeys.at(sf::Keyboard::Right))
	{
		if (center.x < GAME_FIELD_WIDTH - WINDOW_WIDTH / 2)
		{
			view.move(MOVE_SPEED * deltaTime, 0);
		}
	}
	if (pressedKeys.at(sf::Keyboard::Up))
	{
		if (center.y > -1.f * GAME_FIELD_HEIGHT + WINDOW_HEIGHT / 2)
		{
			view.move(0, -1.f * MOVE_SPEED * deltaTime);
		}
	}
	if (pressedKeys.at(sf::Keyboard::Down))
	{
		if (center.y < GAME_FIELD_HEIGHT - WINDOW_HEIGHT / 2)
		{
			view.move(0, MOVE_SPEED * deltaTime);
		}
	}

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

void onKeyPress(const sf::Event::KeyEvent& event, KeysMap& pressedKeys)
{
	pressedKeys[event.code] = true;
}

void onKeyRelease(const sf::Event::KeyEvent& event, KeysMap& pressedKeys)
{
	pressedKeys[event.code] = false;
}
