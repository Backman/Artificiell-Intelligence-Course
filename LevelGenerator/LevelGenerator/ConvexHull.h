#pragma once

#include <SFML\Graphics.hpp>

struct Point
{
	Point()
	{ }

	Point(float x, float y) :
		x(x), y(y)
	{ }
	float x, y;

	bool operator<(const Point& p) const
	{
		return x < p.x || (x == p.x && y < p.y);
	}
};

class ConvexHull
{
	typedef std::vector<sf::Vector2f> Vertices;
public:
	static Vertices process(const Vertices& points);

private:
	static float cross(const Point& o, const Point& a, const Point& b);
};

