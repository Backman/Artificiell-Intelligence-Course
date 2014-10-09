#pragma once
#include "Machine.h"
#include "Walking.h"

class Agent
{
public:
	Agent();
	~Agent();

	void tick();

private:
	Machine<Agent> _machine;
	Walking _walking;
};

