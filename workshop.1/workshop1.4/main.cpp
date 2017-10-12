#include "main.hpp"

int main()
{
#ifdef _WIN32
	ShowWindow(GetConsoleWindow(), SW_HIDE);
#endif

	sf::ContextSettings settings;
	sf::RenderWindow window(sf::VideoMode(WINDOW_WIDTH, WINDOW_HEIGHT), WINDOW_TITLE);
	window.setFramerateLimit(MAX_FPS);
	sf::Clock clock;

	Kitty kitty;
	Pointer pointer;

	sf::Vector2f mousePosition = { WINDOW_WIDTH / 2, WINDOW_HEIGHT / 2 };

	init(kitty, pointer);

	while (window.isOpen())
	{
		pollEvents(window, mousePosition, pointer);
		float deltaTime = clock.restart().asSeconds();
		update(mousePosition, kitty, pointer, deltaTime);
		redrawFrame(window, kitty, pointer);
	}
}

void update(sf::Vector2f& mousePosition, Kitty& kitty, Pointer& pointer, float deltaTime)
{
	const sf::Vector2f delta = mousePosition - kitty.position;

	kitty.updatePosition(delta, deltaTime);
	kitty.updateElement();

	pointer.updatePosition(mousePosition);
	pointer.updateElement();
}

void Kitty::updatePosition(sf::Vector2f delta, float deltaTime)
{
	auto angle = static_cast<float>(atan2(delta.x, delta.y));

	if (angle < 0)
	{
		angle = fmodf(static_cast<float>(angle + 2 * M_PI), static_cast<float>(2 * M_PI));
	}

	angle = toDegrees(angle);

	if ((angle >= 0) && (angle < 180))
	{
		this->scale = { 1, 1 };
	}
	else
	{
		this->scale = { -1, 1 };
	}

	const auto deltaLength = static_cast<float>(std::sqrt(std::pow(delta.x, 2) + std::pow(delta.y, 2)));
	sf::Vector2f direction = { 0, 0 };

	if (deltaLength != 0)
	{
		direction = { delta.x / deltaLength, delta.y / deltaLength };
	}

	const float speed = std::min(deltaLength, 100.f * deltaTime);

	this->position = this->position + direction * speed;
}

void init(Kitty& kitty, Pointer& pointer)
{
	kitty.texture.loadFromFile(kitty.SPRITE_PATH);
	kitty.sprite.setTexture(kitty.texture);
	kitty.sprite.setOrigin(kitty.texture.getSize().x / 2, kitty.texture.getSize().y / 2);
	kitty.position = { WINDOW_WIDTH / 2, WINDOW_HEIGHT / 2 };

	pointer.texture.loadFromFile(pointer.SPRITE_PATH);
	pointer.sprite.setTexture(pointer.texture);
	pointer.sprite.setOrigin(pointer.texture.getSize().x / 2, pointer.texture.getSize().y / 2);
	pointer.scale = { 0, 0 };
}

void pollEvents(sf::RenderWindow& window, sf::Vector2f& mousePosition, Pointer& pointer)
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
			onMouseClick(event.mouseButton, mousePosition, pointer);
			break;
		default:
			break;
		}
	}
}

void redrawFrame(sf::RenderWindow& window, Kitty& kitty, Pointer& pointer)
{
	window.clear(BACKGROUND_COLOR);
	window.draw(pointer.sprite);
	window.draw(kitty.sprite);
	window.display();
}

void onMouseClick(const sf::Event::MouseButtonEvent& event, sf::Vector2f& mousePosition, Pointer& pointer)
{
	pointer.scale = { 1, 1 };
	mousePosition = { static_cast<float>(event.x), static_cast<float>(event.y) };
}

void Pointer::updatePosition(sf::Vector2f& mousePosition)
{
	this->position = mousePosition;
}

void Pointer::updateElement()
{
	this->sprite.setPosition(this->position);
	this->sprite.setScale(this->scale);
}

void Kitty::updateElement()
{
	this->sprite.setPosition(this->position);
	this->sprite.setScale(this->scale);
}

float toDegrees(float radians)
{
	return static_cast<float>(radians * 180.0 / M_PI);
}
