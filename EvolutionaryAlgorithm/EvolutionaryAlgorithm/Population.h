#pragma once

#include <algorithm>
#include "Individual.h"

class Population
{
private:
	typedef std::vector<Individual> IndividualList;

public:

	Population() :
		_individuals()
	{
	}

	~Population()
	{ }

	Population& operator=(const Population& rhs)
	{
		_individuals = rhs._individuals;

		return *this;
	}

	void sortPopulation()
	{
		std::sort(_individuals.begin(), _individuals.end(),
			[](const Individual& a, const Individual& b)
		{
			return a > b;
		});
	}

	void randomize()
	{
		for (auto& ind : _individuals) {
			ind.randomize();
		}
	}

	int getIndividualCount() const
	{
		return _individuals.size();
	}

	Individual& operator[](int index)
	{
		return _individuals[index];
	}

	void addIndividual(Individual& individual)
	{
		_individuals.push_back(individual);
	}

	bool operator<(const Population& rhs) const
	{
		return _individuals.size() < rhs._individuals.size();
	}

	float getTotalFitness() const
	{
		int fitness = 0;
		for (auto& ind : _individuals) {
			fitness += ind.getFitness();
		}

		return fitness;
	}

	IndividualList& getIndividualList()
	{
		return _individuals;
	}

private:

	IndividualList _individuals;
};