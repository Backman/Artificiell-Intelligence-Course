#include "Engine.h"
#include "TKGenerator.h"
#include "Graph.h"
#include "Utility.h"

#include <SFML\Graphics.hpp>
#include "Triangulate.h"
#include "ConvexHull.h"

int main()
{
	srand(time(NULL));
	Engine e(1280, 720, "Level Generator");
	
	TKGenerator gen;

	int cellCount = 80;
	int tileSize = 8;
	int minCellSize = 4;
	int maxCellSize = 10;
	int minCellThreshold = 5;
	int maxCellThrehsold = 7;

	gen.initGenerator(cellCount, tileSize, minCellSize, maxCellSize, minCellThreshold, maxCellThrehsold);
	e.setGenerator(&gen);
	e.run();
	
	//sf::RenderWindow window(sf::VideoMode(1024, 760), "Generator");

	//Graph<sf::Vector2f> g;

	//std::vector<sf::Vector2f> a;

	//for (int i = 0; i < 15; ++i)
	//{
	//	float x = Utility::randomFloatRange(300, 600);
	//	float y = Utility::randomFloatRange(300, 600);


	//	a.push_back(sf::Vector2f(x, y));

	//	g.addNode(new Node<sf::Vector2f>(sf::Vector2f(x, y)));
	//}

	//for (auto& n1 : g.getNodes())
	//{
	//	for (auto& n2 : g.getNodes())
	//	{
	//		if (n1 != n2)
	//		{
	//			g.addEdge(n1, n2);
	//		}
	//	}
	//}

	//std::vector<sf::Vector2f> hull = ConvexHull::process(a);

	//sf::VertexArray lines(sf::Lines, hull.size()*2);
	//for (int i = 1; i < hull.size()*2; ++i)
	//{
	//	sf::Vector2f point1 = hull[(i - 1) % hull.size()];
	//	sf::Vector2f point2 = hull[i % hull.size()];
	//	lines[i - 1] = sf::Vertex(sf::Vector2f(point1.x, point1.y), sf::Color::Yellow);
	//	lines[i] = sf::Vertex(sf::Vector2f(point2.x, point2.y), sf::Color::Yellow);
	//}

	//sf::VertexArray l(sf::Lines, a.size() * 2);
	//for (int i = 1; i < a.size() * 2; ++i)
	//{
	//	sf::Vector2f point1 = a[(i - 1) % a.size()];
	//	sf::Vector2f point2 = a[i % a.size()];
	//	l[i - 1] = sf::Vertex(sf::Vector2f(point1.x, point1.y), sf::Color::Yellow);
	//	l[i] = sf::Vertex(sf::Vector2f(point2.x, point2.y), sf::Color::Yellow);
	//}

	//// allocate an STL vector to hold the answer.

	//std::vector<sf::Vector2f> result;
	//std::string process = Triangulate::process(a, result) ? "True" : "False";

	////  Invoke the triangulator to triangulate this polygon.
	//std::cout << process << std::endl;

	//sf::VertexArray l2(sf::Lines, result.size() * 2);
	//for (int i = 1; i < result.size() * 2; ++i)
	//{
	//	sf::Vector2f point1 = result[(i - 1) % result.size()];
	//	sf::Vector2f point2 = result[i % result.size()];
	//	l2[i - 1] = sf::Vertex(sf::Vector2f(point1.x, point1.y), sf::Color::Yellow);
	//	l2[i] = sf::Vertex(sf::Vector2f(point2.x, point2.y), sf::Color::Yellow);
	//}


	//// print out the results.
	//int tcount = result.size() / 3;

	//std::vector<sf::VertexArray> tris;
	//for (int i = 0; i<tcount; i++)
	//{
	//	const sf::Vector2f &p1 = result[i * 3 + 0];
	//	const sf::Vector2f &p2 = result[i * 3 + 1];
	//	const sf::Vector2f &p3 = result[i * 3 + 2];

	//	tris.push_back(sf::VertexArray(sf::Lines, 3));
	//	tris[i][0] = p1;
	//	tris[i][1] = p2;
	//	tris[i][2] = p3;

	//	printf("Triangle %d => (%0.0f,%0.0f) (%0.0f,%0.0f) (%0.0f,%0.0f)\n", i + 1, p1.x, p1.y, p2.x, p2.y, p3.x, p3.y);
	//}

	//while (window.isOpen())
	//{
	//	sf::Event evt;
	//	while (window.pollEvent(evt))
	//	{
	//		if (evt.type == sf::Event::Closed ||evt.key.code == sf::Keyboard::Escape)
	//		{
	//			window.close();
	//		}
	//	}
	//	
	//	window.clear();
	//	//g.renderGraph(&window);
	//	//window.draw(lines);
	//	//window.draw(l);
	//	//window.draw(l2);

	//	/*for (auto& tri : tris)
	//	{
	//		window.draw(tri);
	//	}*/

	//	window.display();
	//}

	return 0;
}

