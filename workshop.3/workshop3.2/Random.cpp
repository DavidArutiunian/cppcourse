#include <cassert>

#include "consts.h"

void initGenerator(PRNG& generator)
{
	const auto seed = static_cast<unsigned>(std::time(nullptr));
	generator.engine.seed(seed);
}

unsigned randomInt(PRNG& generator, unsigned minValue, unsigned maxValue)
{
	assert(minValue < maxValue);
	std::uniform_int_distribution<unsigned> distribution(minValue, maxValue);
	return distribution(generator.engine);
}

float randomFloat(PRNG& generator, float minValue, float maxValue)
{
	assert(minValue < maxValue);
	std::uniform_real_distribution<float> distribution(minValue, maxValue);
	return distribution(generator.engine);
}