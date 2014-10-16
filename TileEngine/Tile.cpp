#include "Tile.h"
#include "Assert.h"

Tile::Tile(sf::Image& image)
{
	ASSERT(_texture.loadFromImage(image));

	_sprite.setTexture(_texture);
}


Tile::~Tile()
{
}

void Tile::render(int x, int y, sf::RenderWindow* window)
{
	_sprite.setPosition(x, y);
	window->draw(_sprite);
}