//
//#include <Thor/Math/Triangulation.hpp>
//#include <Thor/Vectors/VectorAlgebra2D.hpp>
//#include <Aurora/Tools/ForEach.hpp>
//#include <SFML/Graphics.hpp>
//#include <iterator>
//#include <vector>
//
//// Typedefs for simplicity. You can also use a different type than sf::Vector2f if you fulfill some requirements (see doc)
//typedef std::vector<sf::Vector2f>					VertexContainer;
//typedef std::vector<thor::Triangle<sf::Vector2f>>	TriangleContainer;
//
//// Declarations of functions
//bool	removeVertex(const VertexContainer& vertices, sf::Vector2f position);
//bool	handleVertexClick(sf::Event::MouseButtonEvent mouseEvent, VertexContainer& vertices);
//bool	handleEvents(sf::RenderWindow& window, VertexContainer& vertices, TriangleContainer& triangles);
//
//int main()
//{
//	// Create render window
//	sf::RenderWindow window(sf::VideoMode(640, 480), "Thor Triangulation", sf::Style::Close);
//	window.setFramerateLimit(20);
//
//	// Create containers in which we store the vertices and the computed triangles
//	VertexContainer vertices;
//	TriangleContainer triangles;
//
//	//sf::Font font;
//	//if (!font.loadFromFile("Media/sansation.ttf"))
//	//	return 1;
//
//	//// Description with instructions
//	//sf::Text instructions(
//	//	"Left click to add point\n"
//	//	"Right click to remove point\n"
//	//	"C key to clear everything",
//	//	font, 14u);
//
//	// Main loop
//	for (;;)
//	{
//		// Event handling, possible quit
//		if (!handleEvents(window, vertices, triangles))
//			return 0;
//
//		// Clear background
//		window.clear();
//
//		// Draw all triangles
//		AURORA_FOREACH(const thor::Triangle<sf::Vector2f>& triangle, triangles)
//		{
//			sf::ConvexShape shape;
//			shape.setPointCount(3);
//			shape.setFillColor(sf::Color(0, 150, 255, 100));
//			shape.setOutlineColor(sf::Color::Blue);
//			shape.setOutlineThickness(1.f);
//
//			for (unsigned int i = 0; i < 3; ++i)
//				shape.setPoint(i, triangle[i]);
//
//			window.draw(shape);
//		}
//
//		// Draw all points
//		AURORA_FOREACH(sf::Vector2f vertex, vertices)
//		{
//			sf::CircleShape circle;
//			circle.setPosition(vertex - sf::Vector2f(6.f, 6.f));
//			circle.setRadius(6.f);
//			circle.setFillColor(sf::Color(255, 0, 150));
//
//			window.draw(circle);
//		}
//
//		// Draw description
//		//window.draw(instructions);
//
//		// Update screen
//		window.display();
//	}
//}
//
//// Finds out whether a vertex is near a given position.
//bool removeVertex(VertexContainer& vertices, sf::Vector2f position)
//{
//	// Find out which point was clicked on (tolerance radius is 6 pixels, as big as the circle's radius)
//	for (auto itr = vertices.begin(); itr != vertices.end(); ++itr)
//	{
//		if (thor::squaredLength(position - *itr) <= 36.f)
//		{
//			vertices.erase(itr);
//			return true;
//		}
//	}
//
//	return false;
//}
//
//// Handles clicks on a vertex. Returns true if a new triangulation is required.
//bool handleVertexClick(sf::Event::MouseButtonEvent mouseEvent, VertexContainer& vertices)
//{
//	sf::Vector2f clickPos(sf::Vector2i(mouseEvent.x, mouseEvent.y));
//
//	// Add point when left-clicking
//	if (mouseEvent.button == sf::Mouse::Left)
//	{
//		// Don't insert the same point twice
//		AURORA_FOREACH(sf::Vector2f vertex, vertices)
//		{
//			if (vertex == clickPos)
//				return false;
//		}
//
//		// If not contained yet, insert point
//		vertices.push_back(clickPos);
//		return true;
//	}
//
//	// Remove point when right-clicking
//	else if (mouseEvent.button == sf::Mouse::Right)
//	{
//		if (removeVertex(vertices, clickPos))
//			return true;
//	}
//
//	return false;
//}
//
//// Handles SFML events. Returns false if the application should be quit.
//bool handleEvents(sf::RenderWindow& window, VertexContainer& vertices, TriangleContainer& triangles)
//{
//	sf::Event event;
//	while (window.pollEvent(event))
//	{
//		switch (event.type)
//		{
//			// Mouse buttons: Add or remove vertex
//		case sf::Event::MouseButtonPressed:
//		{
//											  // Compute new triangulation for points if necessary
//											  if (handleVertexClick(event.mouseButton, vertices))
//											  {
//												  triangles.clear();
//												  thor::triangulate(vertices.begin(), vertices.end(), std::back_inserter(triangles));
//											  }
//		} break;
//
//		// Keys (C -> Clear, Escape -> Quit)
//		case sf::Event::KeyPressed:
//		{
//									  switch (event.key.code)
//									  {
//									  case sf::Keyboard::Escape:
//										  return false;
//
//									  case sf::Keyboard::C:
//										  vertices.clear();
//										  triangles.clear();
//									  }
//		} break;
//
//		// [X] clicked
//		case sf::Event::Closed:
//			return false;
//		}
//	}
//
//	return true;
//}