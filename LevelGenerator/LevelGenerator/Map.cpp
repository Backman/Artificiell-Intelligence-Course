#include "Map.h"
#include "TileGrid.h"
#include "Tile.h"
#include "Utility.h"

Map::Map()
{
}


Map::~Map()
{
	Utility::deletePointer<TileGrid>(_tileGrid);
}

void Map::initMap(int width, int height, int tileSize)
{
	_tileGrid = new TileGrid;
	_tileGrid->initGrid(width, height, tileSize);

	_width = width;
	_height = height;
	_tileSize = tileSize;
}

void Map::render(sf::RenderWindow* rw)
{
	Tile* tile;
	for (int y = 0; y < _height;  ++y)
	{
		for (int x = 0; x < _width; ++x)
		{
			tile = _tileGrid->getTile(x, y);

			if (tile != nullptr)
			{
				tile->render(x * _tileSize, y * _tileSize, rw);
			}
		}
	}
}
