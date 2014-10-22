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
	

	_mst.clearGraph();
	_graph.clearGraph();

}

void TKGenerator::initGenerator(int cellCount, int tileSize, int minSize, int maxSize, int minCellThreshold, int maxCellThreshold)
{
	_initialized = true;
	createCells(cellCount, tileSize, minSize, maxSize);
	_cellCount = cellCount;
	_tileSize = tileSize;

	_minCellThreshold = minCellThreshold;
	_maxCellThreshold = maxCellThreshold;

	_doSeparation = true;
}

void TKGenerator::createCells(int cellCount, int tileSize, int minSize, int maxSize)
{
	clearCells();

	int x, y, width, height;

	TKCell* cell;

	int rad = cellCount * 2;

	for (int i = 0; i < cellCount; ++i)
	{
		x = Utility::randomFloatRange(rad - (rad / 2), rad + (rad / 2));
		x = ((x / tileSize) + 1) * tileSize;

		y = Utility::randomFloatRange(rad - (rad / 2), rad + (rad / 2));
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
	//if (_initialized)
	//{
	//	while (_doSeparation)
	//	{
	//		seperate();
	//	}
	//}
	
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
		if (computeSeparation(cell, v))
		{
			overlap = true;
		}
	}

	if (!overlap)
	{
		std::cout << "DONE SEPARATING!" << std::endl;

		std::cout << "Fill empty space" << std::endl;
		fillEmptySpace();

		std::cout << "Filter cells" << std::endl;
		filterCells(_cells, _minCellThreshold, _maxCellThreshold);

		std::cout << "Triangulation" << std::endl;
		delunayTriangulation();

		std::cout << "Construct graph" << std::endl;
		constructGraph();

		std::cout << "Cosntruct MST" << std::endl;
		constructMST();

		std::cout << "Create corridors" << std::endl;
		createCorridors();

		std::cout << "Create map grid" << std::endl;
		createMapGrid();

		std::cout << "DONE!" << std::endl;
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
			sf::FloatRect intersection;
			if (other->intersects(*currCell, intersection))
			{
				float y = 0.0f;
				float x = 0.0f;

				cellPos = currCell->getCenter();
				otherPos = other->getCenter();

				float xDiff = otherPos.x - cellPos.x;
				float yDiff = otherPos.y - cellPos.y;

				x -= xDiff;
				x = ((x / _tileSize) + 1) * _tileSize;

				y -= yDiff;
				y = ((y / _tileSize) + 1) * _tileSize;

				newPos += sf::Vector2f(x, y);

				ret = true;
			}
		}
	}

	currCell->setPosition(currCell->getCenter() + newPos);

	return ret;
}

void TKGenerator::getMinMax(int& xMin, int& xMax, int& yMin, int& yMax) const
{
	xMin = std::numeric_limits<int>::max();
	xMax = std::numeric_limits<int>::min();
	yMin = std::numeric_limits<int>::max();
	yMax = std::numeric_limits<int>::min();

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
}

