#include "ConvexHull.h"

bool compare(const sf::Vector2f& a, const sf::Vector2f& b)
{
	return a.x < b.x || (a.x == b.x && a.y < b.y);
}

struct VectorComparer
{
	bool operator()(sf::Vector2f a, sf::Vector2f b) const
	{
		return a.x < b.x || (a.x == b.x && a.y < b.y);
	}

	/*bool operator()(const sf::Vector2f* a, const sf::Vector2f* b) const
	{
		return a->x < b->x || (a->x == b->x && a->y < b->y);
	}*/
} comparer;

ConvexHull::Vertices ConvexHull::process(const Vertices& v)
{
	int n = v.size();

	std::vector<Point> points(n);
	for (int i = 0; i < n; ++i)
	{
		points[i] = Point(v[i].x, v[i].y);
	}

	std::vector<Point> H(n * 2);

	std::sort(points.begin(), points.end());
	sf::Vector2f p(1.0f, 1.0f);
	sf::Vector2f asdsa = p;
	Vertices upper, lower;

	int k = 0;
	for (int i = 0; i < n; ++i)
	{
		while (k >= 2 && cross(H[k - 2], H[k - 1], points[i]) <= 0.0f)
		{
			--k;
		}

		H[k++] = points[i];
	}

	for (int i = n - 2, t = k + 1; i >= 0; --i)
	{
		while (k >= t && cross(H[k - 2], H[k - 1], points[i]) <= 0.0f)
		{
			--k;
		}

		H[k++] = points[i];
	}
	H.resize(k);

	Vertices ret(H.size());
	for (int i = 0; i < H.size(); ++i)
	{
		ret[i] = sf::Vector2f(H[i].x, H[i].y);
	}

	return ret;
}

float ConvexHull::cross(const Point& o, const Point& a, const Point& b)
{
	return (a.x - o.x) * (b.y - o.y) - (a.y - o.y) * (b.x - o.x);
}
