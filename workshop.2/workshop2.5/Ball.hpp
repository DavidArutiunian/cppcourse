#pragma once

#include "Random.hpp"
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

	static void addBall(std::vector<Ball>& balls, sf::Vector2f& mousePosition);

	static void checkIntersection(std::vector<Ball>& balls, Ball& ball);

	static float length(const sf::Vector2f& vector);

	bool operator==(Ball& toCompare);
};
