#pragma once

#include "Tile.h"

class Camera
{
public:
	Camera(int width, int height, float moveSpeed);
	~Camera();

	void move(int x, int y);
	void moveCenter(int x, int y);

	void goTo(int x, int y);
	void goToCenter(int x, int y);

	void tick();

	sf::Vector2i getPosition() const;

	sf::Vector2i getTileOffset(int tileSize) const;
	sf::IntRect getTileBounds(int tileSize) const;

private:
	sf::Vector2f _position;
	sf::Vector2f _target;
	sf::Vector2i _size;
	float _moveSpeed;
};

