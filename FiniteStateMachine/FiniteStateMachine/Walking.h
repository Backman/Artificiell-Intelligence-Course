#pragma once
#include "Agent.h"
#include "State.h"

class Walking : public State<Agent>
{
public:
	Walking();
	~Walking();


	virtual void tick(){ }
	virtual void reason(){ }
	virtual void enter(){ }
	virtual void exit(){ }
};

