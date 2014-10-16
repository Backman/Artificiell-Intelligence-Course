#include "Level.h"
#include "Tile.h"

Level::Level()
{
}


Level::~Level()
{
}

int Level::getWidth() const
{
	return _width;
}

int Level::getHeight() const
{
	return _height;
}

void Level::setDimensions(int width, int height)
{
	_tileGrid.resize(width);

	for (int i = 0; i < width; ++i)
	{
		_tileGrid[i].resize(height, 0);
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

void Level::initLevel(int width, int height, ImageManager& imageManager)
{
	setDimensions(width, height);
	_width = width;
	_height = height;

	Tile* tile;
	for (int y = 0; y < height; ++y)
	{
		for (int x = 0; x < width; ++x)
		{
			if (y % 4 == 0)
			{
				tile = new Tile(imageManager[1]);
			}
			else
			{
				tile = new Tile(imageManager[0]);
			}

			addTile(x, y, tile);
		}
	}
}

void Level::render(sf::IntRect bounds, int tileSize, int camOffsetX, int camOffsetY, sf::RenderWindow* window)
{
	Tile* tile;
	for (int y = 0, tileY = bounds.top; y < bounds.height; ++y, ++tileY)
	{
		for (int x = 0, tileX = bounds.left; x < bounds.width; ++x, ++tileX)
		{
			tile = getTile(tileX, tileY);

			if (tile != nullptr)
			{
				tile->render((x * tileSize) - camOffsetX, (y * tileSize) - camOffsetY, window);
			}
		}
	}
}
