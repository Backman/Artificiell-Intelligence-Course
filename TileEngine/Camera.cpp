#include "Camera.h"


Camera::Camera(int width, int height, float moveSpeed) : 
	_size(sf::Vector2i(width, height)), _moveSpeed(moveSpeed)
{
	if (_moveSpeed < 0.0f)
	{
		_moveSpeed = 0.0f;
	}
	if (_moveSpeed > 0.0f)
	{
		_moveSpeed = 1.0f;
	}
}


Camera::~Camera()
{
}

void Camera::move(int x, int y)
{
	_position = sf::Vector2f((float)x, (float)y);
	_target = sf::Vector2f((float)x, (float)y);
}

void Camera::moveCenter(int x, int y)
{
	x = x - (_size.x / 2);
	y = y - (_size.y / 2);

	_position = sf::Vector2f((float)x, (float)y);
	_target = sf::Vector2f((float)x, (float)y);
}

void Camera::goTo(int x, int y)
{
	_target = sf::Vector2f((float)x, (float)y);
}

void Camera::goToCenter(int x, int y)
{
	x = x - (_size.x / 2);
	y = y - (_size.y / 2);

	_target = sf::Vector2f((float)x, (float)y);
}

void Camera::tick()
{
	float dx, dy, dist;
	float vx, vy, v;

	dx = _target.x - _position.x;
	dy = _target.y - _position.y;

	if ((dx*dx + dy*dy) <= 1.0f)
	{
		_position = _target;
	}
	else
	{
		dist = sqrt(dx*dx + dy*dy);

		v = (dist * _moveSpeed) / 60.0f;

		if (v < 1.0f)
		{
			v = 1.0f;
		}

		vx = dx * (v / dist);
		vy = dy * (v / dist);

		_position.x += vx;
		_position.y += vy;
	}
}

sf::Vector2i Camera::getPosition() const
{
	return sf::Vector2i((int)_position.x, (int)_position.y);
}

sf::Vector2i Camera::getTileOffset(int tileSize) const
{
	return sf::Vector2i((int)(_position.x) % tileSize, (int)(_position.y) % tileSize);
}

sf::IntRect Camera::getTileBounds(int tileSize) const
{
	int x = (int)(_position.x / tileSize);
	int y = (int)(_position.y / tileSize);

	int width = _size.x / tileSize + 2;
	int height = _size.y / tileSize + 2;

	if (x % tileSize != 0)
	{
		++width;
	}
	if (y % tileSize != 0)
	{
		++height;
	}

	return sf::IntRect(x, y, width, height);
}

