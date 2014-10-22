#include "TileGrid.h"
#include "Tile.h"
#include "Utility.h"

TileGrid::TileGrid()
{
}

TileGrid::~TileGrid()
{
	clearTiles();
}

void TileGrid::clearTiles()
{
	if (_grid.size() > 1)
	{
		int k = 0;
	}

	while (!_grid.empty())
	{
		Utility::clearPointerVector<Tile>(&_grid.back());
		_grid.pop_back();
	}
}

void TileGrid::initGrid(int width, int height, int tileSize)
{
	setDimensions(width, height);

	Tile* tile;

	for (int y = 0; y < height; ++y)
	{
		for (int x = 0; x < width; ++x)
		{
			tile = new Tile(tileSize);

			addTile(x, y, tile);
		}
	}
}

void TileGrid::setDimensions(int width, int height)
{
	_grid.resize(width);

	for (int i = 0; i < width; ++i)
	{
		_grid[i].resize(height);
	}
}

void TileGrid::addTile(int x, int y, Tile* tile)
{
	if (x < _grid.size())
	{
		if (y < _grid[x].size())
		{
			_grid[x][y] = tile;
		}
	}
}

Tile* TileGrid::getTile(int x, int y) const
{
	if (x < _grid.capacity())
	{
		if (y < _grid[x].capacity())
		{
			return _grid[x][y];
		}
	}

	return nullptr;
}

TileType TileGrid::getTileType(int x, int y) const
{
	if (x < _grid.capacity())
	{
		if (y < _grid[x].capacity())
		{
			return _grid[x][y]->getTileType();
		}
	}

	return TileType::Empty;
}

void TileGrid::setTileType(int x, int y, TileType type)
{
	if (x < _grid.capacity())
	{
		if (y < _grid[x].capacity())
		{
			return _grid[x][y]->setTileType(type);
		}
	}
}

void TileGrid::render(sf::Vector2f pos, int tileSize, sf::RenderWindow* rw)
{
	for (int y = 0; y < _grid[0].size(); ++y)
	{
		for (int x = 0; x < _grid.size(); ++x)
		{
			Tile* tile = getTile(x, y);

			if (tile != nullptr)
			{
				int xPos = pos.x + tileSize*x;
				int yPos = pos.y + tileSize*y;

				tile->render(xPos, yPos, rw);
			}
		}
	}
}
