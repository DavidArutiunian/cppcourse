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
	constexpr auto getVectorLength = [](sf::Vector2f vector) -> float {
		return static_cast<float>(std::sqrt(std::pow(vector.x, 2) + std::pow(vector.y, 2)));
	};

	constexpr auto getDotProduct = [](sf::Vector2f left, sf::Vector2f right) -> float {
		return left.x * right.x + left.y * right.y;
	};

	const auto getSpeedAfterCollision = [&getDotProduct](Ball* a, Ball* b) -> sf::Vector2f {
		const sf::Vector2f deltaPosition = a->position - b->position;
		const sf::Vector2f deltaSpeed = a->speed - b->speed;
		const auto squareLength = static_cast<float>(std::pow(getVectorLength((deltaPosition)), 2));
		const float leftSide = getDotProduct(deltaSpeed, deltaPosition) / squareLength;
		return a->speed - leftSide * deltaPosition;
	};

	const auto size = static_cast<size_t>(std::distance(balls.begin(), balls.end()));

	for (size_t fi = 0; fi < size; ++fi)
	{
		Ball* firstBall = &balls.at(fi);
		for (size_t si = fi + 1; si < size; ++si)
		{
			Ball* secondBall = &balls.at(si);

			const float currentDistance = getVectorLength((firstBall->position - secondBall->position));
			const float collisionDistance = firstBall->size + secondBall->size;

			if (currentDistance <= collisionDistance)
			{
				const sf::Vector2f first = getSpeedAfterCollision(firstBall, secondBall);
				const sf::Vector2f second = getSpeedAfterCollision(secondBall, firstBall);
				firstBall->speed = first;
				secondBall->speed = second;
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

	const auto getRandomColor = [&getMixedColor, &generator](const std::vector<sf::Color>& colors) -> sf::Color {
		const auto length = static_cast<unsigned>(std::distance(colors.begin(), colors.end())) - 1;
		const auto i = static_cast<unsigned long long>(random_int(generator, 0, length));
		const auto j = static_cast<unsigned long long>(random_int(generator, 0, length));
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
		const auto i = static_cast<unsigned long long>(std::distance(balls.begin(), iterator));
		Ball* ball = &balls.at(i);
		ball->id = i;
		ball->color = getRandomColor(colors);
		ball->size = sizes.at(i);
		ball->speed = speeds.at(i);
		ball->position = positions.at(i);
		ball->shape.setPosition(ball->position);
		ball->shape.setOrigin(ball->size, ball->size);
		ball->shape.setRadius(ball->size);
		ball->shape.setFillColor(ball->color);
	}
}

bool Ball::operator==(Ball& toCompare)
{
	return this->id == toCompare.id;
}