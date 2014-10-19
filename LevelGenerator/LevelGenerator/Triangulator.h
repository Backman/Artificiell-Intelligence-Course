#pragma once

#include "Assert.h"
#include <SFML\Graphics.hpp>


typedef sf::Vector2f Point;

struct Edge
{
	Point* p;
	Point* q;

	Edge(Point& p1, Point& p2) :
		p(&p1), q(&p2)
	{ 
		if (p1.y > p2.y)
		{
			q = &p1;
			p = &p2;
		}
		else if (p1.y == p2.y)
		{
			if (p1.x > p2.x)
			{
				q = &p1;
				p = &p2;
			}
			else if (p1.x == p2.x)
			{
				ASSERT(false);
			}
		}

	}
};

struct Triangle
{
	Point a, b, c;
};



class Triangulator
{
public:
	static std::vector<Triangle> bowyerWatson(std::vector<Point>& points);

	static bool Circumcircle(const Point& p0, const Point& p1, const Point& p2, Point& center, float& radius);
};