#pragma once

#include <vector>
#include "ImageManager.h"

class Tile;

class Level
{
public:
	Level();
	~Level();

	void initLevel(int width, int height, ImageManager& imageManager);

	void render(sf::IntRect bounds, int tileSize, int camOffsetX, int camOffsetY, sf::RenderWindow* window);

	void addTile(int x, int y, Tile* tile);
	Tile* getTile(int x, int y) const;

	int getWidth() const;
	int getHeight() const;

private:
	void setDimensions(int width, int height);


	typedef std::vector<std::vector<Tile*>> TileGrid;
	TileGrid _tileGrid;

	int _width, _height;
};

