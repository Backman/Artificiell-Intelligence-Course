#include "DungeonGenerator.h"
#include "Cell.h"
#include <iostream>
#include <random>

DungeonGenerator::DungeonGenerator(int width, int height) :
	_width(width), _height(height)
{
}


DungeonGenerator::~DungeonGenerator()
{
	clearCells();
}

void DungeonGenerator::clearCells()
{
	while (!_cells.empty())
	{
		delete _cells.back();
		_cells.pop_back();
	}

	while (!_fillCells.empty())
	{
		delete _fillCells.back();
		_fillCells.pop_back();
	}
}

void DungeonGenerator::generate(int cellCount, int tileSize, int minSize, int maxSize)
{
	_doneSeparation = false;
	init(cellCount, tileSize, minSize, maxSize);
	while (true)
	{
		seperate();
		if (_doneSeparation)
		{
			break;
		}
	}
	
	//fillGaps();

	int minThreshold = 5;
	int maxThreshold = 7;
	pickCells(minThreshold, maxThreshold);
}

void DungeonGenerator::seperate()
{
	if (_doneSeparation)
	{
		return;
	}

	bool overlap = false;
	for (int i = 0; i < _cells.size(); ++i)
	{
		Cell* cell = _cells[i];

		sf::Vector2f v;
		bool seperate = computeSeparation(cell, v);

		if (seperate)
		{
			overlap = true;
			sf::Vector2f center(cell->getCenter().x, cell->getCenter().y);
			v = center + v;

			cell->setPosition(v);
		}
	}
	if (!overlap)
	{
		std::cout << "DONE SEPARATING!" << std::endl;

		_doneSeparation = true;
	}
}

void DungeonGenerator::fillGaps()
{
	int xMax = -999999, yMax = -999999;
	int xMin = 999999, yMin = 999999;

	int left, right, top, bottom;

	for (auto& cell : _cells)
	{
		left = cell->getLeft();
		right = cell->getRight();
		top = cell->getTop();
		bottom = cell->getBottom();

		if (left < xMin)
		{
			xMin = left;
		}
		if (right > xMax)
		{
			xMax = right;
		}
		if (top < yMin)
		{
			yMin = top;
		}
		if (bottom > yMax)
		{
			yMax = bottom;
		}
	}

	for (int x = xMin; x < xMax; x += _tileSize)
	{
		for (int y = yMin; y < yMax; y += _tileSize)
		{
			Cell* cell = new Cell(_tileSize, x, y, 1, 1, sf::Color(0.2f * 255, 0.2f * 255, 0.2f * 255, 255));
			_fillCells.push_back(cell);
		}
	}
}

void DungeonGenerator::pickCells(int minThreshold, int maxThreshold)
{
	minThreshold *= _tileSize;
	maxThreshold *= _tileSize;
	std::vector<Cell*>::iterator it;
	for (it = _cells.begin(); it != _cells.end();)
	{
		Cell* cell = *it;
		if (cell->getWidth() < minThreshold || cell->getWidth() > maxThreshold ||
			cell->getHeight() < minThreshold || cell->getHeight() > maxThreshold)
		{
			it = _cells.erase(it);
		}
		else
		{
			++it;
		}
	}
}

void DungeonGenerator::init(int cellCount, int tileSize, int minSize, int maxSize)
{
	_cellCount = cellCount;
	_tileSize = tileSize;

	clearCells();

	int radius = std::min<int>(_width, _height) / 2;
	
	std::minstd_rand g;
	g.seed(time(NULL));
	
	std::uniform_int_distribution<> dSize(minSize, maxSize);
	std::uniform_int_distribution<> dPos(radius - (radius / 2), radius + (radius / 2));

	int width, height, x, y;

	for (int i = 0; i < cellCount; ++i)
	{
		width = dSize(g);
		height = dSize(g);
		x = dPos(g);
		y = dPos(g);

		_cells.push_back(new Cell(tileSize, x, y, width, height));
	}
}

void DungeonGenerator::render(sf::RenderWindow* window)
{
	for (auto& cell : _fillCells)
	{
		cell->render(window);
	}
	for (auto& cell : _cells)
	{
		cell->render(window);
	}
}

bool DungeonGenerator::computeSeparation(Cell* cell, sf::Vector2f& pos)
{
	//return false;
	bool ret = false;
	sf::Vector2i originPos = cell->getCenter();
	sf::Vector2i otherPos;

	int dx, dy, dxSqr, dySqr, distSqr, dist;

	float c = _tileSize * 2.0f;

	for (auto& other : _cells)
	{
		if (other != cell)
		{
			otherPos = other->getCenter();

			dx = originPos.x - otherPos.x;
			dy = originPos.y - otherPos.y;
			dxSqr = dx*dx;
			dySqr = dy*dy;

			distSqr = (dxSqr + dySqr);
			dist = sqrt(distSqr);

			if (dx != 0.0f)
			{
				if (dx <= 0.0f)
				{
					pos.x -= c / dist;
				}
				else
				{
					pos.x += c / dist;
				}
			}
			if (dy != 0.0f)
			{
				if (dy <= 0.0f)
				{
					pos.y -= c / dist;
				}
				else
				{
					pos.y += c / dist;
				}
			}


			if (cell->intersects(*other))
			{
				ret = true;
			}
		}
	}

	//pos *= -1.0f;

	return ret;
}

void DungeonGenerator::constructGraph()
{

}
