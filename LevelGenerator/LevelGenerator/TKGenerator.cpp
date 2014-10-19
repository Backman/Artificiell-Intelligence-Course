#include "TKGenerator.h"
#include "TKCell.h"
#include "Utility.h"

#include <Aurora\Tools\ForEach.hpp>
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
	Utility::clearPointerVector<TKCell>(&_emptyCells);
	Utility::clearPointerVector<TKCell>(&_corridors);
	Utility::clearPointerVector<TKCell>(&_filteredCells);
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
		x = ((x / tileSize) + 1) * tileSize;

		y = Utility::randomFloatRange(hRadius - (hRadius / 2), hRadius + (hRadius / 2));
		y = ((y / tileSize) + 1) * tileSize;

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

		fillEmptySpace();
		filterCells(_cells, _minCellThreshold, _maxCellThreshold);
		delunayTriangulation();
		_doSeparation = false;
	}
}

bool TKGenerator::computeSeparation(TKCell* currCell, sf::Vector2f& outPos)
{
	bool ret = false;
	sf::Vector2f cellPos;
	sf::Vector2f otherPos;

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

				float xDiff = otherPos.x - cellPos.x;
				float yDiff = otherPos.y - cellPos.y;

				float distSqr = xDiff*xDiff + yDiff*yDiff;

				x = xDiff < 0.0f ? x + _tileSize : x - _tileSize;
				y = yDiff < 0.0f ? y + _tileSize : y - _tileSize;

				//x -= ((int)xDiff % _tileSize) + xDiff;
				//y -= ((int)yDiff % _tileSize) + yDiff;

				newPos += sf::Vector2f(x, y);

				currCell->setPosition(currCell->getCenter() + newPos);

				ret = true;
			}
		}
	}


	return ret;
}

void TKGenerator::fillEmptySpace()
{
	int xMin = std::numeric_limits<int>::max();
	int xMax = std::numeric_limits<int>::min();
	int yMin = std::numeric_limits<int>::max();
	int yMax = std::numeric_limits<int>::min();

	for (auto& c : _cells)
	{
		float left = c->getLeft();
		float right = c->getRight();
		float top = c->getTop();
		float bottom = c->getBottom();

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
			bool shouldAddCell = true;

			TKCell tmpCell(_tileSize, x, y, 1, 1);
			for (auto& c : _cells)
			{
				if (c->getLeft() <= x && c->getTop() <= y &&
					c->getRight() > x && c->getBottom() > y)
				{

					shouldAddCell = false;
					break;
				}
			}

			if (shouldAddCell)
			{
				TKCell* cell = new TKCell(_tileSize, x, y, 1, 1);
				cell->setTileOutlineColor(sf::Color(255, 0, 0, 50));
				_emptyCells.push_back(cell);
			}
		}
	}
}

void TKGenerator::filterCells(Cells& cells, int minThreshold, int maxThreshold)
{
	minThreshold *= _tileSize;
	maxThreshold *= _tileSize;
	Cells::iterator it;

	TKCell* cell;
	for (it = cells.begin(); it != cells.end();)
	{
		cell = *it;
		int width = cell->getWidth();
		int height = cell->getHeight();
		if (width < minThreshold || width > maxThreshold ||
			height < minThreshold || height > maxThreshold)
		{
			(*it)->setTileOutlineColor(sf::Color(255, 255, 0, 128));
			++it;
		}
		else
		{
			_filteredCells.push_back(*it);
			it = cells.erase(it);
		}
	}
}

void TKGenerator::delunayTriangulation()
{
	_vertices.clear();
	for (auto& cell : _filteredCells)
	{
		_vertices.push_back(cell->getCenter());
	}
	thor::triangulate(_vertices.begin(), _vertices.end(), std::back_inserter(_triangles));

	constructGraph();
	constructMST();
}

void TKGenerator::constructGraph()
{
	int n = _vertices.size();
	_graph.init(n);

	for (int i = 0; i < n; ++i)
	{
		sf::Vector2f v1 = _vertices[i];
		for (int j = 0; j < n; ++j)
		{
			if (i == j)
				continue;

			sf::Vector2f v2 = _vertices[j];
			for (auto& tri : _triangles)
			{
				sf::Vector2f tv1 = tri[0];
				sf::Vector2f tv2 = tri[1];
				sf::Vector2f tv3 = tri[2];

				if ((v1 == tv1 || v1 == tv2 || v1 == tv3) && (v2 == tv1 || v2 == tv2 || v2 == tv3))
				{
					_graph.addEdge(i, j);
				}
			}
		}
	}
}

int minKey(std::vector<int>& key, std::vector<int>& mstSet)
{
	int min = INT_MAX, minIndex;

	for (int i = 0; i < key.size(); ++i)
	{
		if (!mstSet[i] && key[i] < min)
		{
			min = key[i];
			minIndex = i;
		}
	}

	return minIndex;
}

void TKGenerator::constructMST()
{
	const int n = _vertices.size();

	std::vector<int> parent(n);
	std::vector<int> key(n);
	std::vector<int> mstSet(n);

	for (int i = 0; i < n; ++i)
	{
		key[i] = INT_MAX;
		mstSet[i] = false;
	}

	key[0] = 0;
	parent[0] = -1;

	for (int count = 0; count < n - 1; ++count)
	{
		int u = minKey(key, mstSet);

		mstSet[u] = true;

		for (int v = 0; v < n; ++v)
		{
			bool isEdge = _graph.isEdge(u, v);
			int edge = _graph.getEdge(u, v);
			if (isEdge && !mstSet[v] && edge < key[v])
			{
				parent[v] = u;
				key[v] = edge;
			}
		}
	}

	_mst.init(n);

	for (int i = 1; i < n; ++i)
	{
		_mst.addEdge(parent[i], i);
	}
}

void TKGenerator::createCorridors()
{
	std::vector<sf::Vector2f> connections;
	for (int i = 0; i < _mst.getVertexCount(); ++i)
	{
		for (int j = 0; j < _mst.getVertexCount(); ++j)
		{
			int vert = _mst.getEdge(i, j);
			if (vert > 0)
			{
				connections.push_back(_vertices[i]);
			}
		}
	}
}

void TKGenerator::render(sf::RenderWindow* rw)
{
	for (auto& cell : _emptyCells)
	{
		cell->render(rw);
	}
	for (auto& cell : _cells)
	{
		cell->render(rw);
	}
	for (auto& cell : _filteredCells)
	{
		cell->render(rw);
	}

	for (int i = 0; i < _mst.getVertexCount(); ++i)
	{
		for (int j = 0; j < _mst.getVertexCount(); ++j)
		{
			if (_mst.isEdge(i, j))
			{
				sf::VertexArray line(sf::PrimitiveType::Lines, 2);

				line[0] = _vertices[i];
				line[1] = _vertices[j];

				line[0].color = sf::Color::Green;
				line[1].color = sf::Color::Green;


				rw->draw(line);

			}
		}
	}

	AURORA_FOREACH(const thor::Triangle<sf::Vector2f>& triangle, _triangles)
	{
		sf::ConvexShape shape;
		shape.setPointCount(3);
		shape.setFillColor(sf::Color::Transparent);

		shape.setOutlineColor(sf::Color(0, 255, 0, 128));
		shape.setOutlineThickness(3.f);

		for (unsigned int i = 0; i < 3; ++i)
			shape.setPoint(i, triangle[i]);

		//rw->draw(shape);
	}
}
