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

	Ball ball1;
	Ball ball2;
	Ball ball3;
	Ball ball4;

	std::vector<Ball> balls = { ball1, ball2, ball3, ball4 };

	Ball::init(balls);

	init(balls);

	while (window.isOpen())
	{
		pollEvents(window);
		float deltaTime = clock.restart().asSeconds();
		update(balls, deltaTime);
		redrawFrame(window, balls);
	}
}

void Ball::updatePosition(float deltaTime)
{
	this->position = this->shape.getPosition();
	this->position += this->speed * deltaTime;

	if ((this->position.x + 2 * this->size >= WINDOW_WIDTH) && (this->speed.x > 0))
	{
		this->speed.x = -this->speed.x;
	}
	if ((this->position.x < 0) && (this->speed.x < 0))
	{
		this->speed.x = -this->speed.x;
	}
	if ((this->position.y + 2 * this->size >= WINDOW_HEIGHT) && (this->speed.y > 0))
	{
		this->speed.y = -this->speed.y;
	}
	if ((this->position.y < 0) && (this->speed.y < 0))
	{
		this->speed.y = -this->speed.y;
	}
}

void Ball::updateElement()
{
	this->shape.setPosition(this->position);
}

void Ball::init(std::vector<Ball>& balls)
{
	balls.at(0).color = sf::Color(128, 64, 255);
	balls.at(1).color = sf::Color(255, 64, 128);
	balls.at(2).color = sf::Color(128, 255, 64);
	balls.at(3).color = sf::Color(64, 128, 255);

	balls.at(0).size = 40;
	balls.at(1).size = 50;
	balls.at(2).size = 60;
	balls.at(3).size = 70;

	balls.at(0).speed = { 200.f, 60.f };
	balls.at(1).speed = { 60.f, 200.f };
	balls.at(2).speed = { 100.f, 120.f };
	balls.at(3).speed = { 120.f, 100.f };

	balls.at(0).position = { 0, 0 };
	balls.at(1).position = { WINDOW_WIDTH - 2 * balls.at(1).size, 0 };
	balls.at(2).position = { 0, WINDOW_HEIGHT - 2 * balls.at(2).size };
	balls.at(3).position = { WINDOW_WIDTH - 2 * balls.at(3).size, WINDOW_HEIGHT - 2 * balls.at(3).size };

	for (auto&& ball : balls)
	{
		ball.shape.setPosition(ball.position);
	}
}

void init(std::vector<Ball>& balls)
{
	for (auto&& ball : balls)
	{
		ball.shape.setRadius(ball.size);
		ball.shape.setFillColor(ball.color);
	}
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

void update(std::vector<Ball>& balls, float deltaTime)
{
	for (auto&& ball : balls)
	{
		ball.updatePosition(deltaTime);
		ball.updateElement();
	}
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
