#pragma once

#include <vector>
#include <SFML\Graphics.hpp>

class TileGrid;

class Map
{
public:
	Map();
	~Map();

	void initMap(int width, int height, int tileSize);

	void render(sf::RenderWindow* rw);

private:

	int _width, _height;
	int _tileSize;
	TileGrid* _tileGrid;
};

