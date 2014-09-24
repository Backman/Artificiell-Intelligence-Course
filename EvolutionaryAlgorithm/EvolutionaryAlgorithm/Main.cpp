
#include <iostream>
#include <random>
#include <time.h>
#include <string>
#include "Population.h"
#include "Defines.h"

void evolve(Population& population);
float evaluate(Chromosome& chromosome);
Individual& select(Population& population);
void crossover(Chromosome& chromosome1, Chromosome& chromosome2);
void mutate(Chromosome& chromosome1, Chromosome& chromosome2);

void geneSwap(Gene& gene1, Gene& gene2);

float randomRange(float min, float max);
int randomRange(int min, int max);

const std::string targetString = "Ey man, League of Legends";

float bestFitness = 0;

int main()
{
	srand(time(NULL));
	Population population;

	for (int i = 0; i < POPULATION_COUNT; ++i) {
		Individual ind;
		Chromosome chromosome(targetString.size());
		chromosome.randomize();
		float fitness = evaluate(chromosome);
		ind.setChromosome(chromosome);
		ind.setFitness(fitness);

		population.addIndividual(ind);
	}

	population.sortPopulation();


	std::string solution = "";

	int nth = 128;
	for (int i = 0; i < GENERATION_COUNT; ++i) {
		evolve(population);
		population.sortPopulation();
		if (bestFitness < population[0].getFitness()) {
			bestFitness = population[0].getFitness();
			solution = "";

			Chromosome chrom = population[0].getChromosome();

			for (auto& gene : chrom.getGeneList()) {
				solution += gene.getChar();
			}
			
		}

		if (i % nth == 0) {
			std::cout << "Current best fitness: " << bestFitness << " | " << solution << std::endl;
		}

		if (bestFitness == 1){
			break;
		}
	}

	

	std::cout << "Found solution: " + solution << std::endl;

	

	std::cin.get();
	return 0;
}

void evolve(Population& population)
{
	Population newGeneration;
	while (newGeneration < population) {
		Chromosome chromosome1 = select(population).getChromosome();
		Chromosome chromosome2 = select(population).getChromosome();
		crossover(chromosome1, chromosome2);
		mutate(chromosome1, chromosome2);

		Individual newInd1;
		newInd1.setChromosome(chromosome1);
		newInd1.setFitness(evaluate(chromosome1));
		newGeneration.addIndividual(newInd1);
		if (newGeneration < population) {
			Individual newInd2;
			newInd2.setChromosome(chromosome2);
			newInd2.setFitness(evaluate(chromosome2));
			newGeneration.addIndividual(newInd2);
		}
	}
	population = newGeneration;
}

float evaluate(Chromosome& chromosome)
{
	int targetSize = targetString.size();

	float fitness = 0;
	for (int i = 0; i < targetSize; ++i) {
		if (chromosome[i].getChar() == targetString[i]) {
			fitness += 1;
		}
	}
	
	return fitness / targetSize;
}

Individual& select(Population& population)
{
	float totalFitness = population.getTotalFitness();
	float ballPos = randomRange(0.0f, totalFitness);
	float sum = 0;
	for (auto& ind : population.getIndividualList()) {
		sum += ind.getFitness();
		if (ballPos <= sum) {
			return ind;
		}
	}
}

void crossover(Chromosome& chromosome1, Chromosome& chromosome2)
{
	float randomVal = randomRange(0.0f, 1.0f);
	if (randomVal < CROSSOVER_RATE) {

		int count = std::min(chromosome1.getGeneCount(), chromosome2.getGeneCount());
		int start = randomRange(0, count - 1);
		for (int i = start; i < count; ++i) {
			geneSwap(chromosome1[i], chromosome2[i]);
		}
	}
}

void mutate(Chromosome& chromosome1, Chromosome& chromosome2)
{
	for (auto& gene : chromosome1.getGeneList()) {
		if (randomRange(0.0f, 1.0f) < MUTATION_RATE) {
			gene.randomize();
		}
	}

	for (auto& gene : chromosome2.getGeneList()) {
		if (randomRange(0.0f, 1.0f) < MUTATION_RATE) {
			gene.randomize();
		}
	}
}

float randomRange(float min, float max)
{
	float random = static_cast<float>(rand()) / (static_cast<float>(RAND_MAX / (max - min)));

	return random;
}

int randomRange(int min, int max)
{
	std::random_device rd; // obtain a random number from hardware
	std::mt19937 gen(rd()); // seed the generator
	std::uniform_int_distribution<int> distr(min, max); // define the range

	int random = distr(gen);

	return random;
}

void geneSwap(Gene& gene1, Gene& gene2)
{
	Gene temp(gene1);
	gene1 = gene2;
	gene2 = temp;
}
