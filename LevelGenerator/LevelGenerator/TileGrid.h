#pragma once

#include <SFML\Graphics.hpp>
#include <vector>

class Tile;

class TileGrid
{
public:
	TileGrid();
	~TileGrid();

	void initGrid(int x, int y, int tileSize);
	Tile* getTile(int x, int y) const;
	void addTile(int x, int y, Tile* tile);

	void render(sf::Vector2f pos, int tileSize, sf::RenderWindow* rw);

private:
	void setDimensions(int width, int height);
	void clearTiles();

	std::vector<std::vector<Tile*>> _grid;
};

