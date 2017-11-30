#include <cassert>
#include <cmath>
#include <memory>

#include "Ball.h"
#include "Random.h"
#include "consts.h"

void Ball::updatePosition(const float deltaTime)
{
	position = shape.getPosition();
	position += speed * deltaTime;

	if ((position.x + size >= GAME_FIELD_WIDTH) && (speed.x > 0))
	{
		speed.x = -speed.x;
	}
	if ((position.x - size < -1.f * GAME_FIELD_WIDTH) && (speed.x < 0))
	{
		speed.x = -speed.x;
	}
	if ((position.y + size >= GAME_FIELD_HEIGHT) && (speed.y > 0))
	{
		speed.y = -speed.y;
	}
	if ((position.y - size < -1.f * GAME_FIELD_HEIGHT) && (speed.y < 0))
	{
		speed.y = -speed.y;
	}
}

void Ball::checkIntersection(std::vector<std::shared_ptr<Ball>>& balls, const std::shared_ptr<Ball>& ball)
{
	constexpr unsigned windowArea = GAME_FIELD_WIDTH * GAME_FIELD_HEIGHT;
	auto squareArea = static_cast<float>(std::pow(ball->size * 2, 2));
	const sf::Vector2f position = ball->position;
	const float size = ball->size;

	if (position.x + size >= GAME_FIELD_WIDTH)
	{
		return;
	}
	if (position.x - size < -1.f * GAME_FIELD_WIDTH)
	{
		return;
	}
	if (position.y + size >= GAME_FIELD_HEIGHT)
	{
		return;
	}
	if (position.y - size < -1.f * GAME_FIELD_HEIGHT)
	{
		return;
	}

	const auto doNotIntersect = [&squareArea, &position, &size](std::shared_ptr<Ball> ball) -> bool {
		const float currentDistance = Ball::length((ball->position - position));
		const float collisionDistance = ball->size + size;

		squareArea += std::pow(ball->size * 2, 2);

		const bool doesIntersect = currentDistance <= collisionDistance;
		const bool doesNotFit = squareArea > windowArea;

		return !(doesIntersect || doesNotFit);
	};

	if (std::all_of(balls.begin(), balls.end(), doNotIntersect))
	{
		balls.push_back(ball);
	}
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

	sf::CircleShape& shape = ball->shape;

	shape.setPosition(ball->position);
	shape.setOrigin(ball->size, ball->size);
	shape.setRadius(ball->size);
	shape.setFillColor(ball->color);
	shape.setOutlineColor(sf::Color::Black);
	shape.setOutlineThickness(ball->size / 10);

	Ball::checkIntersection(balls, ball);
}

void Ball::checkCollisions(std::vector<std::shared_ptr<Ball>>& balls)
{
	const auto areCloseAbsolute = [](float a, float b, float tolerance = 0.001f) -> bool {
		return std::abs(a - b) < tolerance;
	};

	const auto areCloseRelative = [](float a, float b, float tolerance = 0.001f) -> bool {
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

	const auto dot = [](const sf::Vector2f& left, const sf::Vector2f& right) -> float {
		return left.x * right.x + left.y * right.y;
	};

	const auto getSpeedAfterCollision = [&dot, &areFuzzyEqual](const std::shared_ptr<Ball> a,
											const std::shared_ptr<Ball> b) -> sf::Vector2f {
		sf::Vector2f deltaPosition = a->position - b->position;
		sf::Vector2f deltaSpeed = a->speed - b->speed;
		const auto squareLength = static_cast<float>(std::pow(Ball::length((deltaPosition)), 2));
		assert(!areFuzzyEqual(squareLength, 0.f));
		const float leftSide = dot(deltaSpeed, deltaPosition) / squareLength;
		return a->speed - leftSide * deltaPosition;
	};

	const auto getFullEnergy = [](const sf::Vector2f& lhs, const sf::Vector2f& rhs) -> float {
		return static_cast<float>(std::pow(length(lhs), 2) + std::pow(length(rhs), 2));
	};

	const auto size = static_cast<size_t>(std::distance(balls.begin(), balls.end()));

	/// Iterate though std::vector<Ball> without duplicates
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
				const float prevEnergy = getFullEnergy(prevFirstSpeed, prevSecondSpeed);
				const float nextEnergy = getFullEnergy(nextFirstSpeed, nextSecondSpeed);
				const float prevI = length(prevFirstSpeed + prevSecondSpeed);
				const float nextI = length(nextFirstSpeed + nextSecondSpeed);
				assert(areFuzzyEqual(prevEnergy, nextEnergy));
				assert(areFuzzyEqual(prevI, nextI));
				firstBall->setSpeed(nextFirstSpeed);
				secondBall->setSpeed(nextSecondSpeed);
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

	const auto getMixedColor = [](const sf::Color& a, const sf::Color& b) -> sf::Color {
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
		{ GAME_FIELD_WIDTH - sizes.at(1), sizes.at(1) },
		{ sizes.at(2), GAME_FIELD_WIDTH - sizes.at(2) },
		{ GAME_FIELD_WIDTH - sizes.at(3), GAME_FIELD_WIDTH - sizes.at(3) },
	};

	const auto applyForEach = [&](std::shared_ptr<Ball> ball) -> void {
		const auto iterator = std::find(balls.begin(), balls.end(), ball);
		const auto i = static_cast<unsigned long long>(std::distance(balls.begin(), iterator));

		ball = std::make_shared<Ball>(Ball(positions.at(i), speeds.at(i), getRandomColor(colors), sizes.at(i)));

		sf::CircleShape& shape = ball->shape;

		shape.setPosition(ball->position);
		shape.setOrigin(ball->size, ball->size);
		shape.setRadius(ball->size);
		shape.setFillColor(ball->color);
		shape.setOutlineColor(sf::Color::Black);
		shape.setOutlineThickness(ball->size / 10);
		balls.at(i) = ball;
	};

	std::for_each(balls.begin(), balls.end(), applyForEach);
}

bool Ball::operator==(Ball& toCompare) const
{
	return std::addressof(*this) == std::addressof(toCompare);
}

float Ball::length(const sf::Vector2f& vector)
{
	return static_cast<float>(std::sqrt(std::pow(vector.x, 2) + std::pow(vector.y, 2)));
}

void Ball::updateBallLifetimes(const float deltaTime)
{
	lifeTime += deltaTime;
}

void Ball::removeDeathBalls(std::vector<std::shared_ptr<Ball>>& balls)
{
	const auto shouldRemove = [](const std::shared_ptr<Ball>& ball) -> bool {
		return ball->lifeTime >= MAX_LIFETIME;
	};
	balls.erase(std::remove_if(balls.begin(), balls.end(), shouldRemove), balls.end());
}

void Ball::draw(sf::RenderTarget& target, const sf::RenderStates states) const
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

void Ball::setSpeed(const sf::Vector2f& nextSpeed)
{
	speed = nextSpeed;
}
