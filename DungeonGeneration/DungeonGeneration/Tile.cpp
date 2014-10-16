#include "Tile.h"

Tile::Tile(int size, sf::Color color) :
	_shape(sf::Vector2f((float)size - 1.0f, (float)size - 1.0f))
{
	_shape.setOutlineThickness(1.0f);
	_shape.setOutlineColor(sf::Color::Red);
	_shape.setFillColor(sf::Color::Transparent);
}

Tile::~Tile()
{
}

void Tile::render(int x, int y, sf::RenderWindow* window)
{
	_shape.setPosition(x, y);

	window->draw(_shape);
}
