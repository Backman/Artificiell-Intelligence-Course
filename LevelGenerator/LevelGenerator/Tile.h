#pragma once

#include <SFML\Graphics.hpp>

enum class TileType
{
	StoneFloor,
	DirtFloor,
	Wall,
	Empty
};

class Tile
{
public:
	Tile(int tileSize, TileType tileType = TileType::StoneFloor);
	~Tile();

	void render(int x, int y, sf::RenderWindow* rw);

	TileType getTileType() const;
	void setTileType(TileType type);

private:
	int _tileSize;

	TileType _type;
};

