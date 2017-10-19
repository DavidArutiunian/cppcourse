#pragma once

#include <cassert>
#include <chrono>
#include <random>

struct PRNG
{
	std::mt19937 engine;
};

void initGenerator(PRNG& generator);

unsigned int random_int(PRNG& generator, unsigned int minValue, unsigned int maxValue);

float random_float(PRNG& generator, float minValue, float maxValue);
