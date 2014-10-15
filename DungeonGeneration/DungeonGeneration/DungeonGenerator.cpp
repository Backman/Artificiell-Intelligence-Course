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

	while (!_cells.empty())
	{
		delete _cells.back();
		_cells.pop_back();
	}
}

void DungeonGenerator::generate(int cellCount, int tileSize, int minSize, int maxSize)
{
	_done = false;
	init(cellCount, tileSize, minSize, maxSize);
}

bool DungeonGenerator::seperate()
{
	if (_done)
	{
		return true;
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
			v = cell->getPosition() + v;

			cell->setPosition(v);
		}
	}

	_done = !overlap;

	if (!overlap)
	{
		std::cout << "DONE SEPARATING!" << std::endl;

		return true;
	}

	return false;
}

void DungeonGenerator::fillGaps()
{
	float xMax = -1000.0f, yMax = -1000.0f;
	float xMin = 1000.0f, yMin = 1000.0f;

	float x, y;

	for (auto& cell : _cells)
	{
		x = cell->getPosition().x;
		y = cell->getPosition().y;

		if (x < xMin)
		{
			xMin = x;
		}
		if (x > xMax)
		{
			xMax = x;
		}
		if (y < yMin)
		{
			yMin = y;
		}
		if (y > yMax)
		{
			yMax = y;
		}
	}


}

void DungeonGenerator::init(int cellCount, int tileSize, int minSize, int maxSize)
{
	_cellCount = cellCount;
	_tileSize = tileSize;

	clearCells();

	float radius = std::min<int>(_width, _height) / 2;
	
	std::minstd_rand g;
	g.seed(time(NULL));
	
	std::uniform_int_distribution<> dSize(minSize, maxSize);
	std::uniform_int_distribution<> dPos(radius - (radius / 2), radius + (radius / 2));
	//std::uniform_int_distribution<> dPos(250, 350);



	for (int i = 0; i < cellCount; ++i)
	{
		int width, height, x, y;

		width = dSize(g) * tileSize;
		height = dSize(g) * tileSize;
		x = dPos(g);
		y = dPos(g);

		_cells.push_back(new Cell(x, y, width, height, i));
	}
}

void DungeonGenerator::render(sf::RenderWindow* window)
{
	for (auto& cell : _cells)
	{
		cell->render(window);
	}
}

bool DungeonGenerator::computeSeparation(Cell* cell, sf::Vector2f& pos)
{
	//return false;
	bool ret = false;
	sf::Vector2f originPos = cell->getPosition();
	sf::Vector2f otherPos;

	float dx, dy, dxSqr, dySqr, distSqr, dist;

	float c = _tileSize * 2;

	for (auto& other : _cells)
	{
		if (*other != *cell)
		{
			otherPos = other->getPosition();

			dx = originPos.x - otherPos.x;
			dy = originPos.y - otherPos.y;
			dxSqr = dx*dx;
			dySqr = dy*dy;

			distSqr = (dxSqr + dySqr);
			dist = sqrt(distSqr);

			if (dx != 0.0f)
			{
				//pos.x -= c / dist;
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
				//pos.y -= c / dist;
				if (dy <= 0.0f)
				{
					pos.y -= c / dist;
				}
				else
				{
					pos.y += c / dist;
				}
			}
			if (/*cell->intersects(*other)*/distSqr < 5 * _tileSize)
			{
				ret = true;

				//pos -= sf::Vector2f(dx*dx, dy*dy);

				//if (dx != 0.0f)
				//{
				//	//pos.x -= c / dx;// * 0.03f;
				//	float dxSqr = dx*dx;
				//	
				//	if (dx <= 0.0f)
				//	{
				//		pos.x += c / len;
				//	}
				//	else
				//	{
				//		pos.x -= c / len;
				//	}
				//}
				//if (dy != 0.0f)
				//{
				//	//pos.y -= c / dy;// * 0.03f;
				//	float dySqr = dy*dy;
				//	if (dy <= 0.0f)
				//	{
				//		pos.y += c / len;
				//	}
				//	else
				//	{
				//		pos.y -= c / len;
				//	}
				//}
			}
		}
	}

	//pos *= -1.0f;

	return ret;
}
