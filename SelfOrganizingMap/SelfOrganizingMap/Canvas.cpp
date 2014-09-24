#include "Canvas.h"


Canvas::Canvas(int rows, int cols, int cellSize)
{
	initCanvas(rows, cols, cellSize);

	_rows = rows;
	_cols = cols;
}


Canvas::~Canvas()
{
}

void Canvas::drawCanvas(sf::RenderWindow* window)
{
	for (auto& cell : _cells) {
		cell.renderNode(window);
	}
}

/********************************
	Private functions
*********************************/
void Canvas::initCanvas(int rows, int cols, int cellSize)
{
	int xOffset = 0;
	int yOffset = 0;
	for (int y = 0; y < cols; ++y) {
		for (int x = 0; x < rows; ++x) {
			_cells.push_back(Node(xOffset, yOffset, cellSize, cellSize, 3));
			xOffset += cellSize;
		}
		xOffset = 0;
		yOffset += cellSize;
	}
}