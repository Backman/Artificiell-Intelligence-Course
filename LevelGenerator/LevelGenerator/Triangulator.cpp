#include "Triangulator.h"

std::vector<Triangle> Triangulator::bowyerWatson(std::vector<Point>& points)
{
	int xMin = std::numeric_limits<int>::max();
	int xMax = std::numeric_limits<int>::min();
	int yMin = std::numeric_limits<int>::max();
	int yMax = std::numeric_limits<int>::min();

	for (auto& p : points)
	{
		float x = p.x;
		float y = p.y;
		if (x < xMin)
		{
			xMin = x;
		}
		if (x > xMax)
		{
			xMax = x;
		}
		if (y < yMin)
		{
			yMin = y;
		}
		if (y > yMax)
		{
			yMax = y;
		}
	}
	
	std::vector<Triangle> triangles;

	Triangle superTriangle;
	superTriangle.a = sf::Vector2f(xMin + ((xMax - xMin) / 2), yMin * 10.0f);
	superTriangle.b = sf::Vector2f(xMin * -10.0f, yMax * 10.0f);
	superTriangle.c = sf::Vector2f(xMax * 10.0f, yMax * 10.0f);

	triangles.push_back(superTriangle);

	for (auto& p : points)
	{
		std::vector<Triangle> badTriangles;
		for (auto& t : triangles)
		{
			float r;
			Point center;
			Circumcircle(t.a, t.b, t.c, center, r);

			if ((p.x - center.x) * (p.x - center.x) + (p.y - center.y) * (p.y - center.y) < r * r)
			{
				badTriangles.push_back(t);
			}
		}

		for (auto& t1 : badTriangles)
		{
			for (auto& t2 : badTriangles)
			{
				
			}
		}
	}

	return triangles;
}


bool Triangulator::Circumcircle(const Point& p0, const Point& p1, const Point& p2, Point& center, float& radius)
{
	float dA, dB, dC, aux1, aux2, div;

	dA = p0.x * p0.x + p0.y * p0.y;
	dB = p1.x * p1.x + p1.y * p1.y;
	dC = p2.x * p2.x + p2.y * p2.y;

	aux1 = (dA*(p2.y - p1.y) + dB*(p0.y - p2.y) + dC*(p1.y - p0.y));
	aux2 = -(dA*(p2.x - p1.x) + dB*(p0.x - p2.x) + dC*(p1.x - p0.x));
	div = (2 * (p0.x*(p2.y - p1.y) + p1.x*(p0.y - p2.y) + p2.x*(p1.y - p0.y)));

	if (div == 0)
	{
		return false;
	}

	center.x = aux1 / div;
	center.y = aux2 / div;

	radius = sqrt((center.x - p0.x)*(center.x - p0.x) + (center.y - p0.y)*(center.y - p0.y));

	return true;
}