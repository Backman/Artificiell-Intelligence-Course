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

	bool operator<(const Individual& rhs) const
	{
		return _fitness < rhs._fitness;
	}

	Individual& operator=(const Individual& rhs) 
	{
		_fitness = rhs._fitness;
		_chromosome = rhs._chromosome;

		return *this;
	}

	friend std::ostream& operator<<(std::ostream& os, const Individual& ind)
	{
		os << "Fitness: " << ind._fitness << " | Chromosome: " << ind._chromosome;

		return os;
	}

private:
	float _fitness;
	Chromosome _chromosome;
};