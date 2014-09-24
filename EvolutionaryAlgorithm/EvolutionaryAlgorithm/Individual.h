#pragma once

#include "Chromosome.h"

class Individual
{
public:

	Individual()
	{ }

	~Individual()
	{ }

	float getFitness() const
	{
		return _fitness;
	}

	Chromosome& getChromosome()
	{
		return _chromosome;
	}

	void setChromosome(Chromosome& chromosome)
	{
		_chromosome = chromosome;
	}

	void setFitness(float val)
	{
		_fitness = val;
	}

	void randomize()
	{
		_chromosome.randomize();
	}

	bool operator>(const Individual& rhs) const
	{
		return _fitness > rhs._fitness;
	}

private:
	float _fitness;
	Chromosome _chromosome;
};