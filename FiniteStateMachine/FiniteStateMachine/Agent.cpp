#include "Agent.h"


Agent::Agent() :
	_machine(*this, _walking)
{
}


Agent::~Agent()
{
}

void Agent::tick()
{
	_machine.tick();
}
