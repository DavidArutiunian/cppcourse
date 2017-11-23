#ifndef CPPCOURSE_RANDOM_H
#define CPPCOURSE_RANDOM_H

#include <random>

struct PRNG
{
	std::mt19937 engine;
};

void initGenerator(PRNG& generator);

unsigned randomInt(PRNG& generator, unsigned minValue, unsigned maxValue);

float randomFloat(PRNG& generator, float minValue, float maxValue);

#endif //CPPCOURSE_RANDOM_H
