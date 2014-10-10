#pragma once

#include "State.h"


class Walking : public State
{
public:
	Walking();
	~Walking();


	virtual void tick()
	{
		if (!_isEntered)
		{
			std::cout << "Walking" << std::endl;
			_isEntered = true;
		}
	}
	virtual void enter()
	{
		std::cout << "Walking Enter" << std::endl;
	}
	virtual void exit()
	{
		_isEntered = false;
		std::cout << "Walking Exit" << std::endl;
	}
};

