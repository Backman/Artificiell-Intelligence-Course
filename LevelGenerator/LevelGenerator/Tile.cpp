#include "Tile.h"


Tile::Tile(int tileSize, TileType tileType, sf::Color color) :
	_tileSize(tileSize),
	_type(tileType),
	_shape(sf::Vector2f(tileSize, tileSize))
{
	_shape.setFillColor(sf::Color::Transparent);

	
	_shape.setOutlineThickness(1.0f);
}


Tile::~Tile()
{
}

void Tile::render(int x, int y, sf::RenderWindow* rw)
{
	_shape.setPosition(x, y);

	rw->draw(_shape);
}

void Tile::setOutlineColor(sf::Color color)
{
	_shape.setOutlineColor(color);
}

TileType Tile::getTileType() const
{
	return _type;
}

void Tile::setTileType(TileType type)
{
	_type = type;
}
