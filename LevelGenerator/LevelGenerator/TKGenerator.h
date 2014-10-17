#pragma once

#include "MapGenerator.h"
#include <vector>

class TKCell;

class TKGenerator :
	public MapGenerator
{
	typedef std::vector<TKCell*> Cells;
public:
	TKGenerator();
	~TKGenerator();

	void initGenerator(int cellCount, int tileSize, int minSize, int maxSize, int minRoomThreshold, int maxRoomThreshold);
	virtual Map* generate() override;

	void render(sf::RenderWindow* rw);

	void seperate();

private:
	void clearCells();
	void createCells(int count, int tileSize, int minSize, int maxSize);

	bool computeSeparation(TKCell* currCell, sf::Vector2f& outPos);

	Cells _cells;

	int _cellCount;
	int _tileSize;
	int _minCellThreshold, _maxCellThreshold;
	bool _initialized = false;
	bool _doSeparation = true;
};

