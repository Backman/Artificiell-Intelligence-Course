#pragma once

#include "MapGenerator.h"
#include "Graph.h"
#include <Thor/Math/Triangulation.hpp>
#include <Thor/Vectors/VectorAlgebra2D.hpp>
#include <vector>

class TKCell;

class TKGenerator :
	public MapGenerator
{
	typedef std::vector<TKCell*> Cells;
	typedef std::vector<sf::Vector2f> Points;
	typedef std::vector<thor::Triangle<sf::Vector2f>> Triangles;
public:
	TKGenerator();
	~TKGenerator();

	void initGenerator(int cellCount, int tileSize, int minSize, int maxSize, int minCellThreshold, int maxCellThreshold);
	virtual Map* generate() override;

	void render(sf::RenderWindow* rw);

	void seperate();

private:
	void clearCells();
	void createCells(int count, int tileSize, int minSize, int maxSize);

	bool computeSeparation(TKCell* currCell, sf::Vector2f& outPos);
	void fillEmptySpace();
	void filterCells(Cells& cells, int minThreshold, int maxThreshold);
	void delunayTriangulation();
	void constructGraph();
	void constructMST();
	void createCorridors();

	Cells _corridors;
	Cells _emptyCells;
	Cells _cells;
	Cells _filteredCells;
	Graph _graph;
	Graph _mst;
	Triangles _triangles;
	Points _vertices;

	int _cellCount;
	int _tileSize;
	int _minCellThreshold, _maxCellThreshold;
	bool _initialized = false;
	bool _doSeparation = true;
};

