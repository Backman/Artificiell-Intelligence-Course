#pragma once

#include <SFML\Graphics.hpp>

class Tile
{
public:
	Tile(sf::Image& image);
	~Tile();

	void render(int x, int y, sf::RenderWindow* window);

private:
	sf::Sprite _sprite;
	sf::Texture _texture;
};

