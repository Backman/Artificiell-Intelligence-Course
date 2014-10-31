#pragma once

#include <vector>
#include <SFML\Graphics.hpp>
#include "TileGrid.h";

enum class CellStatus
{
	AVAILABLE,
	UNAVAILABLE,
	FILL
};

enum class CellType
{
	DefaultRoom,
	CorridorRoom,
	Corridor
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

	bool intersects(TKCell& other) const;
	bool intersects(const sf::FloatRect& other) const;
	bool containsPoint(int x, int y) const;

	CellStatus getStatus() const;
	void setStatus(CellStatus s);

	CellType getType() const;
	void setType(CellType type);

private:
	int _tileSize;
	CellStatus _status;
	CellType _type;

	sf::Vector2f _pos;
	sf::Vector2f _size;
	TileGrid _tileGrid;
};

