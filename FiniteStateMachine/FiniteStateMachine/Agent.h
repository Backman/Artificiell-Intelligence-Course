#pragma once
#include "Machine.h"
#include <SFML\Window\Event.hpp>
#include <SFML\Window\Window.hpp>

class Agent
{
public:
	Agent();
	~Agent();

	void tick();
	void reason();

private:
	void handleInput();

	std::shared_ptr<Machine> _machine;

	bool _up, _down, _left, _right;
};

