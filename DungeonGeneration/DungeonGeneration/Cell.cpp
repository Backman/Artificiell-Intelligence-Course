#include "Cell.h"
#include "Tile.h"

Cell::Cell(int tileSize, int x, int y, int width, int height, sf::Color color) :
	_tileSize(tileSize),
	_pos(x, y),
	_size(width * tileSize, height * tileSize)
{
	setDimensions(width, height);

	_shape = sf::RectangleShape((sf::Vector2f)_size);
	_shape.setFillColor(color);

	int w = (_size.x > 1) ? _size.x / tileSize : 1;
	int h = (_size.y > 1) ? _size.y / tileSize : 1;

	for (int x = 0; x < w; ++x)
	{
		for (int y = 0; y < h; ++y)
		{
			Tile* tile = new Tile(tileSize, color);
			_tiles[x][y] = tile;
		}
	}
}


Cell::~Cell()
{
	destoryTiles();
}

void Cell::destoryTiles()
{
	for (int i = 0; i < _tiles.size(); ++i)
	{
		while (!_tiles[i].empty())
		{
			delete _tiles[i].back();
			_tiles[i].pop_back();
		}
	}
}

void Cell::setDimensions(int width, int height)
{
	_tiles.resize(width);

	for (int i = 0; i < width; ++i)
	{
		_tiles[i].resize(height, 0);
	}
}

Tile* Cell::getTile(int x, int y)
{
	if (x < _tiles.capacity())
	{
		if (y < _tiles[x].capacity())
		{
			return _tiles[x][y];
		}
	}

	return nullptr;
}

void Cell::render(sf::RenderWindow* window)
{
	int w = (_size.x > 1) ? _size.x / _tileSize : 1;
	int h = (_size.y > 1) ? _size.y / _tileSize : 1;

	_shape.setPosition((sf::Vector2f)_pos);
	window->draw(_shape);

	for (int y = 0; y < h; ++y)
	{
		for (int x = 0; x < w; ++x)
		{
			Tile* tile = getTile(x, y);
			if (tile != nullptr)
			{
				int posX = _pos.x + _tileSize*x;
				int posY = _pos.y + _tileSize*y;
				
				tile->render(posX, posY, window);
			}
		}
	}
}

sf::Vector2i Cell::getCenter() const
{
	return sf::Vector2i(_pos.x + (_size.x / 2), _pos.y + (_size.y / 2));
}

void Cell::setPosition(sf::Vector2f pos)
{
	_pos.x = pos.x - (_size.x / 2);
	_pos.y = pos.y - (_size.y / 2);
}

void Cell::setPosition(float x, float y)
{
	_pos.x = x - (_size.x / 2);
	_pos.y = y - (_size.y / 2);
}

bool Cell::intersects(const Cell& other) const
{
	return getLeft() < other.getRight() && getRight() > other.getLeft() &&
		getTop() < other.getBottom() && getBottom() > other.getTop();
}

int Cell::getLeft() const
{
	return _pos.x;
}

int Cell::getRight() const
{
	return _pos.x + _size.x;
}

int Cell::getTop() const
{
	return _pos.y;
}

int Cell::getBottom() const
{
	return _pos.y + _size.y;
}

int Cell::getWidth() const
{
	return _size.x;
}

int Cell::getHeight() const
{
	return _size.y;
}
