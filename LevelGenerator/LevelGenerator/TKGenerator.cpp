#include "TKGenerator.h"
#include "TKCell.h"
#include "Utility.h"

#include <iostream>

TKGenerator::TKGenerator()
{
}


TKGenerator::~TKGenerator()
{
}

void TKGenerator::clearCells()
{
	Utility::clearPointerVector<TKCell>(&_cells);
}

void TKGenerator::initGenerator(int cellCount, int tileSize, int minSize, int maxSize, int minCellThreshold, int maxCellThreshold)
{
	_initialized = true;
	createCells(cellCount, tileSize, minSize, maxSize);
	_cellCount = cellCount;
	_tileSize = tileSize;

	_minCellThreshold = minCellThreshold;
	_maxCellThreshold = maxCellThreshold;
}

void TKGenerator::createCells(int cellCount, int tileSize, int minSize, int maxSize)
{
	clearCells();

	int x, y, width, height;

	TKCell* cell;

	float wRadius = 512;
	float hRadius = 380;

	for (int i = 0; i < cellCount; ++i)
	{
		x = Utility::randomFloatRange(wRadius - (wRadius / 2), wRadius + (wRadius / 2));
		y = Utility::randomFloatRange(hRadius - (hRadius / 2), hRadius + (hRadius / 2));
		width = Utility::randomIntRange(minSize, maxSize);
		height = Utility::randomIntRange(minSize, maxSize);

		cell = new TKCell(tileSize, x, y, width, height);

		_cells.push_back(cell);
	}
}

Map* TKGenerator::generate()
{
	_doSeparation = true;
	if (_initialized)
	{
		while (_doSeparation)
		{
			seperate();
		}
	}
	
	return nullptr;
}

void TKGenerator::seperate()
{
	if (!_doSeparation)
	{
		return;
	}

	bool overlap = false;
	for (auto& cell : _cells)
	{
		sf::Vector2f v;
		bool separate = computeSeparation(cell, v);
		
		if (separate)
		{
			overlap = true;
			v = cell->getCenter() + v;

			//cell->setPosition(v);
		}
	}

	if (!overlap)
	{
		std::cout << "DONE SEPARATING!" << std::endl;

		_doSeparation = false;
	}
}

bool TKGenerator::computeSeparation(TKCell* currCell, sf::Vector2f& outPos)
{
	bool ret = false;
	sf::Vector2f cellPos;
	sf::Vector2f otherPos;

	float intense = _cellCount * 100.0f;
	float c = 1.0f;// _tileSize * 1.0f;

	sf::Vector2f newPos;

	for (auto& other : _cells)
	{
		if (other != currCell)
		{
			if (currCell->intersects(*other))
			{
				float y = 0.0f;
				float x = 0.0f;

				cellPos = currCell->getCenter();
				otherPos = other->getCenter();

				float strength = 0.0f;

				float xDiff = otherPos.x - cellPos.x;
				float yDiff = otherPos.y - cellPos.y;

				float distSqr = xDiff*xDiff + yDiff*yDiff;
				float dist = sqrt(distSqr);


				if (xDiff != 0.0f)
				{
					if (xDiff < 0.0f)
					{
						x += c / distSqr * intense;
					}
					else
					{
						x -= c / distSqr * intense;
					}
				}
				if (yDiff != 0.0f)
				{
					if (yDiff < 0.0f)
					{
						y += c / distSqr * intense;
					}
					else
					{
						y -= c / distSqr * intense;
					}
				}

				outPos.x += x;
				outPos.y += y;

				strength = c / distSqr;

				newPos += sf::Vector2f(x, y);

				currCell->setPosition(currCell->getCenter() + newPos);

				ret = true;
			}
		}
	}


	return ret;
}

void TKGenerator::render(sf::RenderWindow* rw)
{
	for (auto& cell : _cells)
	{
		cell->render(rw);
	}
}
