#include "Tile.h"


Tile::Tile(int tileSize, TileType tileType) :
	_tileSize(tileSize),
	_type(tileType)
{

}


Tile::~Tile()
{
}

void Tile::render(int x, int y, sf::RenderWindow* rw)
{
	sf::RectangleShape shape(sf::Vector2f(_tileSize, _tileSize));
	shape.setFillColor(sf::Color::Transparent);


	shape.setOutlineThickness(1.0f);
	shape.setPosition(x, y);

	rw->draw(shape);
}

TileType Tile::getTileType() const
{
	return _type;
}

void Tile::setTileType(TileType type)
{
	_type = type;
}
