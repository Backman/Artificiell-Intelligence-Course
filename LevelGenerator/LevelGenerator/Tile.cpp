#include "Tile.h"


Tile::Tile(int tileSize, sf::Color color) :
	_tileSize(tileSize),
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
