#include <iostream>

#include "StackFSM.h"
#include "Entity.h"

int main()
{
	Entity e;

	while (1)
	{
		e.tick();
	}

	std::cin.get();
	return 0;
}