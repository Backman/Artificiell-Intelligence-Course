#pragma once

#include <cstdlib>

static void swapFloats(float& a, float& b)
{
	float temp = a;
	a = b;
	b = temp;
}

static float randomFloatRange(float min = 0.0f, float max = 1.0f)
{
	if (min > max) {
		swapFloats(min, max);
	}

	float randomNum = min + static_cast <float> (rand()) / (static_cast <float> (RAND_MAX / (max - min)));

	return randomNum;
}