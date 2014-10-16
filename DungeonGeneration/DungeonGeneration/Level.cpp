#include "Level.h"
#include "Tile.h"

//Level::Level(int width, int height, int tileSize) :
//	_width(width), _height(height), _tileSize(tileSize)
//{
//}

Level::Level()
{
}


Level::~Level()
{
}

void Level::setDimensions(int width, int height)
{
	_tileGrid.resize(width);

	for (int i = 0; i < width; ++i)
	{
		_tileGrid[i].resize(height, 0);
	}
}

void Level::init(int width, int height, int tileSize)
{
	setDimensions(width, height);
	_width = width;
	_height = height;
	_tileSize = tileSize;
	Tile* tile;

	int w = (width > tileSize) ? width / tileSize : 1;
	int h = (height > tileSize) ? height / tileSize : 1;

	for (int y = 0; y < h; ++y)
	{
		for (int x = 0; x < w; ++x)
		{
			tile = new Tile(tileSize);
			addTile(x, y, tile);
		}
	}
}

void Level::addTile(int x, int y, Tile* tile)
{
	_tileGrid[x][y] = tile;
}

Tile* Level::getTile(int x, int y) const
{
	if (x < _tileGrid.capacity())
	{
		if (y < _tileGrid[x].capacity())
		{
			return _tileGrid[x][y];
		}
	}

	return nullptr;
}

void Level::render(sf::RenderWindow* window)
{
	Tile* tile;

	int w = (_width > _tileSize) ? _width / _tileSize : 1;
	int h = (_height > _tileSize) ? _height / _tileSize : 1;

	for (int y = 0; y < h; ++y)
	{
		for (int x = 0; x < w; ++x)
		{
			tile = getTile(x, y);

			if (tile != nullptr)
			{
				tile->render(x * _tileSize, y * _tileSize, window);
			}
		}
	}
}

