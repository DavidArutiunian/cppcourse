#include "Random.hpp"

void initGenerator(PRNG& generator)
{
	using clock = std::chrono::high_resolution_clock;
	const std::chrono::time_point now = clock::now();
	const std::chrono::time_point epochTime = clock::from_time_t(0);
	const clock::duration duration = now - epochTime;
	const auto seed = static_cast<unsigned>(duration.count());
	generator.engine.seed(seed);
}

unsigned random_int(PRNG& generator, unsigned minValue, unsigned maxValue)
{
	assert(minValue < maxValue);
	std::uniform_int_distribution<unsigned> distribution(minValue, maxValue);
	return distribution(generator.engine);
}

float random_float(PRNG& generator, float minValue, float maxValue)
{
	assert(minValue < maxValue);
	std::uniform_real_distribution<float> distribution(minValue, maxValue + 1.f);
	return distribution(generator.engine);
}