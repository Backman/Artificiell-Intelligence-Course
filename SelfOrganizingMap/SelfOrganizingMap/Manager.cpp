#include "Manager.h"
#include "Utility.h"
#include "Constants.h"

Manager::Manager(int rows, int cols, int cellSize, int epochs) :
	_epoch(epochs)
{
	//initDefinedTargetSets();
	initRandomTargetSets();
	_som = std::make_shared<SOM>(rows, cols, cellSize, epochs);
}


Manager::~Manager()
{
}

void Manager::draw(sf::RenderWindow* window)
{
	_som->draw(window);
}

void Manager::train()
{
	_som->train(_epoch, _targetSet);
	--_epoch;
}

bool Manager::isDone() const
{
	return _som->isDone();
}

int Manager::getEpochCount() const
{
	return _som->getEpochCount();
}

void Manager::initRandomTargetSets()
{
	int targetSetSize = Utility::randomIntRange(MIN_TRAINING_SETS, MAX_TRAINING_SETS);
	
	for (int i = 0; i < targetSetSize; ++i) {
		std::vector<float> target;

		float r = Utility::randomFloatRange(0.0f, 1.0f);
		float g = Utility::randomFloatRange(0.0f, 1.0f);
		float b = Utility::randomFloatRange(0.0f, 1.0f);

		target.push_back(r);
		target.push_back(g);
		target.push_back(b);

		_targetSet.push_back(target);
	}
}

void Manager::initDefinedTargetSets()
{
	std::vector<float> red{ 1, 0, 0 };
	std::vector<float> green{ 0, 1, 0 };
	std::vector<float> blue{ 0, 0, 1 };
	std::vector<float> yellow{ 1, 1, 0 };

	_targetSet.push_back(red);
	_targetSet.push_back(green);
	_targetSet.push_back(blue);
	_targetSet.push_back(yellow);
}
