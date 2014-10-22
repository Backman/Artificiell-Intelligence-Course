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
	Tile(int tileSize, TileType tileType = TileType::StoneFloor, sf::Color color = sf::Color::White);
	~Tile();

	void render(int x, int y, sf::RenderWindow* rw);

	void setOutlineColor(sf::Color color);

	TileType getTileType() const;
	void setTileType(TileType type);

private:
	int _tileSize;
	sf::RectangleShape _shape;
	sf::Color _color;
	sf::Vector2i _pos, _size;

	TileType _type;
};

