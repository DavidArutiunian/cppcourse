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
	sf::ConvexShape pointer;
	sf::Vector2f mousePosition;

	init(pointer);

	while (window.isOpen())
	{
		const float deltaTime = clock.restart().asMilliseconds();
		pollEvents(window, mousePosition);
		update(mousePosition, pointer, deltaTime);
		redrawFrame(window, pointer);
	}
}

void update(const sf::Vector2f& mousePosition, sf::ConvexShape& pointer, float deltaTime)
{
	const sf::Vector2f delta = mousePosition - pointer.getPosition();
	auto angle = static_cast<float>(atan2(delta.y, delta.x));
	if (angle < 0)
	{
		angle += 2 * M_PI;
	}
	angle = toDegrees(angle);
	const float maxDegreesPerFrame = MAX_ANGULAR_VELOCITY / 1000 * deltaTime;
	const float previousRotation = pointer.getRotation();
	const float degreesPerFrame = std::abs((angle - previousRotation) / 1000 * deltaTime);
	if (angle != previousRotation)
	{
		if (angle > previousRotation)
		{
			if (std::ceil(angle - 180) > previousRotation)
			{
				pointer.setRotation(previousRotation - std::min(degreesPerFrame, maxDegreesPerFrame));
			}
			else
			{
				pointer.setRotation(previousRotation + std::min(degreesPerFrame, maxDegreesPerFrame));
			}
		}
		else
		{
			if (std::ceil(angle + 180) < previousRotation)
			{
				pointer.setRotation(previousRotation + std::min(degreesPerFrame, maxDegreesPerFrame));
			}
			else
			{
				pointer.setRotation(previousRotation - std::min(degreesPerFrame, maxDegreesPerFrame));
			}
		}
	}
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

void onMouseMove(const sf::Event::MouseMoveEvent& event, sf::Vector2f& mousePosition)
{
	mousePosition = { static_cast<float>(event.x), static_cast<float>(event.y) };
}

void redrawFrame(sf::RenderWindow& window, sf::ConvexShape& pointer)
{
	window.clear();
	window.draw(pointer);
	window.display();
}

void init(sf::ConvexShape& pointer)
{
	pointer.setPointCount(POINTS_SET.size());
	for (auto iterator = POINTS_SET.begin(); iterator != POINTS_SET.end(); ++iterator)
	{
		const auto index = static_cast<int>(std::distance(POINTS_SET.begin(), iterator));
		if (index < POINTS_SET.size())
		{
			pointer.setPoint((size_t)index, POINTS_SET.at(static_cast<unsigned long long>(index)));
		}
	}
	pointer.setPosition(WINDOW_WIDTH / 2, WINDOW_HEIGHT / 2);
	pointer.setFillColor(POINTER_COLOR);
}

float toDegrees(float radians)
{
	return static_cast<float>(static_cast<double>(radians) * 180 / M_PI);
}
