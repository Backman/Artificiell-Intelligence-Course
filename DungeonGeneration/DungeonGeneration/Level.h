#pragma once

#include <SFML\Graphics.hpp>
#include <vector>

class Tile;

class Level
{
public:
	Level();
	~Level();

	void init(int width, int height, int tileSize);

	void render(sf::RenderWindow* window);

	void addTile(int x, int y, Tile* tile);
	Tile* getTile(int x, int y) const;

private:
	void setDimensions(int width, int height);

	std::vector<std::vector<Tile*>> _tileGrid;
	int _width, _height;
	int _tileSize;
};

