#include "Ball.h"

void Ball::updatePosition(float deltaTime)
{
	position = shape.getPosition();
	position += speed * deltaTime;

	if ((position.x + size >= WINDOW_WIDTH) && (speed.x > 0))
	{
		speed.x = -speed.x;
	}
	if ((position.x - size < 0) && (speed.x < 0))
	{
		speed.x = -speed.x;
	}
	if ((position.y + size >= WINDOW_HEIGHT) && (speed.y > 0))
	{
		speed.y = -speed.y;
	}
	if ((position.y - size < 0) && (speed.y < 0))
	{
		speed.y = -speed.y;
	}
}

void Ball::checkIntersection(std::vector<std::shared_ptr<Ball>>& balls, std::shared_ptr<Ball> ball)
{
	constexpr unsigned windowArea = WINDOW_WIDTH * WINDOW_HEIGHT;
	auto squareArea = static_cast<float>(std::pow(ball->size * 2, 2));

	if (ball->position.x + ball->size >= WINDOW_WIDTH)
	{
		return;
	}
	if (ball->position.x - ball->size < 0)
	{
		return;
	}
	if (ball->position.y + ball->size >= WINDOW_HEIGHT)
	{
		return;
	}
	if (ball->position.y - ball->size < 0)
	{
		return;
	}

	for (auto&& item : balls)
	{
		const float currentDistance = Ball::length((item->position - ball->position));
		const float collisionDistance = item->size + ball->size;

		squareArea += std::pow(item->size * 2, 2);

		const bool doesIntersect = currentDistance <= collisionDistance;
		const bool doesNotFit = squareArea > windowArea;

		if (doesIntersect || doesNotFit)
		{
			return;
		}
	}

	balls.push_back(ball);
}

void Ball::addBall(std::vector<std::shared_ptr<Ball>>& balls, sf::Vector2f& mousePosition)
{
	std::shared_ptr<Ball> ball(std::make_shared<Ball>(Ball(mousePosition,
		{ randomFloat(generator, MIN_SPEED, MAX_SPEED),
			randomFloat(generator, MIN_SPEED, MAX_SPEED) },
		sf::Color(
			static_cast<sf::Uint8>(randomInt(generator, 0, 255)),
			static_cast<sf::Uint8>(randomInt(generator, 0, 255)),
			static_cast<sf::Uint8>(randomInt(generator, 0, 255))),
		randomInt(generator, MIN_SIZE, MAX_SIZE))));

	ball->shape.setPosition(ball->position);
	ball->shape.setOrigin(ball->size, ball->size);
	ball->shape.setRadius(ball->size);
	ball->shape.setFillColor(ball->color);

	Ball::checkIntersection(balls, ball);
}

void Ball::checkCollisions(std::vector<std::shared_ptr<Ball>>& balls)
{
	constexpr auto areCloseAbsolute = [](float a, float b, float tolerance = 0.001f) -> bool {
		return std::abs(a - b) < tolerance;
	};

	constexpr auto areCloseRelative = [](float a, float b, float tolerance = 0.001f) -> bool {
		return std::abs((a - b) / b) < tolerance;
	};

	const auto areFuzzyEqual = [&areCloseAbsolute, &areCloseRelative](float a, float b) -> bool {
		constexpr float tolerance = 0.001f;
		if (std::abs(b) > 1.f)
		{
			return areCloseRelative(a, b, tolerance);
		}
		return areCloseAbsolute(a, b, tolerance);
	};

	constexpr auto dot = [](sf::Vector2f& left, sf::Vector2f& right) -> float {
		return left.x * right.x + left.y * right.y;
	};

	const auto getSpeedAfterCollision = [&dot](std::shared_ptr<Ball> a, std::shared_ptr<Ball> b) -> sf::Vector2f {
		sf::Vector2f deltaPosition = a->position - b->position;
		sf::Vector2f deltaSpeed = a->speed - b->speed;
		const auto squareLength = static_cast<float>(std::pow(Ball::length((deltaPosition)), 2));
		assert(squareLength != 0);
		const float leftSide = dot(deltaSpeed, deltaPosition) / squareLength;
		return a->speed - leftSide * deltaPosition;
	};

	const auto size = static_cast<size_t>(std::distance(balls.begin(), balls.end()));

	for (size_t fi = 0; fi < size; ++fi)
	{
		std::shared_ptr<Ball> firstBall = balls.at(fi);
		for (size_t si = fi + 1; si < size; ++si)
		{
			std::shared_ptr<Ball> secondBall = balls.at(si);

			const float currentDistance = length((firstBall->position - secondBall->position));
			const float collisionDistance = firstBall->size + secondBall->size;

			if (currentDistance <= collisionDistance)
			{
				const sf::Vector2f prevFirstSpeed = firstBall->speed;
				const sf::Vector2f prevSecondSpeed = secondBall->speed;
				const sf::Vector2f nextFirstSpeed = getSpeedAfterCollision(firstBall, secondBall);
				const sf::Vector2f nextSecondSpeed = getSpeedAfterCollision(secondBall, firstBall);
				const auto prevE = static_cast<float>(std::pow(length(prevFirstSpeed), 2) + std::pow(length(prevSecondSpeed), 2));
				const auto nextE = static_cast<float>(std::pow(length(nextFirstSpeed), 2) + std::pow(length(nextSecondSpeed), 2));
				const float prevI = length(prevFirstSpeed + prevSecondSpeed);
				const float nextI = length(nextFirstSpeed + nextSecondSpeed);
				assert(areFuzzyEqual(prevE, nextE));
				assert(areFuzzyEqual(prevI, nextI));
				firstBall->speed = nextFirstSpeed;
				secondBall->speed = nextSecondSpeed;
			}
		}
	}
}

