#pragma once

#include "StackFSM.h"

class Entity
{
public:
	Entity();
	~Entity();
	int count = 0;

	void flee()
	{
		std::cout << "Fleeing from cat..." << std::endl;
		if (!closeToRat)
		{
			_machine.popState();
		}
	}

	void goHome()
	{
		std::cout << "Going home..." << std::endl;
		if (isHome)
		{
			_machine.popState();
			_machine.pushState(findCheeseState);
		}

		if (closeToRat)
		{
			_machine.pushState(fleeState);
		}
	}

	void findCheese()
	{
		std::cout << "Looking for cheese..." << std::endl;
		if (hasCheese)
		{
			_machine.popState();
			_machine.pushState(goHomeState);
		}

		if (closeToRat)
		{
			_machine.pushState(fleeState);
		}
	}

	void tick()
	{
		_machine.tick();


	}

private:
	bool increment;
	bool closeToRat;
	bool hasCheese;
	bool isHome;

	StackFSM _machine;

	State findCheeseState, fleeState, goHomeState;
};

