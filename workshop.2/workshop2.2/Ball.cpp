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
	const std::vector<sf::Color> colors = {
		sf::Color(128, 64, 255),
		sf::Color(255, 64, 128),
		sf::Color(128, 255, 64),
		sf::Color(64, 128, 255),
	};
	const std::vector<sf::Vector2f> speeds = {
		{ 50.f, 100.f },
		{ -150.f, -200.f },
		{ 250.f, 300.f },
		{ -350.f, -400.f },
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
		const auto i = static_cast<unsigned long long>(std::distance(balls.begin(), iterator));
		Ball* ball = &balls.at(i);
		ball->id = i;
		ball->color = colors.at(i);
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