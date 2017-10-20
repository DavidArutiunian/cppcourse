#include "main.hpp"

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

void Ball::checkCollisions(std::vector<Ball>& balls, float deltaTime)
{
	constexpr auto length = [](sf::Vector2f vector) -> float {
		return static_cast<float>(std::sqrt(std::pow(vector.x, 2) + std::pow(vector.y, 2)));
	};

	constexpr auto dot = [](sf::Vector2f left, sf::Vector2f right) -> float {
		return left.x * right.x + left.y * right.y;
	};

	constexpr auto index = [](std::vector<Ball>& vector, std::vector<Ball>::iterator& iterator) -> std::size_t {
		return static_cast<std::size_t>(std::distance(vector.begin(), iterator));
	};

	constexpr auto reflect = [](Ball& a, Ball& b) -> sf::Vector2f {
		const sf::Vector2f deltaPosition = a.position - b.position;
		const sf::Vector2f deltaSpeed = a.speed - b.speed;
		const auto squareLength = static_cast<float>(std::pow(length((deltaPosition)), 2));
		const float argument = dot(deltaSpeed, deltaPosition) / squareLength;
		return a.speed - argument * deltaPosition;
	};

	for (auto parentIterator = balls.begin(); parentIterator != balls.end(); ++parentIterator)
	{
		const std::size_t i = index(balls, parentIterator);
		for (auto childIterator = balls.begin(); childIterator != balls.end(); ++childIterator)
		{
			const std::size_t j = index(balls, childIterator);
			if (balls.at(i) == balls.at(j))
			{
				continue;
			}

			const float currentDistance = length((balls.at(i).position - balls.at(j).position));
			const float collisionDistance = balls.at(i).size + balls.at(j).size;

			if (currentDistance <= collisionDistance)
			{
				const sf::Vector2f parentSpeed = reflect(balls.at(i), balls.at(j));
				const sf::Vector2f childSpeed = reflect(balls.at(j), balls.at(i));
				balls.at(i).speed = parentSpeed;
				balls.at(j).speed = childSpeed;
				balls.at(i).updatePosition(deltaTime);
				balls.at(j).updatePosition(deltaTime);
				balls.at(i).updateElement();
				balls.at(j).updateElement();
			}
		}
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
		{ 50.f, 100.f },
		{ 150.f, 200.f },
		{ 250.f, 300.f },
		{ 350.f, 400.f },
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

	for (auto iterator = balls.begin(); iterator != balls.end(); ++iterator)
	{
		const auto i = static_cast<std::size_t>(std::distance(balls.begin(), iterator));
		balls.at(i).id = i;
		balls.at(i).color = colors.at(i);
		balls.at(i).size = sizes.at(i);
		balls.at(i).speed = speeds.at(i);
		balls.at(i).position = positions.at(i);
		balls.at(i).shape.setPosition(balls.at(i).position);
		balls.at(i).shape.setOrigin(balls.at(i).size, balls.at(i).size);
	}
}

bool Ball::operator==(Ball& toCompare)
{
	return this->id == toCompare.id;
}