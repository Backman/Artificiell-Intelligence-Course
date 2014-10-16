#pragma once

#include <random>

namespace Utility
{
	template<class T>
	static void deletePointer(T* p)
	{
		if (p != nullptr)
		{
			delete p;
			p = nullptr;
		}
	}

	template<class T>
	static void clearPointerVector(std::vector<T*>* vector)
	{
		while (!vector->empty())
		{
			delete vector->back();
			vector->pop_back();
		}
	}

	static void swapFloats(float& a, float& b)
	{
		float temp = a;
		a = b;
		b = temp;
	}

	static int randomIntRange(int min, int max)
	{
		std::random_device rd; // obtain a random number from hardware
		std::mt19937 gen(rd()); // seed the generator
		std::uniform_int_distribution<> distr(min, max); // define the range

		int random = distr(gen);

		return random;
	}

	static float randomFloatRange(float min = 0.0f, float max = 1.0f)
	{
		if (min > max) {
			swapFloats(min, max);
		}

		float randomNum = min + static_cast <float> (rand()) / (static_cast <float> (RAND_MAX / (max - min)));

		return randomNum;
	}
}