#pragma once

#include <SFML\Graphics.hpp>

class Map;

class MapGenerator
{
public:
	MapGenerator();
	virtual ~MapGenerator();

	virtual Map* generate() = 0;
	virtual void render(sf::RenderWindow* rw) { }
};

