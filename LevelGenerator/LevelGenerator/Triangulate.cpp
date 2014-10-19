#include "Triangulate.h"

static const float EPSILON = 0.0000000001f;

float Triangulate::area(const Vertices& contour)
{
	int n = contour.size();

	float a = 0.0f;

	for (int p = n - 1, q = 0; q < n; p = q++)
	{
		a += contour[p].x*contour[q].y - contour[q].x*contour[p].y;
	}

	return a *= 0.5f;
}

bool Triangulate::insideTriangle(float aX, float aY,
	float bX, float bY,
	float cX, float cY,
	float pX, float pY)
{
	float ax, ay;
	float bx, by;
	float cx, cy;
	float apx, apy;
	float bpx, bpy;
	float cpx, cpy;

	float cCrossAP, bCrossCP, aCrossBP;

	ax = cX - bX; ay = cY - bY;
	bx = aX - cX; by = aY - cY;
	cx = bX - aX; cy = bY - aY;
	apx = pX - aX; apy = pY - aY;
	bpx = pX - bX; bpy = pY - bY;
	cpx = pX - cX; cpy = pY - cY;

	aCrossBP = ax*bpy - ay*bpx;
	cCrossAP = cx*apy - cy*apx;
	bCrossCP = bx*cpy - by*cpx;

	return (aCrossBP >= 0.0f && bCrossCP >= 0.0f && cCrossAP >= 0.0f);
}

bool Triangulate::snip(const Vertices& contour, int u, int v, int w, int n, int* V)
{
	int p;
	float aX, aY, bY, bX, cY, cX, pX, pY;

	aX = contour[V[u]].x;
	aY = contour[V[u]].y;

	bX = contour[V[v]].x;
	bY = contour[V[v]].y;

	cX = contour[V[w]].x;
	cY = contour[V[w]].y;

	if (EPSILON > (((bX - aX) * (cY - aY)) - ((bY - aY) * (cX - aX))))
	{
		return false;
	}

	for (int i = 0; i < n; ++i)
	{
		if (i == u || i == v || i == w)
		{
			continue;
		}

		pX = contour[V[i]].x;
		pY = contour[V[i]].y;
		if (insideTriangle(aX, aY, bX, bY, cX, cY, pX, pY))
		{
			return false;
		}
	}

	return true;
}

