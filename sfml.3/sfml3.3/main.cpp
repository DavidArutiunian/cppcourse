#include "main.hpp"

int main()
{
	sf::ContextSettings settings;
	settings.antialiasingLevel = ANTIALIASING_LEVEL;
	sf::RenderWindow window(sf::VideoMode(WINDOW_WIDTH, WINDOW_HEIGHT), WINDOW_TITLE, sf::Style::Default, settings);
	window.setFramerateLimit(MAX_FPS);

	Eye leftEye;
	Eye rightEye;
	sf::Vector2f mousePosition;

	init(leftEye, rightEye);

	while (window.isOpen())
	{
		pollEvents(window, mousePosition);
		update(mousePosition, leftEye, rightEye);
		redrawFrame(window, leftEye, rightEye);
	}
}

void update(const sf::Vector2f& mousePosition, Eye& leftEye, Eye& rightEye)
{
	const double isInLeftEye = checkElipseIntersection(mousePosition,
		leftEye.back.getPosition(),
		leftEye.radius.x / 3,
		leftEye.radius.y / 3);

	const double isInRightEye = checkElipseIntersection(mousePosition,
		rightEye.back.getPosition(),
		rightEye.radius.x / 3,
		rightEye.radius.y / 3);

	if (isInLeftEye > 1.f)
	{
		const sf::Vector2f leftEyeDelta = mousePosition - leftEye.position;
		leftEye.rotation = std::atan2(leftEyeDelta.x, leftEyeDelta.y);
		leftEye.updateElement();
	}
	else
	{
		leftEye.orb.setPosition(mousePosition);
	}

	if (isInRightEye > 1.f)
	{
		const sf::Vector2f rightEyeDelta = mousePosition - rightEye.position;
		rightEye.rotation = std::atan2(rightEyeDelta.x, rightEyeDelta.y);
		rightEye.updateElement();
	}
	else
	{
		rightEye.orb.setPosition(mousePosition);
	}
}

void Eye::updateElement()
{
	const sf::Vector2f offset = toEuclidian(this->radius.x / 3, this->radius.y / 3, this->rotation);
	this->orb.setPosition(this->position + offset);
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

void redrawFrame(sf::RenderWindow& window, Eye& leftEye, Eye& rightEye)
{
	window.clear();
	window.draw(leftEye.back);
	window.draw(leftEye.orb);
	window.draw(rightEye.back);
	window.draw(rightEye.orb);
	window.display();
}

void init(Eye& leftEye, Eye& rightEye)
{
	const sf::Vector2f leftEyePosition = { WINDOW_WIDTH / 2 - WINDOW_WIDTH / 12, WINDOW_HEIGHT / 2 };
	const sf::Vector2f rightEyePosition = { WINDOW_WIDTH / 2 + WINDOW_WIDTH / 12, WINDOW_HEIGHT / 2 };

	leftEye.position = leftEyePosition;
	leftEye.back.setPosition(leftEyePosition);
	leftEye.back.setFillColor(leftEye.eyeColor);
	leftEye.back.setPointCount(leftEye.pointCount);

	leftEye.orb.setPosition(leftEyePosition);
	leftEye.orb.setFillColor(leftEye.orbColor);
	leftEye.orb.setPointCount(leftEye.pointCount / 4);

	leftEye.setPoints();

	rightEye.position = rightEyePosition;
	rightEye.back.setPosition(rightEyePosition);
	rightEye.back.setFillColor(rightEye.eyeColor);
	rightEye.back.setPointCount(rightEye.pointCount);

	rightEye.orb.setPosition(rightEyePosition);
	rightEye.orb.setFillColor(rightEye.orbColor);
	rightEye.orb.setPointCount(rightEye.pointCount / 4);

	rightEye.setPoints();
}

void Eye::setPoints()
{
	const auto backPointCount = static_cast<size_t>(this->back.getPointCount());
	for (size_t i = 0; i < backPointCount; ++i)
	{
		const auto angle = static_cast<float>((2 * M_PI * static_cast<float>(i)) / static_cast<float>(backPointCount));
		sf::Vector2f point = { this->radius.x * std::sin(angle), this->radius.y * std::cos(angle) };
		this->back.setPoint(i, point);
	}

	const auto orbPointCount = static_cast<size_t>(this->orb.getPointCount());
	for (size_t j = 0; j < orbPointCount; ++j)
	{
		const auto angle = static_cast<float>((2 * M_PI * static_cast<float>(j)) / static_cast<float>(orbPointCount));
		sf::Vector2f point = { (this->radius.x / 4) * std::sin(angle), (this->radius.y / 4) * std::cos(angle) };
		this->orb.setPoint(j, point);
	}
}

double checkElipseIntersection(const sf::Vector2f& mousePosition, const sf::Vector2f& position, float a, float b)
{
	return ((std::pow(mousePosition.x - position.x, 2) / std::pow(a, 2)) + (std::pow(mousePosition.y - position.y, 2) / std::pow(b, 2)));
}

sf::Vector2f toEuclidian(float a, float b, float angle)
{
	return { a * std::sin(angle), b * std::cos(angle) };
}