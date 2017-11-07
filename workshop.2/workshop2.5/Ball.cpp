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

void Ball::checkIntersection(std::vector<Ball>& balls, Ball& ball)
{
	constexpr unsigned windowArea = WINDOW_WIDTH * WINDOW_HEIGHT;
	auto squareArea = static_cast<float>(std::pow(ball.size * 2, 2));

	if (ball.position.x + ball.size >= WINDOW_WIDTH)
	{
		return;
	}
	if (ball.position.x - ball.size < 0)
	{
		return;
	}
	if (ball.position.y + ball.size >= WINDOW_HEIGHT)
	{
		return;
	}
	if (ball.position.y - ball.size < 0)
	{
		return;
	}

	for (auto&& item : balls)
	{
		const float currentDistance = Ball::length((item.position - ball.position));
		const float collisionDistance = item.size + ball.size;

		squareArea += std::pow(item.size * 2, 2);

		const bool doesIntersect = currentDistance <= collisionDistance;
		const bool doesNotFit = squareArea > windowArea;

		if (doesIntersect || doesNotFit)
		{
			return;
		}
	}

	balls.push_back(ball);
}

void Ball::addBall(std::vector<Ball>& balls, sf::Vector2f& mousePosition)
{
	const auto size = static_cast<size_t>(std::distance(balls.begin(), balls.end()));

	Ball ball;

	ball.id = size + 1;
	ball.color = sf::Color(
		static_cast<sf::Uint8>(random_int(generator, 0, 255)),
		static_cast<sf::Uint8>(random_int(generator, 0, 255)),
		static_cast<sf::Uint8>(random_int(generator, 0, 255)));
	ball.size = random_int(generator, MIN_SIZE, MAX_SIZE);
	ball.speed = { random_float(generator, MIN_SPEED, MAX_SPEED), random_float(generator, MIN_SPEED, MAX_SPEED) };
	ball.position = mousePosition;
	ball.shape.setPosition(ball.position);
	ball.shape.setOrigin(ball.size, ball.size);
	ball.shape.setRadius(ball.size);
	ball.shape.setFillColor(ball.color);

	Ball::checkIntersection(balls, ball);
}

void Ball::checkCollisions(std::vector<Ball>& balls)
{
	constexpr auto dot = [](sf::Vector2f left, sf::Vector2f right) -> float {
		return left.x * right.x + left.y * right.y;
	};

	const auto getSpeedAfterCollision = [&dot](Ball* a, Ball* b) -> sf::Vector2f {
		const sf::Vector2f deltaPosition = a->position - b->position;
		const sf::Vector2f deltaSpeed = a->speed - b->speed;
		const auto squareLength = static_cast<float>(std::pow(Ball::length((deltaPosition)), 2));
		const float leftSide = dot(deltaSpeed, deltaPosition) / squareLength;
		return a->speed - leftSide * deltaPosition;
	};

	const auto size = static_cast<size_t>(std::distance(balls.begin(), balls.end()));

	for (size_t fi = 0; fi < size; ++fi)
	{
		Ball* firstBall = &balls.at(fi);
		for (size_t si = fi + 1; si < size; ++si)
		{
			Ball* secondBall = &balls.at(si);

			const float currentDistance = Ball::length((firstBall->position - secondBall->position));
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
	initGenerator(generator);

	constexpr auto getMixedColor = [](const sf::Color& a, const sf::Color& b) -> sf::Color {
		sf::Color color;
		color.r = static_cast<sf::Uint8>((a.r + b.r) / 2);
		color.g = static_cast<sf::Uint8>((a.g + b.g) / 2);
		color.b = static_cast<sf::Uint8>((a.b + b.b) / 2);
		return color;
	};

	const auto getRandomColor = [&getMixedColor](const std::vector<sf::Color>& colors) -> sf::Color {
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

float Ball::length(const sf::Vector2f& vector)
{
	return static_cast<float>(std::sqrt(std::pow(vector.x, 2) + std::pow(vector.y, 2)));
}