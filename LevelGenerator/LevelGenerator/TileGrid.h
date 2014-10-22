#pragma once

#include <SFML\Graphics.hpp>
#include <vector>

#include "Tile.h"


class TileGrid
{
public:
	TileGrid();
	~TileGrid();

	void initGrid(int x, int y, int tileSize);
	Tile* getTile(int x, int y) const;
	void addTile(int x, int y, Tile* tile);

	void render(sf::Vector2f pos, int tileSize, sf::RenderWindow* rw);

	TileType getTileType(int x, int y) const;
	void setTileType(int x, int y, TileType type);

private:
	void clearTiles();
	void setDimensions(int width, int height);

	std::vector<std::vector<Tile*>> _grid;
};

