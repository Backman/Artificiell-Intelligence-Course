#pragma once

#include <vector>
#include <SFML\Graphics.hpp>
#include "Node.h"

class Canvas
{
public:
	Canvas(int rows, int cols, int cellSize);
	~Canvas();

	void drawCanvas(sf::RenderWindow* window);

private:
	void initCanvas(int rows, int cols, int cellSize);

	int _rows, _cols;
	std::vector<Node> _cells;
};

