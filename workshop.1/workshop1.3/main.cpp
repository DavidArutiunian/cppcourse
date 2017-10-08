#include "main.hpp"

int main()
{
#ifdef _WIN32
	ShowWindow(GetConsoleWindow(), SW_HIDE);
#endif

	sf::RenderWindow window(sf::VideoMode(WINDOW_WIDTH, WINDOW_HEIGHT), WINDOW_TITLE);
	window.setFramerateLimit(MAX_FPS);

	sf::Texture texture;
	texture.loadFromFile(SPRITE_PATH);

	sf::Sprite sprite;
	sprite.setTexture(texture);
	sprite.setPosition(WINDOW_WIDTH / 2, WINDOW_HEIGHT / 2);

	while (window.isOpen())
	{
		sf::Event event{};
		while (window.pollEvent(event))
		{
			if (event.type == sf::Event::Closed)
			{
				window.close();
			}
		}

		window.clear(BACKGROUND_COLOR);
		window.draw(sprite);
		window.display();
	}
}