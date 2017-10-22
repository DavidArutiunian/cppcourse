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

	if ((this->position.x + this->size >= WINDOW_WIDTH) && (this->speed.x > 0))
	{
		this->speed.x = -this->speed.x;
	}
	if ((this->position.x - this->size < 0) && (this->speed.x < 0))
	{
		this->speed.x = -this->speed.x;
	}
	if ((this->position.y + this->size >= WINDOW_HEIGHT) && (this->speed.y > 0))
	{
		this->speed.y = -this->speed.y;
	}
	if ((this->position.y - this->size < 0) && (this->speed.y < 0))
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
	const std::vector<sf::Color> colors = {
		sf::Color(128, 64, 255),
		sf::Color(255, 64, 128),
		sf::Color(128, 255, 64),
		sf::Color(64, 128, 255),
	};
	const std::vector<sf::Vector2f> speeds = {
		{ 100.f, 100.f },
		{ -150.f, -150.f },
		{ 200.f, 200.f },
		{ -250.f, -250.f },
	};
	const std::vector<float> sizes = {
		40,
		50,
		60,
		70
	};
	const std::vector<sf::Vector2f> positions = {
		{ sizes.at(0), sizes.at(0) },
		{ WINDOW_WIDTH - sizes.at(1), sizes.at(1) },
		{ sizes.at(2), WINDOW_HEIGHT - sizes.at(2) },
		{ WINDOW_WIDTH - sizes.at(3), WINDOW_HEIGHT - sizes.at(3) },
	};

	const auto size = static_cast<unsigned>(std::distance(balls.begin(), balls.end()));

	for (size_t i = 0; i < size; ++i)
	{
		balls.at(i).color = colors.at(i);
		balls.at(i).size = sizes.at(i);
		balls.at(i).speed = speeds.at(i);
		balls.at(i).position = positions.at(i);
		balls.at(i).shape.setPosition(balls.at(i).position);
		balls.at(i).shape.setOrigin(balls.at(i).size, balls.at(i).size);
		balls.at(i).shape.setRadius(balls.at(i).size);
		balls.at(i).shape.setFillColor(balls.at(i).color);
	}
}

void init(std::vector<Ball>& balls)
{
	Ball::init(balls);
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
