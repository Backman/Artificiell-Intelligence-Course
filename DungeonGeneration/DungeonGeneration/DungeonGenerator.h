#pragma once

#include <vector>
#include <SFML\Graphics.hpp>

class Cell;

class DungeonGenerator
{
public:
	DungeonGenerator(int width, int height);
	~DungeonGenerator();

	void generate(int cellCount, int tileSize, int minSize, int maxSize);

	void render(sf::RenderWindow* window);

	void seperate();
	void fillGaps();
	void pickCells(int minThreshold, int maxThreshold);
	void constructGraph();

private:
	void init(int cellCount, int tileSize, int minSize, int maxSize);
	bool computeSeparation(Cell* cell, sf::Vector2f& pos);

	void clearCells();

	typedef std::vector<Cell*> Cells;
	Cells _cells;
	Cells _fillCells;

	bool _doneSeparation;
	int _cellCount;

	int _width, _height;
	int _tileSize;
};

