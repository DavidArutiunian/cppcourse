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

void Ball::checkCollisions(std::vector<Ball>& balls)
{
	constexpr auto length = [](sf::Vector2f vector) -> float {
		return static_cast<float>(std::sqrt(std::pow(vector.x, 2) + std::pow(vector.y, 2)));
	};

	constexpr auto dot = [](sf::Vector2f left, sf::Vector2f right) -> float {
		return left.x * right.x + left.y * right.y;
	};

	const auto reflect = [&dot, &length](Ball& a, Ball& b) -> sf::Vector2f {
		const sf::Vector2f deltaPosition = a.position - b.position;
		const sf::Vector2f deltaSpeed = a.speed - b.speed;
		const auto squareLength = static_cast<float>(std::pow(length((deltaPosition)), 2));
		const float leftSide = dot(deltaSpeed, deltaPosition) / squareLength;
		return a.speed - leftSide * deltaPosition;
	};

	const auto size = static_cast<unsigned>(std::distance(balls.begin(), balls.end()));

	for (size_t i = 0; i < size; ++i)
	{
		for (size_t j = i + 1; j < size; ++j)
		{
			const float currentDistance = length((balls.at(i).position - balls.at(j).position));
			const float collisionDistance = balls.at(i).size + balls.at(j).size;

			if (currentDistance <= collisionDistance)
			{
				const sf::Vector2f parentSpeed = reflect(balls.at(i), balls.at(j));
				const sf::Vector2f childSpeed = reflect(balls.at(j), balls.at(i));
				balls.at(i).speed = parentSpeed;
				balls.at(j).speed = childSpeed;
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
	PRNG generator;
	initGenerator(generator);

	constexpr auto getMixedColor = [](const sf::Color& a, const sf::Color& b) -> sf::Color {
		sf::Color color;
		color.r = static_cast<sf::Uint8>((a.r + b.r) / 2);
		color.g = static_cast<sf::Uint8>((a.g + b.g) / 2);
		color.b = static_cast<sf::Uint8>((a.b + b.b) / 2);
		return color;
	};

	const auto getRandomColor = [&generator, &getMixedColor](const std::vector<sf::Color>& colors) -> sf::Color {
		const auto length = static_cast<unsigned>(std::distance(colors.begin(), colors.end())) - 1;
		const unsigned i = random_int(generator, 0, length);
		const unsigned j = random_int(generator, 0, length);
		const sf::Color first = colors.at(i);
		const sf::Color second = colors.at(j);
		return getMixedColor(first, second);
	};

	const std::vector<sf::Color> colors = {
		sf::Color(0, 0, 255),
		sf::Color(0, 255, 0),
		sf::Color(0, 255, 255),
		sf::Color(204, 51, 255),
		sf::Color(255, 0, 0),
		sf::Color(255, 255, 0),
		sf::Color(255, 255, 255),
		sf::Color(153, 102, 0),
	};
	const std::vector<sf::Vector2f> speeds = {
		{ random_float(generator, MIN_SPEED, MAX_SPEED), random_float(generator, MIN_SPEED, MAX_SPEED) },
		{ random_float(generator, MIN_SPEED, MAX_SPEED), random_float(generator, MIN_SPEED, MAX_SPEED) },
		{ random_float(generator, MIN_SPEED, MAX_SPEED), random_float(generator, MIN_SPEED, MAX_SPEED) },
		{ random_float(generator, MIN_SPEED, MAX_SPEED), random_float(generator, MIN_SPEED, MAX_SPEED) },
	};
	const std::vector<float> sizes = {
		static_cast<float>(random_int(generator, MIN_SIZE, MAX_SIZE)),
		static_cast<float>(random_int(generator, MIN_SIZE, MAX_SIZE)),
		static_cast<float>(random_int(generator, MIN_SIZE, MAX_SIZE)),
		static_cast<float>(random_int(generator, MIN_SIZE, MAX_SIZE)),
	};
	const std::vector<sf::Vector2f> positions = {
		{ sizes.at(0), sizes.at(0) },
		{ WINDOW_WIDTH - sizes.at(1), sizes.at(1) },
		{ sizes.at(2), WINDOW_HEIGHT - sizes.at(2) },
		{ WINDOW_WIDTH - sizes.at(3), WINDOW_HEIGHT - sizes.at(3) },
	};

	for (auto iterator = balls.begin(); iterator != balls.end(); ++iterator)
	{
		const auto i = static_cast<size_t>(std::distance(balls.begin(), iterator));
		balls.at(i).id = i;
		balls.at(i).color = getRandomColor(colors);
		balls.at(i).size = sizes.at(i);
		balls.at(i).speed = speeds.at(i);
		balls.at(i).position = positions.at(i);
		balls.at(i).shape.setPosition(balls.at(i).position);
		balls.at(i).shape.setOrigin(balls.at(i).size, balls.at(i).size);
		balls.at(i).shape.setRadius(balls.at(i).size);
		balls.at(i).shape.setFillColor(balls.at(i).color);
	}
}

bool Ball::operator==(Ball& toCompare)
{
	return this->id == toCompare.id;
}