void TKGenerator::fillEmptySpace()
{
	getMinMax(_xMin, _xMax, _yMin, _yMax);

	for (int x = _xMin; x < _xMax; x += _tileSize)
	{
		for (int y = _yMin; y < _yMax; y += _tileSize)
		{
			bool shouldAddCell = true;

			for (auto& c : _cells)
			{
				if (c->getLeft() < (x + _tileSize) && c->getTop() < (y + _tileSize) &&
					c->getRight() > x && c->getBottom() > y)
				{
					shouldAddCell = false;
					break;
				}
			}

			if (shouldAddCell)
			{
				TKCell* cell = new TKCell(_tileSize, x, y, 1, 1);

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

	for (auto& c : _cells)
	{
		int width = c->getWidth();
		int height = c->getHeight();

		if (width < minThreshold || width > maxThreshold ||
			height < minThreshold || height > maxThreshold)
		{
			c->setStatus(Status::UNAVAILABLE);
		}
	}
}

void TKGenerator::delunayTriangulation()
{
	_vertices.clear();
	for (auto& cell : _cells)
	{
		if (cell->getStatus() == Status::AVAILABLE)
		{
			_vertices.push_back(cell->getCenter());
		}
	}
	thor::triangulate(_vertices.begin(), _vertices.end(), std::back_inserter(_triangles));
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
	std::vector<sf::FloatRect> connections;
	std::map<int, int> _map;
	int rectSize = 1;
	for (int i = 0; i < _mst.getVertexCount(); ++i)
	{
		for (int j = 0; j < _mst.getVertexCount(); ++j)
		{
			if (_map[j] == i)
				continue;

			int edge = _mst.getEdge(i, j);
			if (edge > 0)
			{
				

				_map[i] = j;
				sf::Vector2f v1 = _vertices[i];
				sf::Vector2f v2 = _vertices[j];

				float xDiff = v2.x - v1.x;
				float yDiff = v1.y - v2.y;

				sf::FloatRect r1(v1.x, v1.y - (rectSize / 2), xDiff, rectSize);
				sf::FloatRect r2(v2.x - (rectSize / 2), v2.y, 4, yDiff);

				float random = Utility::randomFloatRange();
				/*if (random < 0.75)
				{
					r1 = sf::FloatRect(v1.x, v1.y - 2, -xDiff, 4);
					r2 = sf::FloatRect(v2.x - 2, v2.y, 4, yDiff);
				}*/

				connections.push_back(r1);
				connections.push_back(r2);
			}
		}
	}

	for (int i = 0; i < _graph.getVertexCount(); ++i)
	{
		for (int j = 0; j < _graph.getVertexCount(); ++j)
		{
			if (_graph.getEdge(i, j) > 0)
			{
				float chance = Utility::randomFloatRange();

				if (chance > 0.75f)
				{
					sf::Vector2f v1 = _vertices[i];
					sf::Vector2f v2 = _vertices[j];

					float xDiff = v2.x - v1.x;
					float yDiff = v1.y - v2.y;

					sf::FloatRect r1(v1.x, v1.y - (rectSize / 2), xDiff, rectSize);
					sf::FloatRect r2(v2.x - (rectSize / 2), v2.y, 4, yDiff);
					
					connections.push_back(r1);
					connections.push_back(r2);
				}
				else
				{
					_graph.removeEdge(i, j);
				}
			}
		}
	}

	float minThreshold = _minCellThreshold * _tileSize;
	float maxThreshold = _maxCellThreshold * _tileSize;

	for (auto& rect : connections)
	{
		for (auto& c : _cells)
		{
			if (c->getStatus() != Status::AVAILABLE)
			{
				if (c->intersects(rect))
				{
					c->setStatus(Status::AVAILABLE);
				}
			}
		}

		for (Cells::iterator it = _emptyCells.begin(); it != _emptyCells.end();)
		{

			if ((*it)->intersects(rect))
			{
				TKCell* c = new TKCell(*(*it));
				_cells.push_back(c);

				it = _emptyCells.erase(it);
			}
			else
			{
				++it;
			}
		}
	}
}

void TKGenerator::createMapGrid()
{
	int n = std::max(_xMax - _xMin, _yMax - _yMin);

	//_mapGrid.initGrid(n, n, _tileSize);
	
	//_mst.printGraph();
}

void TKGenerator::render(sf::RenderWindow* rw)
{
	for (auto& cell : _emptyCells)
	{
		//cell->render(rw);
	}
	for (auto& cell : _cells)
	{
		if (cell->getStatus() == Status::AVAILABLE)
		{
			cell->render(rw);
		}
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

	for (int i = 0; i < _graph.getVertexCount(); ++i)
	{
		for (int j = 0; j < _graph.getVertexCount(); ++j)
		{
			if (_graph.isEdge(i, j))
			{
				sf::VertexArray line(sf::PrimitiveType::Lines, 2);

				line[0] = _vertices[i];
				line[1] = _vertices[j];

				line[0].color = sf::Color::Cyan;
				line[1].color = sf::Color::Cyan;


				rw->draw(line);

			}
		}
	}

	for(const auto& triangle : _triangles)
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
