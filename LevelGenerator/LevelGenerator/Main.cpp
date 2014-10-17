#include "Engine.h"
#include "TKGenerator.h"

int main()
{
	srand(time(NULL));
	Engine e(1024, 760, "Level Generator");
	
	TKGenerator gen;

	int cellCount = 50;
	int tileSize = 10;
	int minCellSize = 4;
	int maxCellSize = 10;

	gen.initGenerator(cellCount, tileSize, minCellSize, maxCellSize);

	e.run(&gen);
	
	return 0;
}