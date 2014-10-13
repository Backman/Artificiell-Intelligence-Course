#include <iostream>
#include "BehaviorTree.h"

#include "BTSelector.h"
#include "BTMaxTimes.h"

int main()
{
	BehaviorTree t;

	BTSelector* s1 = new BTSelector(nullptr);
	BTSelector* s2 = new BTSelector(s1);
	s1->addChild(s2);

	BTMaxTimes* maxTimes = new BTMaxTimes(s2, 10);

	s2->addChild(maxTimes);
	
	t.init(s1);

	do
	{

	} while (t.tick() != Status::SUCCEDED);

	std::cout << "Press enter to exit...";
	std::cin.get();
	return 0;
}