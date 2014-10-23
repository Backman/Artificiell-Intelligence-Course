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
	int maxCellSize = 12;
	int minCellThreshold = 5;
	int maxCellThrehsold = 7;

	gen.initGenerator(cellCount, tileSize, minCellSize, maxCellSize, minCellThreshold, maxCellThrehsold);
	e.setGenerator(&gen);
	e.run();

	return 0;
}