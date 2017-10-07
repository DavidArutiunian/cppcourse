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

	Arrow arrow;
	sf::Vector2f mousePosition = { WINDOW_WIDTH / 2, WINDOW_HEIGHT / 2 };

	init(arrow);

	while (window.isOpen())
	{
		pollEvents(window, mousePosition);
		float deltaTime = clock.restart().asSeconds();
		update(mousePosition, arrow, deltaTime);
		redrawFrame(window, arrow);
	}
}

void update(sf::Vector2f& mousePosition, Arrow& arrow, float deltaTime)
{
	const sf::Vector2f delta = mousePosition - arrow.position;
	arrow.updateRotation(arrow, delta, deltaTime);
	arrow.updatePosition(arrow, delta, deltaTime);
	arrow.updateElement();
}

void Arrow::updateRotation(Arrow& arrow, const sf::Vector2f delta, float deltaTime)
{
	auto angle = static_cast<float>(atan2(delta.y, delta.x));
	if (angle < 0)
	{
		angle = static_cast<float>(angle + 2 * M_PI);
	}
	angle = toDegrees(angle);
	const float maxDegreesPerFrame = 90 * deltaTime;
	const float previousRotation = arrow.shape.getRotation();
	const float degreesPerFrame = std::abs(angle - previousRotation);
	if (angle != previousRotation)
	{
		if (angle > previousRotation)
		{
			if ((angle - 180) > previousRotation)
			{
				arrow.rotation = previousRotation - std::min(maxDegreesPerFrame, degreesPerFrame);
			}
			else
			{
				arrow.rotation = previousRotation + std::min(maxDegreesPerFrame, degreesPerFrame);
			}
		}
		else
		{
			if ((angle + 180) < previousRotation)
			{
				arrow.rotation = previousRotation + std::min(maxDegreesPerFrame, degreesPerFrame);
			}
			else
			{
				arrow.rotation = previousRotation - std::min(maxDegreesPerFrame, degreesPerFrame);
			}
		}
	}
}

void Arrow::updatePosition(Arrow& arrow, const sf::Vector2f delta, float deltaTime)
{
	const auto deltaLength = static_cast<float>(std::sqrt(std::pow(delta.x, 2) + std::pow(delta.y, 2)));
	sf::Vector2f direction = { 0, 0 };
	if (deltaLength != 0)
	{
		direction = { delta.x / deltaLength, delta.y / deltaLength };
	}
	const float speed = 20 * deltaTime;
	arrow.position = arrow.position + direction * speed;
}

void Arrow::updateElement()
{
	this->shape.setPosition(this->position);
	this->shape.setRotation(this->rotation);
}

void Arrow::setPoints()
{
	this->position = { WINDOW_WIDTH / 2, WINDOW_HEIGHT / 2 };
	this->shape.setPosition(this->position);
	this->shape.setFillColor(this->arrowColor);
	this->shape.setPointCount(this->pointCount);
	this->shape.setPoint(0, { 0, 40 });
	this->shape.setPoint(1, { 40, 0 });
	this->shape.setPoint(2, { 0, -40 });
	this->shape.setPoint(3, { 0, -20 });
	this->shape.setPoint(4, { -40, -20 });
	this->shape.setPoint(5, { -40, 20 });
	this->shape.setPoint(6, { 0, 20 });
	this->shape.setOutlineColor(this->outlineColor);
	this->shape.setOutlineThickness(this->outlineThickness);
}

void init(Arrow& arrow)
{
	arrow.setPoints();
}

void pollEvents(sf::RenderWindow& window, sf::Vector2f& mousePosition)
{
	sf::Event event{};
	while (window.pollEvent(event))
	{
		switch (event.type)
		{
		case sf::Event::Closed:
			window.close();
			break;
		case sf::Event::MouseMoved:
			onMouseMove(event.mouseMove, mousePosition);
			break;
		default:
			break;
		}
	}
}

void redrawFrame(sf::RenderWindow& window, Arrow& arrow)
{
	window.clear(BACKGROUND_COLOR);
	window.draw(arrow.shape);
	window.display();
}

void onMouseMove(const sf::Event::MouseMoveEvent& event, sf::Vector2f& mousePosition)
{
	mousePosition = { static_cast<float>(event.x), static_cast<float>(event.y) };
}

float toDegrees(float radians)
{
	return float(double(radians) * 180.0 / M_PI);
}