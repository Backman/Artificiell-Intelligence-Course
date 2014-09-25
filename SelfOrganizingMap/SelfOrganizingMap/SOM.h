#pragma once

#include <vector>
#include <SFML\Graphics.hpp>
#include "Node.h"

class SOM
{
public:
	SOM(int rows, int cols, int cellSize, int epochs);
	~SOM();

	void draw(sf::RenderWindow* window);

	std::vector<float> getRandomSample();
	Node& getBMU(const std::vector<float>& target);
	void train(const std::vector<std::vector<float>>& targetSet);

	bool isDone() const;

	int getEpochCount() const;

private:
	void initSOM(int rows, int cols, int cellSize);

	float neighbourhoodRadius(int t, float timeConstant);
	float learningRateFunction(int t, float timeConstant);

	bool _isDone;
	int _rows, _cols;
	int _epochCount;
	int _currentEpoch;
	float _timeConstant;

	std::vector<Node> _nodes;
};

