#include "main.h"

int main()
{
#ifdef _WIN32
	ShowWindow(GetConsoleWindow(), SW_HIDE);
#endif

	sf::RenderWindow window;
	sf::Clock clock;
	Ball ball;

	createWindow(window);
	init(ball);

	while (window.isOpen())
	{
		const float deltaTime = clock.restart().asSeconds();
		pollEvents(window);
		redrawFrame(window, ball);
		update(ball, deltaTime);
	}
}

void init(Ball& ball)
{
	ball.init(BALL_RADIUS, BALL_THICKNESS, BALL_FONT_SIZE, BALL_TEXT, BALL_BACKGROUND_COLOR, BALL_OUTLINE_COLOR);
}

void pollEvents(sf::RenderWindow& window)
{
	sf::Event event{};
	while (window.pollEvent(event))
	{
		switch (event.type)
		{
		case sf::Event::Closed:
			window.close();
			break;
		default:
			break;
		}
	}
}

void redrawFrame(sf::RenderWindow& window, Ball& ball)
{
	window.clear(BACKGROUND_COLOR);
	window.draw(ball);
	window.display();
}

void update(Ball& ball, float deltaTime)
{
	ball.updatePosition(deltaTime);
}

void createWindow(sf::RenderWindow& window)
{
	sf::ContextSettings settings;
	settings.antialiasingLevel = ANTIALIASING_LEVEL;
	sf::VideoMode videoMode = sf::VideoMode((unsigned)WINDOW_WIDTH, (unsigned)WINDOW_HEIGHT);
	window.create(videoMode, WINDOW_TITLE, sf::Style::Default, settings);
	window.setFramerateLimit(MAX_FPS);
}
