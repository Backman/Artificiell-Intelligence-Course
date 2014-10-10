#pragma once
#include "State.h"

class Running : public State
{
public:
	Running();
	~Running();

	virtual void tick()
	{ 
		if (!_isEntered)
		{
			std::cout << "Running" << std::endl;
			_isEntered = true;
		}
	}
	virtual void enter()
	{ 
		std::cout << "Running Enter" << std::endl; 
	}
	virtual void exit()
	{ 
		_isEntered = false;
		std::cout << "Running Exit" << std::endl; 
	}
};

