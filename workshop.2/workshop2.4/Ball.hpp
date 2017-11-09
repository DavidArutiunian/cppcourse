#pragma once

#include <SFML/Graphics.hpp>
#include <SFML/System.hpp>
#include <SFML/Window.hpp>

struct Ball
{
	sf::CircleShape shape;
	sf::Vector2f position;

	float size = 0.f;
	size_t id = 0;
	sf::Vector2f speed;
	sf::Color color;

	void updatePosition(float deltaTime);

	void updateElement();

	static void init(std::vector<Ball>& balls);

	static void checkCollisions(std::vector<Ball>& balls);

	bool operator==(Ball& toCompare);
};
