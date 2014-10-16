#pragma once

#include <SFML\Graphics.hpp>

class Tile
{
public:
	Tile(int tileSize, sf::Color color = sf::Color::White);
	~Tile();

	void render(int x, int y, sf::RenderWindow* rw);

	void setColor(sf::Color color);

private:
	int _tileSize;
	sf::RectangleShape _shape;
	sf::Color _color;
	sf::Vector2i _pos, _size;
};

