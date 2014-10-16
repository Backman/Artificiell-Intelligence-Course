#include "Engine.h"
#include "TKGenerator.h"

int main()
{
	srand(time(NULL));
	Engine e(1024, 760, "Level Generator");
	
	TKGenerator gen;
	gen.initGenerator(50, 10, 4, 10);

	e.run(&gen);
	
	return 0;
}