bool Triangulate::process(const Vertices& contour, Vertices& result)
{
	int n = contour.size();

	if (n < 3)
	{
		return false;
	}

	int* V = new int[n];

	if (0.0f < area(contour))
	{
		for (int i = 0; i < n; ++i)
		{
			V[i] = i;
		}
	}
	else
	{
		for (int i = 0; i < n; ++i)
		{
			V[i] = (n - 1) - i;
		}
	}

	int nv = n;

	int count = 2 * nv;

	for (int m = 0, v = nv - 1; nv > 2;)
	{
		if (0 >= (count--))
		{
			return false;
		}

		int u = v;
		if (nv <= u)
		{
			u = 0;
		}

		v = u + 1;
		if (nv <= v)
		{
			v = 0;
		}
		int w = v + 1;
		if (nv <= w)
		{
			w = 0;
		}

		if (snip(contour, u, v, w, nv, V))
		{
			int a, b, c, s, t;

			a = V[u];
			b = V[v];
			c = V[w];

			result.push_back(contour[a]);
			result.push_back(contour[b]);
			result.push_back(contour[c]);

			++m;

			for (s = v, t = v + 1; t < nv; ++s, ++t)
			{
				V[s] = V[t];
				--nv;
			}

			count = 2 * nv;
		}
	}

	delete V;

	return true;
}
//
//#include <stdio.h>
//#include <stdlib.h>
//#include <string.h>
//#include <assert.h>
//
//#include "Triangulate.h"
//
//static const float EPSILON = 0.0000000001f;
//
//float Triangulate::Area(const Vector2dVector &contour)
//{
//
//	int n = contour.size();
//
//	float A = 0.0f;
//
//	for (int p = n - 1, q = 0; q<n; p = q++)
//	{
//		A += contour[p].x*contour[q].y - contour[q].x*contour[p].y;
//	}
//	return A*0.5f;
//}
//
///*
//InsideTriangle decides if a point P is Inside of the triangle
//defined by A, B, C.
//*/
//bool Triangulate::InsideTriangle(float Ax, float Ay,
//	float Bx, float By,
//	float Cx, float Cy,
//	float Px, float Py)
//
//{
//	float ax, ay, bx, by, cx, cy, apx, apy, bpx, bpy, cpx, cpy;
//	float cCROSSap, bCROSScp, aCROSSbp;
//
//	ax = Cx - Bx;  ay = Cy - By;
//	bx = Ax - Cx;  by = Ay - Cy;
//	cx = Bx - Ax;  cy = By - Ay;
//	apx = Px - Ax;  apy = Py - Ay;
//	bpx = Px - Bx;  bpy = Py - By;
//	cpx = Px - Cx;  cpy = Py - Cy;
//
//	aCROSSbp = ax*bpy - ay*bpx;
//	cCROSSap = cx*apy - cy*apx;
//	bCROSScp = bx*cpy - by*cpx;
//
//	return ((aCROSSbp >= 0.0f) && (bCROSScp >= 0.0f) && (cCROSSap >= 0.0f));
//};
//
//bool Triangulate::Snip(const Vector2dVector &contour, int u, int v, int w, int n, int *V)
//{
//	int p;
//	float Ax, Ay, Bx, By, Cx, Cy, Px, Py;
//
//	Ax = contour[V[u]].x;
//	Ay = contour[V[u]].y;
//
//	Bx = contour[V[v]].x;
//	By = contour[V[v]].y;
//
//	Cx = contour[V[w]].x;
//	Cy = contour[V[w]].y;
//
//	if (EPSILON > (((Bx - Ax)*(Cy - Ay)) - ((By - Ay)*(Cx - Ax)))) return false;
//
//	for (p = 0; p<n; p++)
//	{
//		if ((p == u) || (p == v) || (p == w)) continue;
//		Px = contour[V[p]].x;
//		Py = contour[V[p]].y;
//		if (InsideTriangle(Ax, Ay, Bx, By, Cx, Cy, Px, Py)) return false;
//	}
//
//	return true;
//}
//
//bool Triangulate::Process(const Vector2dVector &contour, Vector2dVector &result)
//{
//	/* allocate and initialize list of Vertices in polygon */
//
//	int n = contour.size();
//	if (n < 3) return false;
//
//	int *V = new int[n];
//
//	/* we want a counter-clockwise polygon in V */
//
//	if (0.0f < Area(contour))
//	for (int v = 0; v<n; v++) V[v] = v;
//	else
//	for (int v = 0; v<n; v++) V[v] = (n - 1) - v;
//
//	int nv = n;
//
//	/*  remove nv-2 Vertices, creating 1 triangle every time */
//	int count = 2 * nv;   /* error detection */
//
//	for (int m = 0, v = nv - 1; nv>2;)
//	{
//		/* if we loop, it is probably a non-simple polygon */
//		if (0 >= (count--))
//		{
//			//** Triangulate: ERROR - probable bad polygon!
//			return false;
//		}
//
//		/* three consecutive vertices in current polygon, <u,v,w> */
//		int u = v; if (nv <= u) u = 0;     /* previous */
//		v = u + 1; if (nv <= v) v = 0;     /* new v    */
//		int w = v + 1; if (nv <= w) w = 0;     /* next     */
//
//		if (Snip(contour, u, v, w, nv, V))
//		{
//			int a, b, c, s, t;
//
//			/* true names of the vertices */
//			a = V[u]; b = V[v]; c = V[w];
//
//			/* output Triangle */
//			result.push_back(contour[a]);
//			result.push_back(contour[b]);
//			result.push_back(contour[c]);
//
//			m++;
//
//			/* remove v from remaining polygon */
//			for (s = v, t = v + 1; t<nv; s++, t++) V[s] = V[t]; nv--;
//
//			/* resest error detection counter */
//			count = 2 * nv;
//		}
//	}
//
//
//
//	delete V;
//
//	return true;
//}