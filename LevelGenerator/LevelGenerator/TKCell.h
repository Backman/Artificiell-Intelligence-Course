#pragma once

#include <vector>
#include <SFML\Graphics.hpp>

class TileGrid;

class TKCell
{
public:
	TKCell(int tileSize, int x, int y, int width, int height);
	~TKCell();

	void render(sf::RenderWindow* rw);

	sf::Vector2f getCenter() const;
	sf::Vector2f getPosition() const;

	void setPosition(sf::Vector2f newPos);
	void setPosition(float newX, float newY);

	int getLeft() const;
	int getRight() const;
	int getTop() const;
	int getBottom() const;

	bool intersects(TKCell& other) const;

private:
	int _rows, _cols;
	int _tileSize;
	sf::Color _color;

	sf::Vector2f _pos;
	sf::Vector2f _size;
	TileGrid* _tileGrid;
};
