#pragma once

#include <vector>
#include <SFML\Graphics.hpp>
#include "TileGrid.h";

enum class Status
{
	AVAILABLE,
	UNAVAILABLE,
	FILL
};

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
	
	int getWidth() const;
	int getHeight() const;

	bool intersects(TKCell& other, sf::FloatRect& intersection) const;
	bool intersects(const sf::FloatRect& other) const;
	bool containsPoint(int x, int y) const;

	void setColor(sf::Color& color);
	void setTileOutlineColor(sf::Color& color);

	Status getStatus() const;
	void setStatus(Status s);

private:

	int _rows, _cols;
	int _tileSize;
	Status _status;
	sf::Color _color;

	sf::Vector2f _pos;
	sf::Vector2f _size;
	TileGrid _tileGrid;
};

