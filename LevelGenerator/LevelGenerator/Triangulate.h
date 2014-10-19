#pragma once

#include <SFML\Graphics.hpp>
#include <vector>

enum class TriangulationMethod
{
	FLIPCODE
};

class Triangulate
{
	typedef std::vector<sf::Vector2f> Vertices;
public:

	static bool process(const Vertices& contour, Vertices& result);

	static float area(const Vertices& contour);

	static bool insideTriangle(float aX, float ay,
		float bX, float bY,
		float cX, float cY,
		float pX, float pY);

private:
	static bool snip(const Vertices& contour, int u, int v, int w, int n, int* V);
};
//
//// Typedef an STL vector of vertices which are used to represent
//// a polygon/contour and a series of triangles.
//typedef std::vector< sf::Vector2f > Vector2dVector;
//
//
//class Triangulate
//{
//public:
//
//	// triangulate a contour/polygon, places results in STL vector
//	// as series of triangles.
//	static bool Process(const Vector2dVector &contour,
//		Vector2dVector &result);
//
//	// compute area of a contour/polygon
//	static float Area(const Vector2dVector &contour);
//
//	// decide if point Px/Py is inside triangle defined by
//	// (Ax,Ay) (Bx,By) (Cx,Cy)
//	static bool InsideTriangle(float Ax, float Ay,
//		float Bx, float By,
//		float Cx, float Cy,
//		float Px, float Py);
//
//
//private:
//	static bool Snip(const Vector2dVector &contour, int u, int v, int w, int n, int *V);
//
//};