void Ball::updateElement()
{
	shape.setPosition(position);
}

void Ball::init(std::vector<std::shared_ptr<Ball>>& balls)
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
		const auto i = static_cast<unsigned long long>(randomInt(generator, 0, length));
		const auto j = static_cast<unsigned long long>(randomInt(generator, 0, length));
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
		{ randomFloat(generator, MIN_SPEED, MAX_SPEED), randomFloat(generator, MIN_SPEED, MAX_SPEED) },
		{ randomFloat(generator, MIN_SPEED, MAX_SPEED), randomFloat(generator, MIN_SPEED, MAX_SPEED) },
		{ randomFloat(generator, MIN_SPEED, MAX_SPEED), randomFloat(generator, MIN_SPEED, MAX_SPEED) },
		{ randomFloat(generator, MIN_SPEED, MAX_SPEED), randomFloat(generator, MIN_SPEED, MAX_SPEED) },
	};
	const std::vector<float> sizes = {
		static_cast<float>(randomInt(generator, MIN_SIZE, MAX_SIZE)),
		static_cast<float>(randomInt(generator, MIN_SIZE, MAX_SIZE)),
		static_cast<float>(randomInt(generator, MIN_SIZE, MAX_SIZE)),
		static_cast<float>(randomInt(generator, MIN_SIZE, MAX_SIZE)),
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
		std::shared_ptr<Ball> ball = std::make_shared<Ball>(Ball(positions.at(i),
			speeds.at(i),
			getRandomColor(colors),
			sizes.at(i)));
		ball->shape.setPosition(ball->position);
		ball->shape.setOrigin(ball->size, ball->size);
		ball->shape.setRadius(ball->size);
		ball->shape.setFillColor(ball->color);

		balls.at(i) = ball;
	}
}

bool Ball::operator==(Ball& toCompare) const
{
	return std::addressof(*this) == std::addressof(toCompare);
}

float Ball::length(const sf::Vector2f& vector)
{
	return static_cast<float>(std::sqrt(std::pow(vector.x, 2) + std::pow(vector.y, 2)));
}

void Ball::updateBallLifetimes(float deltaTime)
{
	lifeTime += deltaTime;
}

void Ball::removeDeathBalls(std::vector<std::shared_ptr<Ball>>& balls)
{
	constexpr auto shouldRemove = [](const std::shared_ptr<Ball> ball) -> bool {
		return ball->lifeTime >= MAX_LIFETIME;
	};
	balls.erase(std::remove_if(balls.begin(), balls.end(), shouldRemove), balls.end());
}

void Ball::draw(sf::RenderTarget& target, sf::RenderStates states) const
{
	target.draw(shape, states);
}

Ball::Ball(sf::Vector2f position, sf::Vector2f speed, sf::Color color, float size)
	: position(position)
	, speed(speed)
	, color(color)
	, size(size)
{
}