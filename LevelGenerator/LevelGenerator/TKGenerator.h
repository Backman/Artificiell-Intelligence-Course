#pragma once

#include "MapGenerator.h"
#include "Graph.h"
#include "TileGrid.h"
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
	virtual void render(sf::RenderWindow* rw) override;
	virtual void reset() override;

	void seperate();

private:
	void clearCells();
	void createCells(int count, int tileSize, int minSize, int maxSize);

	bool computeSeparation(TKCell* currCell, sf::Vector2f& outPos);
	void fillGaps();
	void filterCells();
	void delunayTriangulation();
	void constructMST();
	void createCorridors();

	void getMinMax(int& xMin, int& xMax, int& yMin, int& yMax) const;

	Cells _gapCells;
	Cells _cells;
	Graph _graph;
	Graph _mst;
	Points _vertices;

	int _cellCount;
	int _tileSize;
	int _minCellSize, _maxCellSize;
	int _minCellThreshold, _maxCellThreshold;
	bool _initialized = false;
	bool _doSeparation = true;
	int _xMin, _xMax, _yMin, _yMax;

	bool _filled, _filtered, _triangulated, _mstFound, _corridors;
};

