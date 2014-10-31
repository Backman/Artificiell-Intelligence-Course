#include "Engine.h"
#include "TKGenerator.h"
#include "Graph.h"
#include "Utility.h"


int main()
{
	srand(time(NULL));
	Engine e(1000, 1000, "Level Generator");
	
	TKGenerator gen;

	int cellCount = 150;
	int tileSize = 6;
	int minCellSize = 4;
	int maxCellSize = 12;
	int minCellThreshold = 5;
	int maxCellThrehsold = 9;

	gen.initGenerator(cellCount, tileSize, minCellSize, maxCellSize, minCellThreshold, maxCellThrehsold);
	e.setGenerator(&gen);
	e.run();

	return 0;
}