#pragma once

#include <SFML\Graphics.hpp>

class Tile
{
public:
	Tile(int size, sf::Color color = sf::Color::White);
	~Tile();

	void render(int x, int y, sf::RenderWindow* window);

private:
	int _width, _height;
	sf::RectangleShape _shape;
};