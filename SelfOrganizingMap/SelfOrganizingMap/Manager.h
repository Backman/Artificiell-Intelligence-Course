#pragma once

#include <memory>
#include "SOM.h"

class Manager
{
public:
	Manager(int rows, int cols, int cellSize, int epochs);
	~Manager();

	void draw(sf::RenderWindow* window);
	void train();
	bool isDone() const;

	int getEpochCount() const;

private:
	void initTargetSets();

	std::shared_ptr<SOM> _som;

	std::vector<std::vector<float>> _targetSet;
};

