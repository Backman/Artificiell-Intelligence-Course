#include "TKCell.h"
#include "Utility.h"
#include "TileGrid.h"
#include "Tile.h"

#include <SFML\Graphics.hpp>

TKCell::TKCell(int tileSize, int x, int y, int width, int height) : 
	_tileSize(tileSize),
	_pos(x, y),
	_size(width * tileSize, height * tileSize),
	_status(CellStatus::AVAILABLE),
	_type(CellType::DefaultRoom)
{
	_tileGrid.initGrid(width, height, tileSize);
}


TKCell::~TKCell()
{
	
}

sf::Vector2f TKCell::getCenter() const
{
	return sf::Vector2f(_pos.x + (_size.x / 2), _pos.y + (_size.y / 2));
}

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

int TKCell::getWidth() const
{
	return _size.x;
}

int TKCell::getHeight() const
{
	return _size.y;
}

bool TKCell::intersects(TKCell& other) const
{
	sf::FloatRect r1(_pos, _size);
	sf::FloatRect r2(other._pos, other._size + sf::Vector2f(_tileSize, _tileSize));
	sf::FloatRect inter;

	return r1.intersects(r2);
}

bool TKCell::intersects(const sf::FloatRect& other) const
{
	sf::FloatRect r(_pos, _size);// +sf::Vector2f(_tileSize, _tileSize));

	return r.intersects(other);
}

bool TKCell::containsPoint(int x, int y) const
{
	sf::FloatRect rect(_pos.x, _pos.y, _size.x, _size.y);

	return rect.contains(x, y);
}

CellStatus TKCell::getStatus() const
{
	return _status;
}

void TKCell::setStatus(CellStatus s)
{
	_status = s;
}

CellType TKCell::getType() const
{
	return _type;
}

void TKCell::setType(CellType type)
{
	_type = type;
}

void TKCell::render(sf::RenderWindow* rw)
{
	if (_status == CellStatus::UNAVAILABLE)
	{
		return;
	}

	sf::RectangleShape shape(_size);
	shape.setPosition(_pos);

	if (_type == CellType::DefaultRoom)
	{
		shape.setOutlineColor(sf::Color::Red);
	}
	else if (_type == CellType::CorridorRoom)
	{
		shape.setOutlineColor(sf::Color(0, 0, 128, 255));
	}
	else if (_type == CellType::Corridor)
	{
		shape.setOutlineColor(sf::Color::Black);// (0, 255, 0, 128));
	}
	shape.setOutlineThickness(1.0f);
	shape.setFillColor(sf::Color::Transparent);


	_tileGrid.render(_pos, _tileSize, rw);
	rw->draw(shape);

}
