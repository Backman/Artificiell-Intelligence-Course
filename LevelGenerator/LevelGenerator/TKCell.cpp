#include "TKCell.h"
#include "Utility.h"
#include "TileGrid.h"
#include "Tile.h"

#include <SFML\Graphics.hpp>

TKCell::TKCell(int tileSize, int x, int y, int width, int height) : 
	_tileSize(tileSize),
	_pos(x, y),
	_size(width * tileSize, height * tileSize),
	_rows(width), _cols(height)
{
	_tileGrid = new TileGrid;
	_tileGrid->initGrid(width, height, tileSize);

	_color = sf::Color(Utility::randomFloatRange() * 255,
		Utility::randomFloatRange() * 255,
		Utility::randomFloatRange() * 255,
		255);
}


TKCell::~TKCell()
{
	Utility::deletePointer<TileGrid>(_tileGrid);
}

sf::Vector2f TKCell::getCenter() const
{
	return sf::Vector2f(_pos.x + (_size.x / 2), _pos.y + (_size.y / 2));
}

//sf::Vector2f TKCell::getPosition() const
//{
//	return _pos;
//}

void TKCell::setPosition(sf::Vector2f newPos)
{	
	_pos.x = newPos.x - (_size.x / 2);
	_pos.y = newPos.y - (_size.y / 2);
}

void TKCell::setPosition(float newX, float newY)
{
	_pos.x = newX - (_size.x / 2);
	_pos.y = newY - (_size.y / 2);
}

int TKCell::getLeft() const
{
	return _pos.x;
}

int TKCell::getRight() const
{
	return _pos.x + _size.x;
}

int TKCell::getTop() const
{
	return _pos.y;
}

int TKCell::getBottom() const
{
	return _pos.y + _size.y;
}

bool TKCell::intersects(TKCell& other) const
{
	bool cond1, cond2, cond3, cond4;

	cond1 = getLeft() <= other.getRight();
	cond2 = getRight() >= other.getLeft();
	
	cond3 = getTop() <= other.getBottom();
	cond4 = getBottom() >= other.getTop();

	return cond1 && cond2 && cond3 && cond4;
}

void TKCell::render(sf::RenderWindow* rw)
{
	int w = _size.x / _tileSize;
	int h = _size.y / _tileSize;

	sf::RectangleShape shape(_size);
	shape.setPosition(_pos);
	shape.setFillColor(sf::Color::White);
	rw->draw(shape);

	/*Tile* tile;
	for (int y = 0; y < _cols; ++y)
	{
		for (int x = 0; x < _rows; ++x)
		{
			tile = _tileGrid->getTile(x, y);

			if (tile != nullptr)
			{
				int xPos = _pos.x + _tileSize*x;
				int yPos = _pos.y + _tileSize*y;

				tile->render(xPos, yPos, rw);
			}
		}
	}*/

	_tileGrid->render(_pos, _tileSize, rw);
}
