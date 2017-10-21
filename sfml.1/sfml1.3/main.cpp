#include <SFML/Graphics.hpp>
#include <SFML/System.hpp>
#include <SFML/Window.hpp>
#include <cmath>

float OFFSET = 20;

float WINDOW_WIDTH = 800;
float WINDOW_HEIGHT = 600;

struct Shape
{
	sf::RectangleShape shape;
	sf::Color color;
	float width{};
	float height{};
	float x{};
	float y{};
};

struct CircleShape
{
	sf::CircleShape shape;
	sf::Color color;
	float x{};
	float y{};
	float r{};
};

struct ConvexShape : Shape
{
	sf::ConvexShape shape;
	float offset{};
};

Shape drawWalls(sf::RenderWindow* window)
{
	Shape wall;

	wall.width = WINDOW_WIDTH - WINDOW_WIDTH / 4;
	wall.height = WINDOW_HEIGHT - WINDOW_HEIGHT / 2;

	wall.x = WINDOW_WIDTH / 2 - wall.width / 2 + OFFSET;
	wall.y = WINDOW_HEIGHT - wall.height + OFFSET;

	wall.color = sf::Color(0x4D, 0x2E, 0xB);

	sf::RectangleShape shape;
	shape.setSize({ wall.width, wall.height });
	shape.setFillColor(wall.color);
	shape.setPosition({ wall.x, wall.y });

	window->draw(shape);

	wall.shape = shape;

	return wall;
}

Shape drawDoor(sf::RenderWindow* window, Shape* wall)
{
	Shape door;

	door.width = wall->width / 5;
	door.height = static_cast<float>(wall->height / 1.5);

	door.x = wall->width / 10 + wall->x;
	door.y = wall->y + wall->height - door.height;

	door.color = sf::Color(0x18, 0x17, 0x17);

	sf::RectangleShape shape;
	shape.setSize({ door.width, door.height });
	shape.setFillColor(door.color);
	shape.setPosition({ door.x, door.y });

	window->draw(shape);

	door.shape = shape;

	return door;
}

ConvexShape drawRoof(sf::RenderWindow* window, Shape* wall)
{
	ConvexShape roof;

	roof.width = wall->width;
	roof.height = static_cast<float>(wall->height / 2.25);

	roof.x = wall->x;
	roof.y = wall->y - roof.height;

	roof.color = sf::Color(0x5D, 0x1E, 0x17);

	roof.offset = roof.width / 8;

	sf::ConvexShape shape;
	shape.setFillColor(roof.color);
	shape.setPosition({ roof.x, roof.y });
	shape.setPointCount(4);
	shape.setPoint(0, { roof.offset * 1.75f, 0 });
	shape.setPoint(1, { roof.width - roof.offset * 1.75f, 0 });
	shape.setPoint(2, { roof.width + roof.offset, roof.height });
	shape.setPoint(3, { -roof.offset, roof.height });

	window->draw(shape);

	roof.shape = shape;

	return roof;
}

ConvexShape drawChimney(sf::RenderWindow* window, Shape* wall, ConvexShape* roof)
{
	ConvexShape chimney;

	chimney.width = wall->width / 9;
	chimney.height = wall->width / 5;

	chimney.x = roof->x + roof->shape.getPoint(1).x - chimney.width;
	chimney.y = roof->y - chimney.height / 2;

	chimney.color = sf::Color(0x3B, 0x38, 0x38);

	chimney.offset = chimney.width / 6;

	sf::ConvexShape shape;
	shape.setFillColor(chimney.color);
	shape.setPosition({ chimney.x, chimney.y });
	shape.setPointCount(8);
	shape.setPoint(0, { 0, 0 });
	shape.setPoint(1, { chimney.width, 0 });
	shape.setPoint(2, { chimney.width, chimney.height / 2.3f });
	shape.setPoint(3, { chimney.width - chimney.offset, 0 });
	shape.setPoint(4, { chimney.width - chimney.offset, chimney.height });
	shape.setPoint(5, { chimney.offset, chimney.height });
	shape.setPoint(6, { chimney.offset, 0 });
	shape.setPoint(7, { 0, chimney.height / 2.3f });

	chimney.shape = shape;

	window->draw(shape);

	return chimney;
}

std::vector<CircleShape> drawSmoke(sf::RenderWindow* window, Shape* wall)
{

	std::vector<CircleShape> vector;

	for (int i = 0; i <= 3; ++i)
	{
		CircleShape smoke;

		float offset = 3.f * i;

		smoke.r = wall->width / 30 + offset;

		smoke.x = wall->x + wall->width / 1.575f + 2 * smoke.r + offset;
		smoke.y = wall->y - wall->height / 1.35f - i * smoke.r;

		smoke.color = sf::Color(0xBF, 0xBF, 0xBF);

		sf::CircleShape shape;
		shape.setRadius(smoke.r);
		shape.setPosition({ smoke.x, smoke.y });
		shape.setFillColor(smoke.color);

		smoke.shape = shape;

		vector.push_back(smoke);
	}

	for (CircleShape smoke : vector)
	{
		window->draw(smoke.shape);
	}

	return vector;
}

int main()
{
	Shape wall;
	Shape door;
	ConvexShape roof;
	ConvexShape chimney;
	std::vector<CircleShape> smoke;

	sf::VideoMode videoMode = sf::VideoMode((unsigned)WINDOW_WIDTH + (unsigned)(2 * OFFSET),
		(unsigned)WINDOW_HEIGHT + (unsigned)(2 * OFFSET));

	sf::RenderWindow window(videoMode, "Home, sweet home");

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

		window.clear();

		wall = drawWalls(&window);
		door = drawDoor(&window, &wall);
		roof = drawRoof(&window, &wall);
		smoke = drawSmoke(&window, &wall);
		chimney = drawChimney(&window, &wall, &roof);

		window.display();
	}
}