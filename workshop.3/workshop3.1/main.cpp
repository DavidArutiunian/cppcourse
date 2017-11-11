#include "main.h"

int main()
{
#ifdef _WIN32
	ShowWindow(GetConsoleWindow(), SW_HIDE);
#endif

	sf::ContextSettings settings;
	settings.antialiasingLevel = ANTIALIASING_LEVEL;
	sf::VideoMode videoMode = sf::VideoMode((unsigned)WINDOW_WIDTH, (unsigned)WINDOW_HEIGHT);
	sf::RenderWindow window(videoMode, WINDOW_TITLE, sf::Style::Default, settings);
	window.setFramerateLimit(MAX_FPS);

	sf::Clock clock;

	Ball ball;

	init(ball);

	while (window.isOpen())
	{
		pollEvents(window);
		redrawFrame(window, ball);
	}
}

void init(Ball& ball)
{
	ball.init(BALL_SIZE, BALL_TEXT, BALL_BACKGROUND_COLOR, BALL_OUTLINE_COLOR, BALL_THICKNESS, BALL_FONT_SIZE);
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
