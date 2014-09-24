#pragma once

#include <vector>
#include "Gene.h"

class Chromosome
{
private:
	typedef std::vector<Gene> GeneList;
public:
	Chromosome(int geneCount = 0) :
		_genes(GeneList(geneCount, Gene()))
	{ }

	~Chromosome()
	{ }

	void randomize()
	{
		for (auto& gene : _genes) {
			gene.randomize();
		}
	}

	Gene& operator[](int index)
	{
		return _genes[index];
	}

	const Gene& operator[](int index) const
	{
		return _genes[index];
	}
	
	int getGeneCount() const
	{
		return _genes.size();
	}

	GeneList& getGeneList()
	{
		return _genes;
	}

	friend std::ostream& operator<<(std::ostream& os, const Chromosome& chromosome)
	{
		std::string s = "";

		for (auto& gene : chromosome._genes) {
			s += gene.getChar();
		}

		os << '"' << s << '"';

		return os;
	}

private:
	GeneList _genes;
};