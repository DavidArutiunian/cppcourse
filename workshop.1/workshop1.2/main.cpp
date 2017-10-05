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

	Arrow arrow;
	sf::Vector2f mousePosition;

	init(arrow);

	while (window.isOpen())
	{
		pollEvents(window, mousePosition);
		update(mousePosition, arrow);
		redrawFrame(window, arrow);
	}
}

// TODO: calculate rotation & position
void update(const sf::Vector2f& mousePosition, Arrow& arrow)
{
	const sf::Vector2f delta = mousePosition - arrow.position;
	const auto path = static_cast<float>(std::sqrt(std::pow(delta.x, 2) - std::pow(delta.y, 2)));
	arrow.position = mousePosition;
	arrow.updateElement();
}

// TODO: set rotation & position
void Arrow::updateElement()
{
	this->shape.setPosition(this->position);
}

void Arrow::setPoints()
{
	this->position = { WINDOW_WIDTH / 2, WINDOW_HEIGHT / 2 };
	this->shape.setPosition(this->position);
	this->shape.setFillColor(this->arrowColor);
	this->shape.setPointCount(this->pointCount);
	this->shape.setPoint(0, { 0, -40 });
	this->shape.setPoint(1, { 40, 0 });
	this->shape.setPoint(2, { 20, 0 });
	this->shape.setPoint(3, { 20, 40 });
	this->shape.setPoint(4, { -20, 40 });
	this->shape.setPoint(5, { -20, 0 });
	this->shape.setPoint(6, { -40, 0 });
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