#pragma once

#include <SFML\Graphics.hpp>

class Cell
{
public:
	Cell(int x, int y, int width, int height, int idx);
	~Cell();

	void render(sf::RenderWindow* window);

	sf::Vector2f getPosition() const;
	void setPosition(sf::Vector2f pos);
	void setPosition(int x, int y);
	void setPosition(float x, float y);

	bool intersects(const Cell& other) const;

	sf::IntRect getRect() const;

	void setIndex(int index);

	bool operator==(const Cell& rhs) const;
	bool operator!=(const Cell& rhs) const;

private:
	sf::IntRect _rect;
	sf::RectangleShape _shape;
	int _index;
};

