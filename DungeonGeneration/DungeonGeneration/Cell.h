#pragma once

#include <SFML\Graphics.hpp>

class Tile;

class Cell
{
public:
	Cell(int tileSize, int x, int y, int width, int height, sf::Color color = sf::Color::White);
	~Cell();

	void render(sf::RenderWindow* window);

	sf::Vector2i getCenter() const;
	void setPosition(sf::Vector2f pos);
	void setPosition(float x, float y);

	bool intersects(const Cell& other) const;

	int getLeft() const;
	int getRight() const;
	int getTop() const;
	int getBottom() const;

	int getWidth() const;
	int getHeight() const;

private:
	Tile* getTile(int x, int y);
	void setDimensions(int width, int height);
	void destoryTiles();

	sf::Vector2i _pos;
	sf::Vector2i _size;

	int _tileSize;
	sf::RectangleShape _shape;
	std::vector<std::vector<Tile*>> _tiles;
};

